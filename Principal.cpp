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
      graph.ajouterSommet("Ottawa",45.41,-75.70);

      cout << "Est vide? 0 = " << graph.estVide() << endl;
      cout << "Sommet existe? 1 = " << graph.sommetExiste("Quebec") << endl;

      vector<string> sommets = graph.listerNomsSommets();
      for(int i = 0 ; (unsigned)i < sommets.size(); i++)
      {
         cout << sommets.at(i) << endl;
      }

      cout << "Nombre de sommets : " << graph.nombreSommets() << endl;

      cout << "Quebec = " << graph.getNomSommet(46.80,-71.24) << endl;
      cout << "Montreal = " << graph.getNomSommet(45.51,-73.55) << endl;
      cout << "Paris = " << graph.getNomSommet(48.86,2.35) << endl;
      cout << "Ottawa = " << graph.getNomSommet(45.41,-75.70) << endl;

      Coordonnees coordQuebec = graph.getCoordonnesSommet("Quebec");
      Coordonnees coordMontreal = graph.getCoordonnesSommet("Montreal");
      Coordonnees coordParis = graph.getCoordonnesSommet("Paris");
      Coordonnees coordOttawa = graph.getCoordonnesSommet("Ottawa");

      cout << "Quebec : " << coordQuebec.lt << "," << coordQuebec.lg << endl;
      cout << "Montreal : " << coordMontreal.lt << "," << coordMontreal.lg << endl;
      cout << "Paris : " << coordParis.lt << "," << coordParis.lg << endl;
      cout << "Ottawa : " << coordOttawa.lt << "," << coordOttawa.lg << endl;

      cout << "Distance entre Quebec et Montreal = " << graph.getDistance("Quebec","Montreal") << endl;
      cout << "Distance entre Montreal et Paris = " << graph.getDistance("Montreal","Paris") << endl;

      cout << "Arc existe? Quebec->Montreal : 0 = " << graph.arcExiste("Quebec","Montreal") << endl;
      cout << "Arc existe? Montreal->Quebec : 0 = " << graph.arcExiste("Montreal","Quebec") << endl;
      cout << "Arc existe? Montreal->Paris : 0 = " << graph.arcExiste("Montreal","Paris") << endl;
      cout << "Arc existe? Montreal->Ottawa : 0 = " << graph.arcExiste("Montreal","Ottawa") << endl;
      graph.ajouterArc("Quebec", "Montreal", 0.80, 220.46, -1);
      graph.ajouterArc("Montreal", "Quebec", 0.83, 149.78, 2);
      graph.ajouterArc("Montreal", "Paris", 6.27, 723.96, -2);
      graph.ajouterArc("Montreal", "Ottawa", 0.66, 192.46, -1);
      cout << "Arc existe? Quebec->Montreal : 1 = " << graph.arcExiste("Quebec","Montreal") << endl;
      cout << "Arc existe? Montreal->Quebec : 1 = " << graph.arcExiste("Montreal","Quebec") << endl;
      cout << "Arc existe? Montreal->Paris : 1 = " << graph.arcExiste("Montreal","Paris") << endl;
      cout << "Arc existe? Montreal->Ottawa : 1 = " << graph.arcExiste("Montreal","Ottawa") << endl;

      vector<string> arcs = graph.listerSommetsAdjacents("Montreal");
      cout << "arcs (sommets adjacents) de Montreal : " << endl;
      for(int i = 0 ; (unsigned)i < arcs.size(); i++)
      {
         cout << arcs[i] << endl;
      }

      Graphe graph3;
      graph3 = graph;
      Graphe graph2(graph3);
      graph.detruireGraphe();
      cout << "Sommet existe? Quebec : 1 = " << graph2.sommetExiste("Quebec") << endl;
      cout << "Sommet existe? Montreal : 1 = " << graph2.sommetExiste("Montreal") << endl;
      cout << "Arc existe? Montreal->Ottawa : 1 = " << graph2.arcExiste("Montreal","Ottawa") << endl;
      cout << "Sommet existe? Quebec : 0 = " << graph.sommetExiste("Quebec") << endl;

      Ponderations ponderQuebecMontreal = graph2.getPonderationsArc("Quebec","Montreal");
      cout << "Pondération Quebec->Montreal = "
           << ponderQuebecMontreal.duree << ", "
           << ponderQuebecMontreal.cout << ", "
           << ponderQuebecMontreal.ns << endl;
      Ponderations ponderMontrealParis = graph2.getPonderationsArc("Montreal","Paris");
      cout << "Pondération Montreal->Paris = "
           << ponderMontrealParis.duree << ", "
           << ponderMontrealParis.cout << ", "
           << ponderMontrealParis.ns << endl;

      graph2.enleverArc("Quebec","Montreal");
      cout << "Arc existe? Quebec->Montreal : 0 = " << graph2.arcExiste("Quebec","Montreal") << endl;
      graph2.enleverArc("Montreal","Paris");
      cout << "Arc existe? Montreal->Quebec : 1 = " << graph2.arcExiste("Montreal","Quebec") << endl;
      cout << "Arc existe? Montreal->Paris : 0 = " << graph2.arcExiste("Montreal","Paris") << endl;
      cout << "Arc existe? Montreal->Ottawa : 1 = " << graph2.arcExiste("Montreal","Ottawa") << endl;

      arcs = graph2.listerSommetsAdjacents("Montreal");
      cout << "arcs (sommets adjacents) de Montreal : " << endl;
      for(int i = 0 ; (unsigned)i < arcs.size(); i++)
      {
         cout << arcs[i] << endl;
      }

      graph2.enleverArc("Montreal","Quebec");
      cout << "Arc existe? Montreal->Quebec : 0 = " << graph2.arcExiste("Montreal","Quebec") << endl;

      arcs = graph2.listerSommetsAdjacents("Montreal");
      cout << "arcs (sommets adjacents) de Montreal : " << endl;
      for(int i = 0 ; (unsigned)i < arcs.size(); i++)
      {
         cout << arcs[i] << endl;
      }


      cout << "Est vide avant destruction? 0 = " << graph2.estVide() << endl;
      graph2.detruireGraphe();
      cout << "Est vide? 1 = " << graph2.estVide() << endl;
      cout << "Sommet existe? Montreal : 0 = " << graph2.sommetExiste("Montreal") << endl;


      //cin>>comm;

   } catch (exception & e)
   {
      cerr << e.what() << endl;
   }

   return 0;
}
