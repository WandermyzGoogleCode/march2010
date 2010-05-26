<?php
if(!defined('IN_LIVES_CUBE'))
{
	exit("Access Denied");
}

echo (base64_decode($env->POST['encryptedPhoneNumber']));
echo "\r\n";
echo (base64_decode($env->POST['userEntry']));

?>