#include <QtCore/QCoreApplication>
#include <QAudioDeviceInfo>
#include <QObject>

#include <QDebug>



void dumpDevices(QAudio::Mode mode) {
  
  for(auto & dev_info : QAudioDeviceInfo::availableDevices(mode)) {
    QString desc = dev_info.deviceName();
    //qInfo(desc); // "Device: %s", desc);
    qInfo() << QString("device: %1").arg(desc);
  }
}
void dumpAudioDevices() 
{
  qInfo("Input devices:");
  dumpDevices(QAudio::AudioInput);
  qInfo("Output devices:");
  dumpDevices(QAudio::AudioOutput);
}


int main(int argv, char **args)
{
    QCoreApplication app(argv, args);

    dumpAudioDevices();
    
    return 0;
}
