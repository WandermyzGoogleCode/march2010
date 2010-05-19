<?php
if(!defined('IN_LIVES_CUBE'))
{
	exit("Access Denied");
}

require_once './library/PlainUserEntry.class.php';

/**
 * 注册一个新单向用户。此函数只需维护新用户在encryptedinfo表中的数据，但不用维护新用户在openinfo表中的数据
 * @param $plainUserEntry 包含新用户信息的userEntry（明文）
 * @return 完成注册的Unix timestamp，0表示失败
 */
function virtualRegister(PlainUserEntry $plainUserEntry)
{
	
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