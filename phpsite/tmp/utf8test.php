<?php

$fp = fopen('testphp.bin', 'wb');
$input = '刘之方';
echo (mb_strlen($input, 'utf8'));
fwrite($fp, $input);
fclose($fp);

/*$fp = fopen('test.txt', 'wb');
$input = base64_encode('今天心情很好');
fwrite($fp, $input);
fclose($fp);

$fp = fopen('test.txt', 'rb');
$output = fread($fp, strlen($input));
fclose($fp);
echo base64_decode($output);
*/
?>