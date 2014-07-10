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
   detruireGraphe();
}

/**
 * \fn Graphe::Graphe(const Graphe &source)
 *
 * \param[in] source : Un objet Graphe existant.
 */
Graphe::Graphe(const Graphe &source)
{
   nbSommets = source.nbSommets;
   nbArcs = source.nbArcs;
   listeSommets = 0;

   if (source.listeSommets != 0)
   {
      _copier(source.listeSommets);
   }
}

/**
 * \fn Graphe& Graphe::operator=(const Graphe& src)
 *
 * \param[in] src : Un objet Graphe existant.
 *
 * \return L'objet courant contenant � pr�sent les donn�es de l'objet src.
 */
Graphe& Graphe::operator=(const Graphe& src)
{
   if (this != &src)
   {
      // Si l'objet courant n'est pas vide
      if (nbSommets != 0)
      {
         detruireGraphe();
      }

      // On copie � partir du d�but
      nbSommets = src.nbSommets;
      nbArcs = src.nbArcs;
      listeSommets = 0;

      if (src.listeSommets != 0)
      {
         _copier(src.listeSommets);
      }
   }

   return (*this);
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
 * \param[in] nom : Le nom du sommet.
 * \param[in] lt : La latitude en d�cimale.
 * \param[in] lg : La longitude en d�cimale.
 */
void Graphe::ajouterSommet(const std::string& nom, float lt, float lg)
{
   //Exception si le sommet existe d�j�
   if (sommetExiste(nom))
      throw std::logic_error("ajouterSommet: Le sommet existe d�j�");

   //On cr�e la coordonn�e et le sommet
   Coordonnees coord;
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
   bool existeSommet1 = false;
   bool existeSommet2 = false;
   Sommet * sommet1 = 0;
   Sommet * sommet2 = 0;
   Sommet * sommetCourant = listeSommets;

   // On parcourt la liste des sommets pour trouver les deux sommets
   for (int i = 0; i < nbSommets; i++)
   {
      if (sommetCourant->nom == nom1)
      {
         sommet1 = sommetCourant;
         existeSommet1 = true;
      }

      if (sommetCourant->nom == nom2)
      {
         sommet2 = sommetCourant;
         existeSommet2 = true;
      }

      sommetCourant = sommetCourant->suivant;
   }

   // Exception si un des deux sommets n'existe pas
   if (!existeSommet1 || !existeSommet2)
      throw std::logic_error("ajouterArc: Un des deux sommets n'existe pas.");

   // Exception s'il y a d�j� un arc orient� entre ces deux sommets
   if (arcExiste(nom1, nom2))
      throw std::logic_error("ajouterArc: Un arc existe d�j� entre ces deux sommets.");


   // Pond�rations de l'arc
   Ponderations newPonder;
   newPonder.duree = duree;
   newPonder.cout = cout;
   newPonder.ns = ns;

   // On cr�e l'arc � ajouter
   Arc * ajout = new Arc;
   ajout->dest = sommet2;
   ajout->ponder = newPonder;
   ajout->suivDest = 0;


   // pointeur de service
   Arc* courant = sommet1->listeDest;

   // On fait l'ajout dans listeDest
   if (courant == 0)
   {
      // Si listeDest de sommetUn est vide, on ajoute au d�but
      sommet1->listeDest = ajout;
      nbArcs++;
   }
   else
   {
      // On cherche le dernier arc de la liste
      while (courant->suivDest != 0)
         courant = courant->suivDest;

      // On ajoute l'arc � la fin
      courant->suivDest = ajout;
      nbArcs++;
   }
}

/**
 * \fn void Graphe::enleverSommet(const std::string& nom)
 *
 * \param[in] nom : Le nom du sommet.
 */
void Graphe::enleverSommet(const std::string& nom)
{
   //exception : logic_error si le sommet sp�cifi� en argument n'existe pas


   // Penser � faire un delete sur tous les arcs du sommet � supprimer
}

/**
 * \fn void Graphe::enleverArc(const std::string& nom1, const std::string& nom2)
 *
 * \param[in] nom1 : Le nom du sommet #1.
 * \param[in] nom2 : Le nom du sommet #2.
 */
void Graphe::enleverArc(const std::string& nom1, const std::string& nom2)
{
   // Exception si un des deux sommets, ou les deux, n'existent pas
   if (!sommetExiste(nom1) || !sommetExiste(nom2))
      throw std::logic_error("enleverArc: Un des deux sommets n'existe pas.");

   // On parcourt la liste des sommets pour trouver le sommet de nom1
   Sommet * sommet1 = 0;
   Sommet * sommetCourant = listeSommets;
   for (int i = 0; i < nbSommets; i++)
   {
      if (sommetCourant->nom == nom1)
      {
         sommet1 = sommetCourant;
         break;
      }

      sommetCourant = sommetCourant->suivant;
   }

   // On cherche l'arc � supprimer dans la liste
   bool existe = false;
   Arc * aSupprimer = sommet1->listeDest;

   // On redirige les pointeurs suivDest avant de supprimer
   // Si l'arc � supprimer est le premier de la liste
   if (sommet1->listeDest->dest->nom == nom2)
   {
      sommet1->listeDest = aSupprimer->suivDest;
      existe = true;
   }
   else
   {
      // Sinon, on cherche l'arc pr�c�dent � celui � supprimer
      Arc * precedent = aSupprimer;
      while (precedent->suivDest != 0)
      {
         if (precedent->suivDest->dest->nom == nom2)
         {
            // et on trouve l'arc � supprimer
            aSupprimer = precedent->suivDest;
            existe = true;
            break;
         }
         precedent = precedent->suivDest;
      }

      // on redirige le pointeur
      precedent->suivDest = aSupprimer->suivDest;
   }

   // Exception s'il n'y a pas d'arc entre les deux sommets
   if (!existe)
      throw std::logic_error("enleverArc: L'arc n'existe pas.");

   // On supprime l'arc
   aSupprimer->dest = 0;
   aSupprimer->suivDest = 0;
   delete aSupprimer;
   nbArcs--;
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
   bool existeSommet = false;
   Sommet * sommet = 0;
   Sommet * sommetCourant = listeSommets;

   // On parcourt la liste des sommets pour trouver le sommet
   for (int i = 0; i < nbSommets; i++)
   {
      if (sommetCourant->nom == nom)
      {
         sommet = sommetCourant;
         existeSommet = true;
         break;
      }

      sommetCourant = sommetCourant->suivant;
   }

   // Exception si le sommet n'existe pas
   if (!existeSommet)
      throw std::logic_error("listerSommetsAdjacents: Le sommet n'existe pas.");

   // On parcourt la liste des arcs du sommet pour retourner les destinations dans le vecteur
   std::vector<std::string> retour;
   Arc * courant = sommet->listeDest;
   while (courant != 0)
   {
      retour.push_back(courant->dest->nom);
      courant = courant->suivDest;
   }

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

      // On parcourt la liste des sommets jusqu'� ce que l'on trouve le bon.
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
   // Exception si l'un ou l'autre, ou les 2 sommets ne font pas partie du graphe
   if (!sommetExiste(sommetUn) || !sommetExiste(sommetDeux))
      throw std::logic_error("arcExiste: Un des sommets n'existe pas.");


   // On parcourt la liste des sommets pour trouver le sommetUn
   Sommet * sommetCourant = listeSommets;
   for (int i = 0; i < nbSommets; i++)
   {
      if (sommetCourant->nom == sommetUn)
         break;

      sommetCourant = sommetCourant->suivant;
   }

   // On parcourt la liste des arcs du sommetUn
   Arc * courant = sommetCourant->listeDest;
   while (courant != 0)
   {
      if (courant->dest->nom == sommetDeux)
         return true;

      courant = courant->suivDest;
   }

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
   // Exception si le sommet source et/ou destination n'existent pas
   if (!sommetExiste(sommetUn) || !sommetExiste(sommetDeux))
      throw std::logic_error("getPonderationsArc: Un des deux sommets n'existe pas.");


   // On parcourt la liste des sommets pour trouver le sommetUn
   Sommet * sommet1 = 0;
   Sommet * sommetCourant = listeSommets;
   for (int i = 0; i < nbSommets; i++)
   {
      if (sommetCourant->nom == sommetUn)
      {
         sommet1 = sommetCourant;
         break;
      }

      sommetCourant = sommetCourant->suivant;
   }

   // On parcourt la liste des arcs du sommetUn pour trouver celui vers sommetDeux
   bool existe = false;
   Arc * courant = sommet1->listeDest;
   while (courant != 0)
   {
      if (courant->dest->nom == sommetDeux)
      {
         existe = true;
         break;
      }

      courant = courant->suivDest;
   }

   //Exception si l'arc n'existe pas.
   if (!existe)
      throw std::logic_error("getPonderationsArc: L'arc n'existe pas.");


   //On retourne la pond�ration de l'arc courant
   Ponderations arcPonder;
   arcPonder.duree = courant->ponder.duree;
   arcPonder.cout = courant->ponder.cout;
   arcPonder.ns = courant->ponder.ns;

   return arcPonder;
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
   if (listeSommets != 0)
   {
      Sommet * courant = 0;
      courant = listeSommets;

      //On parcourt la liste des sommets jusqu'� ce que l'on trouve le bon.
      while (courant != 0)
      {
         if (courant->coord.lt == lt && courant->coord.lg == lg)
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
      throw std::logic_error("getCoordonnesSommet: Il n'y a pas de sommet dans le graphe.");

   //Exception si le sommet n'existe pas
   if (!sommetExiste(nom))
      throw std::logic_error("getCoordonnesSommet: Le sommet n'existe pas.");


   Coordonnees coordonnesSommet;
   Sommet * courant = 0;
   courant = listeSommets;

   //On parcourt la liste des sommets jusqu'� ce que l'on trouve le bon.
   while (courant != 0)
   {
      if (courant->nom == nom)
      {
         coordonnesSommet = courant->coord;
         break;
      }
      courant = courant->suivant;
   }

   return coordonnesSommet;
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
   //Exception si un des sommets n'existe pas.
   if (!sommetExiste(sommetUn) || !sommetExiste(sommetDeux))
      throw std::logic_error("getDistance: Un des sommets n'existe pas.");

   Coordonnees coordUn = getCoordonnesSommet(sommetUn);
   Coordonnees coordDeux = getCoordonnesSommet(sommetDeux);

   return sqrt(pow((coordUn.lt - coordDeux.lt), 2) + pow((coordUn.lg - coordDeux.lg), 2));
}

/**
 * \fn void Graphe::detruireGraphe()
 */
void Graphe::detruireGraphe()
{
   if (!estVide())
   {
      Sommet * tempSommet = listeSommets;
      Sommet * sommetCourant = listeSommets;
      Arc * arcCourant = sommetCourant->listeDest;
      Arc * tempArc = arcCourant;

      // On supprime tous les sommets de la liste des sommets
      while (tempSommet != 0)
      {
         tempSommet = sommetCourant->suivant;

         // On supprime tous les arcs partant du sommet
         while (arcCourant != 0)
         {
            tempArc = arcCourant->suivDest;

            arcCourant->dest = 0;
            arcCourant->suivDest = 0;
            delete arcCourant;

            arcCourant = tempArc;
         }

         sommetCourant->listeDest = 0;
         sommetCourant->precedent = 0;
         sommetCourant->suivant = 0;
         delete sommetCourant;

         sommetCourant = tempSommet;
      }

      nbSommets = 0;
      nbArcs = 0;
      listeSommets = 0;
   }
}

/**
 * \fn void Graphe::_copier(Sommet * ls)
 *
 * \param[in] ls : un pointeur sur la liste des sommets de la source.
 */
void Graphe::_copier(Sommet * ls)
{
   try
   {
      // On copie le premier sommet
      Sommet * s1 = ls;
      listeSommets = new Sommet(s1->nom, s1->coord);

      // On copie le reste de la liste des sommets
      Sommet * nouveau = listeSommets;
      for (Sommet * temp = s1->suivant; temp != 0; temp = temp->suivant)
      {
         nouveau->suivant = new Sommet(temp->nom, temp->coord);
         nouveau = nouveau->suivant;
      }

      // On copie tous les arcs de chacun des sommets

      Sommet * dest = 0;             // pointeur pour trouver le sommet de destination
      Sommet * temp = listeSommets;  // pointeur sur la liste des sommets
      Sommet * listeSource = ls;     // pointeur sur la liste des sommets de la source
      Arc * arcs = ls->listeDest;    // pointeur sur la liste de destination (les arcs)

      for (Sommet * courant = listeSommets; courant != 0; courant = courant->suivant)
      {
         // Tant qu'il y a des arcs dans la liste de destination du sommet
         while (arcs != 0)
         {
            // On cr�e l'arc � ajouter
            Arc * ajout = new Arc;

            // On cherche le sommet de destination dans listeSommets
            while (temp != 0)
            {
               if (arcs->dest->nom == temp->nom)
               {
                  dest = temp;
                  break;
               }

               temp = temp->suivant;
            }

            // On initialise les attributs de l'arc
            ajout->dest = dest;
            ajout->ponder = arcs->ponder;
            ajout->suivDest = 0;

            // pointeur de service
            Arc* arcCourant = courant->listeDest;

            // On fait l'ajout dans listeDest
            if (arcCourant == 0)
            {
               // Si listeDest de sommetUn est vide, on ajoute au d�but
               courant->listeDest = ajout;
            }
            else
            {
               // Sinon, on trouve le dernier arc
               while (arcCourant->suivDest != 0)
                  arcCourant = arcCourant->suivDest;

               // On ajoute l'arc � la fin
               arcCourant->suivDest = ajout;
            }

            // On passe � l'arc suivant dans la m�me liste de destination
            arcs = arcs->suivDest;
         }

         // On met � jour les pointeurs pour la boucle
         temp = listeSommets;
         listeSource = listeSource->suivant;

         if (listeSource != 0)
            arcs = listeSource->listeDest;
      }

   }
   catch (std::exception&)
   {
      // Il y a une erreur d'allocation de m�moire
      // Il faut lib�rer la m�moire d�j� allou�e
      detruireGraphe();

      // On relance alors l'exception pour indiquer qu'une erreur est survenue
      throw;
   }
}


} //Fin du namespace
