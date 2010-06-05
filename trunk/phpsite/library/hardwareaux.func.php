<?php

if(!defined('IN_LIVES_CUBE'))
{
	exit("Access Denied");
}

require_once './configuration/define.config.php';

function acquireLock($lockFileName){
	$lockfp = fopen($lockFileName, "w");
	flock($lockfp, LOCK_EX);
	return $lockfp;
}

function releaseLock($lockfp){
	flock($lockfp, LOCK_UN);
	fclose($lockfp);
}

/**
 * @param $epn EncryptedPhoneNumber
 * @return array(0 => Index, 1 => status returned by caller)
 */
function getIndex($epn) {
	include './include/hardwarecfg.inc.php'; 
	$exchangeFile = fopen($exchangeFileName, "wb");
	fwrite($exchangeFile, $epn, strlen($epn));
	fclose($exchangeFile); 
	$cmd = "$callerName $safeCoreName getIndex $exchangeFileName";
	exec($cmd, $stdout, $status);
	if ($status != 0){
		if ($status == 1)
			echo "bad command: $cmd\n";
		printStdout($stdout);
	}
	$exchangeFile = fopen($exchangeFileName, "rb");
	$index = fread($exchangeFile, SIZE_Index);
	fclose($exchangeFile);
	return array($index, $status);
}

/**
 * @return array(0 => count, 1 => status returned by caller)
 */
function getCurrentCounter(){
	include './include/hardwarecfg.inc.php';
	$cmd = "$callerName $safeCoreName getCurrentCounter $exchangeFileName";
	exec($cmd, $stdout, $status);
	if ($status != 0){
		if ($status == 1)
			echo "bad command: $cmd\n";
		printStdout($stdout);
		return array(-1, $status);
	}
	$exchangeFile = fopen($exchangeFileName, "r");
	fscanf($exchangeFile, "%d", $count);
	return array($count, $status);
}

/**
 * @param $index the index of database
 * @return array(0 => hasEntry, 1 => userEntry)
 */
function getUserEntryFromDataBase($index){
	global $db;
	$result = $db->query("select * from lives3_encryptedinfo where index=?", "b", $index);
	$hasEntry = ($db->num_rows($result) > 0 ? true : false);
	$userEntry = NULL;
	if ($hasEntry){
		$row = $db->fetch_assoc($result);
		$userEntry = $row["userEntry"];
	}
	return array($hasEntry, $userEntry);
}

function replaceUserEntry($tablename, $index, $newUserEntry){
	global $db;
	$db->query("replace into $tablename values(?, ?)", "bb", $index, $newUserEntry);
}

function changeTableName($oldname, $newname){
	global $db;
	$db->query("alter table $oldname rename $newname");
}

function printStdout($stdout){
	foreach($stdout as $line)
		echo "$line\n";
}

?>
