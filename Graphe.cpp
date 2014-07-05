/**
 * \file Graphe.cpp
 * \brief Implémentation d'un graphe orienté où chaque sommet un nom.
 * \author ...
 * \version 0.1
 * \date ...
 *
 *  Travail pratique numéro 3
 *
 */

#include "Graphe.h"
//vous pouvez inclure d'autres librairies si c'est nécessaire

namespace TP3
{

		//À compléter par l'implémentation des méthodes demandées
		Graphe::Graphe(){
			nbSommets = 0;
			nbArcs = 0;
			listeSommets = 0;
		}


        
      /**
       * \brief      Destructeur
       * \post       Le graphe a été détruit 
       */
        Graphe::~Graphe()
		{
			//detruireGraphe();
		}
            
      /**
		* \brief Constructeur de copie.
		* \pre Il y a assez de mémoire.
		* \exception bad_alloc S'il n'y a pas assez de mémoire.
		*/
        Graphe::Graphe(const Graphe &source)
		{

		}
        
      /**
		* \brief Surcharge de l'opérateur d'affectation.
		* \pre Il doit y avoir assez de mémoire.
		* \post Le graphe a un contenu identique à src.
		* \exception bad_alloc s'il n'y a pas assez de mémoire.
		*/
		Graphe& Graphe::operator=(const Graphe& src)
		{
			return *this;
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
			if(sommetExiste(nom))
				throw std::logic_error("ajouterSommet: Le sommet existe déjà");

			//On crée la coordonnée et le sommet
			Coordonnees coord = Coordonnees();
			coord.lg = lg;
			coord.lt = lt;
			Sommet * ajout = new Sommet(nom, coord);
			
			//Si la liste est vide
			if(listeSommets == 0)
			{
				listeSommets = ajout;
				nbSommets++;
			}
			else
			{
				//Sinon on ajoute à la fin
				Sommet * courant = 0;
				courant = listeSommets;
				while(courant->suivant != 0)
				{
					courant = courant->suivant;
				}
				courant->suivant = ajout;
				nbSommets++;
			}



		}
        
       /**
       * \brief Ajout d'un arc au graphe
       * \pre Les deux sommets doivent exister
       * \post Un arc a été ajouté entre le sommet qui a le nom1 et le sommet qui a le nom2
       * \exception  bad_alloc Pas assez de mémoire pour alloué le nouvel arc
       * \exception  logic_error Un des deux sommets n'existe pas
       * \exception  logic_error Il y a déjà un arc orienté entre ces deux sommets
       */ 
		void Graphe::ajouterArc(const std::string& nom1, const std::string& nom2, float duree, float cout, int ns)
		{

		}
        
       /**
       * \brief Enlève un sommet du graphe ainsi que tous les arcs qui vont et partent de ce sommet
       * \pre Le sommet doit exister
       * \post Le sommet identifié par 'nom' a été enlevé du graphe
       * \exception logic_error Le sommet spécifié en argument n'existe pas
       */
        void Graphe::enleverSommet(const std::string& nom)
		{

		}
        
       /**
       * \brief Enlève un arc du graphe
       * \pre Les deux sommets identifiés par leur nom doivent appartenir au graphe.
	   * \pre Un arc reliant les deux sommets doit exister.
       * \post Le graphe contient un arc en moins, le graphe inchangé sinon
       * \exception logic_error Un des deux sommets, ou les deux, n'existent pas
       * \exception logic_error Il n'y a pas d'arc entre les 2 sommets  
       */
        void Graphe::enleverArc(const std::string& nom1, const std::string& nom2)
		{

		}
        
		/**
		 * \brief Retourne la liste des noms des sommets dans un vecteur de chaînes de caractères
		 * \post Le graphe reste inchangé.
		 */
        std::vector<std::string> Graphe::listerNomsSommets() const
		{
			std::vector<std::string> retour;
			return retour;
		}
		
       /**
       * \brief Retourne la liste des noms des sommets adjacents au sommet passé en argument dans un vecteur de chaînes de caractères
       * \pre Le sommet doit appartenir au graphe
	   * \post Le graphe reste inchangé.
       * \exception logic_error si le sommet n'existe pas
       */
        std::vector<std::string> Graphe::listerSommetsAdjacents(const std::string& nom) const
		{
			std::vector<std::string> retour;
			return retour;
		}
        
       /**
		 * \fn int Graphe::nombreSommets() const
		 *
		 */ 
        int Graphe::nombreSommets() const
		{
			return nbSommets;
		}
        
       /**
		 * \fn bool Graphe::estVide() const
		 *
		 */ 
        bool Graphe::estVide() const
		{
			return nbSommets==0;
		}
        
       /**
		 * \fn bool Graphe::sommetExiste(const std::string& nom) const
		 *
		 * \param[in] nom : Le nom du sommet
		 */
        bool Graphe::sommetExiste(const std::string& nom) const
		{
			if(listeSommets != 0)
			{
				Sommet * courant = 0;
				courant = listeSommets;
				//On parcoure la liste des sommets jusqu'à ce que l'on trouve le bon.
				while(courant->suivant != 0)
				{
					courant = courant->suivant;
					if(courant->nom == nom)
						return true;
					
				}
			}
			return false;
		}
        
       /**
       * \brief Retourne l'existence d'un arc
       * \pre Les sommets doivent appartenir au graphe
	   * \post Le graphe reste inchangé.
       * \exception logic_error L'un ou l'autre, ou les 2 sommets ne font pas partie du graphe
       */
        bool Graphe::arcExiste(const std::string& sommetUn, const std::string& sommetDeux) const
		{
			return false;
		}
        
       /**
       * \brief Retourne les pondérations d'un arc passé en argument
       * \pre L'arc doit exister
	   * \post Le graphe reste inchangé.
       * \exception logic_error Le sommet source et/ou destination n'existent pas
       * \exception logic_error L'arc n'existe pas
       */
        Ponderations Graphe::getPonderationsArc(const std::string& sommetUn, const std::string& sommetDeux) const
		{
			return Ponderations();
		}

       /**
		 * \fn std::string Graphe::getNomSommet(float lt, float lg) const
		 *
		 * \param[in] lt : Latitude
		 * \param[in] lg : Longitude
		 */
        std::string Graphe::getNomSommet(float lt, float lg) const
		{
			
			if(listeSommets != 0)
			{
				Sommet * courant = 0;
				courant = listeSommets;
				//On parcoure la liste des sommets jusqu'à ce que l'on trouve le bon.
				while(courant->suivant != 0)
				{
					courant = courant->suivant;
					if(courant->coord.lg == lg && courant->coord.lt == lt)
						return courant->nom;
					
				}
			}

			//Exception si le sommet m'existe pas
			throw std::logic_error("getNomSommet: Le sommet n'existe pas.");
		}
        
		/**
		 * \fn Coordonnees Graphe::getCoordonnesSommet(const std::string& nom) const
		 *
		 * \param[in] nom : Nom du sommet
		 */
        Coordonnees Graphe::getCoordonnesSommet(const std::string& nom) const
		{
			//Exception si aucun sommet
			if(nbSommets == 0)
				throw std::logic_error("getCoordonnesSommet:  Il n'y a pas de sommets dans le graphe");

			//Exception si le sommet m'existe pas
			if(!sommetExiste(nom))
				throw std::logic_error("getNomSommet: Le sommet n'existe pas.");


			Sommet * courant = 0;
			courant = listeSommets;
			//On parcoure la liste des sommets jusqu'à ce que l'on trouve le bon.
			while(courant->suivant != 0)
			{
				courant = courant->suivant;
				if(courant->nom == nom)
					return courant->coord;			
			}	
		}

		/**
		 * \brief Obtenir une distance entre deux sommets.
		 * Cette fonction permet d'obtenir la distance entre deux sommets.
		 * \pre Les sommets doivent exister.
		 * \post Retourne la distance entre les sommets.
		 * \exception logic_error si un des sommets n'existe pas.
		 */
		float Graphe::getDistance(const std::string& sommetUn, const std::string& sommetDeux) const
		{
			Coordonnees coordUn = getCoordonnesSommet(sommetUn);
			Coordonnees coordDeux = getCoordonnesSommet(sommetDeux);
			return sqrt(pow((coordUn.lt-coordDeux.lt),2) + pow((coordUn.lg-coordDeux.lg),2));
		}

       /**
        * \brief Destruction d'un graphe
        * \post Le graphe est détruit
        */
		void detruireGraphe()
		{

		}

}//Fin du namespace