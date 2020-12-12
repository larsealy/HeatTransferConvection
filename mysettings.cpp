#include "mysettings.h"
#include "ui_mysettings.h"

MySettings::MySettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MySettings)
{
    ui->setupUi(this);
}

MySettings::~MySettings()
{
    delete ui;
}

QString MySettings::getMinimumText()
{
    return ui->minimum->text();
}

QString MySettings::getMaximumText()
{
    return ui->maximum->text();
}
