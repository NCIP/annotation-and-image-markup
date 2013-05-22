#L
#  Copyright Northwestern University
#  Copyright Stanford University (ATB 1.0 and ATS 1.0)
#
#  Distributed under the OSI-approved BSD 3-Clause License.
#  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

require 'log.ph';

#
# string makepasswd(string passwd, string AEtitle)
#   encrypt a password string, using the AEtitle string
#   for the initialisation of the crypt() engine.
#   returns a one-way crypted string in hexadecimal coded form.
#
sub makepasswd # (passwd, AEtitle) returns encrypted, encoded string
{
# We derive the "salt" string for crypt (two letters) from the AEtitle
  local($salt1) = 0;
  local($salt2) = 0;
  local($temp, $salt, $crypt);
  local($aetitle) = @_[1];
  while (length($aetitle)>0)
  {
    $temp = $salt1 ^ ord($aetitle);
    $salt1 = $salt2;
    $salt2 = $temp;
    $aetitle = substr($aetitle,1);
  }
  $salt = pack("cc",$salt1, $salt2);
  $crypt = unpack("H*", crypt(@_[0], $salt));
  $crypt;
}

#
#  bool testpasswd(string cryptstring, string passwd, string AEtitle)
#    tests if the passwd/AEtitle combination matches the crypted password string
#    given as first parameter. Returns true if matching, false otherwise.
#
sub testpasswd # (encrypted_string, passwd, AEtitle) returns true if correct.
{
  local($crypt) = &makepasswd(@_[1], @_[2]);
  local($result) = (@_[0] =~ /^$crypt$/i);
  $result;
}

#
#  string passwdfilename(string AEtitle)
#    returns the absolute path / file name of the file where the
#    crypted password for the AEtitle (storage area) is (or should be) stored.
#
sub passwdfilename #(AEtitle)
{
  local($filename) = @_[0];
  if ($filename eq '') { &printlog("password.pl:passwdfilename: unknown AE title @_[0]"); }
  if ($filename !~ /\/.*/) { $filename = join('/',$prefs{'data_path'},$filename); }
  $filename = join('/',$filename,$prefs{'passwdfile'});
  $filename;
}

#
#  void writepasswd(string passwd, string AEtitle)
#    encrypts the password and writes it to file according to the AEtitle
#    (storage area).
#
sub writepasswd # (passwd, AEtitle)
{
  local($crypt) = &makepasswd(@_[0], @_[1]);
  local($filename) = &passwdfilename(@_[1]);
  if (open(PWDFILE,">$filename"))
  {
    printf(PWDFILE "<%s>\n",$crypt);
    close(PWDFILE);
  } else {
    &printlog("password.pl:writepasswd: cannot create password file for AE title @_[1]");
  }
}

#
# bool checkurlcode(string cryptstring, string AEtitle)
#   checks if the cryptstring matches the one stored in file
#   for the given storage area. This allows to check if the URL path is valid.
#
sub checkurlcode # (cryptstring, AETitle)
{
  local($crypt);
  local($filename) = &passwdfilename(@_[1]);
  if (open(PWDFILE,"<$filename"))
  {
    $crypt = <PWDFILE>;
    chop($crypt);
    close(PWDFILE);
    if ($crypt =~ /<.*>/)
    {
      $crypt =~ s/^.*<//;
      $crypt =~ s/>.*$//;
    } else {
      &printlog("password.pl:checkurlcode: cannot parse password file for AE title @_[1]");
    }
  } else {
    # If no password file available, we use an empty password string as default.
    $crypt = &makepasswd('',@_[1]);
  }
  local($result) = (@_[0] =~ /^$crypt$/i);
  $result;
}

1;
