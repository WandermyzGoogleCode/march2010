{include file='web/header.tpl'}

{$message}<br/>
{if $redirect != ''}
2秒后将自动跳转。<a href="{$redirect}">立即跳转</a>
{/if}

{include file='web/footer.tpl'}
