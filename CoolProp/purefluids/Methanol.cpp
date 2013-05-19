#include "CoolProp.h"
#include <vector>
#include "CPExceptions.h"
#include "FluidClass.h"
#include "Methanol.h"

MethanolClass::MethanolClass()
{
	double n[] = {0, -2.80062505988E+00, 1.25636372418E+01, -1.30310563173E+01, 3.26593134060E+00, -4.11425343805E+00, 3.46397741254E+00, -8.36443967590E-02, -3.69240098923E-01, 3.13180842152E-03, 6.03201474111E-01, -2.31158593638E-01, 1.06114844945E-01, -7.92228164995E-02, -4.22419150975E-05, 7.58196739214E-03, -2.44617434701E-05, 1.15080328802E-06, -1.25099747447E+01, 2.70392835391E+01, -2.12070717086E+01, 6.32799472270E+00, 1.43687921636E+01, -2.87450766617E+01, 1.85397216068E+01, -3.88720372879E+00, -4.16602487963E+00, 5.29665875982E+00, 5.09360272812E-01, -3.30257604839E+00, -3.11045210826E-01, 2.73460830583E-01, 5.18916583979E-01, -2.27570803104E-03, 2.11658196182E-02, -1.14335123221E-02, 2.49860798459E-03, -2.03082179968E-02, 1.18633328180E-03, -1.10096601940E-03, 4.45237953531E-04, -1.70439564392E-03, 3.33949287490E-11, -9.56134921098E-11, 1.58312814197E-11};
	double d[] = {0, 1, 1, 1, 1, 2, 2, 2, 2, 2, 3, 3, 3, 4, 4, 5, 6, 7, 1, 1, 1, 1, 2, 2, 2, 2, 3, 4, 5, 5, 5, 5, 6, 9, 6, 6, 4, 1, 1, 1, 1, 1, 3, 3, 3};
	double t[] = {0, 0, 1, 2, 3, 1, 2, 3, 4, 6, 0, 3, 4, 0, 7, 1, 6, 7, 1, 2, 3, 4, 1, 2, 3, 5, 1, 2, 1, 2, 4, 5, 2, 5, 9, 14, 19, 0, 0, 0, 0, 0, 0, 0, 0};
	double l[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 4, 4, 6, 2, 3, 2, 4, 2, 3, 2, 4};
	double a[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3.894074564651700, 3.894074564651700, 3.894074564651700, 3.894074564651700, 3.894074564651700, 23.064903190629300, 23.064903190629300, 23.064903190629300};
	double g[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.0173351022305, 1.0173351022305, 1.0173351022305, 1.0173351022305, 1.0173351022305, 1.0173351022305, 1.0173351022305, 1.0173351022305, 1.0173351022305, 1.0173351022305, 1.0173351022305, 1.0173351022305, 1.0173351022305, 1.0173351022305, 1.0173351022305, 1.0173351022305, 1.0349707102304, 1.0349707102304, 1.0529120332978, 4.069340408922090, 8.208920156211850, 9.156015920074710, 83.832627528661600, 16.277361635688400, 27.705105527215000, 16.277361635688400, 264.952501818980000};

    // Critical parameters
    crit.rho = 8.6*32.04216;
    crit.p = 8103.5;
    crit.T = 512.6;
    crit.v = 1.0/crit.rho;

	reduce.rho = 8.78517*32.04216;
    reduce.p = 8103.5;
    reduce.T = 513.38;
    reduce.v = 1.0/crit.rho;

	preduce = &reduce;

    // Other fluid parameters
    params.molemass = 32.04216;
    params.Ttriple = 175.61;
	params.ptriple = 0.00018629;
    params.accentricfactor = 0.5625;
    params.R_u = 8.31448;

    // Limits of EOS
	limits.Tmin = params.Ttriple;
    limits.Tmax = 500.0;
    limits.pmax = 100000.0;
    limits.rhomax = 1000000.0*params.molemass;    

	// Residual part
    phirlist.push_back(new phir_power(n,d,t,l,1,17,45));
	phirlist.push_back(new phir_exponential(n,d,t,l,g,18,36,45));
	phirlist.push_back(new phir_exponential2(n,d,l,a,g,37,44,45));

	// Ideal-gas part
	const double f0[]={0.0, 2.49667488720, 2.90079118498, -62.5713535015, 10.9926773951, 18.3368299465, -16.3660043791, -6.22323476219, 2.80353628228, 1.07780989422, 0.969656970177};
    const double g0[]={0.0, 0, 0, 0, 4.11978538315, 3.26499998052, 3.76946349682, 2.93149354474, 8.22555789084, 10.3162789084, 0.532489267209};
	phi0list.push_back(new phi0_power(f0[1], 0));
	phi0list.push_back(new phi0_power(f0[3], 1));
	phi0list.push_back(new phi0_logtau(f0[2]));
	phi0list.push_back(new phi0_Planck_Einstein3(f0,g0,4,10,11));

    name.assign("Methanol");
    aliases.push_back(std::string("Methanol"));
    REFPROPname.assign("METHANOL");

	BibTeXKeys.EOS = "deReuck-BOOK-1993";
	BibTeXKeys.SURFACE_TENSION = "Mulero-JPCRD-2012";
}

double MethanolClass::psat(double T)
{
    const double t[]={0, 1, 1.5, 2, 2.5};
    const double N[]={0, -8.8738823, 2.3698322, -10.852598, -0.12446396};
    double summer=0,theta;
    theta=reduce.T/T-1;
    for (int i=1;i<=5;i++)
    {
        summer += N[i]*pow(theta,t[i]);
    }
    return reduce.p*exp(T/reduce.T*summer);
}

double MethanolClass::rhosatL(double T)
{
    const double t[] = {0, 1.0/3.0, 2.0/3.0, 4.0/3.0, 11.0/3.0, 13.0/3.0};
    const double N[] = {0, 1.8145364, 1.2703194, -1.0182657, 2.7562720, -1.8958692};
    double summer=0,theta;
    theta=1-T/reduce.T;
	for (int i=1; i<=5; i++)
	{
		summer += N[i]*pow(theta,t[i]);
	}
	return reduce.rho*(summer+1);
}

double MethanolClass::rhosatV(double T)
{
    // Maximum absolute error is 0.370753 % between 175.610001 K and 513.379990 K
    const double t[] = {0, 0.16666666666666666, 0.3333333333333333, 0.5, 0.6666666666666666, 0.8333333333333334, 1.0, 1.1666666666666667, 1.3333333333333333, 1.5, 2.0, 2.3333333333333335, 2.8333333333333335, 3.3333333333333335, 4.166666666666667, 4.833333333333333, 5.833333333333333, 6.333333333333333, 7.333333333333333, 8.5, 9.833333333333334, 11.333333333333334, 12.833333333333334, 15.666666666666666, 18.666666666666668, 21.666666666666668};
    const double N[] = {0, 7597.1931157028366, -302294.66965590609, 4388396.8619273659, -33603221.401948757, 154437053.95209551, -445246674.15078759, 795873412.58213127, -810870583.94155431, 357750028.59211421, 87423503.387399897, -330273149.09998244, 627733578.63101625, -833167128.85553205, 1457124162.2768552, -2420510495.7178898, 6120215016.4571819, -7389022540.083499, 4611943493.9085159, -3397415663.398644, 2439723597.0041828, -1604131016.1799223, 755743289.06624866, -215370091.3594358, 95044773.686583579, -29267867.091564715};
    double summer=0,theta;
    theta=1-T/reduce.T;	
	for (int i=1; i<=25; i++)
	{
		summer += N[i]*pow(theta,t[i]);
	}
	return reduce.rho*exp(reduce.T/T*summer);
}
double MethanolClass::surface_tension_T(double T)
{
	// Mulero, JPCRD 2012
	return 0.22421*pow(1-T/reduce.T,1.3355) - 0.21408*pow(1-T/reduce.T,1.677) + 0.083233*pow(1-T/reduce.T,4.4402);
}