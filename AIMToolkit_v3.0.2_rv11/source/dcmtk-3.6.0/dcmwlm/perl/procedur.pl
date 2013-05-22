#L
#  Copyright Northwestern University
#  Copyright Stanford University (ATB 1.0 and ATS 1.0)
#
#  Distributed under the OSI-approved BSD 3-Clause License.
#  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

require 'prefs.ph';
require 'layout.ph';
require 'password.ph';
require 'lock.ph';
require 'write.ph';

$path_info=$ENV{'PATH_INFO'};

$aetitle = '';
$passwd = '';
if ($path_info ne '')
{
  ($dummy, $aetitle, $passwd, $rest) = split(/\//, $path_info);
}
if (($passwd eq '') || (! &checkurlcode($passwd, $aetitle)))
{
  # Password is incorrect.
  &page_title("Password invalid");
  printf("<A HREF=\"%s\">Click here</A> to return to main menu.\n", $prefs{'main.pl'});
  &page_footer;
} else {
  # Password is correct.
  &page_title("Procedure Data - '$aetitle'");
  printf("<TABLE BORDER CELLSPACING=1 WIDTH=100%>\n");
  printf("<TR><TD nowrap><B>Procedure Title</B></TD>\n");
  printf("<TD nowrap><B>Procedure ID</B></TD></TD><TD></TD><TD></TD></TR>\n");

  &set_readlock("$prefs{'data_path'}/$aetitle");
  $filename = "$prefs{'data_path'}/$aetitle/$prefs{'datafile'}";
  &read_environment($filename);
  &release_lock;
  @keys = @PROCEDURE_KEYS;
  @values = ();
  for (@keys){ push(@values,join("\000",$PROCEDURE_VALUES{"$_\\title"},$_)); }
  for (sort(@values))
  {
    ($name, $key) = split(/\000/);
    printf("<TR><TD nowrap>%s</TD><TD nowrap>%s</TD>", $name, $key);
    printf("<TD nowrap><A HREF=\"%s/%s/%s/%s\">update</A></TD>",
      $prefs{'procedit.pl'}, $aetitle, $passwd, unpack("H*",$key));
    printf("<TD nowrap><A HREF=\"%s/%s/%s/%s\">delete</A></TD></TR>\n",
      $prefs{'procdel.pl'}, $aetitle, $passwd, unpack("H*",$key));
  }
  printf("</TABLE><p>\n");
  printf("<A HREF=\"%s/%s/%s\">Create a new procedure</A><p>\n",
      $prefs{'procedit.pl'}, $aetitle, $passwd);
  printf("<A HREF=\"%s/%s/%s\">Back to main Menu</A>\n",
      $prefs{'main.pl'}, $aetitle, $passwd);
  &page_footer;
}
