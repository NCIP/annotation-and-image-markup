<!DOCTYPE html>
<!-- upload.ftl -->
<html>
<head>
    <title>Publish</title>
    <link rel="stylesheet" type="text/css" href="static/ats-web.css" />
    <link rel="stylesheet" type="text/css" href="static/static.css" />
    <script type="text/javascript" src="http://ajax.googleapis.com/ajax/libs/jquery/1.6.1/jquery.min.js"></script>
</head>
<body>
 <div>
    ${loginHtml}
    <div class="span-24">
        <p class="heading">Publish</p>
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

    <div id="body">
        <div class="wrapper">
            <div id="main">
                <div id="advanced-search-form">
                   	<#if isProperlyLogedIn>
                    <form id="searchForm" action="/templates/upload" enctype="multipart/form-data" method="post">
                        <input type="hidden" name="collection" value="ats_test.dbxml" />
                        <#-- <input type="hidden" name="collection" value="ats_prod.dbxml" /> --> <#-- for production replaces ats_test.dbml -->
                        <fieldset>
                            <ul class="one-column">
                                <li id="file-upload"><label>Upload an AIM Template XML file:</label>
                                <input type="file" name="xmlfile" size="40" multiple="multiple" /></li>
                                <li><span class="notice">* ATS supports AIM Template schema version v1.rv23</span></li>
                            </ul>
                        </fieldset>
                        <p class="actions">
                            <input type="submit" name="submit" value="Submit" class="btn-primary">
                            <input type="reset" name="reset" value="Reset" class="btn-primary">
                        </p>
                    </form>
                    <#else>
                    <span class="msg_left_30">* Only logged in non-guest users can upload templates.</span>
                    </#if>
                </div> <!-- id="advanced-search-form" -->
                ${outputMessage!""}
            </div> <!-- id="main" -->
       </div> <!-- class="wrapper" -->
    </div> <!-- id="body" -->
	<#include "footer.ftl">

 </div>
</body>
</html>