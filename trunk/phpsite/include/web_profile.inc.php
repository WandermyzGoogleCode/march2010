<?php
/**
 * 显示单向用户信息
 * GET数据：
 * 		phonenumber		单向用户手机号
 * 		query			查询字串组合
 */
if(!defined('IN_LIVES_CUBE'))
{
	exit("Access Denied");
}

$result = $db->query('SELECT * FROM lives3_openinfo WHERE PhoneNumber = ?', 's', $env->GET['phonenumber']);

$data = $db->fetch_assoc($result);

if(!$data)
{
	showMessage("指定的用户({$env->GET['phonenumber']})不存在，将返回上一页。", '用户不存在', -1);
}

//prepare tags
$tags = explode(',', $data['TagStr']);
/*
foreach(explode(',', $data['TagStr']) as $tag)
{
	$tags[] = array(
		'str' => $tag,
		'url' => urlencode($tag)	//TODO: PHP手册urlencode的Note
	);	
}*/

$tpl->assign('info', $data);
$tpl->assign('tags', $tags);
//$tpl->assign('title', $data['Name']);
$tpl->display('profile.tpl');

?>