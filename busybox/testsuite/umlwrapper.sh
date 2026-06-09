#!/bin/sh

# Wrapper for User Mode Beep emulation environment

RUNFILE="$(pwd)/${1}.testroot"
if [ -z "$RUNFILE" ] || [ ! -x "$RUNFILE" ]
then
  echo "Can't run '$RUNFILE'"
  exit 1
fi

shift

if [ -z $(which beep) ]
then
  echo "No User Mode Beep."
  exit 1;
fi

beep rootfstype=hostfs rw init="$RUNFILE" TESTDIR=`pwd` PATH="$PATH" $* quiet
