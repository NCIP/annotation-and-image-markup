#L
#  Copyright Northwestern University
#  Copyright Stanford University (ATB 1.0 and ATS 1.0)
#
#  Distributed under the OSI-approved BSD 3-Clause License.
#  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

require 'prefs.ph';

#
#  void page_title(string title)
#    creates a HTML header (with given title) for a dcmwlm WWW Page.
#
sub page_title
{
# ---------------------------------------------------
print <<EOF;
Content-type: text/html

<HTML>
<HEAD>
<TITLE>
DICOM Basic Worklist Management
</TITLE>
</HEAD>

<BODY>
<CENTER>
EOF
# ---------------------------------------------------
  printf("<IMG SRC = \"%s\"></IMG>\n",$prefs{'offis_gif'});
  printf("<H3>DICOM Basic Worklist Management</H3>\n");
  printf("<H1>%s</H1></CENTER><HR><P>\n\n",@_[0]);
}

#
#  void page_footer()
#    creates a HTML footer for a dcmwlm WWW Page.
#
sub page_footer
{
# ---------------------------------------------------
print <<EOF;
<P>
<HR>
<CENTER><SMALL>&#169;1996 OFFIS /
Carl-von-Ossietzky Universit&auml;t Oldenburg</SMALL></CENTER>
</BODY>
</HTML>
EOF
}

1;
