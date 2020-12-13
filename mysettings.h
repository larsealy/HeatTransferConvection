#ifndef MYSETTINGS_H
#define MYSETTINGS_H

#include <QDialog>
#include <QAbstractButton>
#include <iostream>

namespace Ui {
class MySettings;
}

class MySettings : public QDialog
{
    Q_OBJECT

public:
    explicit MySettings(QWidget *parent = nullptr);
    ~MySettings();

    double getDensity();
    double getSpecificHeat();
    double getDynamicViscosity();
    double getKinematicViscosity();
    double getThermalConductivity();
    double getThermalDiffusivity();
    double getPrandtlNumber();
    double getBeta();


private:
    Ui::MySettings *ui;
};

#endif // MYSETTINGS_H
