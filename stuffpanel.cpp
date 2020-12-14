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

    heatTransferLibrary = new HeatTransferLibrary();

    QDoubleValidator* doubleValidator = new QDoubleValidator;
    ui->velocityValue->setValidator(doubleValidator);
    ui->characteristicLengthValue->setValidator(doubleValidator);

    flowType = "external";
    flowGeometry = "Flat Plate";

    //    ui->FlowTypeOptions->def
    set_visibility_for_flow_geometry_options(false);
    set_visibility_for_reynolds_number_features(false);
    set_visibility_for_reynolds_number_answer(false);
    set_visibility_for_nusselt_number_features(false);
    set_visibility_for_nusselt_number_answer(false);
}

void StuffPanel::set_visibility_for_flow_geometry_options(bool toggle)
{
    ui->flowGeometry->setVisible(toggle);
    ui->flowGeometryOptions->setVisible(toggle);
}

void StuffPanel::set_visibility_for_reynolds_number_features(bool toggle)
{
    ui->velocity->setVisible(toggle);
    ui->velocityValue->setVisible(toggle);
    ui->characteristicLengthDescriptor->setVisible(toggle);
    ui->characteristicLengthValue->setVisible(toggle);
    ui->mixedTF->setVisible(toggle);
    ui->findReynolds->setVisible(toggle);
}

void StuffPanel::set_visibility_for_reynolds_number_answer(bool toggle)
{
    ui->reynoldsNumber->setVisible(toggle);
    ui->reynoldsNumberValue->setVisible(toggle);
    ui->flowTypeDescriptor->setVisible(toggle);
    ui->flowTypeValue->setVisible(toggle);
}

void StuffPanel::set_visibility_for_nusselt_number_features(bool toggle)
{
    ui->resultType->setVisible(toggle);
    ui->printData->setVisible(toggle);
}

void StuffPanel::set_visibility_for_nusselt_number_answer(bool toggle)
{
    ui->nusseltNumberDescriptor->setVisible(toggle);
    ui->nusseltNumberValue->setVisible(toggle);
}

StuffPanel::~StuffPanel()
{
    delete ui;
    delete heatTransferLibrary;
}

void StuffPanel::load_thermophysical_properties(double rho, double Cp, double mu,
                                                double nu, double k, double alpha,
                                                double Pr, double beta)
{
    delete heatTransferLibrary;
    heatTransferLibrary = new HeatTransferLibrary(flowType, flowGeometry,
                                                  rho, Cp, mu, nu,
                                                  k, alpha, Pr, beta);
}

void StuffPanel::enable_functions_to_calculate_reynolds_number()
{
    set_visibility_for_reynolds_number_features(true);

    //    ui->velocityValue->setVisible(true);
    ui->velocityValue->setEnabled(true);

    //    ui->characteristicLengthValue->setVisible(true);
    ui->characteristicLengthValue->setEnabled(true);

    //    ui->findReynolds->setVisible(true);
    ui->findReynolds->setEnabled(true);

    //    ui->mixedTF->setVisible(true);
    ui->mixedTF->setEnabled(true);
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

    QString message = QString::fromStdString(heatTransferLibrary->get_status() + "\n");
    emit(stuff_done(message));
    ui->nusseltNumberValue->setText(QString::number(nusseltNumber));

    set_visibility_for_nusselt_number_answer(true);
}

void StuffPanel::on_findReynolds_clicked()
{
    set_visibility_for_reynolds_number_answer(true);

    double velocity = ui->velocityValue->text().toDouble();
    double characteristicLength = ui->characteristicLengthValue->text().toDouble();
    bool neglectMixedBL = ui->mixedTF->isChecked();
    double reynoldsNumber = heatTransferLibrary->find_reynolds_number(velocity, characteristicLength, neglectMixedBL);
    ui->reynoldsNumberValue->setText(QString::number(reynoldsNumber));

    std::string flowCondition = heatTransferLibrary->determine_flow_condition();
    ui->flowTypeValue->setText(QString::fromStdString(flowCondition));

    QString message = QString::fromStdString(heatTransferLibrary->get_status());
    emit(stuff_done(message));

    ui->resultType->setEnabled(true);
    ui->printData->setEnabled(true);

    set_visibility_for_nusselt_number_features(true);
}

void StuffPanel::on_externalRadioButton_toggled(bool checked)
{
    flowType = "external";

    if (checked)
    {
        set_visibility_for_flow_geometry_options(true);
        ui->flowGeometryOptions->setEnabled(true);
        set_visibility_for_nusselt_number_features(false);
        set_visibility_for_nusselt_number_answer(false);
    }
}

void StuffPanel::on_internalRadioButton_toggled(bool checked)
{
    flowType = "internal";
    if (checked)
    {
        set_visibility_for_flow_geometry_options(false);
        set_visibility_for_nusselt_number_features(false);
        set_visibility_for_nusselt_number_answer(false);
    }
}

void StuffPanel::on_naturalRadioButton_toggled(bool checked)
{
    flowType = "natural";

    if (checked)
    {
        set_visibility_for_flow_geometry_options(false);
        set_visibility_for_nusselt_number_features(false);
        set_visibility_for_nusselt_number_answer(false);
    }
}
