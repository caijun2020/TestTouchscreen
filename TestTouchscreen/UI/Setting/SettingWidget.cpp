#include "SettingWidget.h"
#include "ui_SettingWidget.h"
#include <QDebug>

const SettingWidget::COMBOX_LIST SettingWidget::touchscreen_type_combox[] =
{
    {(int)SettingWidget::TOUCHSCREEN_PROFACE, "Proface"},
    {(int)SettingWidget::TOUCHSCREEN_MKU, "MKU"},
};

SettingWidget::SettingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingWidget),
    m_settingFile("config.ini"),
    touchType(TOUCHSCREEN_PROFACE),
    screenHSize(1024),
    screenVSize(768)
{
    ui->setupUi(this);

    // Init UI elements
    initUI();

    // Default setting file
    m_setting = new QConfigSetting(m_settingFile);

    // Load Settings from ini file
    loadSettingFromIniFile();
}

SettingWidget::~SettingWidget()
{
    delete ui;
    delete m_setting;
}

void SettingWidget::notifyTouchType()
{
    // Emit signal
    emit touchTypeChanged(touchType);
}

void SettingWidget::initUI()
{
    ui->comboBox_touch->clear();

    for(uint32_t i = 0; i < sizeof(touchscreen_type_combox)/sizeof(COMBOX_LIST); i++)
    {
        ui->comboBox_touch->insertItem(i, QString(touchscreen_type_combox[i].text));
    }
}

void SettingWidget::loadSettingFromIniFile()
{
    QString section = "Touchscreen";

    if(m_setting->isKeyExist(section, "Type"))
    {
        touchType = m_setting->getValue(section, "Type").toInt();
    }
    else
    {
        m_setting->setValue(section, "Type", touchType);
    }

    if(m_setting->isKeyExist(section, "HScreen"))
    {
        screenHSize = m_setting->getValue(section, "HScreen").toInt();
    }
    else
    {
        m_setting->setValue(section, "HScreen", screenHSize);
    }

    if(m_setting->isKeyExist(section, "VScreen"))
    {
        screenVSize = m_setting->getValue(section, "VScreen").toInt();
    }
    else
    {
        m_setting->setValue(section, "VScreen", screenVSize);
    }

    // Update comboBox UI
    ui->comboBox_touch->setCurrentIndex(touchType);
}

void SettingWidget::updateSettingToFile()
{
    QString section = "Touchscreen";
    m_setting->setValue(section, "Type", touchType);
    m_setting->setValue(section, "HScreen", screenHSize);
    m_setting->setValue(section, "VScreen", screenVSize);
}

void SettingWidget::on_comboBox_touch_activated(int index)
{
    touchType = index;

    // Emit signal
    notifyTouchType();

    // Update to ini setting file
    updateSettingToFile();
}


void SettingWidget::on_pushButton_save_clicked()
{
    // Update to ini setting file
    updateSettingToFile();
}
