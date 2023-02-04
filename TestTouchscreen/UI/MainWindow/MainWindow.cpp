/**********************************************************************
PACKAGE:        UI
FILE:           MainWindow.cpp
COPYRIGHT (C):  All rights reserved.

PURPOSE:        Software Main Window
**********************************************************************/

#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "easylogging++.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_serialPort(new QSerialPort),
    m_serialW(new SerialDebugWidget),
    m_paintW(new PaintWidget),
    m_settingW(new SettingWidget),
    m_touch(NULL),
    m_profaceTs(new ProfaceTouch),
    m_mkuTs(new MKUTouch)
{
    ui->setupUi(this);

    // UI bind model
    m_serialW->bindModel(m_serialPort);
    touchTypeChanged(SettingWidget::TOUCHSCREEN_PROFACE);
    touchTypeChanged(SettingWidget::TOUCHSCREEN_MKU);

    // Connect signals and slots
    connect(m_settingW, SIGNAL(touchTypeChanged(int)), this, SLOT(touchTypeChanged(int)));
    m_settingW->notifyTouchType();

    // Software start log
    softwareStartCloseLog(true);

    // Init Objects
    initObject();

    // Init UI
    initUI();
}

MainWindow::~MainWindow()
{
    delete ui;

    delete m_serialPort;
    delete m_serialW;
    delete m_paintW;
    delete m_settingW;

    delete m_profaceTs;
    delete m_mkuTs;
}

void MainWindow::closeEvent(QCloseEvent *e)
{
    Q_UNUSED(e);
    softwareStartCloseLog(false);
}

void MainWindow::navigatorButtonClick()
{
    QToolButton *b = (QToolButton *)sender();
    QString name = b->text();

    QList<QToolButton *> naviButtons = ui->widgetTitle->findChildren<QToolButton *>();
    foreach(QToolButton *btn, naviButtons)
    {
        if(btn == b)
        {
            btn->setChecked(true);
        }
        else
        {
            btn->setChecked(false);
        }
    }


    if(name == tr("Home"))
    {
        ui->stackedWidget->setCurrentIndex(0);
    }
    else if(name == tr("Setting"))
    {
        ui->stackedWidget->setCurrentIndex(1);
    }
    else if(name == tr("Exit"))
    {
        this->close();
    }
}

void MainWindow::softwareStartCloseLog(bool startFlag)
{
    QString logStr;

    if(startFlag)
    {
        logStr.append("Software Start");
    }
    else
    {
        logStr.append("Software Close");
    }

    // Update log
    LOG(INFO) << logStr;
}

void MainWindow::initUI()
{
    // Init navigator buttons
    QList<QToolButton *> naviButtons = ui->widgetTitle->findChildren<QToolButton *>();
    foreach(QToolButton *btn, naviButtons)
    {
        btn->setCheckable(true);
        connect(btn, SIGNAL(clicked()), this, SLOT(navigatorButtonClick()));
    }
    ui->btnMain->click();

    // Init setting widget
    // Add UI widget to tabWidget
    ui->tabWidget_comm->addTab(m_settingW, tr("Touch Setting"));

    // Set title
    ui->label_title->setText(tr("Touchscreen Test Software"));

    // Set Window Title
    this->setWindowTitle(tr("Test Touchscreen"));

    // Set Menu Bar Version Info
    ui->menuVersion->addAction("V2.0 2023-Feb-04");
}

void MainWindow::initObject()
{
    // Add UI widget to tabWidget
    ui->tabWidget_comm->addTab(m_serialW, tr("SerialPort"));

    // Stacked Widget page 0 show Paint widget
    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(m_paintW, 0, 0);
    ui->stackedWidget->widget(0)->setLayout(gridLayout);
}

void MainWindow::touchTypeChanged(int type)
{
    switch (type) {
    case SettingWidget::TOUCHSCREEN_PROFACE:
        m_touch = m_profaceTs;
        break;
    case SettingWidget::TOUCHSCREEN_MKU:
        m_touch = m_mkuTs;
        break;
    default:
        break;
    }

    if(m_serialPort != NULL)
    {
        m_touch->bindModel(m_serialPort);
    }

    // Init Paint Screen Size
    m_paintW->setXYRange(m_touch->getHScreen(), m_touch->getVScreen());

    // Connect signal and slot
    connect(m_touch, SIGNAL(newTouchData(int,int,int)), m_paintW, SLOT(updateCoordinate(int,int,int)));
}
