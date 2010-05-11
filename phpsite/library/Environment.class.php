<?php
if(!defined(IN_LIVES_CUBE))
{
	exit("Access Denied");
}

/**
 * 存储当前HTTP会话的各种数据，包括GET和POST数据、上传的附件，已登录的用户信息等
 * @author Wander
 *
 */
class Environment
{
	var $_GET;
	var $_POST;
	var $_FILES;
	var $_COOKIE;
	
	function Environment()
	{
		
	}
}

?>