#include "stuffpanel.h"
#include "ui_stuffpanel.h"
#include <QColorDialog>
#include <QColor>
#include <QPalette>
#include <QDoubleValidator>

StuffPanel::StuffPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StuffPanel)
{
    ui->setupUi(this);

    QDoubleValidator* doubleValidator = new QDoubleValidator;
//    ui->initialVelocity->setValidator(doubleValidator);
}

StuffPanel::~StuffPanel()
{
    delete ui;
}
void StuffPanel::on_colorButton_clicked()
{
    QColor color = QColorDialog::getColor();
    ui->selectedColor->setText(color.name());
    ui->selectedColor->setPalette(QPalette(color));
    ui->selectedColor->setAutoFillBackground(true);
}

void StuffPanel::on_printData_clicked()
{
    std::string resultType;

    if (ui->local->isChecked())
    {
        resultType = "local";
    }
    else
    {
        resultType = "average";
    }

    heatTransferLibrary->set_result_type(resultType);
    double nusseltNumber = heatTransferLibrary->get_nusselt_number();

    ui->nusseltNumberValue->setText(QString::number(nusseltNumber));

//    QString message;
//    message="Color "+ui->selectedColor->text()+"\n";
////    message+="Initial Velocity "+ui->initialVelocity->text()+"\n";
//    emit(stuff_done(message));
}

void StuffPanel::on_findReynolds_clicked()
{
    double rho = ui->densityValue->text().toDouble();
    double Cp = ui->specificHeatValue->text().toDouble();
    double mu = ui->dynamicViscosityValue->text().toDouble();
    double nu = ui->kinematicViscosityValue->text().toDouble();
    double k = ui->thermalConductivityValue->text().toDouble();
    double alpha = ui->thermalDiffusivityValue->text().toDouble();
    double Pr = ui->prandtlNumberValue->text().toDouble();
    double beta = ui->betaValue->text().toDouble();

    heatTransferLibrary = new HeatTransferLibrary(rho, Cp, mu, nu,
                                                  k, alpha, Pr, beta);

    double velocity = ui->velocityValue->text().toDouble();
    double characteristicLength = ui->characteristicLengthValue->text().toDouble();
    double reynoldsNumber = heatTransferLibrary->find_reynolds_number(velocity, characteristicLength);
    ui->reynoldsNumberValue->setText(QString::number(reynoldsNumber));

    std::string flowCondition = heatTransferLibrary->determine_flow_condition();
    ui->flowTypeValue->setText(QString::fromStdString(flowCondition));

    ui->resultType->setEnabled(true);
    ui->printData->setEnabled(true);

//    QString message2;
//    message2=ui->densityValue->text()+"\n";
//    emit(stuff_done(message2));

}
