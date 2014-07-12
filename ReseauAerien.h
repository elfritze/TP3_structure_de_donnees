/**
 * \file ReseauAerien.h
 * \brief Gestion d'un r�seau a�rien.
 * \author �ric Guillemette, Mathieu L'�cuyer
 * \version 0.1
 * \date juillet 2014
 *
 * Travail pratique num�ro 3
 *
 */

#ifndef _RESEAUAERIEN__H
#define _RESEAUAERIEN__H

#include "Graphe.h"
#include <climits>
#include <fstream>
#include <iostream>
#include <queue>
#include <stack>
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

const int infinie = INT_MAX;  /*!< Constante infinie */

/**
 * \struct Chemin
 * \brief Une struture repr�sentant un chemin entre une ville origine et une ville destination.
 */
struct Chemin
{
   std::vector<std::string> listeVilles;  /*!< Doit contenir la liste des villes formant le chemin.
                                               Le point de d�part du chemin correspond � l'�l�ment
                                               d'indice 0 du vecteur. Le point d'arriv�e correspond
                                               au dernier �l�ment du vecteur. */

   float dureeTotale; /*!< Dur�e totale du vol du chemin en heures incluant le temps d'escale */
   float coutTotal;   /*!< Cout total en dollars du chemin entre la ville de d�part et la ville
                           de destination */
   int nsTotal;       /*!< Niveau de s�curit� total du chemin */
   bool reussi;       /*!< Un bool�en qui vaut true si chemin a �t� trouv�, false sinon */
};

/**
 * \class ReseauAerien
 * \brief Cette classe sert � repr�senter un r�seau a�rien.
 *
 * Le r�seau a�rien est un graphe (orient�, pond�r� et �tiquet�) constitu� d'un ensemble de villes
 * (sommet du graphe) et un ensemble de trajets d'avions reliant ces villes (arcs du graphe).
 */
class ReseauAerien
{

public:

   /**
    * \brief Constructeur par d�faut.
    *        Le constructeur ne fait rien vu que le type ReseauAerien est compos� d'un graphe.
    *        C'est le constructeur de ce dernier qui sera appel�.
    *
    * \post Un r�seau a�rien vide est instanci�.
    */
   ReseauAerien() {}

   /**
    * \brief D�truit et lib�re toute la m�moire allou�e auparavant pour le r�seau a�rien.
    *        Le destructeur ne fait rien, c'est celui du type Graphe qui sera appel� implicitement.
    *
    * \post Toute la m�moire allou�e auparavant pour le r�seau a�rien est lib�r�e.
    * \post L'Objet ReseauAerien n'est plus valide.
    */
   ~ReseauAerien() {};

   /**
    * \brief Constructeur de copie.
    *
    * \pre Il y a assez de m�moire.
    *
    * \exception bad_alloc : s'il n'y a pas assez de m�moire.
    */
   ReseauAerien(const ReseauAerien &source);

   /**
    * \brief Surcharge de l'op�rateur d'affectation.
    *
    * \pre Il doit y avoir assez de m�moire.
    *
    * \post Le r�seau a�rien a un contenu identique � src.
    *
    * \exception bad_alloc : s'il n'y a pas assez de m�moire.
    */
   ReseauAerien& operator=(const ReseauAerien& src);

   /**
    * \brief Surcharge de l'op�rateur de sortie.
    *
    * \post Le reseau a�rien sera affich�.
    */
   friend std::ostream& operator<<(std::ostream& out, const ReseauAerien& g);

   /**
    * \brief Charger un r�seau � partir d'un fichier texte en entr�e.
    *        Construit un reseau a�rien � partir d'une liste de villes ainsi que leurs liens.
    *
    * \pre Il y a assez de m�moire pour charger toutes les villes et les trajets du r�seau.
    * \pre fichierEntree est ouvert corectement.
    *
    * \post fichierEntree n'est pas ferm� par la fonction.
    * \post Si les pr�conditions sont respect�es, les donn�es du r�seau contenu
    *       dans le fichier en entr�e sont organis�es dans un graphe en m�moire.
    *
    * \exception bad_alloc : si pas assez de m�moire pour contenir toute la liste du fichier.
    * \exception logic_error : si fichierEntree n'est pas ouvert correctement.
    */
   void chargerReseau(std::ifstream & fichierEntree);

   /**
    * \brief Sauvegarder un r�seau dans un fichier texte.
    *
    * \pre SortieFichier est ouvert correctement.
    *
    * \post SortieFichier n'est pas ferm� par la fonction.
    * \post Si les pr�conditions sont respect�es, les donn�es du r�seau sont
    *       sauvegard�es dans le fichier.
    *
    * \exception logic_error : si SortieFichier n'est pas ouvert correctement.
    */
   void sauvegarderReseau(std::ofstream & SortieFichier) const;

   /**
    * \brief Vider le r�seau.
    *
    * \post Le r�seau est d�truit.
    */
   void viderReseau();

   /**
    * \brief D�terminer la fermeture transitive du r�seau.
    *
    * \pre Le r�seau est correctement initialis�.
    *
    * \post La fermeture transitive du r�seau est retourn�e.
    * \post Le r�seau original reste inchang�.
    *
    * \exception bad_alloc : si pas assez de m�moire
    */
   ReseauAerien fermetureReseau();

   /**
    * \brief Algorithme du parcours en largeur afin de trouver un chemin entre une ville origine
    *        et une ville destination.
    *
    * \pre La ville origine (le d�part) et la ville destination (l'arriv�e) doivent faire partie
    *      du r�seau a�rien.
    *
    * \post Le chemin trouv� est retourn� sous forme d'un tableau de cha�nes de caract�res.
    * \post Le r�seau original reste inchang�.
    *
    * \exception logic_error : si le d�part ou l'arriv�e ne fait pas partie du r�seau a�rien.
    */
   std::vector<std::string> rechercheCheminLargeur(const std::string& origine,
                                                   const std::string& destination);

   /**
    * \brief Algorithme de Dijkstra afin de retrouver le plus court chemin entre deux villes en
    *        utilisant soit la dur�e du vol en heures soit le co�t du vol en dollars comme
    *        pond�rations sur les trajets.
    *
    * \pre La ville origine (le d�part) et la ville destination (l'arriv�e) doivent faire partie
    *      du r�seau a�rien.
    *
    * \post Le plus court chemin selon la pond�ration choisie est retourn� dans une structure Chemin.
    * \post Le r�seau original reste inchang�.
    *
    * \exception logic_error : si le d�part ou l'arriv�e ne fait pas partie du r�seau a�rien.
    */
   Chemin rechercheCheminDijkstra(const std::string& origine, const std::string& destination,
                                  bool dureeCout);

   /**
    * \brief Algorithme de Bellman-Ford afin de retrouver le plus court chemin entre deux villes en
    *        utilisant les trois diff�rents types de pond�rations sur les trajets.
    *
    * \pre La ville origine (le d�part) et la ville destination (l'arriv�e) doivent faire partie
    *      du r�seau a�rien.
    * \pre dureeCoutNiveau a comme valeur 1, 2 ou 3.
    *
    * \post Le plus court chemin selon la pond�ration choisie est retourn� dans une structure Chemin.
    * \post Le r�seau original reste inchang�.
    *
    * \exception logic_error : si le d�part ou l'arriv�e ne fait pas partie du r�seau a�rien.
    * \exception logic_error : si dureeCoutNiveau est diff�rent des valeurs 1, 2 ou 3.
    */
   Chemin bellManFord(const std::string& origine, const std::string& destination,
                      int dureeCoutNiveau);

   /**
    * \brief Algorithme A* afin de retrouver le plus court chemin entre deux villes en
    *        utilisant soit la dur�e du vol en heures soit le co�t du vol en dollars comme
    *        pond�rations sur les trajets.
    *
    * \pre La ville origine (le d�part) et la ville destination (l'arriv�e) doivent faire partie
    *      du r�seau a�rien.
    *
    * \post Le plus court chemin selon la pond�ration choisie est retourn� dans une structure Chemin.
    * \post Le r�seau original reste inchang�.
    *
    * \exception logic_error : si le d�part ou l'arriv�e ne fait pas partie du r�seau a�rien.
    */
   Chemin algorithmeAstar(const std::string& origine, const std::string& destination,
                          bool dureeCout);

   /**
    * \brief M�thode pour afficher le graphe du r�seau a�rien dans Graphviz.
    *
    * \pre Le fichier out est ouvert correctement.
    * \pre dureeCoutNiveau a comme valeur 0, 1, 2 ou 3.
    *
    * \post Le r�seau original reste inchang�.
    * \post Le r�seau est sauvegard� dans le fichier out pour �tre manipul� par Graphviz.
    *
    * \exception logic_error : si le fichier out est incorrect.
    * \exception logic_error : si dureeCoutNiveau est diff�rent des valeurs 0, 1, 2 ou 3.
    */
   void displayInGraphviz(std::ostream & out, int dureeCoutNiveau);

private:
   Graphe unReseau;        /*!< Le type ReseauAerien est compos� d'un graphe. */
   std::string nomReseau;  /*!< Le nom du r�seau (exemple: Air Canada). */


   // Vous pouvez d�finir des constantes ici.

   // D�claration �ventuelles de m�thodes priv�es. � vous de voir!
};

} //Fin du namespace

#endif
