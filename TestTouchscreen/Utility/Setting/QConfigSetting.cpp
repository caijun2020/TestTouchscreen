/**********************************************************************
PACKAGE:        Utility
FILE:           QConfigSetting.cpp
COPYRIGHT (C):  All rights reserved.

PURPOSE:        Provide config file operations
                (Read from config/Write to config)
**********************************************************************/

#include "QConfigSetting.h"
#include "QUtilityBox.h"
#include <QMutexLocker>


QConfigSetting::QConfigSetting(QString fileName, bool withAbsolutePath) :
    m_configFile(fileName)
{
    if(!withAbsolutePath)
    {
        // Prepend the exe absolute path
        m_configFile.prepend(QUtilityBox::instance()->getAppDirPath());
    }

    // Setting file handler
    m_setting = new QSettings(m_configFile, QSettings::IniFormat);
}

QConfigSetting::~QConfigSetting()
{
    delete m_setting;
}

QVariant QConfigSetting::getValue(const QString &section, const QString &key)
{
    QMutexLocker locker(&m_mutex);

    QVariant ret;

    m_setting->beginGroup(section);

    if(m_setting->contains(key))
    {
        ret = m_setting->value(key);
    }

    m_setting->endGroup();

    return ret;
}

bool QConfigSetting::setValue(const QString &section, const QString &key, const QVariant &value)
{
    QMutexLocker locker(&m_mutex);

    bool ret = false;

    m_setting->beginGroup(section);

    m_setting->setValue(key, value);

    m_setting->endGroup();

    ret = true;

    return ret;
}

bool QConfigSetting::isKeyExist(const QString &section, const QString &key)
{
    QMutexLocker locker(&m_mutex);

    bool ret = false;

    m_setting->beginGroup(section);

    ret = m_setting->contains(key);

    m_setting->endGroup();

    return ret;
}
