<!DOCTYPE html>
<!-- adv-container-search.ftl -->
<html>
<head>
    <title>Advanced Container Search</title>
    <link rel='stylesheet' type='text/css' href='static/ats-web.css' />
    <link rel='stylesheet' type='text/css' href='static/static.css' />
    <script type='text/javascript' src='http://ajax.googleapis.com/ajax/libs/jquery/1.6.1/jquery.min.js'></script>
</head>
<body>
    <div>
        ${loginHtml}
        <div class='span-24'>
            <p class='heading'>Template Group Search</p>
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
                            <input type='hidden' name='function' value='getAdvancedContainer' />

                            <fieldset>
                                <ul>
                                    <li><label>Container Name:</label>
                                        <input type='text' name='cn' size='20' /></li>
                                    <li><label>Container Description:</label>
                                        <input type='text' name='cd' size='20' /></li>
                                    <li><label>Container Author:</label>
                                        <input type='text' name='ca' size='20' /></li>
                                </ul>
                                <ul>
                                    <li><label>Disease:</label>
                                        <input type='text' name='d' size='20' /></li>
                                    <li><label>Body Part:</label>
                                        <input type='text' name='bp' size='20' /></li>
                                </ul>
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