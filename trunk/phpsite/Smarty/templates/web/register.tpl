{include file='web/header.tpl' title='新单向用户注册（仅管理员）'}

<form id="registerForm" name="registerForm" method="post" action="./?op=24">
	<input type="hidden" name="registerSubmit" id="registerSubmit" value="1"/>
  <table width="100%" border="0" cellspacing="0" cellpadding="0">
    <tr>
      <th width="12%" scope="row"><label for="PhoneNumber">手机号</label></th>
      <td width="88%"><input name="PhoneNumber" type="text" id="PhoneNumber" size="11" maxlength="11" /></td>
    </tr>
    <tr>
      <th scope="row"><label for="Name">姓名</label></th>
      <td><input name="Name" type="text" id="Name" size="11" maxlength="8"/></td>
    </tr>
    <tr>
      <th scope="row"><label for="MemberInfo">用户资料</label></th>
      <td><textarea name="MemberInfo" cols="50" rows="10" id="MemberInfo"></textarea></td>
    </tr>
    <tr>
      <th scope="row"><label for="Tags">标签</label></th>
      <td>
      	<select name="Tags[]" size="1" multiple="multiple" id="Tags">
      		{foreach item=tag from=$tags}
      			<option value="{$tag}">{$tag}</option>       		
      		{/foreach}       
        </select>       </td>
    </tr>
    <tr>
      <th scope="row"><label for="Password">管理员密码</label></th>
      <td><input type="password" name="Password" id="Password" /></td>
    </tr>
    <tr>
      <th scope="row">&nbsp;</th>
      <td><input type="submit" name="Submit" id="Submit" value="提交" /></td>
    </tr>
  </table>
</form>

{include file='web/footer.tpl'}
