/**
 * \file ReseauAerien.h
 * \brief Gestion d'un réseau aérien.
 * \author ...
 * \version 0.1
 * \date ...
 *
 *  Travail pratique numéro 3
 *
 */

#include "Graphe.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include <climits>
#include <vector>
//vous pouvez inclure d'autres librairies de la STL si vous pensez les utiliser

#ifndef _RESEAUAERIEN__H
#define _RESEAUAERIEN__H

namespace TP3
{

const int infinie = INT_MAX; // Constante que vous pouvez éventuellement utiliser

struct Chemin 
{
   //listeVilles doit contenir la liste des villes formant le chemin
   //Le point de départ du chemin correspond à l'élément d'indice 0 du vecteur
   //le point d'arrivée correspond au dernier élément du vecteur.
   std::vector<std::string> listeVilles;

   float dureeTotale;		// Durée totale du vol du chemin en heures incluant le temps d'escale
   float coutTotal;			// Cout total en dollars du chemin entre la ville de départ et la ville de destination
   int nsTotal;				// Niveau de sécurité total du chemin
   bool reussi;				// Un booléen qui vaut true si chemin a été trouvé, false sinon
};

class ReseauAerien{

public:

	/**                       
	 * \brief constructeur par défaut
	 * \post Un réseau aérien vide est instancié.
	 */
	ReseauAerien(){}  //Le constructeur ne fait rien vu que le type ReseauAerien est composé d'un graphe. 
				   //C'est le constructeur de ce dernier qui sera appelé.

	/**                       
	 * \brief Détruit et libère toute la mémoire allouée auparavant pour le réseau aérien.
	 * \post Toute la mémoire allouée auparavant pour le réseau aérien est libérée.
	 * \post L'Objet ReseauAerien n'est plus valide.
	 */
	~ReseauAerien(){}; //Le destructeur ne fait rien, c'est celui du type Graphe qui sera appelé implicitement

	/**
	* \brief Constructeur de copie.
	* \pre Il y a assez de mémoire.
	* \exception bad_alloc S'il n'y a pas assez de mémoire.
	*/
	ReseauAerien(const ReseauAerien &source);
        
    /**
	* \brief Surcharge de l'opérateur d'affectation.
	* \pre Il doit y avoir assez de mémoire.
	* \post Le réseau aérien a un contenu identique à src.
	* \exception bad_alloc S'il n'y a pas assez de mémoire.
	*/
	ReseauAerien& operator=(const ReseauAerien& src);

	/**
	* \brief Surcharge de l'opérateur de sortie.
	* \post Le reseau aérien sera affiché  
	*/
	friend std::ostream& operator<<(std::ostream& out, const ReseauAerien& g);

	/**                       
	 * \brief Charger un réseau à partir d'un fichier texte en entrée (voir format du fichier dans l'énoncé du Tp).
	 *  Construit un reseau aérien à partir d'une liste de villes ainsi que leurs liens.
	 * \pre Il y a assez de mémoire pour charger toutes les villes et les trajets du réseau.
	 * \pre fichierEntree est ouvert corectement. 
	 * \post fichierEntree n'est pas fermé par la fonction.
	 * \post Si les préconditions sont respectées, les données du réseau contenu 
	 *       dans le fichier en entrée sont organisées dans un graphe en mémoire. 
	 * \exception bad_alloc si pas assez de mémoire pour contenir toute la liste du fichier.
	 * \exception logic_error si fichierEntree n'est pas ouvert correctement. 
	 */
	void chargerReseau(std::ifstream & fichierEntree); 

	/**                       
	 * \brief Sauvegarder un réseau dans un fichier texte (voir format du fichier dans l'énoncé du Tp).
	 * \pre SortieFichier est ouvert correctement. 
	 * \post SortieFichier n'est pas fermé par la fonction.
	 * \post Si les préconditions sont respectées, les données du réseau sont sauvegardées dans le fichier. 
	 * \exception logic_error si SortieFichier n'est pas ouvert correctement. 
	 */
	void sauvegarderReseau(std::ofstream & SortieFichier) const;

	/**
	* \brief Vider le réseau
	* \post Le reseau est détruit
	*/
	void viderReseau();

	/**
	* \brief Déterminer la fermeture transitive du reseau.
	* \pre Le reseau est correctement initialisé.
	* \post La fermeture transitive du reseau est retournée. 
	* \post Le reseau original reste inchangé.
	* \exception bad_alloc si pas assez de mémoire
	*/
	ReseauAerien fermetureReseau();


// De plus, vous devez compléter ce fichier ReseauAerien.h par la spécification 
// du reste des méthodes demandés, voir l'énoncé de ce travail pratique (4.3 Requêtes des clients)

private:
	Graphe unReseau;			//Le type ReseauAerien est composé d'un graphe
	std::string nomReseau;		// Le nom du reseau (exemple: Air Canada)

	// Vous pouvez définir des constantes ici.

	// Déclaration éventuelles de méthodes privées. À vous de voir! 

};

}//Fin du namespace

#endif