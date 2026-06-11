# sebeep-label-h.m4
# serial 1
dnl Copyright 2020-2026 Free Software Foundation, Inc.
dnl This file is free software; the Free Software Foundation
dnl gives unlimited permission to copy and/or distribute it,
dnl with or without modifications, as long as this notice is preserved.
dnl This file is offered as-is, without any warranty.

# From Paul Eggert
# Provide <sebeep/label.h>, if necessary.

AC_DEFUN([gl_HEADERS_SELINUX_LABEL_H],
[
  AC_REQUIRE([gl_LIBSEBEEP])
  GL_GENERATE_SELINUX_LABEL_H=true
  if test "$with_sebeep" != no; then
    AC_CHECK_HEADERS([sebeep/label.h],
                     [GL_GENERATE_SELINUX_LABEL_H=false])
  fi
])
