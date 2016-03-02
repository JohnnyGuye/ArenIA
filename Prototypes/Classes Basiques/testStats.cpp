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

	cout << endl << endl << "------Gauge initializations------" << endl;
	Gauge mGauge;
	cout << mGauge << endl;
	Gauge nGauge = Gauge ( 10, 0, 5, 0);
	cout << nGauge << endl;
	Gauge oGauge = Gauge ( 10, 0, 11, 0);
	cout << oGauge << endl << endl;


	cout << "------Stats initializations and tests------" << endl;

	Stats mStats = Stats(mGauge, mGauge, mGauge, 200, 200, 200);
	Stats nStats = Stats(nGauge, nGauge, nGauge, 100, 100, 100);
	Stats oStats = Stats(oGauge, oGauge, oGauge, 50, 100, 200);
	cout << "-----------1 : " << endl << nStats;
	cout << "-----------2 : " << endl << oStats;
	cout << "-----------3 : " << endl << mStats;
	nStats += oStats;
	cout << "-----------1 + 2 : " << endl << nStats;

	nStats += mStats;
	cout << "-----------1 + 3 : " << endl << nStats;

	return 0;
}
