<?php
/**
 * 用户更新自己的信息
 * POST数据：
 * 		encryptedPhoneNumber	加上PADDING并用服务器公钥做加密后得到的EncryptedPhoneNumber，base64编码
 * 		userEntry 先用服务器公钥做加密，再用用户自己的私钥加密后得到的UserEntry，base64编码
 * 输出：
 * 		MIME类型： text/plain（纯文本）
 * 		内容：完成更新的Unix timestamp，0表示失败
 */

if(!defined(IN_LIVES_CUBE))
{
	exit("Access Denied");
}

?>