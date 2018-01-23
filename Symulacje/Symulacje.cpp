#include <iostream>
#include <math.h>
#include <time.h>

using std::cout;
using std::endl;
//============== do statystyk==========================================================

short   ile_razy_sklep = 0,
		ile_razy_nsklep = 0,
		ile_razy_jedno = 0,
		ile_razy_dwa = 0,
		ile_razy_trzy = 0;



//===================pomocnicze========================================================
double los = 0.0,calk_czas=0.0,czas_zmyw=0.0,czas_sklep=0.0;
short dania = 0;
//===========losowanie=========================================================================
double losuj() 
{
	return  (double)rand() / RAND_MAX;
}

//=======rozklady=========================================================================
double rozk_Norm(double sigma, double mi) { // sigma odchylenie mi - srodek przedz
	double r1 = losuj(), r2 = losuj();

	double R = sqrt(-2 * log(r1));
	double theta = 2.0 * 3.14159 * r2;
	double Z = R * cos(theta);

	return Z * sigma + mi;
}

double rozk_Wyklad(double lambda, double przesuniecie)
{
	return (-1.0 / lambda) * log(losuj()) + przesuniecie;
}

double rown(double a, double b)// a-poczatek przedzialu, b-koniec
{
	return a + (losuj()*(b - a));
}


//==============================================================================
short ile_Dan(double jedno, double dwa, double trzy) 
// z rozkl dyskretnego prawd. 0,3 0,5 0,2 (w fun( 0.3,0.8,1)
//okresla z konkretnym prawd. ilu daniowy bedzie obiad
{
	los = losuj();
	if (los <= jedno)
	{
		dania = 1;
		ile_razy_jedno++;
	}
	else if (los <= dwa) {
		dania = 2;
		ile_razy_dwa++;
	}
	else if (los <= trzy) {
		dania = 3;
		ile_razy_trzy++;

	}
	//cout << "Dania= " << dania << endl;
	return dania;
}


void do_Sklepu(double tak, double nie)
// z rozkl dyskretnego 
//okresla na podstawie okreslonego prawd. czy musimy isc do sklepu,
//jesli tak, dodaje do calkowitego czasu wartosc wysymulowana z rozkl norm.
//ilosc dan ma znaczenie( wiecej dan, prawd. rosnie, wiecej dan, dluzsze zakupy)
{
	czas_sklep = 0.0;

	los = losuj();
	if (los <= tak)
	{
		ile_razy_sklep++;
		switch (dania)
		{
		case 1:
			czas_sklep= rozk_Norm(5, 20);
			calk_czas += czas_sklep;
			calk_czas += 3;
			break;
		case 2:
			czas_sklep = rozk_Norm(10, 40);
			calk_czas += czas_sklep;
			calk_czas += 3;
			break;
		case 3:
			czas_sklep = rozk_Norm(15, 70);
			calk_czas += czas_sklep;
			calk_czas += 3;
			break;
		}			
	}
	else if (los <= nie) 
	{
		ile_razy_nsklep++;
		calk_czas += 3;
	}
	//cout << "czas_sklep= " << czas_sklep << endl;
	//return dania;
}


void ile_Zmywania(double malo, double srednio, double duzo)
//z rozkladu dyskretnego z pstwem losowanym z rozkladu rownomiernego
//okresle ile zmywania trzeba wykonac przed/po przygotowaniu obiadu
//
{
	los = losuj();

	if (los <= malo)
	{
		czas_zmyw= rozk_Wyklad(1,5);
		calk_czas += czas_zmyw;

	}
	else if (los <= srednio)
	{
		czas_zmyw += rozk_Wyklad(1.5,12);
		calk_czas += czas_zmyw;
	}
	else if (los <= duzo)
	{
		czas_zmyw += rozk_Wyklad(2,20);
		calk_czas += czas_zmyw;
	}
	//cout << "Czas_zmyw= " << czas_zmyw << endl;
}


void gotowanie_Dodatkow()
//z rozkl rownomiernego o roznych przedzialch w zaleznosci od ilosci dan
//
{
	double tmp = 0.0;

	switch (dania)
	{
	case 1:

		tmp= rown(8, 10);
		calk_czas += tmp;
		break;

	case 2:
		tmp = rown(15, 25);
		calk_czas += tmp;
		break;

	case 3:
		tmp = rown(20, 40);
		calk_czas += tmp;
		break;

	}
	//cout << "Przyg_dod= " << tmp << endl;


}


double calosc()
{
	//wyliczy ile czasu potrzebne bedzie na wszystko

	short dania = ile_Dan(0.3, 0.8, 1);
	double sklep_tak = 0.0, sklep_nie = 0.0;

	switch (dania)
	{
	case 1:
		sklep_tak = 0.2;
		sklep_nie = 1;
		break;
	case 2:
		sklep_tak = 0.6;
		sklep_nie = 1;
		break;
	case 3:
		sklep_tak = 0.8;
		sklep_nie = 1;
		break;
	}

	do_Sklepu(sklep_tak, sklep_nie);

	double mZmyw = rown(0,1), sZmyw=rown(0,(1-mZmyw)),dZmyw=1-(mZmyw+sZmyw);// malo losowane z prezdz (0,1), srednio (0,malo), duzo = 1- (malo+srednio)


	ile_Zmywania(mZmyw, mZmyw + sZmyw, mZmyw + sZmyw + dZmyw); //sumujemy do 1 

	gotowanie_Dodatkow();

	return calk_czas;

}


int main()
{
	srand(time(NULL));

	//double mZmyw = rown(0, 1), sZmyw = rown(0, (1 - mZmyw)), dZmyw = 1 - (mZmyw + sZmyw);

	
	for(int i=0;i<2000;i++)
	{
		//mZmyw = rown(0, 1), sZmyw = rown(0, (1 - mZmyw)), dZmyw = 1 - (mZmyw + sZmyw);
		//double x = rown(20,40);

		//calk_czas = 0;
		//cout << x << endl; //mZmyw<<"   "<<sZmyw<<"  "<<dZmyw << "  " <<mZmyw+sZmyw+dZmyw <<endl;
		cout << calosc() << endl;
		//ile_Zmywania(0.3, 0.8, 1);
		//cout <<"Calk_czas:" <<calk_czas<<"  ilosc dan "<<dania<<"  czas w sklepie "<< czas_sklep <<"  Czas_zmyw "<< czas_zmyw << endl;
		//system("pause");
		calk_czas = 0.0;
		//system("pause");

	}
	

	system("pause");
	return 0;
}