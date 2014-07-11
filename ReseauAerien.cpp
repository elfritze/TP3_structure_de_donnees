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
   //Constructeur de copie
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
   //exception logic_error si fichierEntree n'est pas ouvert correctement.
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

   // ajout des trajets (arcs) au graphe
   getline(fichierEntree,line);
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
   //exception logic_error si SortieFichier n'est pas ouvert correctement.

   //À noter : SortieFichier n'est pas fermé par la fonction.
}

/**
 * \fn void ReseauAerien::viderReseau()
 */
void ReseauAerien::viderReseau()
{

}

/**
 * \fn ReseauAerien ReseauAerien::fermetureReseau()
 *
 * \return La fermeture transitive du réseau.
 */
ReseauAerien ReseauAerien::fermetureReseau()
{
   return ReseauAerien();
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

}//Fin du namespace
