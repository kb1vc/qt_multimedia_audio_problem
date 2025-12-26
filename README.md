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

# What happens: 

```
# setup a fake device that should show up as an
# output device "TESTQT" but also as an input device
# "TESTQT.mon"
pactl load-module module-null-sink sink_name=TESTQT sink_properties=device.description="TESTQT"
```

Now let's run the qt5 version of the code that lists its input and output devices: 
```
fedora:qt_multimedia_audio_problem> ./build_qt5/cons5_audiodevices 
Input devices:
"device: pipewire"
"device: default"
"device: sysdefault:CARD=PCH"
"device: front:CARD=PCH,DEV=0"
"device: nx_remapped_out"
"device: RadioToModem.monitor"
"device: ModemToRadio.monitor"
"device: raop_sink.Matts-Mac-mini.local.192.168.1.244.7000.monitor"
"device: alsa_output.pci-0000_00_1f.3.analog-stereo.monitor"
"device: nx_voice_out.monitor"
"device: barney"
"device: fred.monitor"
"device: RSink.monitor"
"device: MSink.monitor"
"device: TESTQT.monitor"
Output devices:
"device: pipewire"
"device: default"
"device: sysdefault:CARD=PCH"
"device: front:CARD=PCH,DEV=0"
"device: surround21:CARD=PCH,DEV=0"
"device: surround40:CARD=PCH,DEV=0"
"device: surround41:CARD=PCH,DEV=0"
"device: surround50:CARD=PCH,DEV=0"
"device: surround51:CARD=PCH,DEV=0"
"device: surround71:CARD=PCH,DEV=0"
"device: hdmi:CARD=PCH,DEV=0"
"device: hdmi:CARD=PCH,DEV=1"
"device: hdmi:CARD=PCH,DEV=2"
"device: hdmi:CARD=PCH,DEV=3"
"device: alsa_output.pci-0000_00_1f.3.analog-stereo"
"device: RadioToModem"
"device: ModemToRadio"
"device: raop_sink.Matts-Mac-mini.local.192.168.1.244.7000"
"device: nx_voice_out"
"device: fred"
"device: RSink"
"device: MSink"
"device: TESTQT"
```
There are many devices there (this system is pretty busy and has an SDR running with a separate radio modem (wsjt).  

But note the TESTQT device in the output section, and the TESTQT.monitor in the input section.  These were created by the pactl stuff, as were the RSink and MSink devices.  The ModemToRadio and RadioToModem were created by a pipewire config file, and the "fred" and "barney" devices were created like this: 
```
> pw-loopback --capture-props='media.class=Audio/Sink node.name=fred' --playback-props='media.class=Audio/Source node.name=barney'
```

This is what happens when we try to list devices with the Qt6 version: 
```
> ./build_qt6/cons6_audiodevices 
qt.multimedia.ffmpeg: Using Qt multimedia with FFmpeg version 7.1.2 GPL version 3 or later
Failed to open VDPAU backend libvdpau_nvidia.so: cannot open shared object file: No such file or directory
libva info: VA-API version 1.22.0
libva info: Trying to open /usr/lib64/dri-nonfree/iHD_drv_video.so
libva info: Trying to open /usr/lib64/dri-freeworld/iHD_drv_video.so
libva info: Trying to open /usr/lib64/dri/iHD_drv_video.so
libva info: Found init function __vaDriverInit_1_22
libva info: va_openDriver() returns 0
libva info: VA-API version 1.22.0
libva info: Trying to open /usr/lib64/dri-nonfree/iHD_drv_video.so
libva info: Trying to open /usr/lib64/dri-freeworld/iHD_drv_video.so
libva info: Trying to open /usr/lib64/dri/iHD_drv_video.so
libva info: Found init function __vaDriverInit_1_22
libva info: va_openDriver() returns 0
Input devices:
Output devices:
"device: Built-in Audio Analog Stereo"
"device: Matt’s Mac mini"
"device: ModemSink"
"device: NoMachine Output"
"device: RadioSink"
"device: TESTQT"
```

The output side looks ok.  It is missing fred and barney and the other pipewire devices. But it does have the two devices (RadioSink and ModemSink) that were created by pactl. 

But the input side is empty.  

This is the problem. 



# Dependencies

From what I can tell, the application requires only qtbase and qtmultimedia. 
I've built both test programs under a real-live-three-dimensional Fedora 42 and Fedora 43 system. I've also built them in Docker containers. 


