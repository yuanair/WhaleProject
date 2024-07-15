cd ./cmake-build-debug-ndk/bin
adb devices
adb push ./libNDKTest.so /data/local/tmp/
adb shell chmod a+x /data/local/tmp/libNDKTest.so
adb shell /data/local/tmp/libNDKTest.so