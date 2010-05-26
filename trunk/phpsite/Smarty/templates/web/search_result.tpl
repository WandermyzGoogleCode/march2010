{include file='web/header.tpl' title='搜索结果'}

<table width="100%" border="1" cellspacing="0" cellpadding="0">
  <tr>
    <th width="15%" scope="column">手机号</th>
    <th width="25%" scope="column">名称</th>
    <th width="20%" scope="column">状态文本</th>
    <th width="20%" scope="column">用户资料</th>
    <th width="20%" scope="column">标签</th>
  </tr>
  {foreach item=row from=$dataset}
  <tr>
    <td><a href="./?op=23&phonenumber={$row.PhoneNumber}&q={$queryCodeword}">{$row.PhoneNumber}</a></td>
    <td>{$row.Name}</td>
    <td>{$row.Status|truncate:40}</td>
    <td>{$row.MemberInfo|truncate:40}</td>
    <td>
    	{foreach item=tag from=$row.Tags}
    	     <a href="./?op=22&tag={$tag|escape:'url'}">{$tag}</a>&nbsp;
    	{foreachelse}
    		（无）
    	{/foreach}
    </td>
  </tr>
  {foreachelse}
	  <tr><td colspan="5">
	  		（未找到任何满足条件的用户）
	  </td></tr>
  {/foreach}
</table>

{include file='web/footer.tpl'}
