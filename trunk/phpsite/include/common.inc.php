<?php

/**
 * 由index.php包含，完成连接数据库、处理和检查输入数据等操作
 * common.inc.php将会新建MySqlImproved对象$db、Envrionment对象$env以及GlobalConfig对象$cfg
 */

if(!defined('IN_LIVES_CUBE'))
{
	exit("Access Denied");
}

require_once('./configuration/global.config.php');
require_once('./configuration/define.config.php');
require_once('./library/global.func.php');
require_once('./library/MySqlImproved.class.php');
require_once('./library/Environment.class.php');
require_once('./library/Template.class.php');

/**
 * 全局配置
 * @var GlobalConfig
 */
$cfg = new GlobalConfig();

/**
 * 环境变量
 * @var Environment
 */
$env = new Environment($cfg);

/**
 * 数据库管理器 
 * @var MySqlImproved
 */
$db = new MySqlImproved($cfg->dbHost, $cfg->dbUser, $cfg->dbPassword, $cfg->dbName, $cfg->port);
$cfg->clearSensitive();

/**
 * 模板系统
 * @var Template
 */
$tpl = new Template($cfg, $env);

date_default_timezone_set("Asia/Chongqing");

?>