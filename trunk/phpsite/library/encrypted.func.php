<?php

if(!defined('IN_LIVES_CUBE'))
{
	exit("Access Denied");
}

require_once './library/hardwareaux.func.php';

/*
 * 注意，以下用到的EncryptedPhoneNumber, UserEntry, UpdateEntry等
 * 全部是用C语言定义的struct，具体见data.h。
 */

/**
 * 用户注册
 * @param $encryptedPhoneNumber 加上PADDING并用服务器公钥做加密后得到的EncryptedPhoneNumber
 * @param $userEntry 用随即密钥对称加密，然后用服务器公钥做加密对称密钥后得到的UserEntry
 * @return 一个bool表示成功或者失败
 */
function encryptedRegister($encryptedPhoneNumber, $userEntry){
	include './include/hardwarecfg.inc.php';
	$lockfp = acquireLock($lockFileName);
	$res = false;
	
	do{
		if (strlen($encryptedPhoneNumber) != SIZE_EncryptedPhoneNumber ||
			strlen($userEntry) != SIZE_UserEntry)
		{
			echo "Bad input for encryptedRegister\n";
			break;
		}
		
		$temp = getCurrentCounter();
		if ($temp[1] != 0)
			break;
		$currentCounter = $temp[0];
		$counterNeeded = 2;
		if ($currentCounter+$counterNeeded >= MAX_COUNTER){
			updateWholeTable(false);
			continue;
		}
				
		$temp = getIndex($encryptedPhoneNumber);
		if ($temp[1] != 0)
			break;
		$index = $temp[0];
		
		global $db;
		$temp = getUserEntryFromDataBase($index);
		$hasOld = $temp[0];
		$oldUserEntry = $temp[1];
		if ($hasOld){
			$hasOldBin = pack("C", 1);
		} else {
			$oldUserEntry = $userEntry;
			$hasOldBin = pack("C", 0);
		}
			
		$exchangeFile = fopen($exchangeFileName, "wb");
		fwrite($exchangeFile, $hasOldBin, 1);
		assert(strlen($oldUserEntry) == SIZE_UserEntry);
		fwrite($exchangeFile, $oldUserEntry, strlen($oldUserEntry));
		assert(strlen($userEntry) == SIZE_UserEntry);
		fwrite($exchangeFile, $userEntry, strlen($userEntry));
		fclose($exchangeFile);
		
		$cmd = "$callerName $safeCoreName makeNewUserEntry $exchangeFileName";
		exec($cmd, $stdout, $status);
		
		echo "testing\n";
		printStdout($stdout);
		
		if ($status != 0){
			if ($status == 1)
				echo "bad command: $cmd\n";
			printStdout($stdout);
			break;
		}
		$exchangeFile = fopen($exchangeFileName, "rb");
		fread($exchangeFile, $newUserEntry, SIZE_UserEntry);
		fclose($exchangeFile);
		
		$db->query("replace into lives3_encryptedinfo values(?, ?)", "bb", $index, $newUserEntry);
		$res = true;
		break;
	} while (true);
	
	releaseLock($lockfp);
	return $res;
}

/**
 * 用户更新自己的信息
 * @param $encryptedPhoneNumber 加上PADDING并用服务器公钥做加密后得到的EncryptedPhoneNumber
 * @param $userEntry 用随即密钥对称加密，然后用服务器公钥做加密对称密钥后得到的UserEntry，
 * 			并且用户会用原来的私钥对加密后的对称密钥做签名。
 * @return 一个bool表示成功或者失败
 */
function encryptedUpdate($encryptedPhoneNumber, $userEntry){
	include './include/hardwarecfg.inc.php';
	$lockfp = acquireLock($lockFileName);
	$res = false;
	
	do{
		if (strlen($encryptedPhoneNumber) != SIZE_EncryptedPhoneNumber ||
			strlen($userEntry) != SIZE_UserEntry)
		{
			echo "Bad input for encryptedRegister\n";
			break;
		}
		
				$temp = getCurrentCounter();
		if ($temp[1] != 0)
			break;
		$currentCounter = $temp[0];
		$counterNeeded = 2;
		if ($currentCounter+$counterNeeded >= MAX_COUNTER){
			updateWholeTable(false);
			continue;
		}
		
		$temp = getIndex($encryptedPhoneNumber);
		if ($temp[1] != 0)
			break;
		$index = $temp[0];
		
		global $db;
		$temp = getUserEntryFromDataBase($index);
		$hasOld = $temp[0];
		$oldUserEntry = $temp[1];
		if (!$hasOld)
			break;
			
		$exchangeFile = fopen($exchangeFileName, "wb");
		assert(strlen($oldUserEntry) == SIZE_UserEntry);
		fwrite($exchangeFile, $oldUserEntry, strlen($oldUserEntry));
		assert(strlen($userEntry) == SIZE_UserEntry);
		fwrite($exchangeFile, $userEntry, strlen($userEntry));
		fclose($exchangeFile);

		$cmd = "$callerName $safeCoreName makeUpdateUserEntry $exchangeFileName";
		exec($cmd, $stdout, $status);
		if ($status != 0){
			if ($status == 1)
				echo "bad command: $cmd\n";
			printStdout($stdout);
			break;
		}
		$exchangeFile = fopen($exchangeFileName, "rb");
		fread($exchangeFile, $newUserEntry, SIZE_UserEntry);
		fclose($exchangeFile);
		
		$db->query("replace into lives3_encryptedinfo values(?, ?)", "bb", $index, $newUserEntry);
		$res = true;
		break;
	} while (true);
	
	releaseLock($lockfp);
	return $res;
}

/**
 * 用户获取自己联系人的最新信息
 * @param $encryptedPhoneNumber 加上PADDING并用服务器公钥做加密后得到的EncryptedPhoneNumber
 * @param $updateRequest EncryptedPhoneNumber数组，其中包含了需要获得哪些联系人的最新信息（加密过的）
 * @param $threshold 用户最后更新的时间，用于做增量更新。
 * @return 获得的UpdateEntry数组，包含了更新过的联系人信息（已经做了时间增量处理）
 */
function getEncryptedUpdatePackage($encryptedPhoneNumber, array $updateRequest, $threshold){
	include './include/hardwarecfg.inc.php';
	$lockfp = acquireLock($lockFileName);
	$res = array();
	
	do{
		if (strlen($encryptedPhoneNumber) != SIZE_EncryptedPhoneNumber || strlen($threshold) != Size_TimeType)
		{
			echo "Bad input for encryptedRegister\n";
			break;
		}
	
		$temp = getCurrentCounter();
		if ($temp[1] != 0)
			break;
		$currentCounter = $temp[0];
		$counterNeeded = 2+count($updateRequest)*2;
		if ($currentCounter+$counterNeeded >= MAX_COUNTER){
			updateWholeTable(false);
			continue;
		}
		
		$temp = getIndex($encryptedPhoneNumber);
		if ($temp[1] != 0)
			break;
		$operateIndex = $temp[0];
		$temp = getUserEntryFromDataBase($operateIndex);
		if (!$temp[0])
			break;
		else
			$operateUser = $temp[1];
		
		$binFalse = pack("C", 0);
		for($i=0; $i<count($updateRequest); $i++){
			$temp = getIndex($updateRequest[i]);
			if (strlen($temp) != SIZE_EncryptedPhoneNumber)
				continue;
			if ($temp[1] != 0)
				continue;
			$targetIndex = $temp[0];
			$temp = getUserEntryFromDataBase($targetIndex);
			if (!$temp[0])
				continue;
			$targetUser = $temp[1];
			
			$exchangeFile = fopen($exchangeFileName, "wb");
			assert(strlen($operateUser) == SIZE_UserEntry);
			assert(strlen($targetUser) == SIZE_UserEntry);
			assert(strlen($threshold) == SIZE_TimeType);
			fwrite($exchangeFile, $operateUser, strlen($operateUser));
			fwrite($exchangeFile, $targetUser, strlen($targetUser));
			fwrite($exchangeFile, $threshold, strlen($threshold));
			fclose($exchangeFile);
			$cmd = "$callerName $safeCoreName getUpdateEntry $exchangeFileName";
			exec($cmd, $stdout, $status);
			if ($status != 0){
				if ($status == 1)
					echo "bad command: $cmd\n";
				printStdout($stdout);
				continue;
			}
			$exchangeFile = fopen($exchangeFileName, "rb");
			fread($exchangeFile, $updateEntry, SIZE_UpdateEntry);
			fread($exchangeFile, $binUpdated, 1);
			if (strcmp($binFalse, $binUpdated) != 0)
				$res[] = $updateEntry;
			fclose($exchangeFile);
		}
		break;
	} while (true);
	
	releaseLock($lockfp);
	return $res;
}

function updateWholeTable($needlock = true){
	include './include/hardwarecfg.inc.php';
	if ($needlock)
		$lockfp = acquireLock($lockFileName);
	
	$nextTableName = "lives3_next_encryptedinfo";
	
	global $db;
	$db->query("delete * from $nextTableName");
	$result = $db->query("select * from lives3_encryptedinfo");
	$n = $db->num_rows($result);
	for($i=0; $i<(int)$n/2; $i++){
		$row = array();
		$row[] = $db->fetch_assoc($result);
		$row[] = $db->fetch_assoc($result);
		$index = array();
		$entry = array();
		$exchangeFile = fopen($exchangeFileName, "wb");
		for($j=0; $j<2; $j++){
			$index[$j] = $row[$j]["index"];
			$entry[$j] = $row[$j]["userEntry"]; 
			assert(strlen($index[$j]) == SIZE_Index);
			assert(strlen($entry[$j]) == SIZE_UserEntry);
			fwrite($exchangeFile, $index[$j], strlen($index[$j]));
			fwrite($exchangeFile, $entry[$j], strlen($entry[$j]));
		}
		fclose($exchangeFile);
		exec("$callerName $safeCoreName refreshEntries $exchangeFileName", $stdout, $status);
		assert($status == 0);
		$exchangeFile = fopen($exchangeFileName, "rb");
		for($j=0; $j<2; $j++){
			fread($exchangeFile, $index[$j], SIZE_Index);
			fread($exchangeFile, $entry[$j], SIZE_UserEntry);
			replaceUserEntry($nextTableName, $index[$j], $entry[$j]);
		}
		fclose($exchangeFile);
	}
	
	if (n%2 == 1){
		$row = $db->fetch_assoc($result);
		$index = $row["index"];
		$entry = $row["userEntry"];
		assert(strlen($index) == SIZE_Index);
		assert(strlen($entry) == SIZE_UserEntry);
		$exchangeFile = fopen($exchangeFileName, "wb");
		fwrite($exchangeFile, $index, strlen($index));
		fwrite($exchangeFile, $entry, strlen($entry));
		fclose($exchangeFile);
		exec("$callerName $safeCoreName refreshEntry $exchangeFileName", $stdout, $status);
		assert($status == 0);
		$exchangeFile = fopen($exchangeFileName, "rb");
		fread($exchangeFile, $index, SIZE_Index);
		fread($exchangeFile, $entry, SIZE_UserEntry);
		replaceUserEntry($nextTableName, $index, $entry);
		fclose($exchangeFile);
	}
	
	$oldTableName = "lives3_encryptedinfo";
	$tempTableName = "lives3_temp_encryptedinfo";
	rename($oldTableName, $tempTableName);
	rename($nextTableName, $oldTableName);
	rename($tempTableName, $nextTableName);
	
	if ($needlock)
		releaseLock($lockfp);
}

?>
