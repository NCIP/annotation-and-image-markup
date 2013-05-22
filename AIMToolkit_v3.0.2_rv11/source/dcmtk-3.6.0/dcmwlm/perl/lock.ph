#L
#  Copyright Northwestern University
#  Copyright Stanford University (ATB 1.0 and ATS 1.0)
#
#  Distributed under the OSI-approved BSD 3-Clause License.
#  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

require 'prefs.ph';

$fcntldata=`$prefs{'preplock'}`;
eval $fcntldata;

$fd_inuse=0;   # 0=no_lock, 1=read_lock, 2=write_lock

#
# usage: &set_readlock('pathname');
#   returns 1 if successful, 0 upon failure.
#   modifies the global variable $fd_inuse and the file descriptor fd.
#
sub set_readlock
{
  local($lockname, $last, $fcntldata);

  if ((@_ != 1)||($_[0] eq ''))
  {
    printf(stderr "error: NULL path not allowed\n");
    return 0;
  }
  $lockname = $_[0];

  if ($fd_inuse ne 0)
  {
    printf(stderr "error: nested read locks not allowed!\n");
    return 0;
  }

  $last = chop($lockname);
  if ($last eq '/')
  {
    $lockname = join('','+<',$lockname,$last,$prefs{'lockfile'});
  } else {
    $lockname = join('','+<',$lockname,$last,'/',$prefs{'lockfile'});
  }

  if (!open(fd, $lockname))
  {
     $fd_inuse = 0;
     printf(stderr "error: cannot open file %s\n",$lockname);
     return 0;
  } else {
    $fd_inuse=1;
  }

  $fcntldata = $const_RDLCK_STRUCT;

  if (-1 eq fcntl(fd,$const_F_SETLKW, $fcntldata))
  {
    printf(stderr "error: cannot set read lock on file %s\n",$lockname);
    close(fd);
    $fd_inuse = 0;
    return 0;
  }

  return 1;
}

#
# usage: &set_writelock('pathname');
#   returns 1 if successful, 0 upon failure.
#   modifies the global variable $fd_inuse and the file descriptor fd.
#
sub set_writelock
{
  local($lockname, $last, $fcntldata);

  if ((@_ != 1)||($_[0] eq ''))
  {
    printf(stderr "error: NULL path not allowed\n");
    return 0;
  }
  $lockname = $_[0];

  if ($fd_inuse eq 2)
  {
    printf(stderr "error: nested write locks not allowed!\n");
    return 0;
  }

  $last = chop($lockname);
  if ($last eq '/')
  {
    $lockname = join('','+<',$lockname,$last,$prefs{'lockfile'});
  } else {
    $lockname = join('','+<',$lockname,$last,'/',$prefs{'lockfile'});
  }

  if ($fd_inuse eq 0)
  {
    if (!open(fd, $lockname))
    {
       $fd_inuse = 0;
       printf(stderr "error: cannot open file %s\n",$lockname);
       return 0;
    }
  }

  $fcntldata = $const_WRLCK_STRUCT;

  if (-1 eq fcntl(fd,$const_F_SETLKW, $fcntldata))
  {
    printf(stderr "error: cannot set write lock on file %s\n",$lockname);
    close(fd);
    $fd_inuse = 0;
    return 0;
  }

  $fd_inuse=2;
  return 1;
}

#
# usage: &release_lock;
#   returns 1 if successful, 0 upon failure.
#   modifies the global variable $fd_inuse and the file descriptor fd.
#
sub release_lock
{
  local($lockname, $last, $fcntldata);

  if ($fd_inuse eq 0)
  {
    printf(stderr "error: no lock to release!\n");
    return 0;
  }

  $fcntldata = $const_UNLCK_STRUCT;

  if (-1 eq fcntl(fd,$const_F_SETLKW, $fcntldata))
  {
    printf(stderr "error: cannot release lock.\n");
    close(fd);
    $fd_inuse = 0;
    return 0;
  }

  $fd_inuse = 0;
  return 1;
}

1;
