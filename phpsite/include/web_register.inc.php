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
	
	if(strlen($env->POST['Name']) > MAX_NAME_LENGTH)
	{
		showMessage("姓名长度不能超过32字节（8个中文字符）", -1);
	}
	
	$checkExist = $db->query('SELECT NULL FROM lives3_openinfo WHERE PhoneNumber = ?', 's', $env->POST['PhoneNumber']);
	if($db->num_rows($checkExist) > 0)
	{
		showMessage("手机号{$env->POST['PhoneNumber']}已存在", '手机号重复', '-1');
	}
	
		
	$entry = new PlainUserEntry();
	$entry->phoneNumber = $env->POST['PhoneNumber'];
	$entry->name = $env->POST['Name'];
	$entry->status = $cfg->newUserStatus;
	
	//print_r($entry);
	
	$virtual =  virtualRegister($entry);	
	
	if(!$virtual)
	{
		showMessage("virtualRegister模块出错", -1);
	}
	
	
	$db->query('INSERT INTO lives3_openinfo(PhoneNumber, Name, Status, MemberInfo, TagStr) VALUES(?, ?, ?, ?, ?)', 'sssss',
			$env->POST['PhoneNumber'],
			$env->POST['Name'],
			$cfg->newUserStatus,
			$env->POST['MemberInfo'],
			$env->POST['Tags'] ? implode(',', $env->POST['Tags']) : ""
		);
		
	if($env->POST['Tags'])
	{
		foreach($env->POST['Tags'] as $tag)
		{
			$db->query('INSERT INTO lives3_tags VALUES(?, ?)', 'ss', $tag, $env->POST['PhoneNumber']);
		}
	}
	
	showMessage("新单向用户({$env->POST['PhoneNumber']})注册成功！", '注册成功', -1);
}
else
{
	$tpl->assign('tags', $cfg->defaultTags);
	$tpl->display('register.tpl');
}

?>