#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/seokyeongkim/Downloads/VST_SDK/VSTApps/FFTPitchShift/build
  make -f /Users/seokyeongkim/Downloads/VST_SDK/VSTApps/FFTPitchShift/build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/seokyeongkim/Downloads/VST_SDK/VSTApps/FFTPitchShift/build
  make -f /Users/seokyeongkim/Downloads/VST_SDK/VSTApps/FFTPitchShift/build/CMakeScripts/ReRunCMake.make
fi

