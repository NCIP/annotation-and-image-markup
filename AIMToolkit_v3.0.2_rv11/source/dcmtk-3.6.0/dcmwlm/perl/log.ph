#L
#  Copyright Northwestern University
#  Copyright Stanford University (ATB 1.0 and ATS 1.0)
#
#  Distributed under the OSI-approved BSD 3-Clause License.
#  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

require 'prefs.ph';

#
#  void printlog(string text)
#    appends a line with date/time and the given text
#    to the log file (the path to which is defined in prefs.pl).
#
sub printlog # (string)
{
  local($sec,$min,$hour,$mday,$mon,$year,$wday,$yday,$isdst);
  ($sec,$min,$hour,$mday,$mon,$year,$wday,$yday,$isdst) = localtime;

  local($filename) = join('/',$prefs{'data_path'},$prefs{'logfile'});
  if (open(outfile, ">>$filename"))
  {
    printf(outfile "%04d-%02d-%02d %02d:%02d:%02d %s\n",
      $year+1900, $mon+1, $mday, $hour, $min, $sec, @_[0]);
    close(outfile);
  }
}

1;
