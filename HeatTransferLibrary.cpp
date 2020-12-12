#include "HeatTransferLibrary.h"

HeatTransferLibrary::HeatTransferLibrary()
{

}

HeatTransferLibrary::HeatTransferLibrary(double const &rho, double const &Cp, double const &mu, double const &nu,
                                         double const &k, double const &alpha, double const &Pr, double const &beta)
{
    this->rho = rho;
    this->Cp = Cp;
    this->mu = mu;
    this->nu = nu;
    this->k = k;
    this->alpha = alpha;
    this->Pr = Pr;
    this->beta = beta;

    Re = 0;
    ReCritical = 0;
    flowCondition = "";
    resultType = "";
}

double HeatTransferLibrary::find_reynolds_number(double const &velocity, double const &characteristicLength)
{
    Re = velocity * characteristicLength / nu;

    return Re;
}

std::string HeatTransferLibrary::determine_flow_condition()
{
    return determine_flow_condition(5*pow(10,5));
}

std::string HeatTransferLibrary::determine_flow_condition(double const &criticalReynoldsNumber)
{
    ReCritical = criticalReynoldsNumber;

    if (Re < ReCritical)
    {
        flowCondition = "laminar";
    }
    else
    {
        flowCondition = "turbulent";
    }

    return flowCondition;
}

void HeatTransferLibrary::set_result_type(std::string const &resultType)
{
    this->resultType = resultType;
}

double HeatTransferLibrary::get_nusselt_number()
{
    if (flowCondition == "laminar")
    {
        find_nusselt_number_laminar();
    }
    else if (flowCondition == "turbulent")
    {
        find_nusselt_number_turbulent();
    }

    return Nu;
}

void HeatTransferLibrary::find_nusselt_number_laminar()
{
    if (resultType == "local")
    {
        find_nusselt_number_laminar_local();
    }
    else if (resultType == "average")
    {
        set_nusselt_number_laminar_average();
    }
}

void HeatTransferLibrary::find_nusselt_number_laminar_local()
{
    if ((Pr > 0.6) && (Pr < 50))
    {
        set_nusselt_number_laminar_local_larger_Pr();
    }
    else if (Pr < 0.05)
    {
        set_nusselt_number_laminar_local_smaller_Pr();
    }
}

void HeatTransferLibrary::set_nusselt_number_laminar_local_larger_Pr()
{
    Nu = 0.332 * pow(Re, 0.5) * pow(Pr, 0.33);
}

void HeatTransferLibrary::set_nusselt_number_laminar_local_smaller_Pr()
{
    Nu = 0.565 * pow(Pr, 0.5);
}

void HeatTransferLibrary::set_nusselt_number_laminar_average()
{
    Nu = 0.664 * pow(Re, 0.5) * pow(Pr, 0.33);
}

void HeatTransferLibrary::find_nusselt_number_turbulent()
{
    if (resultType == "local")
        set_nusselt_number_turbulent_local();
}

void HeatTransferLibrary::set_nusselt_number_turbulent_local()
{
    Nu = 0.0296 * pow(Re, 0.8) * pow(Pr, 0.33);
}














