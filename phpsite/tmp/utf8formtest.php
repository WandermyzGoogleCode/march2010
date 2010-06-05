<?php
if(!$_POST['submit'])
{
?>

<form method="POST" action="utf8formtest.php">
	<input type="hidden" name="submit" value="1"/>
	<input type="text" name="data"/>
	<input type="submit" value="submit"/>
</form>
<?php 	
}
else
{
	$fp = fopen('testphp.bin', 'wb');
	$input = $_POST['data'];
	echo strlen($input);
	fwrite($fp, $input);
	fclose($fp);
}

?>