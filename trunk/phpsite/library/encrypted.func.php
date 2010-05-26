<?php

if(!defined('IN_LIVES_CUBE'))
{
	exit("Access Denied");
}

require_once './library/hardwareaux.func.php';

/*
 * 注意，以下用到的EncryptedPhoneNumber, UserEntry, UpdateRequest, UpdatePackage
 * 全部是用C语言定义的struct，具体见data.h。
 * 
 * 不知道如何让php中也可以处理这种纯2进制数据？
 */

/**
 * 用户注册
 * @param $encryptedPhoneNumber 加上PADDING并用服务器公钥做加密后得到的EncryptedPhoneNumber
 * @param $userEntry 用服务器公钥做加密后得到的UserEntry
 * @return 一个bool表示成功或者失败
 */
function encryptedRegister($encryptedPhoneNumber, $userEntry){
	include './include/hardwarecfg.inc.php';
	$lockfp = acquireLock($lockFileName);
	$res = false;
	
	do{
		$currentCounter = getCurrentCounter();
		$counterNeeded = 2;
		if ($currentCounter+$counterNeeded >= MAX_COUNTER)//TODO SHIFT TO NEXT KEY
			break;
		
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
		fwrite($exchangeFile, $oldUserEntry, strlen($oldUserEntry));
		fwrite($exchangeFile, $userEntry, strlen($userEntry));
		fclose($exchangeFile);
		
		system("$callerName $safeCoreName makeNewUserEntry $exchangeFileName", $status);
		if ($status != 0)
			break;
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
 * @param $userEntry 先用服务器公钥做加密，再用用户自己的私钥加密后得到的UserEntry
 * @return 一个bool表示成功或者失败
 */
function encryptedUpdate($encryptedPhoneNumber, $userEntry){
	include './include/hardwarecfg.inc.php';
	$lockfp = acquireLock($lockFileName);
	$res = false;
	
	do{
		$currentCounter = getCurrentCounter();
		$counterNeeded = 2;
		if ($currentCounter+$counterNeeded >= MAX_COUNTER)//TODO SHIFT TO NEXT KEY
			break;
		
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
		fwrite($exchangeFile, $oldUserEntry, strlen($oldUserEntry));
		fwrite($exchangeFile, $userEntry, strlen($userEntry));
		fclose($exchangeFile);
		
		system("$callerName $safeCoreName makeUpdateUserEntry $exchangeFileName", $status);
		if ($status != 0)
			break;
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
 * @param $updateRequest 普通的UpdateRequest，其中包含了需要获得哪些联系人的最新信息（加密过的）
 * @param $threshold 用户最后更新的时间，用于做增量更新。
 * @return 获得的UpdatePackage，包含了更新过的联系人信息（已经做了时间增量处理）
 */
function getEncryptedUpdatePackage($encryptedPhoneNumber, array $updateRequest, $threshold){
	include './include/hardwarecfg.inc.php';
	$lockfp = acquireLock($lockFileName);
	$res = array();
	
	do{
		$currentCounter = getCurrentCounter();
		$counterNeeded = 1+count($updateRequest)*2;
		if ($currentCounter+$counterNeeded >= MAX_COUNTER)//TODO SHIFT TO NEXT KEY
			break;
		
		$temp = getIndex($encryptedPhoneNumber);
		if ($temp[1] != 0)
			break;
		$operateIndex = $temp[0];
		$temp = getUserEntryFromDataBase($operateIndex);
		if (!$temp[0])
			break;
		else
			$operateUser = $temp[1];
		
		for($i=0; $i<count($updateRequest); $i++){
			$temp = getIndex($updateRequest[i]);
			if ($temp[1] != 0)
				continue;
			$targetIndex = $temp[0];
			$temp = getUserEntryFromDataBase($targetIndex);
			
			$exchangeFile = fopen($exchangeFileName, "wb");
		}
	} while (true);
}

?>
