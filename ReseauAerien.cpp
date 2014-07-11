/**
 * \file ReseauAerien.cpp
 * \brief Implémentattion de la classe ReseauAerien.
 * \author Éric Guillemette, Mathieu L'Écuyer
 * \version 0.1
 * \date juillet 2014
 *
 * Travail pratique numéro 3
 *
 */

#include "ReseauAerien.h"

/**
 * \namespace TP3
 *
 * Espace de nommage regroupant les définitions du TP3.
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
   unReseau = source.unReseau;   // Surcharge de l'opérateur d'affectation de la classe Graphe
   nomReseau = source.nomReseau;
}

/**
 * \fn ReseauAerien& ReseauAerien::operator=(const ReseauAerien& src)
 *
 * \param[in] src : Un objet ReseauAerien existant.
 *
 * \return L'objet courant contenant à présent les données de l'objet src.
 */
ReseauAerien& ReseauAerien::operator=(const ReseauAerien& src)
{
   if (this != &src)
   {
      unReseau = src.unReseau;   // Surcharge de l'opérateur d'affectation de la classe Graphe
      nomReseau = src.nomReseau;
   }

   return (*this);
}

/**
 * \fn std::ostream& operator<<(std::ostream& out, const ReseauAerien& g)
 *
 * \param[in] out : un stream vide dans lequel on va écrire.
 * \param[in] g : un objet ReseauAerien déjà existant.
 *
 * \return Le stream dans lequel on a écrit.
 */
std::ostream& operator<<(std::ostream& out, const ReseauAerien& g)
{
   return out << g.unReseau;
}

/**
 * \fn void ReseauAerien::chargerReseau(std::ifstream & fichierEntree)
 *
 * \param[in] fichierEntree : un flux d'entrée contenant un fichier texte.
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

   // lecture du fichier pour récupérer le nom du réseau aérien
   fichierEntree.ignore(15);
   getline(fichierEntree, nom);

   nomReseau = nom;

   // récupération du nombre de sommets et du nombre d'arcs (pour les compteurs des boucles)
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
      fichierEntree.ignore(1,'\n');

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
      fichierEntree.ignore(1,'\n');

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
	for (int i = 0; (unsigned)i < sommets.size(); i++)
	{
		Coordonnees coord = unReseau.getCoordonnesSommet(sommets.at(i));
		SortieFichier << sommets.at(i) << std::endl << coord.lt << " " << coord.lg << std::endl;
	}

	SortieFichier << "Liste des trajets:" << std::endl;
	for (int i = 0; (unsigned)i < sommets.size(); i++)
	{
		std::vector<std::string> adjacents = unReseau.listerSommetsAdjacents(sommets.at(i));
		for (int j = 0; (unsigned)j < adjacents.size(); j++)
		{
			Ponderations pond = unReseau.getPonderationsArc(sommets.at(i),adjacents.at(j));
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
 * \return La fermeture transitive du réseau.
 */
ReseauAerien ReseauAerien::fermetureReseau()
{
   ReseauAerien r;
   r.unReseau = unReseau;
   r.nomReseau = nomReseau;

   std::vector<std::string> sommets = r.unReseau.listerNomsSommets();

   for (int k = 0; (unsigned)k < sommets.size(); k++)
   {
      for (int i = 0; (unsigned)i < sommets.size(); i++)
      {
         for (int j = 0; (unsigned)j < sommets.size(); j++)
         {

            if(!r.unReseau.arcExiste(sommets.at(i),sommets.at(k)))
               r.unReseau.ajouterArc(sommets.at(i),sommets.at(k),INT_MAX,INT_MAX,INT_MAX);
            if(!r.unReseau.arcExiste(sommets.at(k),sommets.at(j)))
               r.unReseau.ajouterArc(sommets.at(k),sommets.at(j),INT_MAX,INT_MAX,INT_MAX);
            if(!r.unReseau.arcExiste(sommets.at(i),sommets.at(j)))
               r.unReseau.ajouterArc(sommets.at(i),sommets.at(j),INT_MAX,INT_MAX,INT_MAX);

            Ponderations pond1 = r.unReseau.getPonderationsArc(sommets.at(i),sommets.at(k));
            Ponderations pond2 = r.unReseau.getPonderationsArc(sommets.at(k),sommets.at(j));
            Ponderations pond3 = r.unReseau.getPonderationsArc(sommets.at(i),sommets.at(j));

            if(pond1.duree + pond2.duree < pond3.duree)
            {
               r.unReseau.enleverArc(sommets.at(i),sommets.at(j));
               r.unReseau.ajouterArc(sommets.at(i),sommets.at(j),pond1.duree + pond2.duree,
                                     pond1.cout + pond2.cout,pond1.ns + pond2.ns);
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
 * \param[in] origine : La ville origine (le départ).
 * \param[in] destination : La ville destination (l'arrivée).
 *
 * \return Le chemin trouvé est retourné sous forme d'un tableau de chaînes de caractères.
 */
std::vector<std::string> ReseauAerien::rechercheCheminLargeur(const std::string& origine,
                                                              const std::string& destination)
{
   //exception logic_error : si le départ ou l'arrivée ne fait pas partie du réseau aérien.

   std::vector<std::string> retour;
   return retour;
}

/**
 * \fn Chemin ReseauAerien::rechercheCheminDijkstra(const std::string& origine, const std::string&
 *                                                  destination, bool dureeCout)
 *
 * \param[in] origine : La ville origine (le départ).
 * \param[in] destination : La ville destination (l'arrivée).
 * \param[in] dureeCout : Un booléen true s'il faut utiliser la durée du vol comme pondération,
 *                        false s'il faut utiliser le coût du vol comme pondération sur les trajets.
 *
 * \return Le plus court chemin selon la pondération choisie est retourné dans une structure Chemin.
 */
Chemin ReseauAerien::rechercheCheminDijkstra(const std::string& origine, const std::string&
                                             destination, bool dureeCout)
{
   //exception logic_error : si le départ ou l'arrivée ne fait pas partie du réseau aérien.

   return Chemin();
}

/**
 * \fn Chemin ReseauAerien::bellManFord(const std::string& origine, const std::string& destination,
                                        int dureeCoutNiveau)
 *
 * \param[in] origine : La ville origine (le départ).
 * \param[in] destination : La ville destination (l'arrivée).
 * \param[in] dureeCoutNiveau : Un entier de valeur 1 s'il faut utiliser la durée du vol comme
 *                              pondération, 2 s'il faut utiliser le coût du vol ou 3 s'il faut
 *                              utiliser le niveau de sécurité.
 *
 * \return Le plus court chemin selon la pondération choisie est retourné dans une structure Chemin.
 */
Chemin ReseauAerien::bellManFord(const std::string& origine, const std::string& destination,
                                 int dureeCoutNiveau)
{
   //exception logic_error : si le départ ou l'arrivée ne fait pas partie du réseau aérien.

   //exception logic_error : si dureeCoutNiveau est différent des valeurs 1, 2 ou 3.

   return Chemin();
}

/**
 * \fn Chemin ReseauAerien::algorithmeAstar(const std::string& origine, const std::string&
 *                                          destination, bool dureeCout)
 *
 * \param[in] origine : La ville origine (le départ).
 * \param[in] destination : La ville destination (l'arrivée).
 * \param[in] dureeCout : Un booléen true s'il faut utiliser la durée du vol comme pondération,
 *                        false s'il faut utiliser le coût du vol comme pondération sur les trajets.
 *
 * \return Le plus court chemin selon la pondération choisie est retourné dans une structure Chemin.
 */
Chemin ReseauAerien::algorithmeAstar(const std::string& origine, const std::string& destination,
                                     bool dureeCout)
{
   //exception logic_error : si le départ ou l'arrivée ne fait pas partie du réseau aérien.

   return Chemin();
}

/**
 * \fn void ReseauAerien::displayInGraphviz(std::ostream & out, int dureeCoutNiveau)
 *
 * \param[in] out : un stream vide dans lequel on va écrire.
 * \param[in] dureeCoutNiveau : Un entier de valeur 1 s'il faut utiliser la durée du vol comme
 *                              pondération, 2 s'il faut utiliser le coût du vol ou 3 s'il faut
 *                              utiliser le niveau de sécurité.
 */
void ReseauAerien::displayInGraphviz(std::ostream & out, int dureeCoutNiveau)
{
   if (!out.good())
      throw std::logic_error("displayInGraphViz: fichier incorrect");

   if (dureeCoutNiveau < 1 || dureeCoutNiveau > 3)
      throw std::logic_error("displayInGraphviz: la valeur de l'entier doit être 1, 2 ou 3");

   out << "digraph g {" << std::endl;

   std::vector<std::string> sommets = unReseau.listerNomsSommets();
   for (int i = 0; (unsigned)i < sommets.size(); i++)
   {
      std::vector<std::string> arcs = unReseau.listerSommetsAdjacents(sommets.at(i));

      out << "\"" << sommets.at(i) << "\"" << std::endl;

      for (int j = 0; (unsigned)j < arcs.size(); j++)
      {
         Ponderations ponder = unReseau.getPonderationsArc(sommets.at(i),arcs.at(j));

         // Pondération pour la durée
         if (dureeCoutNiveau == 1)
            out << "\t \"" << sommets.at(i) << "\" -> \"" << arcs.at(j)
                << "\" [label=" << ponder.duree << "];" << std::endl;

         // Pondération pour le coût
         if (dureeCoutNiveau == 2)
            out << "\t \"" << sommets.at(i) << "\" -> \"" << arcs.at(j)
                << "\" [label=" << ponder.cout << "];" << std::endl;

         // Pondération pour le niveau de sécurité
         if (dureeCoutNiveau == 3)
            out << "\t \"" << sommets.at(i) << "\" -> \"" << arcs.at(j)
                << "\" [label=" << ponder.ns << "];" << std::endl;
      }
   }

   out << "}" << std::endl;
}

}//Fin du namespace
