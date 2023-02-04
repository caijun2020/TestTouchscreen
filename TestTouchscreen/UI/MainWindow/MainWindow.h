/**********************************************************************
PACKAGE:        UI
FILE:           MainWindow.h
COPYRIGHT (C):  All rights reserved.

PURPOSE:        Software Main Window
**********************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "SerialDebugWidget.h"
#include "PaintWidget.h"
#include "ProfaceTouch.h"
#include "MKUTouch.h"
#include "SettingWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow();

protected:
    virtual void closeEvent(QCloseEvent *e);

private slots:
    void navigatorButtonClick();

    void touchTypeChanged(int type);

private:
    Ui::MainWindow *ui;

    // Communication models
    QSerialPort *m_serialPort;

    // UIs
    SerialDebugWidget *m_serialW;
    PaintWidget *m_paintW;
    SettingWidget *m_settingW;

    // Touch handler
    TouchAbs *m_touch;
    ProfaceTouch *m_profaceTs;
    MKUTouch *m_mkuTs;

    // Init UI
    void initUI();

    // Init object
    void initObject();

    // Add Software Start or Close to log
    void softwareStartCloseLog(bool startFlag);
};
#endif // MAINWINDOW_H
