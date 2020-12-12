#ifndef HEATTRANSFERLIBRARY_H
#define HEATTRANSFERLIBRARY_H

#include <iostream>


class HeatTransferLibrary
{
public:
    HeatTransferLibrary();
    HeatTransferLibrary(double const &rho, double const &Cp, double const &mu, double const &nu,
                        double const &k, double const &alpha, double const &Pr, double const &beta);

    double find_reynolds_number(double const &velocity, double const &characteristicLength);
    std::string determine_flow_condition();
    std::string determine_flow_condition(double const &criticalReynoldsNumber);
    void set_result_type(std::string const &resultType);
    double get_nusselt_number();

private:
    double rho;
    double Cp;
    double mu;
    double nu;
    double k;
    double alpha;
    double Pr;
    double beta;

    double Re;
    double Nu; //Nusselt Number
    double ReCritical;
    std::string flowCondition;
    std::string resultType;

    void find_nusselt_number_laminar();
    void find_nusselt_number_laminar_local();
    void set_nusselt_number_laminar_local_larger_Pr();
    void set_nusselt_number_laminar_local_smaller_Pr();
    void set_nusselt_number_laminar_average();

    void find_nusselt_number_turbulent();
    void set_nusselt_number_turbulent_local();


};

#endif // HEATTRANSFERLIBRARY_H
