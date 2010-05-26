<?php
/**
 * 用户注册
 * GET:
 * op=11					操作码
 * POST数据：
 * 		encryptedPhoneNumber	加上PADDING并用服务器公钥做加密后得到的EncryptedPhoneNumber, base64编码
 * 		userEntry 				用服务器公钥做加密后得到的UserEntry, base64编码
 * 输出：
 * 		MIME类型： text/plain（纯文本）
 * 		内容：1表示成功，0表示失败
 */

if(!defined('IN_LIVES_CUBE'))
{
	exit("Access Denied");
}

require_once('./library/encrypted.func.php');

$encryptedPhoneNumber = base64_decode($env->POST['encryptedPhoneNumber']);
$userEntry = base64_decode($env->POST['userEntry']);

$result = encryptedRegister($encryptedPhoneNumber, $userEntry);

echo $result;

?>