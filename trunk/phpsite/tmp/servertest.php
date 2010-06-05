<?php
if(!defined('IN_LIVES_CUBE'))
{
	exit("Access Denied");
}

$db->query("select * from lives3_encryptedinfo where index = 'a'", "s", "abcdefg");

?>