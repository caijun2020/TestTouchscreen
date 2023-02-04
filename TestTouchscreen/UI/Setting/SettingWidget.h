#ifndef SETTINGWIDGET_H
#define SETTINGWIDGET_H

#include <QWidget>
#include "QConfigSetting.h"

namespace Ui {
class SettingWidget;
}

class SettingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SettingWidget(QWidget *parent = nullptr);
    ~SettingWidget();

    struct COMBOX_LIST
    {
        int index;
        const char text[50];
    };

    enum TOUCHSCREEN_TYPE
    {
        TOUCHSCREEN_PROFACE,
        TOUCHSCREEN_MKU,
        TOUCHSCREEN_COUNT
    };

    static const struct COMBOX_LIST touchscreen_type_combox[];

    // Notify actions
    void notifyTouchType();

signals:
    void touchTypeChanged(int);

private slots:
    void on_comboBox_touch_activated(int index);

    void on_pushButton_save_clicked();

private:
    Ui::SettingWidget *ui;

    QString m_settingFile;
    QConfigSetting *m_setting;  // Store current setting with ini file

    int touchType;
    int screenHSize;            //screen horizontal size
    int screenVSize;            //screen vertical size

    // Init UI elements
    void initUI();

    // Load setting from ini file
    void loadSettingFromIniFile();

    // Update setting to ini file
    void updateSettingToFile();

};

#endif // SETTINGWIDGET_H
