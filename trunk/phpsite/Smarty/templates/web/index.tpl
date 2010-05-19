{include file='web/header.tpl'}
Hello {$name}! <br/>

{foreach item=data from=$dataset}
    {$data.PhoneNumber}, {$data.Name}, {$data.Status} <br/>
{foreachelse}

{/foreach}

{include file='web/footer.tpl'}
