/*************************************************************************
                           testStats  -  description
                             -------------------
    début                : 25 févr. 2016
    copyright            : (C) 2016 par ska
*************************************************************************/

//---------- Réalisation de la classe <testStats> (fichier testStats.cpp) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "Gauge.h"
#include "Stats.h"

int main( )
{
	Gauge mGauge;
	Gauge nGauge = Gauge ( 10, 0, 5, 0);

	Stats myyStats = Stats(mGauge, mGauge, mGauge, 200, 200, 200);
	Stats myStats = Stats(nGauge, nGauge, nGauge, 100, 100, 100);
	cout << "-----------1 : " << endl << myStats;
	cout << "-----------2 : " << endl << myyStats;
	myStats += myyStats;
	cout << "-----------1 + 2 : " << endl << myStats;
	return 0;
}
