<!DOCTYPE html>
<!-- login.ftl -->
<html>
<head>
    <title>AIM Template Service Login</title>
    <link rel="stylesheet" href="static/ats-web.css" type="text/css" media="screen, projection" />
    <script type="text/javascript" src="http://ajax.googleapis.com/ajax/libs/jquery/1.6.1/jquery.min.js"></script>
</head>
<body>
 <div class="container">
    <div class="span-24">
    	<div class="logo"></div>
        <p class="heading">AIM Template Service</p>
    </div>
    <div id="body">
        <div class="wrapper">
            <div id="main">
		        <div id="loginSection" style="display:none">
		            <form class="loginForm" action="/templates/login" method="post">
		                <table id="login">
		                    <tr><td style="text-align: right;">Username:</td><td><input type="text" id="user" name="user" size="15"></td></tr>
		                    <tr><td style="text-align: right;">Password:</td><td><input type="password" id="pass" name="pass" size="15"></td></tr>
		                    <tr><td style="text-align: right;"><input type="checkbox" name="guest" /></td><td> Login as guest</td></tr>
		                    <tr><td></td><td><input type="submit" value="Sign in"></td></tr>
		                </table>
		            </form>
		        </div>
            </div> <!-- id="main" -->
       </div> <!-- class="wrapper" -->
    </div> <!-- id="body" -->
    <div id="footer">
        <div class="wrapper">
        	<div id="main">
        		<br />
        		<br />
    			<a href="https://wiki.nci.nih.gov/display/AIM/AIM+Template+Service+User%27s+Guide#AIMTemplateServiceUsersGuide-RegisteringforacaGridAccount" target="_blank">How to Create a User Account</a> |
    			<a href="https://wiki.nci.nih.gov/display/AIM/AIM+Template+Service+User%27s+Guide" target="_blank">User Manual</a>
    		</div> <!-- id="main" -->
    	</div> <!-- id="wrapper" -->
    </div> <!-- id="footer" -->
 </div>
 <script type="text/javascript">
        <#-- make things fade-in here. -->
        $(document).ready(function() {
            // put all your jQuery goodness in here.
            $("#loginSection").fadeIn(1000); // fade in
            $("#user").focus();
         });
 </script>
</body>
</html>