/**
 * \file ReseauAerien.cpp
 * \brief Impl�mentattion de la classe ReseauAerien.
 * \author �ric Guillemette, Mathieu L'�cuyer
 * \version 0.1
 * \date juillet 2014
 *
 * Travail pratique num�ro 3
 *
 */

#include "ReseauAerien.h"

/**
 * \namespace TP3
 *
 * Espace de nommage regroupant les d�finitions du TP3.
 */
namespace TP3
{

/**
 * \fn ReseauAerien::ReseauAerien(const ReseauAerien &source)
 *
 * \param[in] source : Un objet ReseauAerien existant.
 */
ReseauAerien::ReseauAerien(const ReseauAerien &source)
{
   unReseau = source.unReseau;   // Surcharge de l'op�rateur d'affectation de la classe Graphe
   nomReseau = source.nomReseau;
}

/**
 * \fn ReseauAerien& ReseauAerien::operator=(const ReseauAerien& src)
 *
 * \param[in] src : Un objet ReseauAerien existant.
 *
 * \return L'objet courant contenant � pr�sent les donn�es de l'objet src.
 */
ReseauAerien& ReseauAerien::operator=(const ReseauAerien& src)
{
   if (this != &src)
   {
      unReseau = src.unReseau;   // Surcharge de l'op�rateur d'affectation de la classe Graphe
      nomReseau = src.nomReseau;
   }

   return (*this);
}

/**
 * \fn std::ostream& operator<<(std::ostream& out, const ReseauAerien& g)
 *
 * \param[in] out : un stream vide dans lequel on va �crire.
 * \param[in] g : un objet ReseauAerien d�j� existant.
 *
 * \return Le stream dans lequel on a �crit.
 */
std::ostream& operator<<(std::ostream& out, const ReseauAerien& g)
{
   return out << g.unReseau;
}

/**
 * \fn void ReseauAerien::chargerReseau(std::ifstream & fichierEntree)
 *
 * \param[in] fichierEntree : un flux d'entr�e contenant un fichier texte.
 */
void ReseauAerien::chargerReseau(std::ifstream & fichierEntree)
{
   // Exception si fichierEntree n'est pas ouvert correctement.
   if (!fichierEntree.is_open())
      throw std::logic_error("chargerReseau: Le fichier texte n'est pas ouvert correctement.");

   // Variables pour la lecture du fichier
   std::string line, nom, ville1, ville2;
   int nbVilles, nbTrajets, ns;
   float lt, lg, duree, cout;

   // lecture du fichier pour r�cup�rer le nom du r�seau a�rien
   fichierEntree.ignore(15);
   getline(fichierEntree, nom);

   nomReseau = nom;

   // r�cup�ration du nombre de sommets et du nombre d'arcs (pour les compteurs des boucles)
   fichierEntree >> nbVilles;
   getline(fichierEntree, line);
   fichierEntree >> nbTrajets;
   getline(fichierEntree, line);
   getline(fichierEntree, line);

   // ajout des villes (sommets) au graphe
   for (int i = 0; i < nbVilles; i++)
   {
      getline(fichierEntree, ville1);
      fichierEntree >> lt;
      fichierEntree >> lg;
      fichierEntree.ignore(1, '\n');

      unReseau.ajouterSommet(ville1, lt, lg);
   }
   getline(fichierEntree, line);

   // ajout des trajets (arcs) au graphe
   for (int j = 0; j < nbTrajets; j++)
   {
      getline(fichierEntree, ville1);
      getline(fichierEntree, ville2);
      fichierEntree >> duree;
      fichierEntree >> cout;
      fichierEntree >> ns;
      fichierEntree.ignore(1, '\n');

      unReseau.ajouterArc(ville1, ville2, duree, cout, ns);
   }
}

/**
 * \fn void ReseauAerien::sauvegarderReseau(std::ofstream & SortieFichier) const
 *
 * \param[in] SortieFichier : un flux de sortie pour sauvegarder dans un fichier texte.
 */
void ReseauAerien::sauvegarderReseau(std::ofstream & SortieFichier) const
{
   // Exception si SortieFichier n'est pas ouvert correctement.
   if (!SortieFichier.is_open())
      throw std::logic_error("sauvegarderReseau: Le fichier n'est pas ouvert correctement");

   SortieFichier << "Reseau Aerien: " << nomReseau << std::endl;
   SortieFichier << unReseau.nombreSommets() << " villes" << std::endl;
   SortieFichier << unReseau.nombreArcs() << " trajets" << std::endl;
   SortieFichier << "Liste des villes:" << std::endl;

   std::vector<std::string> sommets = unReseau.listerNomsSommets();
   for (int i = 0; (unsigned) i < sommets.size(); i++)
   {
      Coordonnees coord = unReseau.getCoordonnesSommet(sommets.at(i));
      SortieFichier << sommets.at(i) << std::endl << coord.lt << " " << coord.lg << std::endl;
   }

   SortieFichier << "Liste des trajets:" << std::endl;
   for (int i = 0; (unsigned) i < sommets.size(); i++)
   {
      std::vector<std::string> adjacents = unReseau.listerSommetsAdjacents(sommets.at(i));
      for (int j = 0; (unsigned) j < adjacents.size(); j++)
      {
         Ponderations pond = unReseau.getPonderationsArc(sommets.at(i), adjacents.at(j));
         SortieFichier << sommets.at(i) << std::endl;
         SortieFichier << adjacents.at(j) << std::endl;
         SortieFichier << pond.duree << " " << pond.cout << " " << pond.ns << std::endl;
      }
   }
}

/**
 * \fn void ReseauAerien::viderReseau()
 */
void ReseauAerien::viderReseau()
{
   unReseau.detruireGraphe();
}

/**
 * \fn ReseauAerien ReseauAerien::fermetureReseau()
 *
 * \return La fermeture transitive du r�seau.
 */
ReseauAerien ReseauAerien::fermetureReseau()
{
   ReseauAerien r;
   r.unReseau = unReseau;
   r.nomReseau = nomReseau;

   std::vector<std::string> sommets = r.unReseau.listerNomsSommets();

   //Pour chaque sommet
   for (int k = 0; (unsigned) k < sommets.size(); k++)
   {
      //Pour chaque paire de sommets i et j
      std::string ville1 = sommets.at(k);
      for (int i = 0; (unsigned) i < sommets.size(); i++)
      {
         std::string ville2 = sommets.at(i);
         for (int j = 0; (unsigned) j < sommets.size(); j++)
         {
            std::string ville3 = sommets.at(j);

            //S'il n'existe pas de chemin entre i et j
            if (!r.unReseau.arcExiste(ville2, ville3))
            {
               //S'il existe un chemin entre i et k et entre k et j alors on fait un chemin entre i et j
               if (r.unReseau.arcExiste(ville2, ville1) && r.unReseau.arcExiste(ville1, ville3))
               {
                  r.unReseau.ajouterArc(ville2, ville3, 0, 0, 0);
               }
            }
         }
      }
   }

   return r;
}

/**
 * \fn std::vector<std::string> ReseauAerien::rechercheCheminLargeur(const std::string& origine,
 *                                                                   const std::string& destination)
 *
 * \param[in] origine : La ville origine (le d�part).
 * \param[in] destination : La ville destination (l'arriv�e).
 *
 * \return Le chemin trouv� est retourn� sous forme d'un tableau de cha�nes de caract�res.
 */
std::vector<std::string> ReseauAerien::rechercheCheminLargeur(const std::string& origine,
      const std::string& destination)
{
   //Exception si le d�part ou l'arriv�e ne fait pas partie du r�seau a�rien.
   if (!unReseau.sommetExiste(origine) || !unReseau.sommetExiste(destination))
      throw std::logic_error(
            "rechercheCheminLargeur: Le d�part ou l'arriv�e ne fait pas partie du r�seau a�rien.");

   // Conteneurs pour l'algorithme
   std::vector<std::string> chemin;
   std::queue<std::string> fileParcours;
   std::stack<std::string> pile;

   // On initialise l'�tat des sommets du graphe
   unReseau.initialiserEtats();

   // On initialise les pointeurs pr�c�dents des sommets du graphe
   unReseau.initialiserPrecedents();

   // On enfile et on marque le sommet origine
   fileParcours.push(origine);
   unReseau.marquerEtatSommet(origine);

   // Tant que la file n'est pas vide
   // D�filer le prochain sommet
   // Pour chaque sommets adjacents non marqu� : marquer, enfiler et pointer vers pr�c�dent
   std::string courant;
   std::vector<std::string> adjacents;
   while (!fileParcours.empty() && courant != destination)
   {
      courant = fileParcours.front();
      adjacents = unReseau.listerSommetsAdjacents(courant);

      for (int i = 0; (unsigned) i < adjacents.size(); i++)
      {
         if (!unReseau.getEtatSommet(adjacents[i]))
         {
            unReseau.marquerEtatSommet(adjacents[i]);
            unReseau.setPrecedent(adjacents[i], courant);
            fileParcours.push(adjacents[i]);
         }
      }

      fileParcours.pop();
   }

   // On cr�e le chemin en remontant de la destination � l'origine
   if (origine == destination)
   {
      // si la ville de d�part est la ville d'arriv�e
      std::cout << "Vous �tes d�j� � destination.\n";
   }
   else if (unReseau.getPrecedent(destination).empty())
   {
      // s'il n'y a pas de chemin pour se rendre � la destinition
      std::cout << "Destination inatteignable � partir de la ville de d�part.\n";
   }
   else
   {
      // On empile d'abord la destination
      pile.push(destination);

      // puis on empile les villes pr�c�dentes
      std::string precedent;
      while (precedent != origine)
      {
         precedent = unReseau.getPrecedent(pile.top());
         pile.push(precedent);
      }

      // On d�pile toutes les villes dans le chemin
      while (!pile.empty())
      {
         chemin.push_back(pile.top());
         pile.pop();
      }
   }

   // On r�initialise les �tats et les pointeurs avant de quitter.
   unReseau.initialiserEtats();
   unReseau.initialiserPrecedents();

   return chemin;
}

/**
 * \fn Chemin ReseauAerien::rechercheCheminDijkstra(const std::string& origine, const std::string&
 *                                                  destination, bool dureeCout)
 *
 * \param[in] origine : La ville origine (le d�part).
 * \param[in] destination : La ville destination (l'arriv�e).
 * \param[in] dureeCout : Un bool�en true s'il faut utiliser la dur�e du vol comme pond�ration,
 *                        false s'il faut utiliser le co�t du vol comme pond�ration sur les trajets.
 *
 * \return Le plus court chemin selon la pond�ration choisie est retourn� dans une structure Chemin.
 */
Chemin ReseauAerien::rechercheCheminDijkstra(const std::string& origine,
      const std::string& destination, bool dureeCout)
{
   // Exception si le d�part ou l'arriv�e ne fait pas partie du r�seau a�rien.
   if (!unReseau.sommetExiste(origine) || !unReseau.sommetExiste(destination))
      throw std::logic_error(
            "rechercheCheminDijkstra: Le d�part ou l'arriv�e ne fait pas partie du r�seau a�rien.");

   // Initialisation du chemin
   Chemin chemin;

   // On initialise l'�tat des sommets du graphe
   unReseau.initialiserEtats();

   // Conteneurs pour l'algorithme...
   std::vector<std::string> villes = unReseau.listerNomsSommets();  //la liste des villes
   std::vector<std::string> adjacents; //pour contenir les villes adjacentes � la ville courante
   std::queue<std::string> file; //file pour parcourir les diff�rents trajets
   std::vector<float> ponderation(villes.size(), infinie); //pour contenir les pond�rations
   std::vector<std::string> precedent(villes.size()); //pour contenir les villes pr�c�dentes

   // Dans la liste des villes, on trouve les positions de la ville origine et la destination
   // et on met � 0 la pond�ration de la ville origine
   int positionDestination;
   for (int i = 0; (unsigned) i < villes.size(); i++)
   {
      if (villes[i] == origine)
         ponderation[i] = 0;

      if (villes[i] == destination)
         positionDestination = i;
   }

   // On cr�e une file � partir de l'origine et on parcourt tous les trajets possibles.

   int positionA;
   int positionB;
   std::string courant;

   file.push(origine);  // On commence par enfiler l'origine

   // et on boucle tant que la file n'est pas vide
   while (!file.empty())
   {
      courant = file.front();
      adjacents = unReseau.listerSommetsAdjacents(courant);

      // on retire la ville courante de la file
      file.pop();

      // On parcourt les villes adjacentes de la ville courante
      for (int i = 0; (unsigned) i < adjacents.size(); i++)
      {
         // Si la ville adjacente n'a pas d�j� �t� visit�e
         if (!unReseau.getEtatSommet(adjacents[i]))
         {
            // on ajoute la ville adjacente � la file
            file.push(adjacents[i]);
            unReseau.marquerEtatSommet(adjacents[i]); // On change son �tat � true

            // on trouve les positions de la ville courante et de la ville adjacente
            for (int j = 0; (unsigned) j < villes.size(); j++)
            {
               if (villes[j] == courant)
                  positionA = j;

               if (villes[j] == adjacents[i])
                  positionB = j;
            }

            // On obtient les pond�rations du trajet entre les deux villes
            Ponderations ponder = unReseau.getPonderationsArc(courant, adjacents[i]);

            // On compare la pond�ration � celle du tableau (par d�faut, la valeur est infinie)
            // Si celle du tableau est plus grande, on remplace par la nouvelle
            // et on change la ville pr�c�dente pour la ville courante

            if (dureeCout == true)
            {
               if (ponderation[positionB] > (ponderation[positionA] + ponder.duree))
               {
                  ponderation[positionB] = ponderation[positionA] + ponder.duree;
                  precedent[positionB] = courant;
               }
            }
            else
            {
               if (ponderation[positionB] > (ponderation[positionA] + ponder.cout))
               {
                  ponderation[positionB] = ponderation[positionA] + ponder.cout;
                  precedent[positionB] = courant;
               }
            }
         }
      }
   }

   // On v�rifie s'il a �t� possible d'atteindre la destination
   if (ponderation[positionDestination] == infinie)
   {
      // Sinon, on retourne un chemin vide et le bool�en reussi = false
      std::cout << "Destination inatteignable � partir de la ville de d�part.\n";
      chemin.reussi = false;
      chemin.dureeTotale = 0;
      chemin.coutTotal = 0;

      return chemin;
   }

   // Une fois toutes les villes visit�es, on construit le chemin

   int positionPrecedent;
   std::string villePrecedente;
   std::stack<std::string> pile; // Pile pour remonter le chemin de l'arriv�e au d�part

   // On ajoute la destination � la pile
   pile.push(destination);

   // On r�cup�re la ville pr�c�dente
   villePrecedente = precedent[positionDestination];

   // On boucle pour ajouter � la pile toutes les villes pr�c�dentes jusqu'� la ville origine
   float escale = 0;
   while (villePrecedente != origine)
   {
      for (int i = 0; (unsigned) i < villes.size(); i++)
      {
         if (villes[i] == villePrecedente)
         {
            positionPrecedent = i;
            break;
         }
      }

      pile.push(villePrecedente);
      villePrecedente = precedent[positionPrecedent];

      // On compte le nombre d'escales. Chaque escale �quivaut � 1 heure d'attente.
      escale++;
   }

   // On ajoute l'origine � la pile
   pile.push(origine);

   // Et finalement, on d�pile le chemin dans la liste des villes.
   // Le d�part est en position 0 et l'arriv�e � la fin de la liste.
   while (!pile.empty())
   {
      chemin.listeVilles.push_back(pile.top());
      pile.pop();
   }

   // On met � jour les infos du chemin selon l'option choisie en argument
   if (dureeCout == true)
   {
      chemin.dureeTotale = ponderation[positionDestination] + escale;
      chemin.reussi = true;
      chemin.coutTotal = 0;
   }
   else
   {
      chemin.coutTotal = ponderation[positionDestination];
      chemin.reussi = true;
      chemin.dureeTotale = 0;
   }

   // On r�initialise les �tats avant de quitter.
   unReseau.initialiserEtats();

   return chemin;
}

/**
 * \fn Chemin ReseauAerien::bellManFord(const std::string& origine, const std::string& destination,
 int dureeCoutNiveau)
 *
 * \param[in] origine : La ville origine (le d�part).
 * \param[in] destination : La ville destination (l'arriv�e).
 * \param[in] dureeCoutNiveau : Un entier de valeur 1 s'il faut utiliser la dur�e du vol comme
 *                              pond�ration, 2 s'il faut utiliser le co�t du vol ou 3 s'il faut
 *                              utiliser le niveau de s�curit�.
 *
 * \return Le plus court chemin selon la pond�ration choisie est retourn� dans une structure Chemin.
 */
Chemin ReseauAerien::bellManFord(const std::string& origine, const std::string& destination,
      int dureeCoutNiveau)
{
   //exception logic_error : si le d�part ou l'arriv�e ne fait pas partie du r�seau a�rien.
   if (!unReseau.sommetExiste(origine) || !unReseau.sommetExiste(destination))
      throw std::logic_error("La destination ou l'origine n'appartien pas au r�seau a�rien");

   //exception logic_error : si dureeCoutNiveau est diff�rent des valeurs 1, 2 ou 3.
   if (dureeCoutNiveau != 1 && dureeCoutNiveau != 2 && dureeCoutNiveau != 3)
      throw std::logic_error("La valeur de dureeCoutNiveau doit se situer entre 1 et 3");

   Chemin chemin;
   std::vector<std::string> sommets = unReseau.listerNomsSommets();

   //On initialise les distances les plus courtes � INT_MAX et on initialise les villes pr�c�dentes � z�ro
   unReseau.initialiserDistances();
   unReseau.initialiserPrecedents();

   //On initialise le sommet d'origine � z�ro
   unReseau.marquerDistanceSommet(origine, 0);

   bool stable;
   int nbSommets = 1;
   do
   {
      stable = true;
      //Pour tout sommet
      for (int i = 0; (unsigned)i < sommets.size(); i++)
      {
         //Origine
         std::string origine = sommets.at(i);
         //Liaisons
         std::vector<std::string> adjacents = unReseau.listerSommetsAdjacents(origine);

         //Pour toute lisaison (arc)
         for (int j = 0; (unsigned)j < adjacents.size(); j++)
         {
            //Destination
            std::string destination = adjacents.at(j);
            Ponderations pond = unReseau.getPonderationsArc(origine, destination);
            float distance =
                  unReseau.getDistanceSommet(origine)
                        + (dureeCoutNiveau == 1 ? pond.duree :
                           dureeCoutNiveau == 2 ? pond.cout : pond.ns);

            //RELACHEMENT
            if (distance < unReseau.getDistanceSommet(destination))
            {

               unReseau.marquerDistanceSommet(destination, distance);
               unReseau.setPrecedent(destination, origine);
            }
         }
      }

      //Pour tout sommet
      for (int i = 0; (unsigned)i < sommets.size(); i++)
      {
         //Origine
         std::string origine = sommets.at(i);
         //Liaisons
         std::vector<std::string> adjacents = unReseau.listerSommetsAdjacents(origine);
         //Pour toute lisaison (arc)
         for (int j = 0; (unsigned)j < adjacents.size(); j++)
         {
            //Destination
            std::string destination = adjacents.at(j);
            float distance = unReseau.getDistanceSommet(origine)
                  + unReseau.getPonderationsArc(origine, destination).duree;

            //Si le graphe est stable
            if (distance < unReseau.getDistanceSommet(destination))
               stable = false;
         }
      }

      nbSommets++;
   } while (!stable && (unsigned)nbSommets < sommets.size() + 1); //Tant que le graphe n'est pas stable
                                                                  //ou que nbSommets max est atteint

    // On cr�e le chemin en remontant de la destination � l'origine
	chemin.coutTotal = 0;
	chemin.dureeTotale = 0;
	chemin.nsTotal = 0;
	if (origine == destination)
	{
		// si la ville de d�part est la ville d'arriv�e on est d�j� arriv�. genial
		chemin.listeVilles.push_back(origine);
		chemin.reussi = true;
	}
	else if (unReseau.getPrecedent(destination).empty())
	{
		//Chemin inexistant 
		chemin.reussi = false;
	}
	else
	{
		 std::stack<std::string> pile; 
		 
		//On ajoute toutes les villes pr�c�dentes � partir de la destination
		std::string precedent = destination;
		while (precedent != origine)
		{
			Ponderations pond = unReseau.getPonderationsArc(unReseau.getPrecedent(precedent),precedent);

			//On incr�mente les pond�rations
			if(dureeCoutNiveau == 1)
				chemin.dureeTotale += pond.duree;
			else if(dureeCoutNiveau == 2)
				chemin.coutTotal += pond.cout;
			else
				chemin.nsTotal += pond.ns;
			pile.push(precedent);
			
			precedent = unReseau.getPrecedent(precedent);
		}
		pile.push(precedent);

		//On rempli notre chemin
		while(!pile.empty()){
			chemin.listeVilles.push_back(pile.top());
			pile.pop();
		}

		//On prend en compte les escales
		if(dureeCoutNiveau == 1)
			chemin.dureeTotale += chemin.listeVilles.size() - 2;
		
	}
   return chemin;
}

/**
 * \fn Chemin ReseauAerien::algorithmeAstar(const std::string& origine, const std::string&
 *                                          destination, bool dureeCout)
 *
 * \param[in] origine : La ville origine (le d�part).
 * \param[in] destination : La ville destination (l'arriv�e).
 * \param[in] dureeCout : Un bool�en true s'il faut utiliser la dur�e du vol comme pond�ration,
 *                        false s'il faut utiliser le co�t du vol comme pond�ration sur les trajets.
 *
 * \return Le plus court chemin selon la pond�ration choisie est retourn� dans une structure Chemin.
 */
Chemin ReseauAerien::algorithmeAstar(const std::string& origine, const std::string& destination,
      bool dureeCout)
{
   //exception logic_error : si le d�part ou l'arriv�e ne fait pas partie du r�seau a�rien.
	if(!unReseau.sommetExiste(origine) || !unReseau.sommetExiste(destination))
		throw std::logic_error("La destination ou l'origine n'appartien pas au r�seau a�rien");

	Chemin chemin;
	bool found = false;
	std::list<std::string> aExplorer;
	aExplorer.push_back(origine);

	unReseau.initialiserEtats();
	unReseau.initialiserPrecedents();
	unReseau.initialiserDistances();
	unReseau.marquerDistanceSommet(origine,0);

	//Tant que la liste de villes a explorer n'est pas vide et que la destination n'en fait pas partie
	while(!aExplorer.empty() && !found)
	{
		//Element au cout minimal
		std::string elem;
		//Co�t minimal
		float min = INT_MAX;
		//R�cup�rer le sommet  de co�t total minimum
		for (std::list<std::string>::const_iterator iterator = aExplorer.begin(), end = aExplorer.end(); iterator != end; ++iterator)
		{
			float distance = unReseau.getDistanceSommet(*iterator);
			if(distance < min)
			{
				elem = *iterator;
				min = distance;
			}
		}
		
		//On retire l'�l�ment trouv� de la liste
		aExplorer.remove(elem);
		//Ajouter l'�l�ment de co�t minimal � la liste de destinations � explorer
		unReseau.marquerEtatSommet(elem);
		
		//On v�rifie tous les arcs
		std::vector<std::string> adjacents = unReseau.listerSommetsAdjacents(elem);
		while(!adjacents.empty())
		{
			//On s'assure qu'ils n'ont pas �t� visit�s
			if(!unReseau.getEtatSommet(adjacents.back()))
			{
				
				//L'arc actuel
				Ponderations pond = unReseau.getPonderationsArc(elem,adjacents.back());
				//Distance optimiste par rapport � la destination
				float nouvelleDistance = min + (dureeCout ? pond.duree : pond.cout) + unReseau.getDistance(adjacents.back(),destination);
				//On v�rifie si le sommet � ajouter est d�j� pr�sent
				std::list<std::string>::iterator dejaPresent = std::find(aExplorer.begin(), aExplorer.end(),destination);
				if(dejaPresent != aExplorer.end() )
				{
					//On s'assure que la nouvelle distance est optimale
					if(nouvelleDistance < unReseau.getDistanceSommet(adjacents.back()))
					{
						//On marque la nouvelle distance et le pr�c�dent
						unReseau.marquerDistanceSommet(adjacents.back(),nouvelleDistance);
						unReseau.setPrecedent(adjacents.back(),elem);
					}

				}
				else
				{
					//On ajoute � la liste et on marque le pr�c�dent et la nouvelle distance
					unReseau.marquerDistanceSommet(adjacents.back(),nouvelleDistance);
					unReseau.setPrecedent(adjacents.back(),elem);
					aExplorer.push_back(adjacents.back());

				}
				
			}
			//Plus besoin du sommet
			adjacents.pop_back();
		}

		//Recherche de la destination dans la liste
		std::list<std::string>::iterator city = std::find(aExplorer.begin(), aExplorer.end(),destination);
		//On v�rifie si la destination est atteinte
		city != aExplorer.end() ? found = true : found = false;
	}

	 // On cr�e le chemin en remontant de la destination � l'origine
	chemin.coutTotal = 0;
	chemin.dureeTotale = 0;
	chemin.nsTotal = 0;
	if (origine == destination)
	{
		// si la ville de d�part est la ville d'arriv�e on est d�j� arriv�. genial
		chemin.listeVilles.push_back(origine);
		chemin.reussi = true;
	}
	else if (unReseau.getPrecedent(destination).empty())
	{
		//Chemin inexistant 
		chemin.reussi = false;
	}
	else
	{
		 std::stack<std::string> pile; 
		 
		//On ajoute toutes les villes pr�c�dentes � partir de la destination
		std::string precedent = destination;
		while (precedent != origine)
		{
			Ponderations pond = unReseau.getPonderationsArc(unReseau.getPrecedent(precedent),precedent);

			//On incr�mente les pond�rations
			if(dureeCout)
				chemin.dureeTotale += pond.duree;
			else
				chemin.coutTotal += pond.cout;

			pile.push(precedent);
			precedent = unReseau.getPrecedent(precedent);
		}
		pile.push(precedent);

		//On rempli notre chemin
		while(!pile.empty()){
			chemin.listeVilles.push_back(pile.top());
			pile.pop();
		}

		//On prend en compte les escales
		if(dureeCout)
			chemin.dureeTotale += chemin.listeVilles.size() - 2;
		
	}
   return chemin;
}

/**
 * \fn void ReseauAerien::displayInGraphviz(std::ostream & out, int dureeCoutNiveau)
 *
 * \param[in] out : un stream vide dans lequel on va �crire.
 * \param[in] dureeCoutNiveau : Un entier de valeur 0 pour un graphe sans pond�ration,
 *                              1 s'il faut utiliser la dur�e du vol comme pond�ration,
 *                              2 s'il faut utiliser le co�t du vol ou 3 s'il faut utiliser
 *                              le niveau de s�curit�.
 */
void ReseauAerien::displayInGraphviz(std::ostream & out, int dureeCoutNiveau)
{
   if (!out.good())
      throw std::logic_error("displayInGraphViz: fichier incorrect");

   if (dureeCoutNiveau < 0 || dureeCoutNiveau > 3)
      throw std::logic_error("displayInGraphviz: la valeur de l'entier doit �tre 0, 1, 2 ou 3");

   out << "digraph g {" << std::endl;

   std::vector<std::string> sommets = unReseau.listerNomsSommets();
   for (int i = 0; (unsigned) i < sommets.size(); i++)
   {
      std::vector<std::string> arcs = unReseau.listerSommetsAdjacents(sommets.at(i));

      out << sommets.at(i) << std::endl;

      for (int j = 0; (unsigned) j < arcs.size(); j++)
      {
         Ponderations ponder = unReseau.getPonderationsArc(sommets.at(i), arcs.at(j));

         // sans pond�ration
         if (dureeCoutNiveau == 0)
            out << "\t " << sommets.at(i) << " -> " << arcs.at(j) << std::endl;

         // Pond�ration pour la dur�e
         if (dureeCoutNiveau == 1)
            out << "\t " << sommets.at(i) << " -> " << arcs.at(j) << " [label=" << ponder.duree
                  << "];" << std::endl;

         // Pond�ration pour le co�t
         if (dureeCoutNiveau == 2)
            out << "\t " << sommets.at(i) << " -> " << arcs.at(j) << " [label=" << ponder.cout
                  << "];" << std::endl;

         // Pond�ration pour le niveau de s�curit�
         if (dureeCoutNiveau == 3)
            out << "\t " << sommets.at(i) << " -> " << arcs.at(j) << " [label=" << ponder.ns << "];"
                  << std::endl;
      }
   }

   out << "}" << std::endl;
}

} //Fin du namespace