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
   //Constructeur de copie
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
   //exception logic_error si fichierEntree n'est pas ouvert correctement.
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

   //� noter : SortieFichier n'est pas ferm� par la fonction.
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
 * \return La fermeture transitive du r�seau.
 */
ReseauAerien ReseauAerien::fermetureReseau()
{
   return ReseauAerien();
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
   //exception logic_error : si le d�part ou l'arriv�e ne fait pas partie du r�seau a�rien.

   std::vector<std::string> retour;
   return retour;
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
Chemin ReseauAerien::rechercheCheminDijkstra(const std::string& origine, const std::string&
                                             destination, bool dureeCout)
{
   //exception logic_error : si le d�part ou l'arriv�e ne fait pas partie du r�seau a�rien.

   return Chemin();
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

   //exception logic_error : si dureeCoutNiveau est diff�rent des valeurs 1, 2 ou 3.

   return Chemin();
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

   return Chemin();
}

}//Fin du namespace
