# The problem:

```

I used the example programs from
.../qt6/examples/multimedia/audiodevices and consistently find that
the QMediaDevices method that replaced the qt5 QAudioDeviceInfo method
returns just one device.

This is not the case for the audio devices example from
..../qt5/examples/multimemdia/audiodevices .

The problem occurs with both Fedora 42 and Fedora 43. The version in
question is

```
# Test Cases

The ```run_test.sh``` script will build two console-only programs: cons5_audiodevices and cons6_audiodevices. The first uses the Qt5 API to find its input and output devices. The second uses the newer Qt6 scheme.  The latter fails to all but one input device.

The two programs cons[56]_audiodevices.cpp both started with the example code in each release. I removed all graphical components and callbacks.

# Dependencies

From what I can tell, the application requires only qtbase and qtmultimedia. 

