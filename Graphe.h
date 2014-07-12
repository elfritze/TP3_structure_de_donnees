/**
 * \file Graphe.h
 * \brief Gestion d'un graphe.
 * \author �ric Guillemette, Mathieu L'�cuyer
 * \version 0.1
 * \date juillet 2014
 *
 * Travail pratique num�ro 3
 *
 */

#ifndef _GRAPHE__H
#define _GRAPHE__H

#include <cmath>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

/**
 * \namespace TP3
 *
 * Espace de nommage regroupant les d�finitions du TP3.
 */
namespace TP3
{

/**
 * \struct Ponderations
 * \brief Une struture utilis�e pour stocker les pond�rations utilis�es sur les arcs des sommets.
 */
struct Ponderations
{
   float duree; /*!< La dur�e du vol en heures (ex. 0.8 heures entre Qu�bec et Montr�al). */
   float cout;  /*!< Le cout du trajet en dollars (ex. 220.46 $ pour un vol entre Qu�bec et Montr�al). */
   int ns;      /*!< Un niveau de s�curit� repr�sentant un indice qui peut �tre n�gatif. */
};

/**
 * \struct Coordonnees
 * \brief Une structure utilis�e pour stocker les coordonn�es d'un sommet.
 */
struct Coordonnees
{
   float lt;  /*!< La latitude en d�cimale (ex. pour la ville de Qu�bec : 46.80). */
   float lg;  /*!< La longitude en d�cimale (ex. pour la ville de Qu�bec : -71.24). */
};

/**
 * \class Graphe
 * \brief Cette classe sert � repr�senter le type Graphe.
 */
class Graphe
{
public:

   /**
    * \brief Constructeur par d�faut.
    *
    * \post Un graphe vide est cr��.
    */
   Graphe();

   /**
    * \brief Destructeur.
    *
    * \post Le graphe a �t� d�truit.
    */
   ~Graphe();

   /**
    * \brief Constructeur de copie.
    *
    * \pre Il y a assez de m�moire.
    *
    * \exception bad_alloc : s'il n'y a pas assez de m�moire.
    */
   Graphe(const Graphe &source);

   /**
    * \brief Surcharge de l'op�rateur d'affectation.
    *
    * \pre Il doit y avoir assez de m�moire.
    *
    * \post Le graphe a un contenu identique � src.
    *
    * \exception bad_alloc : s'il n'y a pas assez de m�moire.
    */
   Graphe& operator=(const Graphe& src);

   /**
    * \brief Surcharge de l'op�rateur de sortie.
    *
    * \post Le nombre de sommets du graphe sera affich�.
    * \post Pour chaque sommet, son nom sera affich�.
    * \post Pour chaque sommet, les noms de tous ses voisins seront affich�s.
    */
   friend std::ostream& operator<<(std::ostream& out, const Graphe& g);

   /**
    * \brief Ajout d'un sommet au graphe.
    *
    * \pre Il doit y avoir assez de m�moire.
    * \pre Le sommet ne doit pas d�j� exister.
    *
    * \post Un sommet contenant les informations pass�es en argument a �t� ajout� au Graphe.
    *
    * \exception bad_alloc : si pas assez de m�moire pour allouer le nouveau sommet.
    * \exception logic_error : si le sommet existe d�j�.
    */
   void ajouterSommet(const std::string& nom, float lt, float lg);

   /**
    * \brief Ajout d'un arc au graphe.
    *
    * \pre Les deux sommets doivent exister.
    *
    * \post Un arc a �t� ajout� entre le sommet qui a le nom1 et le sommet qui a le nom2.
    *
    * \exception  bad_alloc : si pas assez de m�moire pour allouer le nouvel arc.
    * \exception  logic_error : si un des deux sommets n'existe pas.
    * \exception  logic_error : s'il y a d�j� un arc orient� entre ces deux sommets.
    */
   void ajouterArc(const std::string& nom1, const std::string& nom2, float duree, float cout, int ns);

   /**
    * \brief Enl�ve un sommet du graphe ainsi que tous les arcs qui vont et partent de ce sommet.
    *
    * \pre Le sommet doit exister.
    *
    * \post Le sommet identifi� par 'nom' a �t� enlev� du graphe.
    *
    * \exception logic_error : si le sommet sp�cifi� en argument n'existe pas.
    */
   void enleverSommet(const std::string& nom);

   /**
    * \brief Enl�ve un arc du graphe.
    *
    * \pre Les deux sommets identifi�s par leur nom doivent appartenir au graphe.
    * \pre Un arc reliant les deux sommets doit exister.
    *
    * \post Le graphe contient un arc en moins, le graphe inchang� sinon.
    *
    * \exception logic_error : si un des deux sommets, ou les deux, n'existent pas.
    * \exception logic_error : s'il n'y a pas d'arc entre les deux sommets.
    */
   void enleverArc(const std::string& nom1, const std::string& nom2);

   /**
    * \brief Retourne la liste des noms des sommets dans un vecteur de cha�nes de caract�res.
    *
    * \post Le graphe reste inchang�.
    */
   std::vector<std::string> listerNomsSommets() const;

   /**
    * \brief Retourne la liste des noms des sommets adjacents au sommet pass� en argument dans
    *        un vecteur de cha�nes de caract�res.
    *
    * \pre Le sommet doit appartenir au graphe.
    *
    * \post Le graphe reste inchang�.
    *
    * \exception logic_error : si le sommet n'existe pas.
    */
   std::vector<std::string> listerSommetsAdjacents(const std::string& nom) const;

   /**
    * \brief Retourne le nombre de sommets dans la liste des sommets.
    *
    * \post Le graphe reste inchang�.
    */
   int nombreSommets() const;

   /**
    * \brief Retourne le nombre d'arcs pr�sents dans le graphe.
    *
    * \post Le graphe reste inchang�.
    */
   int nombreArcs() const;

   /**
    * \brief Indique si la liste des sommets est vide.
    *
    * \post Le graphe reste inchang�.
    */
   bool estVide() const;

   /**
    * \brief Retourne l'existence d'un sommet.
    *
    * \post Le graphe reste inchang�.
    */
   bool sommetExiste(const std::string& nom) const;

   /**
    * \brief Retourne l'existence d'un arc.
    *
    * \pre Les sommets doivent appartenir au graphe.
    *
    * \post Le graphe reste inchang�.
    *
    * \exception logic_error : si l'un ou l'autre, ou les deux sommets ne font pas partie du graphe.
    */
   bool arcExiste(const std::string& sommetUn, const std::string& sommetDeux) const;

   /**
    * \brief Retourne les pond�rations d'un arc pass� en argument.
    *
    * \pre L'arc doit exister.
    *
    * \post Le graphe reste inchang�.
    *
    * \exception logic_error : si le sommet source et/ou destination n'existent pas.
    * \exception logic_error : si l'arc n'existe pas.
    */
   Ponderations getPonderationsArc(const std::string& sommetUn, const std::string& sommetDeux) const;

   /**
    * \brief Retourne le nom d'un sommet selon ses coordonn�es.
    *
    * \pre Le sommet doit faire partie du graphe.
    *
    * \post Le graphe reste inchang�.
    *
    * \exception logic_error : si le sommet n'existe pas.
    */
   std::string getNomSommet(float lt, float lg) const;

   /**
    * \brief Retourne les coordonn�es d'un sommet.
    *
    * \pre Le sommet doit exister.
    *
    * \post Le graphe reste inchang�.
    *
    * \exception logic_error : s'il n'y a pas de sommets dans le graphe.
    * \exception logic_error : si le sommet n'existe pas.
    */
   Coordonnees getCoordonnesSommet(const std::string& nom) const;

   /**
    * \brief Permet d'obtenir une distance entre deux sommets.
    *
    * \pre Les sommets doivent exister.
    *
    * \post Retourne la distance entre les sommets.
    *
    * \exception logic_error : si un des sommets n'existe pas.
    */
   float getDistance(const std::string& sommetUn, const std::string& sommetDeux) const;

   /**
    * \brief Destruction d'un graphe.
    *
    * \post Le graphe est d�truit.
    */
   void detruireGraphe();

   /**
    * \brief Retourne l'�tat d'un sommet pass� en argument.
    *
    * \pre Le sommet doit faire partie du graphe.
    *
    * \post Le graphe reste inchang�.
    *
    * \exception logic_error : si le sommet n'existe pas.
    */
   bool getEtatSommet(const std::string& nom) const;

   /**
    * \brief Change l'�tat d'un sommet pass� en argument � vrai.
    *
    * \pre Le sommet doit faire partie du graphe.
    *
    * \post L'�tat du sommet est maintenant �gal � vrai.
    *
    * \exception logic_error : si le sommet n'existe pas.
    */
   void marquerEtatSommet(const std::string& nom);

   /**
    * \brief Permet d'initialiser � faux l'�tat de tous les sommets du graphe.
    *
    * \post Tous les �tats des sommets du graphe sont maintenant faux.
    */
   void initialiserEtats();

private:
   class Sommet;	// Un sommet du graphe, on le d�clare ici � cause de la classe Arc qui s'en sert

   /**
    * \class Arc
    * \brief Description d'un arc qui est ici un trajet.
    */
   class Arc
   {
   public:
      Sommet * dest;			/*!< Un pointeur sur la ville de destination. */
      Ponderations ponder;	/*!< Les pond�rations utilis�es pour un trajet entre deux villes. */
      Arc * suivDest;		/*!< La prochaine ville de destination. */
   };

   /**
    * \class Sommet
    * \brief Noeud typique pour la description d'un sommet.
    */
   class Sommet
   {
   public:
      std::string nom;	  /*!< Le nom de la ville. */
      Coordonnees coord;  /*!< Les coordonn�es g�ospatiales de la ville. */
      Arc * listeDest;    /*!< La liste des arcs entre la ville et les villes qui lui sont adjacentes. */
      bool etat;			  /*!< Pour marquer une ville. */
      Sommet *precedent;  /*!< La ville pr�c�dente dans la liste des villes. */
      Sommet *suivant;	  /*!< La prochaine ville dans la liste. */

      /**
       * \brief Constructeur de la classe Sommet.
       *
       * \post Un noeud typique Sommet est initialis�.
       */
      explicit Sommet(std::string nom, Coordonnees coord, Arc * listeDest = 0, bool etat = false,
                      Sommet *precedent = 0, Sommet *suivant = 0) :
                      nom(nom), coord(coord), listeDest(listeDest), etat(etat),
                      precedent(precedent), suivant(suivant) {}
   };

   int nbSommets;          /*!< Le nombre de sommets dans le graphe. */
   int nbArcs;             /*!< Le nombre des arcs dans le graphe. */
   Sommet * listeSommets;	/*!< Liste des sommets du graphe. */


   // M�thode priv�e

   /**
    * \brief Cette m�thode priv�e sert � copier.
    *
    * \post Une copie profonde est cr��e.
    */
   void _copier(Sommet * ls);

};

} //Fin du namespace

#endif
