/**
 * \file Graphe.cpp
 * \brief Impl�mentation d'un graphe orient� o� chaque sommet poss�de un nom.
 * \author �ric Guillemette, Mathieu L'�cuyer
 * \version 0.1
 * \date juillet 2014
 *
 * Travail pratique num�ro 3
 *
 */

#include "Graphe.h"

/**
 * \namespace TP3
 *
 * Espace de nommage regroupant les d�finitions du TP3.
 */
namespace TP3
{

/**
 * \fn Graphe::Graphe()
 */
Graphe::Graphe()
{
   nbSommets = 0;
   nbArcs = 0;
   listeSommets = 0;
}

/**
 * \fn Graphe::~Graphe()
 */
Graphe::~Graphe()
{
   //detruireGraphe();
}

/**
 * \fn Graphe::Graphe(const Graphe &source)
 *
 * \param[in] source : Un objet Graphe existant.
 */
Graphe::Graphe(const Graphe &source)
{
   //Constructeur de copie
}

/**
 * \fn Graphe& Graphe::operator=(const Graphe& src)
 *
 * \param[in] src : Un objet Graphe existant.
 *
 * \return L'objet courant contenant � pr�sent les donn�es de l'objet source.
 */
Graphe& Graphe::operator=(const Graphe& src)
{
   return *this;
}

/**
 * \fn std::ostream& operator<<(std::ostream& out, const Graphe& g)
 *
 * \param[in] out : un stream vide dans lequel on va �crire.
 * \param[in] g : un objet Graphe d�j� existant.
 *
 * \return Le stream dans lequel on a �crit.
 */
std::ostream& operator<<(std::ostream& out, const Graphe& g)
{
   out << "Le graphe contient " << g.nbSommets << " sommet(s)" << std::endl;
   Graphe::Sommet* vertex = g.listeSommets;
   while (vertex != 0)
   {
      out << "Sommet : " << vertex->nom << std::endl;
      // Afficher les arcs.
      Graphe::Arc* arc = vertex->listeDest;
      if (arc != 0)
      {
         out << "Ce sommet a des liens vers le(s) sommet(s) :" << std::endl;
         while (arc->suivDest != 0)
         {
            out << arc->dest->nom << ", ";
            arc = arc->suivDest;
         }
         out << arc->dest->nom;
      }
      out << std::endl << std::endl;
      vertex = vertex->suivant;
   }
   return out;
}

/**
 * \fn bool Graphe::ajouterSommet(const std::string& nom) const
 *
 * \param[in] nom : Le nom du sommet
 * \param[in] lt : Latitude
 * \param[in] lg : Longitude
 */
void Graphe::ajouterSommet(const std::string& nom, float lt, float lg)
{
   //Exception si le sommet existe
   if (sommetExiste(nom))
      throw std::logic_error("ajouterSommet: Le sommet existe d�j�");

   //On cr�e la coordonn�e et le sommet
   Coordonnees coord = Coordonnees();
   coord.lg = lg;
   coord.lt = lt;
   Sommet * ajout = new Sommet(nom, coord);

   //Si la liste est vide
   if (listeSommets == 0)
   {
      listeSommets = ajout;
      nbSommets++;
   }
   else
   {
      //Sinon on ajoute � la fin
      Sommet * courant = 0;
      courant = listeSommets;
      while (courant->suivant != 0)
      {
         courant = courant->suivant;
      }
      courant->suivant = ajout;
      nbSommets++;
   }
}

/**
 * \fn void Graphe::ajouterArc(const std::string& nom1, const std::string& nom2,
 *                             float duree, float cout, int ns)
 *
 * \param[in] nom1 : Le nom du sommet #1.
 * \param[in] nom2 : Le nom du sommet #2.
 * \param[in] duree : La dur�e du vol en heures.
 * \param[in] cout : Le cout du trajet en dollars.
 * \param[in] ns : Un niveau de s�curit� repr�sentant un indice qui peut �tre n�gatif.
 */
void Graphe::ajouterArc(const std::string& nom1, const std::string& nom2,
                        float duree, float cout, int ns)
{
   //pr�condition : Les deux sommets doivent exister

   //exception : logic_error si un des deux sommets n'existe pas
   //exception : logic_error s'il y a d�j� un arc orient� entre ces deux sommets
}

/**
 * \fn void Graphe::enleverSommet(const std::string& nom)
 *
 * \param[in] nom : Le nom du sommet.
 */
void Graphe::enleverSommet(const std::string& nom)
{
   //pr�condition : Le sommet doit exister

   //exception : logic_error si le sommet sp�cifi� en argument n'existe pas
}

/**
 * \fn void Graphe::enleverArc(const std::string& nom1, const std::string& nom2)
 *
 * \param[in] nom1 : Le nom du sommet #1.
 * \param[in] nom2 : Le nom du sommet #2.
 */
void Graphe::enleverArc(const std::string& nom1, const std::string& nom2)
{
   //pr�condition : Les deux sommets identifi�s par leur nom doivent appartenir au graphe.
   //pr�condition : Un arc reliant les deux sommets doit exister.

   //exception : logic_error si un des deux sommets, ou les deux, n'existent pas
   //exception : logic_error s'il n'y a pas d'arc entre les 2 sommets
}

/**
 * \fn std::vector<std::string> Graphe::listerNomsSommets() const
 *
 * \return La liste des noms des sommets dans un vecteur de cha�nes de caract�res.
 */
std::vector<std::string> Graphe::listerNomsSommets() const
{
   std::vector<std::string> retour;
   Sommet * courant = 0;
   courant = listeSommets;
   while (courant != 0)
   {
      retour.push_back(courant->nom);
      courant = courant->suivant;
   }
   return retour;
}

/**
 * \fn std::vector<std::string> Graphe::listerSommetsAdjacents(const std::string& nom) const
 *
 * \param[in] nom : Le nom du sommet.
 *
 * \return La liste des noms des sommets adjacents au sommet pass� en argument dans un vecteur
 *         de cha�nes de caract�res.
 */
std::vector<std::string> Graphe::listerSommetsAdjacents(const std::string& nom) const
{
   //pr�condition : Le sommet doit appartenir au graphe.

   //exception : logic_error si le sommet n'existe pas


   std::vector<std::string> retour;
   return retour;
}

/**
 * \fn int Graphe::nombreSommets() const
 *
 * \return Le nombre de sommets dans la liste des sommets.
 */
int Graphe::nombreSommets() const
{
   return nbSommets;
}

/**
 * \fn bool Graphe::estVide() const
 *
 * \return VRAI si la liste des sommets est vide, FAUX sinon.
 */
bool Graphe::estVide() const
{
   return nbSommets == 0;
}

/**
 * \fn bool Graphe::sommetExiste(const std::string& nom) const
 *
 * \param[in] nom : Le nom du sommet.
 *
 * \return VRAI si le sommet existe dans le graphe, FAUX sinon.
 */
bool Graphe::sommetExiste(const std::string& nom) const
{
   if (listeSommets != 0)
   {
      Sommet * courant = 0;
      courant = listeSommets;
      //On parcoure la liste des sommets jusqu'� ce que l'on trouve le bon.
      while (courant != 0)
      {

         if (courant->nom == nom)
            return true;
         courant = courant->suivant;

      }
   }
   return false;
}

/**
 * \fn bool Graphe::arcExiste(const std::string& sommetUn, const std::string& sommetDeux) const
 *
 * \param[in] sommetUn : Le nom du sommet #1.
 * \param[in] sommetDeux : Le nom du sommet #2.
 *
 * \return VRAI s'il y a un arc qui existe entre les deux sommets, FAUX sinon.
 */
bool Graphe::arcExiste(const std::string& sommetUn, const std::string& sommetDeux) const
{
   //pr�condition : Les sommets doivent appartenir au graphe.

   //exception : logic_error si l'un ou l'autre, ou les 2 sommets ne font pas partie du graphe

   return false;
}

/**
 * \fn Ponderations Graphe::getPonderationsArc(const std::string& sommetUn,
 *                                             const std::string& sommetDeux) const
 *
 * \param[in] sommetUn : Le nom du sommet #1.
 * \param[in] sommetDeux : Le nom du sommet #2.
 *
 * \return Les pond�rations d'un arc pass� en argument.
 */
Ponderations Graphe::getPonderationsArc(const std::string& sommetUn, const std::string& sommetDeux) const
{
   //pr�condition : L'arc doit exister.

   //exception : logic_error si le sommet source et/ou destination n'existent pas.
   //exception : logic_error si l'arc n'existe pas.


   return Ponderations();
}

/**
 * \fn std::string Graphe::getNomSommet(float lt, float lg) const
 *
 * \param[in] lt : La latitude en d�cimale.
 * \param[in] lg : La longitude en d�cimale.
 *
 * \return Le nom d'un sommet selon ses coordonn�es dans une cha�ne de caract�res.
 */
std::string Graphe::getNomSommet(float lt, float lg) const
{
   //pr�condition : Le sommet doit faire partie du graphe.

   if (listeSommets != 0)
   {
      Sommet * courant = 0;
      courant = listeSommets;
      //On parcoure la liste des sommets jusqu'� ce que l'on trouve le bon.
      while (courant != 0)
      {
         if (courant->coord.lg == lg && courant->coord.lt == lt)
            return courant->nom;
         courant = courant->suivant;

      }
   }

   //Exception si le sommet n'existe pas
   throw std::logic_error("getNomSommet: Le sommet n'existe pas.");
}

/**
 * \fn Coordonnees Graphe::getCoordonnesSommet(const std::string& nom) const
 *
 * \param[in] nom : Le nom du sommet.
 *
 * \return Les coordonn�es d'un sommet.
 */
Coordonnees Graphe::getCoordonnesSommet(const std::string& nom) const
{
   //Exception si aucun sommet
   if (nbSommets == 0)
      throw std::logic_error("getCoordonnesSommet:  Il n'y a pas de sommets dans le graphe");

   //Exception si le sommet m'existe pas
   if (!sommetExiste(nom))
      throw std::logic_error("getNomSommet: Le sommet n'existe pas.");

   Sommet * courant = 0;
   courant = listeSommets;
   //On parcoure la liste des sommets jusqu'� ce que l'on trouve le bon.
   while (courant != 0)
   {
      if (courant->nom == nom)
         return courant->coord;
      courant = courant->suivant;
   }
}

/**
 * \fn float Graphe::getDistance(const std::string& sommetUn, const std::string& sommetDeux) const
 *
 * \param[in] sommetUn : Le nom du sommet #1.
 * \param[in] sommetDeux : Le nom du sommet #2.
 *
 * \return La distance entre deux sommets.
 */
float Graphe::getDistance(const std::string& sommetUn, const std::string& sommetDeux) const
{
   //pr�condition : les sommets doivent exister.

   //exception : logic_error si un des sommets n'existe pas.


   Coordonnees coordUn = getCoordonnesSommet(sommetUn);
   Coordonnees coordDeux = getCoordonnesSommet(sommetDeux);
   return sqrt(pow((coordUn.lt - coordDeux.lt), 2) + pow((coordUn.lg - coordDeux.lg), 2));
}

/**
 * \fn void detruireGraphe()
 */
void detruireGraphe()
{

}


} //Fin du namespace
