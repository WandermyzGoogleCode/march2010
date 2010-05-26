<?php
$fp = fopen('test.txt', 'wb');
$utf8 = utf8_encode('今天心情很好');
fwrite($fp, $utf8);
fclose($fp);

$fp = fopen('test.txt', 'rb');
$data = fread($fp, strlen($utf8));
fclose($fp);
echo utf8_decode($data);
