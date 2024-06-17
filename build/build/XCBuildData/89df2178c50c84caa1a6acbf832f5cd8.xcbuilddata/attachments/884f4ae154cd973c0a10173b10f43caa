#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/seokyeongkim/Downloads/VST_SDK/VSTApps/FFTPitchShift/build
  codesign --force --verbose --sign - /Users/seokyeongkim/Downloads/VST_SDK/VSTApps/FFTPitchShift/build/VST3/Debug/FFTPitchShift.vst3
  cd /Users/seokyeongkim/Downloads/VST_SDK/VSTApps/FFTPitchShift/build/bin
  /Users/seokyeongkim/Downloads/VST_SDK/VSTApps/FFTPitchShift/build/bin/Debug/moduleinfotool -create -version 1.0.0.0 -path /Users/seokyeongkim/Downloads/VST_SDK/VSTApps/FFTPitchShift/build/VST3/Debug/FFTPitchShift.vst3 -output /Users/seokyeongkim/Downloads/VST_SDK/VSTApps/FFTPitchShift/build/VST3/Debug/FFTPitchShift.vst3/Contents/Resources/moduleinfo.json
  cd /Users/seokyeongkim/Downloads/VST_SDK/VSTApps/FFTPitchShift/build/bin
  codesign -f -s - -v /Users/seokyeongkim/Downloads/VST_SDK/VSTApps/FFTPitchShift/build/VST3/Debug/FFTPitchShift.vst3/Contents/Resources/moduleinfo.json
  cd /Users/seokyeongkim/Downloads/VST_SDK/VSTApps/FFTPitchShift/build/bin
  /Users/seokyeongkim/Downloads/VST_SDK/VSTApps/FFTPitchShift/build/bin/Debug/validator /Users/seokyeongkim/Downloads/VST_SDK/VSTApps/FFTPitchShift/build/VST3/Debug/FFTPitchShift.vst3 
  cd /Users/seokyeongkim/Downloads/VST_SDK/VSTApps/FFTPitchShift/build
  /Applications/CMake.app/Contents/bin/cmake -E make_directory /Users/seokyeongkim/Library/Audio/Plug-Ins/VST3
  ln -svfF /Users/seokyeongkim/Downloads/VST_SDK/VSTApps/FFTPitchShift/build/VST3/Debug/FFTPitchShift.vst3 /Users/seokyeongkim/Library/Audio/Plug-Ins/VST3
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/seokyeongkim/Downloads/VST_SDK/VSTApps/FFTPitchShift/build
  codesign --force --verbose --sign - /Users/seokyeongkim/Downloads/VST_SDK/VSTApps/FFTPitchShift/build/VST3/Release/FFTPitchShift.vst3
  cd /Users/seokyeongkim/Downloads/VST_SDK/VSTApps/FFTPitchShift/build/bin
  /Users/seokyeongkim/Downloads/VST_SDK/VSTApps/FFTPitchShift/build/bin/Release/moduleinfotool -create -version 1.0.0.0 -path /Users/seokyeongkim/Downloads/VST_SDK/VSTApps/FFTPitchShift/build/VST3/Release/FFTPitchShift.vst3 -output /Users/seokyeongkim/Downloads/VST_SDK/VSTApps/FFTPitchShift/build/VST3/Release/FFTPitchShift.vst3/Contents/Resources/moduleinfo.json
  cd /Users/seokyeongkim/Downloads/VST_SDK/VSTApps/FFTPitchShift/build/bin
  codesign -f -s - -v /Users/seokyeongkim/Downloads/VST_SDK/VSTApps/FFTPitchShift/build/VST3/Release/FFTPitchShift.vst3/Contents/Resources/moduleinfo.json
  cd /Users/seokyeongkim/Downloads/VST_SDK/VSTApps/FFTPitchShift/build/bin
  /Users/seokyeongkim/Downloads/VST_SDK/VSTApps/FFTPitchShift/build/bin/Release/validator  /Users/seokyeongkim/Downloads/VST_SDK/VSTApps/FFTPitchShift/build/VST3/Release/FFTPitchShift.vst3
  cd /Users/seokyeongkim/Downloads/VST_SDK/VSTApps/FFTPitchShift/build
  /Applications/CMake.app/Contents/bin/cmake -E make_directory /Users/seokyeongkim/Library/Audio/Plug-Ins/VST3
  ln -svfF /Users/seokyeongkim/Downloads/VST_SDK/VSTApps/FFTPitchShift/build/VST3/Release/FFTPitchShift.vst3 /Users/seokyeongkim/Library/Audio/Plug-Ins/VST3
fi

