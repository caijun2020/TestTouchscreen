/**********************************************************************
PACKAGE:        Utility
FILE:           QConfigSetting.h
COPYRIGHT (C):  All rights reserved.

PURPOSE:        Provide config file operations
                (Read from config/Write to config)
**********************************************************************/

#ifndef QCONFIGSETTING_H
#define QCONFIGSETTING_H

#include <QSettings>
#include <QMutex>


class QConfigSetting
{
public:
    QConfigSetting(QString fileName = "config.ini", bool withAbsolutePath = false);
    virtual ~QConfigSetting();

    /*-----------------------------------------------------------------------
    FUNCTION:		getValue
    PURPOSE:		Get the value of key in section
    ARGUMENTS:		QString section, section name
                    QString key, key name
    RETURNS:		QVariant, value of key
    -----------------------------------------------------------------------*/
    QVariant getValue(const QString &section, const QString &key);

    /*-----------------------------------------------------------------------
    FUNCTION:		setValue
    PURPOSE:		Set the value of key in section
    ARGUMENTS:		QString section, section name
                    QString key, key name
                    QVariant value, the value of key
    RETURNS:		bool, true: write successfully, false: write failed
    -----------------------------------------------------------------------*/
    bool setValue(const QString &section, const QString &key, const QVariant &value);

    /*-----------------------------------------------------------------------
    FUNCTION:		isKeyExist
    PURPOSE:		Check key exist or not
    ARGUMENTS:		QString section, section name
                    QString key, key name
    RETURNS:		bool, true: exist, false: not exist
    -----------------------------------------------------------------------*/
    bool isKeyExist(const QString &section, const QString &key);

private:
    QString m_configFile;   // Path of config file

    QSettings *m_setting;  // ini setting file handler

    QMutex m_mutex; // Mutex lock

};

#endif // QCONFIGSETTING_H
