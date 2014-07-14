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
#include <time.h> 

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
		clock_t t1;
		clock_t t2;
		clock_t t3;
	  int f;

	
	 

	  //Tests temps d'éxécution
	  t1 = clock();
	  reseau.rechercheCheminDijkstra("Paris","New_York",true);
	   t1 = clock() - t1;
	   
	   t2= clock();
	  reseau.bellManFord("Paris","New_York",1);
	   t2 = clock() - t2;

	   t3= clock();
	  reseau.algorithmeAstar("Paris","New_York",true);
	   t3 = clock() - t3;

      // Sauvegarde du réseau dans un fichier texte
      ofstream out("Test.txt",ios::out);
      reseau.sauvegarderReseau(out);
      out.close();

      // Fermeture transitive
      ReseauAerien fermeture = reseau.fermetureReseau();
      //cout << fermeture;
	  cout << fermeture;

	  //Tests algorithmes chemin
	  std::vector<std::string> c1 = reseau.rechercheCheminLargeur("Quebec","Bogota");

	  //Duree
	  Chemin c2 = reseau.rechercheCheminDijkstra("Quebec","Bogota",true);
	  Chemin c3 = reseau.bellManFord("Quebec","Bogota",1);
	  Chemin c4 = reseau.algorithmeAstar("Quebec","Bogota",true);

	  //Cout
	  Chemin c5 = reseau.rechercheCheminDijkstra("Quebec","Bogota",false);
	  Chemin c6 = reseau.bellManFord("Quebec","Bogota",2);
	  Chemin c7 = reseau.algorithmeAstar("Quebec","Bogota",false);

	  //Niveau de sécurité
	  Chemin c8 = reseau.bellManFord("Quebec","Bogota",3);

	  reseau.viderReseau();

   } catch (exception & e)
   {
      cerr << e.what() << endl;
   }

   return 0;
}
