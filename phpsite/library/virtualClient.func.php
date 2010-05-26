<?php
if(!defined('IN_LIVES_CUBE'))
{
	exit("Access Denied");
}

require_once './library/PlainUserEntry.class.php';
require_once './configuration/define.config.php';

/**
 * 注册一个新单向用户。此函数只需维护新用户在encryptedinfo表中的数据，但不用维护新用户在openinfo表中的数据
 * @param $plainUserEntry 包含新用户信息的userEntry（明文）
 * @return 完成注册的Unix timestamp，0表示失败
 */
function virtualRegister(PlainUserEntry $plainUserEntry)
{
	global $cfg;
	
	$name_len = strlen(utf8_encode($plainUserEntry->name));
	$phone_num_len = strlen(utf8_encode($plainUserEntry->phoneNumber));
	$status_len = strlen(utf8_encode($plainUserEntry->status));
	
	if ($name_len > MAX_NAME_LENGTH)
	{
		echo "plainUserEntry->name is too long";
		die();
	}
	if ($phone_num_len > 30)
	{
		echo "plainUserEntry->phoneNumber is too long";
		die();
	}
	if ($status_len > MAX_STATUS_LENGTH)
	{
		echo "plainUserEntry->status is too long";
		die();
	}
	
	$fd  = fopen($cfg->tmpDir."virtual_client.tmp", "wb");
		
	$padding = "";
	while ($phone_num_len < 30-1)
	{
		$padding .= "0";
		$phone_num_len++;
	}
	fwrite($fd, $plainUserEntry->phoneNumber);
	fwrite($fd, "\0", 1);
	fwrite($fd, $padding);
		
	$padding = "";
	while ($name_len < MAX_NAME_LENGTH - 1)
	{
		$padding .= "0";
		$name_len++;
	}
	fwrite($fd, utf8_encode($plainUserEntry->name));
	fwrite($fd, "\0", 1);
	fwrite($fd, $padding);
	
	$padding = "";
	while ($status_len < MAX_STATUS_LENGTH - 1)
	{
		$padding .= "0";
		$status_len++;
	}
	fwrite($fd, utf8_encode($plainUserEntry->status));
	fwrite($fd, "\0", 1);
	fwrite($fd, $padding);
	
	fclose($fd);
	
	system($cfg->binDir."vc_caller");
	system("rm ".$cfg->tmpDir."virtual_client.tmp");
	
	$fd = fopen($cfg->tmpDir."virtual_client_c_return.tmp", "rb");
	$encryptedPhoneNum = fread($fd, SIZE_EncryptedPhoneNumber);
	$userEntry = fread($fd, SIZE_ValidUserEntry);
	
	system("rm ".$cfg->tmpDir."virtual_client_c_return.tmp");
	encryptedRegister($encryptedPhoneNum, $userEntry);
}

/**
 * 更新单向用户的信息。此函数只需维护用户在encryptedinfo表中的数据，但不用维护用户在openinfo表中的数据
 * @param $plainUserEntry 用户更改的新的userEntry（明文）
 * @return 完成注册的Unix timestamp，0表示失败
 */
function virtualUpdate(PlainUserEntry $plainUserEntry)
{
	
}

?>