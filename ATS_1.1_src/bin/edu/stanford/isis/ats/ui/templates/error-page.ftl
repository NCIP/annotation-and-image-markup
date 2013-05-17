<!DOCTYPE html>
<html>
<head>
    <link rel='stylesheet' href='static/screen.css' type='text/css' media='screen, projection' />
    <link rel='stylesheet' href='static/ats-web.css' type='text/css' media='screen, projection' />
    <script type='text/javascript' src='http://ajax.googleapis.com/ajax/libs/jquery/1.6.1/jquery.min.js' />
    <script type='text/javascript'>
        <!-- scripts for this page. -->
    </script>
</head>
<body>
 <div class='container'>
    <div class='span-24 last'>
        <#-- This works if from /templates base -->
        <p class='heading'><a href='web'>AIM Template Service</a></p>
    </div>
    <#-- html specific to this page. -->
    <p>Had the following error.</p>

    ${errorMessage}

   <#-- put in a link to return to the main page. -->
   <#-- put in a hidden variable that indicates what page it came from -->

 	<#include "footer.ftl">
 </div>
</body>
</html>