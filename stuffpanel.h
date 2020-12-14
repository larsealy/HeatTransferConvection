#ifndef STUFFPANEL_H
#define STUFFPANEL_H

#include <QWidget>
#include <iostream>
#include "HeatTransferLibrary.h"

namespace Ui {
class StuffPanel;
}

class StuffPanel : public QWidget
{
    Q_OBJECT

public:
    explicit StuffPanel(QWidget *parent = nullptr);
    ~StuffPanel();
    void load_thermophysical_properties(double rho, double Cp, double mu,
                                        double nu, double k, double alpha,
                                        double Pr, double beta);
    void enable_functions_to_calculate_reynolds_number();

signals:
    void stuff_done(QString);

public slots:
//    void on_colorButton_clicked();
    void on_printData_clicked();
private slots:
    void on_findReynolds_clicked();

    void on_externalRadioButton_toggled(bool checked);

    void on_internalRadioButton_toggled(bool checked);

    void on_naturalRadioButton_toggled(bool checked);

private:
    Ui::StuffPanel *ui;
    HeatTransferLibrary *heatTransferLibrary;
    std::string flowType;
    std::string flowGeometry;

    void set_visibility_for_flow_geometry_options(bool toggle);
    void set_visibility_for_reynolds_number_features(bool toggle);
    void set_visibility_for_reynolds_number_answer(bool toggle);
    void set_visibility_for_nusselt_number_features(bool toggle);
    void set_visibility_for_nusselt_number_answer(bool toggle);
};

#endif // STUFFPANEL_H
