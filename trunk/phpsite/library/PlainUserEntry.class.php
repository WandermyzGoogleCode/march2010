<?php
if(!defined('IN_LIVES_CUBE'))
{
	exit("Access Denied");
}

class PlainUserEntry
{
	/**
	 * 电话号码（字符串）
	 * @var string
	 */
	var $phoneNumber;
	/**
	 * 姓名
	 * @var string
	 */
	var $name;
	/**
	 * 状态文本
	 * @var string
	 */
	var $status;
}

?>