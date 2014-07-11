/**
 * \file Principal.cpp
 * \brief Fichier pour les diff�rents tests
 * \author �tudiant 1, �tudiant 2
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

      // Charger le r�seau � partir du fichier texte
      ifstream fichier("ReseauAerien.txt",ios::in);
      reseau.chargerReseau(fichier);
      fichier.close();

      cout << reseau;

      // Sauvegarde du r�seau dans un fichier texte
      ofstream out("Test.txt",ios::out);
      reseau.sauvegarderReseau(out);
      out.close();

      // Fermeture transitive
      ReseauAerien fermeture = reseau.fermetureReseau();

      cout << fermeture;


      // G�n�ration des graphes avec Graphviz
      // Graphe pour la dur�e
      // ofstream fichierGraphviz("Graphe.def");
      // reseau.displayInGraphviz(fichierGraphviz, 1);
      // fichierGraphviz.close();
      // std::system("dot -Tpng -oGraphe_duree.png Graphe.def");

      // Graphe pour le co�t
      // fichierGraphviz.open("Graphe.def");
      // reseau.displayInGraphviz(fichierGraphviz, 2);
      // fichierGraphviz.close();
      // std::system("dot -Tpng -oGraphe_cout.png Graphe.def");

      // Graphe pour le niveau de s�curit�
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
