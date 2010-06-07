<?php
if(!defined('IN_LIVES_CUBE'))
{
	exit("Access Denied");
}

require_once('./library/encrypted.func.php');

if(checkSubmit('updateWholeTableSubmit'))
{
	if($cfg->adminRegisterPassword != lhash($env->POST['Password']))
	{
		showMessage("管理员密码不正确", "错误", -1);
	}
	
	updateWholeTable(true);
	
	showMessage("重建加密数据表操作完成", "完成");
}
else
{
	$tpl->display('updateWholeTable.tpl');
}

?>