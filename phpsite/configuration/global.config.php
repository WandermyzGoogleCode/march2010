<?php
if(!defined('IN_LIVES_CUBE'))
{
	exit("Access Denied");
}

/**
 * 内容待定
 * @author Wander
 *
 */
class GlobalConfig
{
	/***************************************
	 * 目录定义
	 ***************************************/
	/**
	 * 可执行文件存放位置
	 */
	var $binDir = '/usr/local/lives3/bin/';
	
	/**
	 * 数据文件（永久性的）存放位置
	 */
	var $dataDir = '/usr/local/lives3/data/';
	
	/**
	 * 临时文件存放位置，将挂载在RAM Disk上
	 */
	var $tmpDir = '/usr/local/lives3/tmp/';
	
	/****************************************
	 * 数据库设置
	 ****************************************/
	/**
	 * 数据库主机
	 */
	var $dbHost = 'localhost';
	
	/**
	 * 数据库名
	 */
	var $dbName = 'lives3';
	
	/**
	 * 数据库用户名
	 */
	var $dbUser = 'lives3';
	
	/**
	 * 数据库密码
	 */
	var $dbPassword = 'lives3encrypted';
	
	/**
	 * 数据库服务端口号，-1表示使用默认值（通常是3306）
	 * @var unknown_type
	 */
	var $dbPort = -1;
	
	/******************************************
	 * 域名设置
	 ******************************************/
	/**
	 * 网页服务器端使用的域名
	 */
	var $webServerHost = 'info.lives3.net';
	
	/**
	 * 手机服务器端使用的域名
	 */
	var $mobileServerHost = 'server.lives3.net';
	
	/**
	 * 官网地址
	 */
	var $officialURL = 'http://www.lives3.net';
	
	/*****************************************
	 * 模板系统设置
	 */
	var $templateDir = './Smarty/templates';
	var $templateCompileDir = './Smarty/templates_c';
	var $templateCacheDir = './Smarty/cache';
	var $templateConfigDir = './Smarty/configs';
	var $templateWebSubDir = 'web';
	var $templateWapSubDir = 'wap';
	
	/*******************************************
	 * 单向用户设置
	 *******************************************/
	/**
	 * 默认标签
	 */
	var $defaultTags = array (
		'餐饮外卖',
		'食品店',
		'打印服务',
		'协会和社团',
		'其它'
	);
	
	/**
	 * 新单向用户的初始状态
	 */
	var $newUserStatus = '该用户还没有设置过状态';
	
	/**
	 * 注册新单向用户时所用的管理员密码的SHA1字符串
	 */
	var $adminRegisterPassword = 'bca8b4830cc53acfab0db3cf1084dcf85c8c163c';
	
	/*****************************************
	 * 函数
	 *****************************************/
	/**
	 * 从内存中删除敏感数据，如数据库密码等
	 */
	function clearSensitive()
	{
		unset($this->dbUser);
		unset($this->dbPassword);
	}
}

?>