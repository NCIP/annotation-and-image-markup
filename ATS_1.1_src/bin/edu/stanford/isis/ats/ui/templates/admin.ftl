<!DOCTYPE html>
<!-- admin.ftl -->
<html>
<head>
    <title>Admin</title>
    <link rel='stylesheet' type='text/css' href='static/ats-web.css' />
    <link rel='stylesheet' type='text/css' href='static/static.css' />
    <script type='text/javascript' src='http://ajax.googleapis.com/ajax/libs/jquery/1.6.1/jquery.min.js'></script>
</head>
<body>
 <div class='container'>
    ${loginHtml}
    <div class='span-24 last'>
        <p class='heading'>Edit Permissions</p>
    </div>
    <br />

    <div id="header" class="global-nav">
    <div class="bar">
      <div class="wrapper">
        <ul class="nav">
          <li id="nav-primary-file" class="tab"><a href='/templates/web?page=upload'><span>Publish</span></a></li>
          <li id="nav-primary-search-container" class="tab"><a href='/templates/web?page=search&type=adv-container'><span>Search Template Groups</span></a></li>
          <li id="nav-primary-search-template" class="tab"><a href='/templates/web?page=search&type=adv-template'><span>Search Template</span></a></li>
          <#--<li id="nav-primary-search-components" class="tab"><a href='/templates/web?page=search&type=adv-component'><span>Search Components</span></a></li>-->
          <li id="nav-primary-admin" class="tab"><a href='/templates/web?page=admin'><span>Administration</span></a></li>
          <#--<li id="nav-primary-help" class="tab"><a href="help.html"><span>Help</span></a></li>-->
        </ul>
      </div>
    </div>
    </div>

    <br />
    <div class='data-selector'>
        <div class='data-table'>
            ${permissionTableResult}
        </div> <!-- data-table -->
    </div> <!-- data-selector -->

  </div>

<#--
${message}

 <br />
 List all containers.
 <form method='post' action='/templates/search'>
    <input type='hidden' name='function' value='debugAllContainers'/>
    <button type='submit'>debug</button>
 </form>
-->

${message!""}
<#include "footer.ftl">
</body>
</html>