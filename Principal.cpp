/**
 * \file Principal.cpp
 * \brief Fichier pour les diff�rents tests
 * \author �tudiant 1, �tudiant 2
 * \version 0.1
 * \date juillet 2014
 *
 */

#include <iostream>
#include <fstream>
//vous pouvez inclure d'autres librairies si c'est n�cessaire
using namespace std;
#include "ReseauAerien.h"
#include "Graphe.h"

using namespace TP3;

int main()
{
	// Faire vos tests ici.
	string comm;
	Graphe graph = Graphe();
	cout<<graph.sommetExiste("Quebec");
	graph.ajouterSommet("Quebec",46.80,-71.24);
	graph.ajouterSommet("Montreal",45.51,-73.55);
	graph.ajouterSommet("Ottawa",45.41,-75.70);
	cout<<graph.sommetExiste("Quebec");
	cout<<graph.getCoordonnesSommet("Quebec").lg<<" , "<<graph.getCoordonnesSommet("Quebec").lt;
	cin>>comm;
    return 0;
}
