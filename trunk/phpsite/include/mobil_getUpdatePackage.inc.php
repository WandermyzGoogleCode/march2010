<?php
/**
 * 用户获取自己联系人的最新信息
 * GET数据：
 * op=13					操作码
 * POST:
 * encryptedPhoneNumber 	加上PADDING并用服务器公钥做加密后得到的EncryptedPhoneNumber，base64编码
 * threshold				用户最后更新的时间，用于做增量更新，类型为unsigned long long, base64编码
 * updateEntry[] 			updateEntry数组，数组的每一个元素存储一个EncryptedPhoneNumber，其中包含了需要获得哪些联系人的最新信息，每个条目使用base64编码
 * 输出：
 * 	MIME类型：application/octet-stream（二进制）
 *	内容：一个32位整数(little endian)，表示所含的updateEntry个数。后面紧接着每一个updateEntry，包含了新的联系人信息（已经做了时间增量处理）（不使用base64编码！）如果出错则第一个整数返回0
 */

if(!defined('IN_LIVES_CUBE'))
{
	exit("Access Denied");
}

require_once('./library/encrypted.func.php');

$encryptedPhoneNumber = base64_decode($env->POST['encryptedPhoneNumber']);
checkLength($encryptedPhoneNumber, SIZE_EncryptedPhoneNumber, 'encryptedPhoneNumber');

$threshold = base64_decode($env->POST['threshold']);
checkLength($threshold, SIZE_TimeType, 'threshold');

if(!is_array($env->POST['updateEntry']) || count($env->POST['updateEntry']) == 0)
{
	die('updateEntry不是数组或数组元素个数为空');
}
else
{

	$updateRequest = array();
	foreach($env->POST['updateEntry'] as $entry)
	{
		$data = base64_decode($entry);
		checkLength($data, SIZE_EncryptedPhoneNumber, 'updateRequest');
		$updateRequest[] = $data;
	}
	
	$updatePackage = getEncryptedUpdatePackage($encryptedPhoneNumber, $updateRequest, $threshold);
	
	if(!is_array($updatePackage))
	{
		die('getEncryptedUpdatePackage返回的不是数组');
		//$updatePackage = array();
	}
	
	//print_r($updatePackage);
	//return;
	
	$result = pack('V', count($updatePackage));
	//die($updatePackage);
	foreach($updatePackage as $entry)
	{
		$result .= $entry;
	}
	
}

header('Content-Description: File Transfer');
header('Content-Type: application/octet-stream');
header('Content-Disposition: attachment; filename=data.bin');
header('Content-Transfer-Encoding: binary');
header('Cache-Control: must-revalidate, post-check=0, pre-check=0');
header('Pragma: public');
header('Content-Length: '.strlen($result));
ob_clean();
flush();

echo $result;

?>