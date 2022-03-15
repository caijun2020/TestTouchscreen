#include <QApplication>
#include <QDesktopWidget>
#include <QFile>
#include <QDebug>
#include "MainWindow.h"
#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP

QString loadQss(QString filePath);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString qssFile = "./qss/LightBlue.qss";
    qssFile.prepend(QCoreApplication::applicationDirPath().append("/"));

    // Load stylesheet
    QString qss = loadQss(qssFile);
    if(!qss.isEmpty())
    {
        a.setStyleSheet(qss);
    }

    // Load conf setting
    el::Configurations conf("log.conf");
    el::Loggers::reconfigureAllLoggers(conf);

    // Fatal level do not stop program
    el::Loggers::addFlag(el::LoggingFlag::DisableApplicationAbortOnFatalLog);

    MainWindow w;
    //w.show();
    //w.move(abs(QApplication::desktop( )->width( ) - w.width()) / 2, abs(QApplication::desktop( )->height( ) - w.height()) / 3);
    w.showMaximized();

    return a.exec();
}

QString loadQss(QString filePath)
{
    QString qss = "";
    QFile qssFile(filePath);

    qssFile.open(QFile::ReadOnly);

    if(qssFile.isOpen())
    {
        qss = QLatin1String(qssFile.readAll());
        qssFile.close();
     }

    return qss;
}
