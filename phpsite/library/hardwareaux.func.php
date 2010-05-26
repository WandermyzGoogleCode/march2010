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
	system("$callerName $safeCoreName getIndex $exchangeFile", $status);
	$exchangeFile = fopen($exchangeFileName, "rb");
	$index = fread($exchangeFile, SIZE_Index);
	fclose($exchangeFile);
	return array($index, $status);
}

/**
 * @return array(0 => count, 1 => status returned by caller)
 */
function getCurrentCounter(){
	include './include/harwarecfg/inc.php';
	system("$callerName $safeCoreName getCurrentCounter $exchangeFile", $status);
	if ($status != 0)
		return array(-1, $status);
	$exchangeFile = fopen($exchangeFileName, "r");
	fscanf($exchangeFile, "%d", $count);
	return array($count, $status);
}

?>
