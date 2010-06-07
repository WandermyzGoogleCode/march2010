<?php 
/**
 * 系统首页，负责所有HTTP请求的分发操作
 * 该页面可通过http://server.lives.net或者http://info.lives.net（名字待定，分别代表手机服务器端以及网页端）访问。域名将作为第一级操作指令。
 * 第二级操作指令通过GET方法存储在名为op的变量中。
 * 所有操作所需的参数或数据通过GET方法或POST方法传送，具体定义见对应的inc文件
 * 当第一级操作指令为server（手机服务器端）时，op的值代表：
 * 		11 : 	register 用户注册 (mobil_register.inc.php)
 * 		12 :	update 用户更新自己的信息(mobil_update.inc.php)
 * 		13 :	getUpdatePackage 用户获取自己联系人的最新信息	(mobil_getUpdatePackage.inc.php)
 * 		19 : 	for test
 * 当第一级操作指令为info（网页端）时，op值代表：
 * 		21 :	index 首页，显示一个搜索框 (web_index.inc.php)
 * 		22 :	search 搜索单向用户 (web_search.inc.php)
 * 		23 :	profile 单向用户信息 (web_profile.inc.php)
 * 		24 :	register 单向用户注册 (web_register.inc.php)（目前仅对管理团队开放）
 * 		25 :	review 处理用户反馈 (web_review.inc.php)
 *        29:  for test
 */

define('IN_LIVES_CUBE', 1);
include "./include/common.inc.php";

if($env->serverMode == LIVES_CUBE_WEB_SERVER)
{
	switch($env->GET['op'])
	{
		case 21:
		default:
			include './include/web_index.inc.php';
			exit();
			
		case 22:
			include './include/web_search.inc.php';
			exit();
			
		case 23:
			include './include/web_profile.inc.php';
			exit();
			
		case 24:
			include './include/web_register.inc.php';
			exit();
			
		case 25:
			include './include/web_review.inc.php';
			exit();
			
		case 28:
			include './include/web_updateWholeTable.inc.php';
			exit();
			
		case 29:
			include './tmp/lzftest.php';
			exit();
	}
}
else if($env->serverMode == LIVES_CUBE_MOBILE_SERVER)
{
	switch($env->GET['op'])
	{
		case 11:
			include './include/mobil_register.inc.php';
			exit();
			
		case 12:
			include './include/mobil_update.inc.php';
			exit();
			
		case 13:
			include './include/mobil_getUpdatePackage.inc.php';
			exit();
			
		case 19:
			include './tmp/servertest.php';
			exit();
					
		default:
			die('INVALID REQUEST');
	}
}
else
{
	die('INVALID HOST');
}

?>
