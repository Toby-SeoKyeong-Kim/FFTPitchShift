#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/seokyeongkim/Downloads/VST_SDK/VSTApps/FFTPitchShift/build/vst3sdk/public.sdk/samples/vst-hosting/validator
  codesign --force --verbose --sign - /Users/seokyeongkim/Downloads/VST_SDK/VSTApps/FFTPitchShift/build/bin/Debug/validator
  cd /Users/seokyeongkim/Downloads/VST_SDK/VSTApps/FFTPitchShift/build/vst3sdk/public.sdk/samples/vst-hosting/validator
  /Users/seokyeongkim/Downloads/VST_SDK/VSTApps/FFTPitchShift/build/bin/Debug/validator -selftest
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/seokyeongkim/Downloads/VST_SDK/VSTApps/FFTPitchShift/build/vst3sdk/public.sdk/samples/vst-hosting/validator
  codesign --force --verbose --sign - /Users/seokyeongkim/Downloads/VST_SDK/VSTApps/FFTPitchShift/build/bin/Release/validator
  cd /Users/seokyeongkim/Downloads/VST_SDK/VSTApps/FFTPitchShift/build/vst3sdk/public.sdk/samples/vst-hosting/validator
  /Users/seokyeongkim/Downloads/VST_SDK/VSTApps/FFTPitchShift/build/bin/Release/validator -selftest
fi

