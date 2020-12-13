#include "mysettings.h"
#include "ui_mysettings.h"
#include <QDoubleValidator>

MySettings::MySettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MySettings)
{
    ui->setupUi(this);

    QDoubleValidator* doubleValidator = new QDoubleValidator;
    ui->kinematicViscosityValue->setValidator(doubleValidator);
}

MySettings::~MySettings()
{
    delete ui;
}

double MySettings::getDensity()
{
    return ui->densityValue->text().toDouble();
}

double MySettings::getSpecificHeat()
{
    return ui->specificHeatValue->text().toDouble();
}

double MySettings::getDynamicViscosity()
{
    return ui->dynamicViscosityValue->text().toDouble();
}

double MySettings::getKinematicViscosity()
{
    return ui->kinematicViscosityValue->text().toDouble();
}

double MySettings::getThermalConductivity()
{
    return ui->thermalConductivityValue->text().toDouble();
}

double MySettings::getThermalDiffusivity()
{
    return ui->thermalDiffusivityValue->text().toDouble();
}

double MySettings::getPrandtlNumber()
{
    return ui->prandtlNumberValue->text().toDouble();
}

double MySettings::getBeta()
{
    return ui->betaValue->text().toDouble();
}
