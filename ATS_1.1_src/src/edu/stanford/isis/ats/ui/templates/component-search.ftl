<!DOCTYPE html>
<!-- component-search.ftl -->
<html>
<head>
    <title>Component Search</title>
    <link rel='stylesheet' type='text/css' href='static/ats-web.css' />
    <link rel='stylesheet' type='text/css' href='static/static.css' />
    <script type='text/javascript' src='http://ajax.googleapis.com/ajax/libs/jquery/1.6.1/jquery.min.js'></script>
</head>
<body>
    <div>
        ${loginHtml}
        <div class='span-24'>
            <p class='heading'>Component Search</p>
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
        <div id='body'>
            <div class='wrapper'>
                <div id='main'>
                    <div id='advanced-search-form'>
                        <form id='searchForm' action='/templates/search' method='post'>
                            <input type='hidden' name='function' value='getAdvancedTemplate' />
                            <fieldset>

<#-- Replace with components --

                                <ul>
                                    <li><label>Template Name:</label>
                                        <input type='text' name='tn' size='20'/></li>
                                    <li><label>Template Code Desc:</label>
                                        <input type='text' name='tcd' size='20'/></li>
                                    <li><label>Template Description:</label>
                                        <input type='text' name='td' size='20'/></li>
                                    <li><label>Template Author:</label>
                                        <input type='text' name='ta' size='20'/></li>
                                </ul>

                                <ul>
                                    <li><label>Disease:</label>
                                        <input type='text' name='d' size='20'/></li>
                                    <li><label>Body Part:</label>
                                        <input type='text' name='bp' size='20'/></li>
                                    <li><label>Modality:</label>
                                        <input type='text' name='m' size='20'/></li>
                                </ul>

-->

                            </fieldset>

                            <p class='actions'>
                                <input class='btn-primary' type='submit' value='Search' />
                                <input class='btn-primary' type='reset' value='Reset' />
                            </p>
                        </form>
                    </div> <!-- id=advanced-search-form -->
                </div> <!-- id=main -->
                <br />
                <div class='data-selector'>
                    <div class='data-table'>
                        ${resultsTableHtml}
                    </div> <!-- data-table -->
                </div> <!-- data-selector -->
            </div> <!-- class=wrapper -->
        </div> <!-- id=body -->
	    <#include "footer.ftl">
    </div>
</body>
</html>