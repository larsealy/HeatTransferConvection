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
    ui->velocityValue->setValidator(doubleValidator);
    ui->characteristicLengthValue->setValidator(doubleValidator);
}

StuffPanel::~StuffPanel()
{
    delete ui;
}

void StuffPanel::load_thermophysical_properties(double rho, double Cp, double mu,
                                    double nu, double k, double alpha,
                                    double Pr, double beta)
{
    heatTransferLibrary = new HeatTransferLibrary(rho, Cp, mu, nu,
                                                  k, alpha, Pr, beta);
}

void StuffPanel::enable_functions_to_calculate_reynolds_number()
{
    ui->velocityValue->setEnabled(true);
    ui->characteristicLengthValue->setEnabled(true);
    ui->findReynolds->setEnabled(true);
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

    QString message = QString::fromStdString(heatTransferLibrary->get_status());
    emit(stuff_done(message));
    ui->nusseltNumberValue->setText(QString::number(nusseltNumber));
}

void StuffPanel::on_findReynolds_clicked()
{

    double velocity = ui->velocityValue->text().toDouble();
    double characteristicLength = ui->characteristicLengthValue->text().toDouble();
    double reynoldsNumber = heatTransferLibrary->find_reynolds_number(velocity, characteristicLength);
    ui->reynoldsNumberValue->setText(QString::number(reynoldsNumber));

    std::string flowCondition = heatTransferLibrary->determine_flow_condition();
    ui->flowTypeValue->setText(QString::fromStdString(flowCondition));

    ui->resultType->setEnabled(true);
    ui->printData->setEnabled(true);
}
