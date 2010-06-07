{include file='web/header.tpl' title='重建加密数据表（仅管理员）'}

<form id="registerForm" name="registerForm" method="post" action="./?op=28">
	<input type="hidden" name="refreshWholeTableSubmit" id="registerSubmit" value="1"/>
	<label for="Password">管理员密码</label><input type="password" name="Password" id="Password" />
</form>

{include file='web/footer.tpl'}
