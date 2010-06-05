<?php
if(!defined('IN_LIVES_CUBE'))
{
	exit("Access Denied");
}
 
$binstr = pack("iiii",1,2,3,4);
echo bin2hex($binstr);
$db->query("REPLACE INTO lives3_encryptedinfo VALUES(?, ?)", "ss", $binstr, 0);

?>