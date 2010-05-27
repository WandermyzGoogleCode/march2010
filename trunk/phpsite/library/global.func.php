<?php
if(!defined('IN_LIVES_CUBE'))
{
	exit("Access Denied");
}

/**
 * 为字符串加上magic_quotes转义（也就是给'加“\”）。如果PHP系统已经自动做了转义，则不会重复转义
 * @param $string 要被转义的字符串或者字符串数组
 * @param $force 是否无视PHP设置而强制转义，默认为false
 */
function laddslashes($string, $force = 0) {
	!defined('MAGIC_QUOTES_GPC') && define('MAGIC_QUOTES_GPC', get_magic_quotes_gpc());
	if(!MAGIC_QUOTES_GPC || $force) {
		if(is_array($string)) {
			foreach($string as $key => $val) {
				$string[$key] = laddslashes($val, $force);
			}
		} else {
			$string = addslashes($string);
		}
	}
	return $string;
}

/**
 * 计算指定字符串的Hash值
 * @param $string
 */
function lhash($string)
{
	return sha1($string);
}

/**
 * 检查表单提交
 * @param string $identifier 能表示表单已经提交的字段名
 */
function checkSubmit($identifier, $isGet = false)
{
	global $env;
	//TODO: Form Hash?
	return $isGet ? $env->GET[$identifier] : $env->POST[$identifier];
}

/**
 * 显示提示信息
 * @param $message
 * @param $title
 * @param $redirect 若设为'-1'则表示后退
 */
function showMessage($message, $title = '', $redirect = '')
{
	global $tpl;
	$tpl->assign('message',$message);
	$tpl->assign('title', $title);
	
	if($redirect == '-1' || $redirect == -1) 
	{
		$redirect = 'javascript:history.go(-1)';
	}
	
	$tpl->assign('redirect', $redirect);
	$tpl->display('showMessage.tpl');
	
	exit();
}

/**
 * 检查$binstr的长度是否正确。若不正确，且$showMessage为true，则调用showMessage输出错误信息；若不正确，且$showMessage为false，则调用die输出错误信息
 * @param unknown_type $binstr
 * @param unknown_type $expectedLength
 * @param unknown_type $showMessage
 */
function checkLength($binstr, $expectedLength, $varname = '', $showMessage = false)
{
	if(strlen($binstr) != $expectedLength)
	{
		$msg = $varname."长度错误，接收的长度为".strlen($binstr);
		
		if($showMessage)
		{
			showMessage($msg, '长度错误');
		}
		else
		{
			die(utf8_encode($msg));
		}
	}
}




?>