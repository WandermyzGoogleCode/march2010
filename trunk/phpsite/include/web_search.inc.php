<?php

/**
 * 搜索单向用户
 * GET数据：
 * 		q		简单查询字串
 * 		name	商户名称
 * 		tag		商户分类
 * 		status	状态文本
 * 		memberInfo 商户信息
 * 		phoneNumber 电话号码
 */

if(!defined('IN_LIVES_CUBE'))
{
	exit("Access Denied");
}

$input = $env->getCombinedInput();

if(!$input['q'] && !$input['name'] && !$input['tag'] && !$input['status'] && !$input['memberInfo'] && !$input['phoneNumber'])	
{
	$tpl->assign('title', '高级搜索');
	$tpl->assign('tags', $cfg->defaultTags);
	$tpl->display('search.tpl');
}
else
{
	
}

?>