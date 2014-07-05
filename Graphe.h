/**
 * \file Graphe.h
 * \brief Gestion d'un graphe.
 * \author ...
 * \version 0.1
 * \date ...
 *
 *  Travail pratique numéro 3
 *
 */

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>
//Vous pouvez ajouter d'autres librairies de la STL


#ifndef _GRAPHE__H
#define _GRAPHE__H

namespace TP3
{

	// Une struture utilisée pour stocker les pondérations utilisées sur les arcs des sommets
	struct Ponderations
	{
		float duree;		// La durée du vol en heures (ex. 0.8 heures entre Québec et Montréal)
		float cout;			// Le cout du trajet en dollars (ex. 220.46 $ pour un vol entre Québec et Montréal)
		int ns;				// Un niveau de sécurité représentant un indice qui peut être négatif
	};

	// Une structure utilisée pour stocker les coordonnées d'un sommet
	struct Coordonnees	 
	{
		float lt;			// La latitude en décimale (ex. pour la ville de Québec : 46.80)
		float lg;			// La longitude en décimale (ex. pour la ville de Québec : -71.24)
	};

	class Graphe	// Pour représenter le type Graphe
	{
	public:

      /**
       * \brief      Constructeur par défaut
       * \post       Un graphe vide est créé
       */
        Graphe();
        
      /**
       * \brief      Destructeur
       * \post       Le graphe a été détruit 
       */
        ~Graphe();
            
      /**
		* \brief Constructeur de copie.
		* \pre Il y a assez de mémoire.
		* \exception bad_alloc S'il n'y a pas assez de mémoire.
		*/
        Graphe(const Graphe &source);
        
      /**
		* \brief Surcharge de l'opérateur d'affectation.
		* \pre Il doit y avoir assez de mémoire.
		* \post Le graphe a un contenu identique à src.
		* \exception bad_alloc s'il n'y a pas assez de mémoire.
		*/
		Graphe& operator=(const Graphe& src);

		/**
		* \brief Surcharge de l'opérateur de sortie.
		* \post Le nombre de sommets du graphe sera affiché  
		* \post chaque sommet, son nom sera affiché  
		* \post pour chaque sommet, le nom de tous ses voisins seront affichés
		*/
		friend std::ostream& operator<<(std::ostream& out, const Graphe& g)
		{
			out << "Le graphe contient " << g.nbSommets << " sommet(s)" << std::endl;
			Sommet* vertex = g.listeSommets;
			while (vertex != 0)
			{
				out << "Sommet : " << vertex->nom << std::endl;
				// Afficher les arcs.	
				Arc* arc = vertex->listeDest;
				if(arc != 0)
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
       * \brief Ajout d'un sommet au graphe
	   * \pre Il doit y avoir assez de mémoire.
       * \pre Le sommet ne doit pas déjà exister
       * \post Un sommet content les informations passées en argument a été ajouté au Graphe
       * \exception bad_alloc Pas assez de mémoire pour alloué le nouveau sommet
       * \exception logic_error Le sommet existe déjà
       */       
        void ajouterSommet(const std::string& nom, float lt, float lg);
        
       /**
       * \brief Ajout d'un arc au graphe
       * \pre Les deux sommets doivent exister
       * \post Un arc a été ajouté entre le sommet qui a le nom1 et le sommet qui a le nom2
       * \exception  bad_alloc Pas assez de mémoire pour alloué le nouvel arc
       * \exception  logic_error Un des deux sommets n'existe pas
       * \exception  logic_error Il y a déjà un arc orienté entre ces deux sommets
       */ 
		void ajouterArc(const std::string& nom1, const std::string& nom2, float duree, float cout, int ns);
        
       /**
       * \brief Enlève un sommet du graphe ainsi que tous les arcs qui vont et partent de ce sommet
       * \pre Le sommet doit exister
       * \post Le sommet identifié par 'nom' a été enlevé du graphe
       * \exception logic_error Le sommet spécifié en argument n'existe pas
       */
        void enleverSommet(const std::string& nom);
        
       /**
       * \brief Enlève un arc du graphe
       * \pre Les deux sommets identifiés par leur nom doivent appartenir au graphe.
	   * \pre Un arc reliant les deux sommets doit exister.
       * \post Le graphe contient un arc en moins, le graphe inchangé sinon
       * \exception logic_error Un des deux sommets, ou les deux, n'existent pas
       * \exception logic_error Il n'y a pas d'arc entre les 2 sommets  
       */
        void enleverArc(const std::string& nom1, const std::string& nom2);
        
		/**
		 * \brief Retourne la liste des noms des sommets dans un vecteur de chaînes de caractères
		 * \post Le graphe reste inchangé.
		 */
        std::vector<std::string> listerNomsSommets() const;
		
       /**
       * \brief Retourne la liste des noms des sommets adjacents au sommet passé en argument dans un vecteur de chaînes de caractères
       * \pre Le sommet doit appartenir au graphe
	   * \post Le graphe reste inchangé.
       * \exception logic_error si le sommet n'existe pas
       */
        std::vector<std::string> listerSommetsAdjacents(const std::string& nom) const;
        
       /**
       * \brief Retourne le nombre de sommets dans la liste des sommets
	   * \post Le graphe reste inchangé.
       */
        int nombreSommets() const;
        
       /**
       * \brief Indique si la liste des sommets est vide
	   * \post Le graphe reste inchangé
       */
        bool estVide() const;
        
       /**
       * \brief Retourne l'existence d'un sommet
	   * \post Le graphe reste inchangé.
       */
        bool sommetExiste(const std::string& nom) const;
        
       /**
       * \brief Retourne l'existence d'un arc
       * \pre Les sommets doivent appartenir au graphe
	   * \post Le graphe reste inchangé.
       * \exception logic_error L'un ou l'autre, ou les 2 sommets ne font pas partie du graphe
       */
        bool arcExiste(const std::string& sommetUn, const std::string& sommetDeux) const;
        
       /**
       * \brief Retourne les pondérations d'un arc passé en argument
       * \pre L'arc doit exister
	   * \post Le graphe reste inchangé.
       * \exception logic_error Le sommet source et/ou destination n'existent pas
       * \exception logic_error L'arc n'existe pas
       */
        Ponderations getPonderationsArc(const std::string& sommetUn, const std::string& sommetDeux) const;

       /**
       * \brief Retourne le nom d'un sommet selon ses coordonnées
       * \pre Le sommet doit faire partie du graphe
	   * \post Le graphe reste inchangé.
       * \exception logic_error Le sommet n'existe pas
       */
        std::string getNomSommet(float lt, float lg) const;
        
       /**
       * \brief Retourne les coordonnées d'un sommet
       * \pre Le sommet doit exister
	   * \post Le graphe reste inchangé.
       * \exception logic_error Il n'y a pas de sommets dans le graphe
       * \exception logic_error Le sommet n'existe pas
       */
        Coordonnees getCoordonnesSommet(const std::string& nom) const;

		/**
		 * \brief Obtenir une distance entre deux sommets.
		 * Cette fonction permet d'obtenir la distance entre deux sommets.
		 * \pre Les sommets doivent exister.
		 * \post Retourne la distance entre les sommets.
		 * \exception logic_error si un des sommets n'existe pas.
		 */
		float getDistance(const std::string& sommetUn, const std::string& sommetDeux) const;

       /**
        * \brief Destruction d'un graphe
        * \post Le graphe est détruit
        */
		void detruireGraphe();

		//Vous pouvez ajoutez d'autres méthodes publiques si vous sentez leur nécessité

        
	private:
		class Sommet;		// Un sommet du graphe, on le déclare ici à cause de la classe Arc qui s'en sert

		class Arc			// Description d'un arc qui est ici un trajet
		{
		public:         
			Sommet * dest;			// Un pointeur sur la ville de destination
			Ponderations ponder;	// Les pondérations utilisées pour un trajet entre deux villes	
			Arc *  suivDest;		// La prochaine ville de destination

		};
		
		class Sommet		// Description d'un sommet
		{
		public:
			std::string nom;		// Le nom de la ville
			Coordonnees coord;		// Les coordonnées géospatiales de la ville
			Arc * listeDest;		// La liste des arcs entre la ville et les villes qui lui sont adjacentes
			bool etat;			    // Pour marquer une ville
			Sommet *precedent;		// La ville précédente dans la liste des villes
			Sommet *suivant;		// La prochaine ville dans la liste

			explicit Sommet(std::string nom,Coordonnees coord,Arc* listeDest = 0,bool etat = false,Sommet *precedent = 0,Sommet *suivant = 0) :
                           nom(nom),coord(coord),listeDest(listeDest),etat(etat),precedent(precedent),suivant(suivant){}
		};

		int nbSommets;					// Le nombre de sommets dans le graphe
		int nbArcs;						// Le nombre des arcs dans le graphe
		Sommet * listeSommets;			// Liste des sommets du graphe
        
		//Vous pouvez ajoutez d'autres méthodes privées si vous sentez leur nécessité
       
	};

}//Fin du namespace

#endif