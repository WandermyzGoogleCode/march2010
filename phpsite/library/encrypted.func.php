<?php

if(!defined('IN_LIVES_CUBE'))
{
	exit("Access Denied");
}


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
 * @return 完成注册的Unix timestamp，0表示失败
 */
function encryptedRegister($encryptedPhoneNumber, $userEntry){
	//TODO
}

/**
 * 用户更新自己的信息
 * @param $encryptedPhoneNumber 加上PADDING并用服务器公钥做加密后得到的EncryptedPhoneNumber
 * @param $userEntry 先用服务器公钥做加密，再用用户自己的私钥加密后得到的UserEntry
 * @return 完成注册的Unix timestamp，0表示失败
 */
function encryptedUpdate($encryptedPhoneNumber, $userEntry){
	//TODO
}

/**
 * 用户获取自己联系人的最新信息
 * @param $encryptedPhoneNumber 加上PADDING并用服务器公钥做加密后得到的EncryptedPhoneNumber
 * @param $updateRequest 普通的UpdateRequest，其中包含了需要获得哪些联系人的最新信息（加密过的）
 * @return 获得的UpdatePackage，包含了更新过的联系人信息（已经做了时间增量处理）
 */
function getEncryptedUpdatePackage($encryptedPhoneNumber, $updateRequest){
	//TODO
}

?>
