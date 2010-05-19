<?php
if(!defined('IN_LIVES_CUBE'))
{
	exit("Access Denied");
}

/**
 * 域名错误，无法判断服务类型
 */
define('LIVES_CUBE_HOST_ERROR', 0);
/**
 * 网页服务器端
 */
define('LIVES_CUBE_WEB_SERVER', 1);
/**
 * 手机服务器端
 */
define('LIVES_CUBE_MOBILE_SERVER', 2);

/**
 * 未知浏览器类型
 */
define('LIVES_CUBE_UNKNOWN_BROWSER', 0);

/**
 * Web浏览器
 */
define('LIVES_CUBE_WEB_BROWSER', 1);

/**
 * WAP浏览器
 */
define('LIVES_CUBE_WAP_BROWSER', 2);

/**
 * 存储当前HTTP会话的各种数据，包括GET和POST数据、上传的附件，已登录的用户信息等
 * @author Wander
 *
 */
class Environment
{
	var $GET;
	var $POST;
	var $FILES;
	var $COOKIE;
	
	/**
	 * $serverMode == LIVES_BUE_HOST_ERROR时表示域名错误
	 * $serverMode == LIVES_CUBE_WEB_SERVER时表示网页服务器端
	 * $serverMode == LIVES_CUBE_MOBILE_SERVER时表示手机服务器端
	 */
	var $serverMode;
	
	var $clientBrowserMode;
	
	private $timeStart;
	
	function __construct(GlobalConfig $cfg)
	{
		//TODO: 安全检查
		global $_GET, $_POST, $_FILES, $_COOKIE, $_SERVER;
		
		$this->timeStart = microtime(true);
		
		$this->GET = $_GET;
		$this->POST = $_POST;
		$this->FILES = $_FILES;
		$this->COOKIE = $_COOKIE;
		
		if($_SERVER['HTTP_HOST'] == $cfg->webServerHost)
		{
			$this->serverMode = LIVES_CUBE_WEB_SERVER;
		}
		else if($_SERVER['HTTP_HOST'] == $cfg->mobileServerHost)
		{
			$this->serverMode = LIVES_CUBE_MOBILE_SERVER;
		}
		else
		{
			$this->serverMode = LIVES_CUBE_HOST_ERROR;
		}
		
		$clientBrowserMode = LIVES_CUBE_WEB_BROWSER;	//TODO: 判断浏览器类型
	}
	
	function getRunningTime()
	{
		return microtime(true) - $this->timeStart;
	}
}



?>