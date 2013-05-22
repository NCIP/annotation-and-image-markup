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
require 'isocode.ph';

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
  &page_title("Worklist Entries - '$aetitle'");
  printf("<TABLE BORDER CELLSPACING=1 WIDTH=100%>\n");
  &set_readlock("$prefs{'data_path'}/$aetitle");
  $filename = "$prefs{'data_path'}/$aetitle/$prefs{'datafile'}";
  &read_environment($filename);
  printf("<TR><TD nowrap><B>Accession No.</B></TD>\n");
  printf("<TD nowrap><B>Patient's Name</B></TD>\n");
  printf("<TD nowrap><B>Procedure Description</B></TD><TD></TD><TD></TD></TR>\n");
  @dicomfiles = ();
  if (opendir(DIRHANDLE, "$prefs{'data_path'}/$aetitle"))
  {
    $dirent = readdir(DIRHANDLE);
    while ($dirent ne '')
    {
      if ($dirent =~ /.*\.$prefs{'dicom_ext'}$/) { push(@dicomfiles, $dirent); }
      $dirent = readdir(DIRHANDLE);
    }
    closedir(DIRHANDLE);
  }
  &release_lock;

  $commandline = "$prefs{'readoviw'}";
  for (@dicomfiles) { $commandline = "$commandline $prefs{'data_path'}/$aetitle/$_"; }
  if ($#dicomfiles >= 0)
  {
    ($dummy, $overview) = split(/\\/, `$commandline`, 2);
    for (@dicomfiles)
    {
       ($accession, $name, $description, $overview) = split(/\\/,$overview, 4);
       $description=pack("H*",$description);
       if (length($description)>40) { $description = substr($description,0,40); }
       printf("<TR><TD nowrap>%s</TD>\n",&iso_to_html(pack("H*",$accession)));
       printf("<TD nowrap>%s</TD>\n",&iso_to_html(pack("H*",$name)));
       printf("<TD nowrap>%s</TD>\n",&iso_to_html($description));
       printf("<TD nowrap><A HREF=\"%s/%s/%s/%s\">update</A></TD>",
         $prefs{'workedit.pl'}, $aetitle, $passwd, unpack("H*",$_));
       printf("<TD nowrap><A HREF=\"%s/%s/%s/%s\">delete</A></TD></TR>\n",
         $prefs{'workdel.pl'}, $aetitle, $passwd, unpack("H*",$_));
       printf("</TR>\n");
    }
  }
  printf("</TABLE><p>\n");

  # Check if it is possible to create a new entry
  if (($#PATIENT_KEYS >= 0)&&($#PROCEDURESTEP_KEYS >= 0))
  {
    printf("<A HREF=\"%s/%s/%s\">Create a new worklist entry</A><p>\n",
      $prefs{'workedit.pl'}, $aetitle, $passwd);
  } else {
    printf("You cannot create a new worklist entry unless there is at least");
    printf(" one patient and one procedure step.<p>\n");
  }
  printf("<A HREF=\"%s/%s/%s\">Back to main Menu</A>\n",
      $prefs{'main.pl'}, $aetitle, $passwd);
  &page_footer;
}
