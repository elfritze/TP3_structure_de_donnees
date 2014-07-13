/**
 * \file Principal.cpp
 * \brief Fichier pour les différents tests
 * \author Éric Guillemette, Mathieu L'Écuyer
 * \version 0.1
 * \date juillet 2014
 *
 */

#include "Graphe.h"
#include "ReseauAerien.h"

#include <cstdlib>
#include <iostream>
#include <fstream>

using namespace std;
using namespace TP3;

int main()
{
   try
   {
      ReseauAerien reseau;
	  string comm;
      // Charger le réseau à partir du fichier texte
      ifstream fichier("ReseauAerien.txt",ios::in);
      reseau.chargerReseau(fichier);
      fichier.close();

      cout << reseau;
	  Chemin c1 = reseau.rechercheCheminDijkstra("Quebec","New_York",1);
	  Chemin c2 = reseau.bellManFord("Quebec","New_York",1);
      // Sauvegarde du réseau dans un fichier texte
      ofstream out("Test.txt",ios::out);
      reseau.sauvegarderReseau(out);
      out.close();

      // Fermeture transitive
      ReseauAerien fermeture = reseau.fermetureReseau();

      //cout << fermeture;
	  cout << fermeture;
	  cin>>comm;
      // Génération des graphes avec Graphviz

      // Graphe sans pondération
      // ofstream fichierGraphviz("Graphe.def");
      // reseau.displayInGraphviz(fichierGraphviz, 0);
      // fichierGraphviz.close();
      // std::system("dot -Tpng -oGraphe.png Graphe.def");

      // Graphe pour la durée
      // ofstream fichierGraphviz("Graphe.def");
      // reseau.displayInGraphviz(fichierGraphviz, 1);
      // fichierGraphviz.close();
      // std::system("dot -Tpng -oGraphe_duree.png Graphe.def");

      // Graphe pour le coût
      // fichierGraphviz.open("Graphe.def");
      // reseau.displayInGraphviz(fichierGraphviz, 2);
      // fichierGraphviz.close();
      // std::system("dot -Tpng -oGraphe_cout.png Graphe.def");

      // Graphe pour le niveau de sécurité
      // fichierGraphviz.open("Graphe.def");
      // reseau.displayInGraphviz(fichierGraphviz, 3);
      // fichierGraphviz.close();
      // std::system("dot -Tpng -oGraphe_ns.png Graphe.def");


   } catch (exception & e)
   {
      cerr << e.what() << endl;
   }

   return 0;
}
