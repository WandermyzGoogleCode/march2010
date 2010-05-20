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
if($input['tag'] == '-1')
{
	$input['tag'] = $input['customTag'];
}

if(!$input['q'] && !$input['name'] && !$input['tag'] && !$input['status'] && !$input['memberInfo'] && !$input['phoneNumber'])	
{
	$tpl->assign('tags', $cfg->defaultTags);
	$tpl->display('search.tpl');
}
else
{
	//TODO: 简单查询字串
	//TODO: 参数化查询
	

	$query = 'SELECT o.* FROM lives3_openinfo o';
	$where = " 1";
	if($input['tag'])
	{
		$query .= ' LEFT JOIN lives3_tags t ON o.PhoneNumber = t.PhoneNumber';
		$where .= " AND t.Tag = '".laddslashes($input['tag'])."'";
	}
	$where .= $input['phoneNumber'] ? (" AND o.PhoneNumber = '".laddslashes($input['phoneNumber'])."'") : "";
	$where .= $input['name'] ? (" AND o.Name LIKE '%".laddslashes($input['name'])."%'") : "";
	$where .= $input['status'] ? (" AND o.Status LIKE '%".laddslashes($input['status'])."%'") : "";
	$where .= $input['memberInfo'] ? (" AND o.MemberInfo LIKE '%".laddslashes($input['memberInfo'])."%'") : "";
	
	$result = $db->query($query.' WHERE'.$where);	//$where一定不为空
	$dataset = $db->fetch_all_array($result);
	
	for($i = 0; $i < count($dataset); $i++)
	{
		$dataset[$i]['Tags'] = explode(',', $dataset[$i]['TagStr']);
	}
	
	$tpl->assign('dataset', $dataset);
	$tpl->display('search_result.tpl');
}

?>