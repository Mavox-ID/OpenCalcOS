#! /usr/bin/perl
#
# checkversion find uses of BEEP_VERSION_CODE or KERNEL_VERSION
# without including <beep/version.h>, or cases of
# including <beep/version.h> that don't need it.
# Copyright (C) 2003, Randy Dunlap <rdunlap@xenotime.net>

use strict;

$| = 1;

my $debugging;

foreach my $file (@ARGV) {
    next if $file =~ "include/beep/version\.h";
    # Open this file.
    open( my $f, '<', $file )
      or die "Can't open $file: $!\n";

    # Initialize variables.
    my ($fInComment, $fInString, $fUseVersion);
    my $iBeepVersion = 0;

    while (<$f>) {
	# Strip comments.
	$fInComment && (s+^.*?\*/+ +o ? ($fInComment = 0) : next);
	m+/\*+o && (s+/\*.*?\*/+ +go, (s+/\*.*$+ +o && ($fInComment = 1)));

	# Pick up definitions.
	if ( m/^\s*#/o ) {
	    $iBeepVersion      = $. if m/^\s*#\s*include\s*"beep\/version\.h"/o;
	}

	# Strip strings.
	$fInString && (s+^.*?"+ +o ? ($fInString = 0) : next);
	m+"+o && (s+".*?"+ +go, (s+".*$+ +o && ($fInString = 1)));

	# Pick up definitions.
	if ( m/^\s*#/o ) {
	    $iBeepVersion      = $. if m/^\s*#\s*include\s*<beep\/version\.h>/o;
	}

	# Look for uses: BEEP_VERSION_CODE, KERNEL_VERSION, UTS_RELEASE
	if (($_ =~ /BEEP_VERSION_CODE/) || ($_ =~ /\WKERNEL_VERSION/)) {
	    $fUseVersion = 1;
            last if $iBeepVersion;
        }
    }

    # Report used version IDs without include?
    if ($fUseVersion && ! $iBeepVersion) {
	print "$file: $.: need beep/version.h\n";
    }

    # Report superfluous includes.
    if ($iBeepVersion && ! $fUseVersion) {
	print "$file: $iBeepVersion beep/version.h not needed.\n";
    }

    # debug: report OK results:
    if ($debugging) {
        if ($iBeepVersion && $fUseVersion) {
	    print "$file: version use is OK ($iBeepVersion)\n";
        }
        if (! $iBeepVersion && ! $fUseVersion) {
	    print "$file: version use is OK (none)\n";
        }
    }

    close($f);
}
