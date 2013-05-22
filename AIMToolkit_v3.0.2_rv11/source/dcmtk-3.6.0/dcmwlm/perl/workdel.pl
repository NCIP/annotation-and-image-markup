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
require 'isocode.ph';

$path_info=$ENV{'PATH_INFO'};

$aetitle = '';
$passwd = '';
$dicomfile = '';
$command = '';
if ($path_info ne '')
{
  ($dummy, $aetitle, $passwd, $dicomfile, $command, $rest) = split(/\//, $path_info);
}

if (($passwd eq '') || (! &checkurlcode($passwd, $aetitle)))
{
  # Password is incorrect.
  &page_title("Password invalid");
  printf("<A HREF=\"%s\">Click here</A> to return to main menu.\n", $prefs{'main.pl'});
  &page_footer;
} else {
  # Password is correct.
  &set_readlock("$prefs{'data_path'}/$aetitle");
  $diofile = pack("H*",$dicomfile);
  if ($command eq '')
  {
    # display warning
    &page_title("Delete Worklist Entry");

    $overview=`$prefs{'readoviw'} $prefs{'data_path'}/$aetitle/$diofile`;
    ($dummy, $accession, $rest) = split(/\\/,$overview);
    $accession = &iso_to_html(pack("H*",$accession));

    printf("You have requested the deletion of the worklist entry ");
    printf("with accession no. <b>'%s'</b>.<p>\n",$accession);
    printf("<A HREF=\"%s%s/DELETE\">Delete</A> ", $prefs{'workdel.pl'}, $path_info);
    printf("or <A HREF=\"%s%s\">Cancel</A> and return to worklist overview.\n",
      $prefs{'worklist.pl'}, $path_info);
    &page_footer;
  } else {
    # erase and back to worklist overview
    &set_writelock("$prefs{'data_path'}/$aetitle");
    unlink("$prefs{'data_path'}/$aetitle/$diofile");
    printf("Location: %s/%s/%s\n\n", $prefs{'worklist.pl'}, $aetitle, $passwd);
  }
  &release_lock;
}

