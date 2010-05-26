<?php
	if(!defined('IN_LIVES_CUBE'))
	{
		exit("Access Denied");
	}
	
	global $cfg;
	global $db;
	$exchangeFileName = $cfg->tmpDir . $cfg->safeCoreExchangeName;
	$callerName = $cfg->binDir . $cfg->hardwareCallerName;
	$safeCoreName = $cfg->dataDir . $cfg->safeCoreName;
	$lockFileName = $cfg->tmpDir . $cfg->safeCoreLockName;
?>
