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

private:
    Ui::StuffPanel *ui;
    HeatTransferLibrary *heatTransferLibrary;
};

#endif // STUFFPANEL_H
