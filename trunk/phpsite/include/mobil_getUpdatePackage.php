<?php
/**
 * 用户获取自己联系人的最新信息
 * encryptedPhoneNumber 	加上PADDING并用服务器公钥做加密后得到的EncryptedPhoneNumber，base64编码
 * updateRequest 			普通的UpdateRequest，其中包含了需要获得哪些联系人的最新信息，base64编码
 * 输出：
 * 	MIME类型：application/octet-stream（二进制）
 *	内容： 获得的UpdatePackage，包含了更新过的联系人信息（已经做了时间增量处理）（不使用base64编码！）
 */

if(!defined(IN_LIVES_CUBE))
{
	exit("Access Denied");
}

?>