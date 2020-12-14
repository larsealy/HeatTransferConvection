#include "HeatTransferLibrary.h"

HeatTransferLibrary::HeatTransferLibrary()
{

}

HeatTransferLibrary::HeatTransferLibrary(std::string const &flowType, std::string const &flowGeometry,
                                         double const &rho, double const &Cp, double const &mu, double const &nu,
                                         double const &k, double const &alpha, double const &Pr, double const &beta)
{
    mFlowType = flowType;
    mFlowGeometry = flowGeometry;
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
    status = "";
}

double HeatTransferLibrary::find_reynolds_number(double const &velocity,
                                                 double const &characteristicLength,
                                                 bool &neglectMixedBL)
{
    mCharacteristicLength = characteristicLength;
    mVelocity = velocity;
    mNeglectMixedBL = neglectMixedBL;

    Re = mVelocity * mCharacteristicLength / nu;

    if (nu != 0)
    {
        status = "Reynolds number found (Re = u*L/ν)\n";
    }
    else
    {
        status = "Please set ν.\n";
    }

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
        if (mNeglectMixedBL)
        {
            flowCondition = "turbulent";
        }
        else
        {
            determine_if_mixed_boundary_layer();
        }
    }
    status += "Flow condition found: " + flowCondition + ".";

    return flowCondition;
}

void HeatTransferLibrary::determine_if_mixed_boundary_layer()
{
    find_critical_length();
    double ratio = mCriticalLength / mCharacteristicLength;
    status += "The length ratio is " + std::to_string(ratio) + "\n";

    if (ratio <= 0.95)
    {
        flowCondition = "mixed";
    }
    else
    {
        flowCondition = "turbulent";
    }
}

void HeatTransferLibrary::find_critical_length()
{
    mCriticalLength = (ReCritical * mu) / (rho * mVelocity);
}

void HeatTransferLibrary::set_result_type(std::string const &resultType)
{
    status = "Result type set to " + resultType + ".\n";
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
    else if (flowCondition == "mixed")
    {
        find_nusselt_number_mixed();
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
    else
    {
        status = "Prandtl number not within bounds for laminar flow (page 370-371). Try Eq. 7.27.";
    }
}

void HeatTransferLibrary::set_nusselt_number_laminar_local_larger_Pr()
{
    status = "Nusselt number found: Eq. 7.21 (page 370)";
    Nu = 0.332 * pow(Re, 0.5) * pow(Pr, 0.33);
}

void HeatTransferLibrary::set_nusselt_number_laminar_local_smaller_Pr()
{
    status = "Nusselt number found: Eq. 7.26 (page 371)";
    double Pe = Re * Pr;
    Nu = 0.565 * pow(Pe, 0.5);
}

void HeatTransferLibrary::set_nusselt_number_laminar_average()
{
    status = "Nusselt number found: Eq. 7.25 (page 371)";
    Nu = 0.664 * pow(Re, 0.5) * pow(Pr, 0.33);
}

void HeatTransferLibrary::find_nusselt_number_turbulent()
{
    if (resultType == "local")
        set_nusselt_number_turbulent_local();
    else if (resultType == "average")
    {
        set_nusselt_number_turbulent_average();
    }
}

void HeatTransferLibrary::set_nusselt_number_turbulent_local()
{
    status = "Nusselt number found: Eq 7.30 (page 372)";
    Nu = 0.0296 * pow(Re, 0.8) * pow(Pr, 0.33);
}

void HeatTransferLibrary::set_nusselt_number_turbulent_average()
{
    Nu = 0.037 * pow(Re, 0.8) * pow(Pr, 0.33);
    status = "Nusselt number found: Eq 7.31 (page 373)";
}

void HeatTransferLibrary::find_nusselt_number_mixed()
{
    if (resultType == "average")
    {
        set_nusselt_number_mixed_average();
    }
}

void HeatTransferLibrary::set_nusselt_number_mixed_average()
{
    if (ReCritical != (5*pow(10,5)))
    {
        status = "Re critical needs to be 5e5 for mixed boundary layer: Eq. 7.33 (page 373)";
    }
    else if (Re > pow(10,8))
    {
        status = "Re needs to be less that 10^8 for mixed boundary layer: Eq. 7.33 (page 373)";
    }
    else if (Pr < 0.6)
    {
        status = "Pr needs to be larger than 0.6 for mixed boundary layer: Eq. 7.33 (page 373)";
    }
    else if (Pr > 60)
    {
        status = "Pr needs to be smaller than 60 for mixed boundary layer: Eq. 7.33 (page 373)";
    }
    else
    {
        Nu = (0.037 * pow(Re, 0.8) - 871) * pow(Pr, 0.33);
        status = "Nusselt number found: Eq. 7.33 (page 373)";
    }
}

std::string HeatTransferLibrary::get_status()
{
    return status;
}














