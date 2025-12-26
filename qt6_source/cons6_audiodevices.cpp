#include <QCoreApplication>
#include <QTextStream>
#include <QString>

#include <QAudioDevice>
// #include <QMainWindow>
#include <QMediaDevices>
#include <QObject>
#include <QtLogging>
#include <QDebug>



void dumpDevices(QList<QAudioDevice> & devs) {
  for(auto & dev_info : devs) {
    QString desc = dev_info.description();
    //qInfo(desc); // "Device: %s", desc);
    qInfo() << QString("device: %1").arg(desc);
  }
}
void dumpAudioDevices() 
{
  auto input_devs = QMediaDevices::audioInputs();
  auto output_devs = QMediaDevices::audioOutputs();
  qInfo("Input devices:");
  dumpDevices(input_devs);
  qInfo("Output devices:");
  dumpDevices(output_devs);
}

int main(int argv, char **args)
{
    QCoreApplication app(argv, args);

    dumpAudioDevices();
    
    return 0;
}
