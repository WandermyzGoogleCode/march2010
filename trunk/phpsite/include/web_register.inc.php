<?php
if(!defined('IN_LIVES_CUBE'))
{
	exit("Access Denied");
}

require_once('./library/virtualClient.func.php');

if(checkSubmit('registerSubmit'))
{
	if($cfg->adminRegisterPassword != lhash($env->POST['Password']))
	{
		showMessage("管理员密码不正确", "错误", -1);
	}
	
	if(!preg_match('/^[0-9]+$/', $env->POST['PhoneNumber']))
	{
		showMessage('电话号码格式不正确', '错误', -1);
	}
	
	if($env->POST['Name'] == "")
	{
		showMessage('姓名不能为空', '错误', -1);
	}
	
	$checkExist = $db->query('SELECT NULL FROM lives3_openinfo WHERE PhoneNumber = ?', 's', $env->POST['PhoneNumber']);
	if($db->num_rows($checkExist) > 0)
	{
		showMessage("手机号{$env->POST['PhoneNumber']}已存在", '手机号重复', '-1');
	}
	
	$db->query('INSERT INTO lives3_openinfo(PhoneNumber, Name, Status, MemberInfo, TagStr) VALUES(?, ?, ?, ?, ?)', 'sssss',
			$env->POST['PhoneNumber'],
			$env->POST['Name'],
			$cfg->newUserStatus,
			$env->POST['MemberInfo'],
			implode(',', $env->POST['Tags'])
		);
		
	foreach($env->POST['Tags'] as $tag)
	{
		$db->query('INSERT INTO lives3_tags VALUES(?, ?)', 'ss', $tag, $env->POST['PhoneNumber']);
	}
	
	$entry = new PlainUserEntry();
	$entry->phoneNumber = $env->POST['PhoneNumber'];
	$entry->name = $env->POST['Name'];
	$entry->status = $cfg->newUserStatus;
	
	virtualRegister($entry);
	
	showMessage("新单向用户({$env->POST['PhoneNumber']})注册成功！", '注册成功', -1);
}
else
{
	$tpl->assign('tags', $cfg->defaultTags);
	$tpl->assign('title', '新单向用户注册（仅管理员）');
	$tpl->display('register.tpl');
}

?>