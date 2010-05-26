<?php
	$binstr = pack("L*", 1, 2, 3);	
	
	$base64 = base64_encode($binstr);
	//echo $base64;
	$decoded = base64_decode($base64);
	
	
	
	header('Content-Description: File Transfer');
	header('Content-Type: application/octet-stream');
	header('Content-Disposition: attachment; filename=test.bin');
	header('Content-Transfer-Encoding: binary');
	header('Cache-Control: must-revalidate, post-check=0, pre-check=0');
    header('Pragma: public');
    header('Content-Length: '.strlen($binstr));
    ob_clean();
    flush();
    
    echo $decoded;
    
?>