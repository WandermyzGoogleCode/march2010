{include file='web/header.tpl' title='高级搜索'}

<form id="searchForm" name="searchForm" method="post" action="./?op=22">
  <table width="100%" border="0" cellspacing="0" cellpadding="0">
    <tr>
      <th width="12%" scope="row"><label for="phoneNumber">手机号</label></th>
      <td width="88%"><input name="phoneNumber" type="text" id="phoneNumber" size="11" maxlength="11" /></td>
    </tr>
    <tr>
      <th scope="row"><label for="name">姓名包含</label></th>
      <td><input name="name" type="text" id="name" size="11" maxlength="255"/></td>
    </tr>
    <tr>
      <th scope="row"><label for="status">状态文本包含</label></th>
      <td><input name="status" type="text" id="status" size="11"/></td>
    </tr>
    <tr>
      <th scope="row"><label for="memberInfo">用户资料包含</label></th>
      <td><input name="memberInfo" type="text" id="memberInfo" size="11"/></td>
    </tr>
    <tr>
      <th scope="row"><label for="tags">标签</label></th>
      <td>
      	<select name="tag" size="1" id="tags">
      		<option value="0" selected>（不限制）</option>
      		{foreach item=tag from=$tags}
      			<option value="{$tag}">{$tag}</option>       		
      		{/foreach}  
      		<option value="-1">（自定义）</option>     
        </select>       
        <input name="customTag" type="text" id="customTag" size="5"/>
      </td>
    </tr>
    <tr>
      <th scope="row">&nbsp;</th>
      <td><input type="submit" name="Submit" id="Submit" value="提交" /></td>
    </tr>
  </table>
</form>

{include file='web/footer.tpl'}
