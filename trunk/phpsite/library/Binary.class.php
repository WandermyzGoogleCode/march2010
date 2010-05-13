<?php


if(!defined(IN_LIVES_CUBE))
{
	exit("Access Denied");
}

/**
 * 提供对二进制操作的支持。
 * TODO: 待设计
 * TODO: data.h的PHP定义
 */
class Binary
{
	var $binstr;
	
	/**
	 * 由文件读入二进制数据
	 * @param $filepath
	 */
	static function createFromFile($filepath)
	{
		
	}
	
	/**
	 * 解码base64数据
	 * @param $base64code
	 */
	static function createFromBase64($base64code)
	{
		
	}
	
	/**
	 * 将指定的变量打包成二进制数据
	 * @param $format
	 */
	static function pack($format)
	{
		
	}
	
	//TODO: unpack
	
	/**
	 * 编码成base64数据
	 */
	function base64_encode()
	{
		
	}
	
	//TODO: 各种二进制struct的pack和unpack
}

?>