/**
 * \file Principal.cpp
 * \brief Fichier pour les différents tests
 * \author Étudiant 1, étudiant 2
 * \version 0.1
 * \date juillet 2014
 *
 */

#include "Graphe.h"
#include "ReseauAerien.h"

#include <iostream>
#include <fstream>

using namespace std;
using namespace TP3;

int main()
{
	// Faire vos tests ici.
   try
   {
      //string comm;

      Graphe graph;

      cout << "Est vide? 1 = " << graph.estVide() << endl;
      cout << "Sommet existe? 0 = " << graph.sommetExiste("Quebec") << endl;

      graph.ajouterSommet("Quebec",46.80,-71.24);
      graph.ajouterSommet("Montreal",45.51,-73.55);
      graph.ajouterSommet("Paris",48.86,2.35);

      cout << "Sommet existe? 1 = " << graph.sommetExiste("Quebec") << endl;

      vector<string> sommets = graph.listerNomsSommets();
      for(int i = 0 ; (unsigned)i < sommets.size(); i++)
      {
         cout << sommets.at(i) << endl;
      }

      cout << "Est vide? 0 = " << graph.estVide() << endl;
      cout << "Nombre de sommets : " << graph.nombreSommets() << endl;

      cout << "Quebec = " << graph.getNomSommet(46.80,-71.24) << endl;
      cout << "Montreal = " << graph.getNomSommet(45.51,-73.55) << endl;
      cout << "Paris = " << graph.getNomSommet(48.86,2.35) << endl;

      Coordonnees coordQuebec = graph.getCoordonnesSommet("Quebec");
      Coordonnees coordMontreal = graph.getCoordonnesSommet("Montreal");
      Coordonnees coordParis = graph.getCoordonnesSommet("Paris");

      cout << "Quebec : " << coordQuebec.lt << "," << coordQuebec.lg << endl;
      cout << "Montreal : " << coordMontreal.lt << "," << coordMontreal.lg << endl;
      cout << "Paris : " << coordParis.lt << "," << coordParis.lg << endl;

      cout << "Distance entre Quebec et Montreal = " << graph.getDistance("Quebec","Montreal") << endl;
      cout << "Distance entre Montreal et Paris = " << graph.getDistance("Montreal","Paris") << endl;

      cout << "Arc existe? 0 = " << graph.arcExiste("Quebec","Montreal") << endl;
      cout << "Arc existe? 0 = " << graph.arcExiste("Montreal","Quebec") << endl;
      cout << "Arc existe? 0 = " << graph.arcExiste("Montreal","Paris") << endl;
      graph.ajouterArc("Quebec", "Montreal", 0.80, 220.46, -1);
      graph.ajouterArc("Montreal", "Quebec", 0.83, 149.78, 2);
      graph.ajouterArc("Montreal", "Paris", 6.27, 723.96, -2);
      cout << "Arc existe? 1 = " << graph.arcExiste("Quebec","Montreal") << endl;
      cout << "Arc existe? 1 = " << graph.arcExiste("Montreal","Quebec") << endl;
      cout << "Arc existe? 1 = " << graph.arcExiste("Montreal","Paris") << endl;

      vector<string> arcs = graph.listerSommetsAdjacents("Montreal");
      for(int i = 0 ; (unsigned)i < arcs.size(); i++)
      {
         cout << arcs[i] << endl;
      }



      //cin>>comm;

   } catch (exception & e)
   {
      cerr << e.what() << endl;
   }

   return 0;
}
