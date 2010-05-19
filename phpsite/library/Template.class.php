<?php
if(!defined('IN_LIVES_CUBE'))
{
	exit("Access Denied");
}

require_once('./library/Smarty/Smarty.class.php');

class Template
{
	/**
	 * 当服务器类型不是WEB服务器时，不执行任何操作
	 * @var bool
	 */
	var $isDummy;	
	var $browserMode;
	var $tplFolder;
	
	private $smarty;
	
	function __construct(GlobalConfig $cfg, Environment $env)
	{
		$this->isDummy = $env->serverMode != LIVES_CUBE_WEB_SERVER;
		
		if($this->isDummy)
			return;
			
		$this->browserMode = $env->clientBrowserMode;
		$this->tplFolder = $this->browserMode == LIVES_CUBE_WAP_BROWSER ? $cfg->templateWapSubDir : $cfg->templateWebSubDir;
		
		$this->smarty = new Smarty();
		$this->smarty->template_dir = $cfg->templateDir;
		$this->smarty->compile_dir = $cfg->templateCompileDir;
		$this->smarty->cache_dir = $cfg->templateCacheDir;
		$this->smarty->config_dir = $cfg->templateConfigDir;
	}
	
	function assign($tpl_var, $value)
	{
		if($this->isDummy)
			return;
			
		$this->smarty->assign($tpl_var, $value);
	}
	
	function display($source_name)
	{
		global $db, $env;
		
		if($this->isDummy)
			return;
		
		$this->assign('debugQueryCounter', $db->getQueryCounter());
		$this->assign('debugRunningTime', $env->getRunningTime());
			
		$this->smarty->display($this->tplFolder.'/'.$source_name);
	}
}

?>