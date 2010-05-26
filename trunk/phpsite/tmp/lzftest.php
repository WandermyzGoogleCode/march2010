<?php
	
	//define('IN_LIVES_CUBE', 1);

	//require_once './library/PlainUserEntry.class.php';
	require_once './library/virtualClient.func.php';
	
	$p = new PlainUserEntry();
	$p->name = "刘之方";
	$p->phoneNumber = "15810084822";
	$p->status = "今天心情不好! ";
	
	virtualRegister($p);
		
	echo "get here"."</br>";
?>