#ifndef HEATTRANSFERLIBRARY_H
#define HEATTRANSFERLIBRARY_H

#include <iostream>
#include <string>

class HeatTransferLibrary
{
public:
    HeatTransferLibrary();
    HeatTransferLibrary(std::string const &flowType, std::string const &flowGeometry,
                        double const &rho, double const &Cp, double const &mu, double const &nu,
                        double const &k, double const &alpha, double const &Pr, double const &beta);

    double find_reynolds_number(double const &velocity, double const &characteristicLength, bool &neglectMixedBL);
    std::string determine_flow_condition();
    std::string determine_flow_condition(double const &criticalReynoldsNumber);
    void set_result_type(std::string const &resultType);
    double get_nusselt_number();
    std::string get_status();

private:
    std::string mFlowType;
    std::string mFlowGeometry;
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
    std::string status;
    bool mNeglectMixedBL;

    double mCharacteristicLength;
    double mCriticalLength;
    double mVelocity;

    void determine_if_mixed_boundary_layer();
    void find_critical_length();

    void find_nusselt_number_laminar();
    void find_nusselt_number_laminar_local();
    void set_nusselt_number_laminar_local_larger_Pr();
    void set_nusselt_number_laminar_local_smaller_Pr();
    void set_nusselt_number_laminar_average();

    void find_nusselt_number_turbulent();
    void set_nusselt_number_turbulent_local();
    void set_nusselt_number_turbulent_average();

    void find_nusselt_number_mixed();
    void set_nusselt_number_mixed_average();


};

#endif // HEATTRANSFERLIBRARY_H
