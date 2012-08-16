<!DOCTYPE html>
<!-- admin-change.ftl -->
<html>
<head>
    <title>Admin Change</title>
    <link rel='stylesheet' type='text/css' href='static/ats-web.css' />
    <link rel='stylesheet' type='text/css' href='static/static.css' />
    <script type='text/javascript' src='http://ajax.googleapis.com/ajax/libs/jquery/1.6.1/jquery.min.js'></script>
</head>
<body>
 <div class='container'>
    ${loginHtml}
    <div class='span-24 last'>
        <p class='heading'>Change Template Group</p>
        <p class='sub-heading'>${templateDocName}</p>
    </div>
    <br />

    ${containerName}
    <br />
<#--
    <div id="header" class="global-nav">
        <div class="bar">
          <div class="wrapper">
            <ul class="nav">
              <li id="nav-primary-file" class="tab"><a href='/templates/web?page=upload'><span>Publish</span></a></li>
              <li id="nav-primary-search-container" class="tab"><a href='/templates/web?page=search&type=adv-container'><span>Search Template Groups</span></a></li>
              <li id="nav-primary-search-template" class="tab"><a href='/templates/web?page=search&type=adv-template'><span>Search Template</span></a></li>
              <li id="nav-primary-search-components" class="tab"><a href='/templates/web?page=search&type=adv-component'><span>Search Components</span></a></li>
              <li id="nav-primary-admin" class="tab"><a href='/templates/web?page=admin'><span>Administration</span></a></li>
            </ul>
          </div>
        </div>
    </div>
-->

    <br />
    <!-- Some HTML needs to be added here to change the edit group. -->

	<div id='body'>
	<div class='wrapper'>
	<div id='main'>
		<div id='advanced-search-form'>
		    <form id='admin-change' action='admin?function=change' method='post'>
		
		        <input type='hidden' name='uid' value='${uid}' />
		        <input type='hidden' name='function' value='change' />
		
		        <fieldset>
		            <ul>
		                <li>
		                    <label>Permission: </label>
		                    <select name='permission'>
		                        <option value="public"<#if permission?lower_case == 'public'> selected="selected"</#if>>Public</option>
		                        <option value="private"<#if permission?lower_case == 'private'> selected="selected"</#if>>Private</option>
		                        <#-- <option value="group">Group</option> -->
		                    </select>
		                </li>
		                <li>
		                    <label>Allowed Users: </label>
		                    <input type='text' name='allowed-user' value='${allowedUsers}' title='Comma-separated list of user names'/>
		                </li>
		            </ul>
		        </fieldset>
		
		        <p class='actions'>
		            <input class='btn-primary' type='submit' value='Change' title='Save Changes' />
		            <input class='btn-primary' type='reset' value='Reset' title='Reset Changes' />
		            <input class='btn-primary' name='btnCancel' type='submit' value='Cancel' title='Cancel Changes and Return' />
		        </p>
		
		    </form>
		
		    <form id='admin-delete' action='admin?function=delete' method='post'>
		
		        <input type='hidden' name='uid' value='${uid}' />
		        <input type='hidden' name='function' value='delete' />
		
				<#--
		        <fieldset>
		            <ul>
		                <li>
		                    <label>Delete:</label>
		                    <input type='checkbox' name='deletefile' value='yes' />
		                </li>
		            </ul>
		        </fieldset>
		        -->
		        
		        <p class='actions'>
		            <input class='btn-primary' type='submit' value='Delete Template' title='Delete Current Template Document' 
		            onclick='return confirm("Do you want to delete ${templateDocName}?");'/>
		        </p>
		
		    </form>
	    
		</div><!-- id-advanced-search-form -->
	
	</div><!-- id-main -->
	</div><!-- class-wrapper -->
	</div><!-- id-body -->
	<#include "footer.ftl">
  </div>
</body>
</html>