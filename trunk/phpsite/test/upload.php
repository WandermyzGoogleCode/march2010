<html>
<form method="post" action="upload.php" enctype="multipart/form-data" >
<input type="file" name="test"/>
<input type="hidden" name="submit" value="1"/>
<input type="submit"/>
</form>
</html>

<?php 
print_r($_FILES);
?>
