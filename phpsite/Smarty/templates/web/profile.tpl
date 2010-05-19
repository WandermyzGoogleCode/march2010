{include file='web/header.tpl'}

<table width="100%" border="0" cellspacing="0" cellpadding="0">
  <tr>
    <th width="21%" scope="row">用户名称</th>
    <td width="79%">{$info.Name}</td>
  </tr>
    <tr>
    <th scope="row">电话号码</th>
    <td>{$info.PhoneNumber}</td>
  </tr>
  <tr>
    <th scope="row">状态文本</th>
    <td>{$info.Status}</td>
  </tr>
  <tr>
    <th scope="row">用户信息</th>
    <td>{$info.MemberInfo}</td>
  </tr>
  <tr>
    <th scope="row">标签</th>
    <td>
    {foreach item=tag from=$tags}
        <a href="./?op=22&tag={$tag.url}">{$tag.str}</a>&nbsp;&nbsp;
    {foreachelse}
    	（无）
    {/foreach}
    
    </td>
  </tr>
</table>
<p>&nbsp;</p>
<p>您的评价将有助于我们改善产品：</p>
<form method="post" action="./?op=25">
<input type="hidden" name="query" value="{$query}" id="Query" />
<table width="100%" border="0" cellspacing="0" cellpadding="0">
  <tr>
    <th width="21%" scope="row">这条信息对您有用吗？</th>
    <td width="79%">
    	<input name="useful" type="radio" id="useful0" value="0" checked="checked" />
    	<label for="useful0">无</label> 
		<input type="radio" name="useful" id="useful1" value="1" /><label for="useful1">★</label> 
        <input type="radio" name="useful" id="useful2" value="2" /><label for="useful2">★★</label> 
        <input type="radio" name="useful" id="useful3" value="3" /><label for="useful3">★★★</label> 
    </td>
  </tr>
  <tr>
    <th scope="row"><label for="comment">您的评论</label></th>
    <td><textarea name="comment" id="comment" cols="45" rows="5"></textarea></td>
  </tr>
  <tr>
    <th scope="row">&nbsp;</th>
    <td><input type="submit" name="submit" id="submit" value="提交" /></td>
  </tr>
</table>
</form>

{include file='web/footer.tpl'}
