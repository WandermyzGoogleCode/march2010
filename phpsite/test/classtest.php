<?php
class myclass
{
	var $a = "hello";
	
	function __construct()
	{
		echo $this->a;
	}
}

$t = new myclass();


?>