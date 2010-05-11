<?php
	
    print_r($_FILES);

	move_uploaded_file($_FILES['upload']['name'], 'test.bin');
	
?>