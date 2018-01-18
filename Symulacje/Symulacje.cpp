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
double los = 0.0,calk_czas=0.0;
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

	return dania;
}


void do_Sklepu(double tak, double nie)
// z rozkl dyskretnego prawd. 0,3 0,5 0,2 (w fun( 0.3,0.8,1) )
//okresla na podstawie okreslonego prawd. czy musimy isc do sklepu,
//jesli tak, dodaje do calkowitego czasu wartosc wymulowana z rozkl norm.
//ilosc dan ma znaczenie( wiecej dan, prawd. rosnie, wiecej dan, dluzsze zakupy)
{

	los = losuj();
	if (los <= tak)
	{
		ile_razy_sklep++;
		switch (dania)
		{
		case 1:
			calk_czas += rozk_Norm(5, 20);
			break;
		case 2:
			calk_czas += rozk_Norm(10, 40);
			break;
		case 3:
			calk_czas += rozk_Norm(15, 70);
			break;
		}			
	}
	else if (los <= nie) 
	{
		ile_razy_nsklep++;
		calk_czas += 5;
	}
	
	//return dania;
}


void ile_Zmywania(double malo, double srednio, double duzo)
{
	los = losuj();

	if (los <= malo)
	{
		calk_czas += rozk_Wyklad(1,5);

	}
	else if (los <= srednio)
	{
		calk_czas += rozk_Wyklad(1.5,12);
	}
	else if (los <= duzo)
	{
		calk_czas += rozk_Wyklad(2,20);
	}

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
		sklep_tak = 0.4;
		sklep_nie = 1;
		break;
	case 3:
		sklep_tak = 0.8;
		sklep_nie = 1;
		break;
	}

	do_Sklepu(sklep_tak, sklep_nie);
	return calk_czas;

}




int main()
{
	srand(time(NULL));


	
	for(int i=0;i<20;i++)
	{
		calk_czas = 0;
		//cout << rozk_Wyklad(1.5,10) << endl;
		calosc();
		//ile_Zmywania(0.3, 0.8, 1);
		cout << calk_czas << endl;
		system("pause");

	}
	


	system("pause");
	return 0;
}