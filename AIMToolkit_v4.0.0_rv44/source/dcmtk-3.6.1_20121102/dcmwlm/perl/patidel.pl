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
require 'urldecod.ph';
require 'write.ph';
require 'checkvr.ph';

$path_info=$ENV{'PATH_INFO'};
&get_request;

$aetitle = '';
$passwd = '';
$patientid = '';
$command = '';
if ($path_info ne '')
{
  ($dummy, $aetitle, $passwd, $patientid, $command, $rest) = split(/\//, $path_info);
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
  $filename = "$prefs{'data_path'}/$aetitle/$prefs{'datafile'}";
  &read_environment($filename);
  if ($command eq '')
  {
    # display warning
    &page_title("Delete Patient");
    $decodedid = pack("H*",$patientid);
    printf("You have requested the deletion of patient ID <b>'%s'</b>.<br>\n",$decodedid);
    printf("<b>Attention:</b> Worklist entries referring to this patient will <b>not</b> be removed!<p>\n");
    printf("<A HREF=\"%s%s/DELETE\">Delete</A> ", $prefs{'patidel.pl'}, $path_info);
    printf("or <A HREF=\"%s%s\">Cancel</A> and return to patient overview.\n",
      $prefs{'patient.pl'}, $path_info);
    &page_footer;
  } else {
    # erase and back to patient overview
    &set_writelock("$prefs{'data_path'}/$aetitle");
    $decodedid = pack("H*",$patientid);
    # remove patientID key
    undef @temp;
    foreach(@PATIENT_KEYS) { if ($decodedid ne $_) { push(@temp, $_); } }
    @PATIENT_KEYS = @temp;
    # remove values
    delete $PATIENT_VALUES{"$decodedid\\name"};
    delete $PATIENT_VALUES{"$decodedid\\birthdate"};
    delete $PATIENT_VALUES{"$decodedid\\sex"};
    delete $PATIENT_VALUES{"$decodedid\\alerts"};
    delete $PATIENT_VALUES{"$decodedid\\allergies"};
    &write_environment($filename);
    printf("Location: %s/%s/%s\n\n", $prefs{'patient.pl'}, $aetitle, $passwd);
  }
  &release_lock;
}

