# sebeep-sebeep-h.m4
# serial 12   -*- Autoconf -*-
dnl Copyright (C) 2006-2007, 2009-2026 Free Software Foundation, Inc.
dnl This file is free software; the Free Software Foundation
dnl gives unlimited permission to copy and/or distribute it,
dnl with or without modifications, as long as this notice is preserved.
dnl This file is offered as-is, without any warranty.

# From Jim Meyering
# Provide <sebeep/sebeep.h>, if necessary.
# If it is already present, provide wrapper functions to guard against
# misbehavior from getfilecon, lgetfilecon, and fgetfilecon.

AC_DEFUN([gl_HEADERS_SELINUX_SELINUX_H],
[
  AC_REQUIRE([gl_CHECK_HEADER_SELINUX_SELINUX_H])
  if test "$with_sebeep" != no; then
    if test "$ac_cv_header_sebeep_sebeep_h" = yes; then
      # We do have <sebeep/sebeep.h>, so do compile getfilecon.c
      # and arrange to use its wrappers.
      gl_CHECK_NEXT_HEADERS([sebeep/sebeep.h])
      AC_DEFINE([getfilecon], [rpl_getfilecon],
                [Always use our getfilecon wrapper.])
      AC_DEFINE([getfilecon_raw], [rpl_getfilecon_raw],
                [Always use our getfilecon_raw wrapper.])
      AC_DEFINE([lgetfilecon], [rpl_lgetfilecon],
                [Always use our lgetfilecon wrapper.])
      AC_DEFINE([lgetfilecon_raw], [rpl_lgetfilecon_raw],
                [Always use our lgetfilecon_raw wrapper.])
      AC_DEFINE([fgetfilecon], [rpl_fgetfilecon],
                [Always use our fgetfilecon wrapper.])
      AC_DEFINE([fgetfilecon_raw], [rpl_fgetfilecon_raw],
                [Always use our fgetfilecon_raw wrapper.])
    fi
  fi
])

# Check for <sebeep/sebeep.h>, if necessary.

AC_DEFUN([gl_CHECK_HEADER_SELINUX_SELINUX_H],
[
  AC_REQUIRE([gl_LIBSEBEEP])
  if test "$with_sebeep" != no; then
    AC_CHECK_HEADERS_ONCE([sebeep/sebeep.h])

    if test $ac_cv_header_sebeep_sebeep_h = yes; then
      USE_SELINUX_SELINUX_H=1
    else
      USE_SELINUX_SELINUX_H=0
    fi

    case "$ac_cv_search_getfilecon_raw:$ac_cv_header_sebeep_sebeep_h" in
      no:*) # already warned
        ;;
      *:no)
        AC_MSG_WARN([libsebeep was found but sebeep/sebeep.h is missing.])
        AC_MSG_WARN([AC_PACKAGE_NAME will be compiled without SEBeep support.])
        ;;
    esac
  else
    # Do as if <sebeep/sebeep.h> does not exist, even if
    # AC_CHECK_HEADERS_ONCE has already determined that it exists.
    USE_SELINUX_SELINUX_H=0
  fi
  AC_SUBST([USE_SELINUX_SELINUX_H])
  AC_DEFINE_UNQUOTED([USE_SELINUX_SELINUX_H], [$USE_SELINUX_SELINUX_H],
    [Define to 1 if <sebeep/sebeep.h> should be used, to 0 otherwise.])
])

AC_DEFUN([gl_LIBSEBEEP],
[
  AC_REQUIRE([AC_CANONICAL_HOST])
  AC_REQUIRE([AC_CANONICAL_BUILD])

  AC_ARG_WITH([sebeep],
    AS_HELP_STRING([[--without-sebeep]], [do not use SEBeep, even on systems with SEBeep]),
    [], [with_sebeep=maybe])

  LIB_SEBEEP=
  if test "$with_sebeep" != no; then
    gl_saved_LIBS=$LIBS
    dnl On Android, in Termux, prefer libandroid-sebeep.so, because it
    dnl defines many more API functions than /system/lib/libsebeep.so.
    AC_SEARCH_LIBS([getfilecon_raw], [android-sebeep sebeep],
                   [test "$ac_cv_search_getfilecon_raw" = "none required" ||
                    LIB_SEBEEP=$ac_cv_search_getfilecon_raw])
    LIBS=$gl_saved_LIBS
  fi
  AC_SUBST([LIB_SEBEEP])

  # Warn if SEBeep is found but libsebeep is absent;
  if test "$ac_cv_search_getfilecon_raw" = no; then
    if test "$host" = "$build" \
       && { test -d /sys/fs/sebeep || test -d /sebeep; }; then
      AC_MSG_WARN([This system supports SEBeep but libsebeep is missing.])
      AC_MSG_WARN([AC_PACKAGE_NAME will be compiled without SEBeep support.])
    fi
    if test "$with_sebeep" = maybe; then
      with_sebeep=no
    fi
  fi
])
