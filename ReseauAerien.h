/**
 * \file ReseauAerien.h
 * \brief Gestion d'un r�seau a�rien.
 * \author ...
 * \version 0.1
 * \date ...
 *
 *  Travail pratique num�ro 3
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

const int infinie = INT_MAX; // Constante que vous pouvez �ventuellement utiliser

struct Chemin 
{
   //listeVilles doit contenir la liste des villes formant le chemin
   //Le point de d�part du chemin correspond � l'�l�ment d'indice 0 du vecteur
   //le point d'arriv�e correspond au dernier �l�ment du vecteur.
   std::vector<std::string> listeVilles;

   float dureeTotale;		// Dur�e totale du vol du chemin en heures incluant le temps d'escale
   float coutTotal;			// Cout total en dollars du chemin entre la ville de d�part et la ville de destination
   int nsTotal;				// Niveau de s�curit� total du chemin
   bool reussi;				// Un bool�en qui vaut true si chemin a �t� trouv�, false sinon
};

class ReseauAerien{

public:

	/**                       
	 * \brief constructeur par d�faut
	 * \post Un r�seau a�rien vide est instanci�.
	 */
	ReseauAerien(){}  //Le constructeur ne fait rien vu que le type ReseauAerien est compos� d'un graphe. 
				   //C'est le constructeur de ce dernier qui sera appel�.

	/**                       
	 * \brief D�truit et lib�re toute la m�moire allou�e auparavant pour le r�seau a�rien.
	 * \post Toute la m�moire allou�e auparavant pour le r�seau a�rien est lib�r�e.
	 * \post L'Objet ReseauAerien n'est plus valide.
	 */
	~ReseauAerien(){}; //Le destructeur ne fait rien, c'est celui du type Graphe qui sera appel� implicitement

	/**
	* \brief Constructeur de copie.
	* \pre Il y a assez de m�moire.
	* \exception bad_alloc S'il n'y a pas assez de m�moire.
	*/
	ReseauAerien(const ReseauAerien &source);
        
    /**
	* \brief Surcharge de l'op�rateur d'affectation.
	* \pre Il doit y avoir assez de m�moire.
	* \post Le r�seau a�rien a un contenu identique � src.
	* \exception bad_alloc S'il n'y a pas assez de m�moire.
	*/
	ReseauAerien& operator=(const ReseauAerien& src);

	/**
	* \brief Surcharge de l'op�rateur de sortie.
	* \post Le reseau a�rien sera affich�  
	*/
	friend std::ostream& operator<<(std::ostream& out, const ReseauAerien& g);

	/**                       
	 * \brief Charger un r�seau � partir d'un fichier texte en entr�e (voir format du fichier dans l'�nonc� du Tp).
	 *  Construit un reseau a�rien � partir d'une liste de villes ainsi que leurs liens.
	 * \pre Il y a assez de m�moire pour charger toutes les villes et les trajets du r�seau.
	 * \pre fichierEntree est ouvert corectement. 
	 * \post fichierEntree n'est pas ferm� par la fonction.
	 * \post Si les pr�conditions sont respect�es, les donn�es du r�seau contenu 
	 *       dans le fichier en entr�e sont organis�es dans un graphe en m�moire. 
	 * \exception bad_alloc si pas assez de m�moire pour contenir toute la liste du fichier.
	 * \exception logic_error si fichierEntree n'est pas ouvert correctement. 
	 */
	void chargerReseau(std::ifstream & fichierEntree); 

	/**                       
	 * \brief Sauvegarder un r�seau dans un fichier texte (voir format du fichier dans l'�nonc� du Tp).
	 * \pre SortieFichier est ouvert correctement. 
	 * \post SortieFichier n'est pas ferm� par la fonction.
	 * \post Si les pr�conditions sont respect�es, les donn�es du r�seau sont sauvegard�es dans le fichier. 
	 * \exception logic_error si SortieFichier n'est pas ouvert correctement. 
	 */
	void sauvegarderReseau(std::ofstream & SortieFichier) const;

	/**
	* \brief Vider le r�seau
	* \post Le reseau est d�truit
	*/
	void viderReseau();

	/**
	* \brief D�terminer la fermeture transitive du reseau.
	* \pre Le reseau est correctement initialis�.
	* \post La fermeture transitive du reseau est retourn�e. 
	* \post Le reseau original reste inchang�.
	* \exception bad_alloc si pas assez de m�moire
	*/
	ReseauAerien fermetureReseau();


// De plus, vous devez compl�ter ce fichier ReseauAerien.h par la sp�cification 
// du reste des m�thodes demand�s, voir l'�nonc� de ce travail pratique (4.3 Requ�tes des clients)

private:
	Graphe unReseau;			//Le type ReseauAerien est compos� d'un graphe
	std::string nomReseau;		// Le nom du reseau (exemple: Air Canada)

	// Vous pouvez d�finir des constantes ici.

	// D�claration �ventuelles de m�thodes priv�es. � vous de voir! 

};

}//Fin du namespace

#endif