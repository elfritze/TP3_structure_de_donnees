/**
 * \file ReseauAerien.h
 * \brief Gestion d'un réseau aérien.
 * \author Éric Guillemette, Mathieu L'Écuyer
 * \version 0.1
 * \date juillet 2014
 *
 * Travail pratique numéro 3
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
 * Espace de nommage regroupant les définitions du TP3.
 */
namespace TP3
{

const int infinie = INT_MAX;  /*!< Constante infinie */

/**
 * \struct Chemin
 * \brief Une struture représentant un chemin entre une ville origine et une ville destination.
 */
struct Chemin
{
   std::vector<std::string> listeVilles;  /*!< Doit contenir la liste des villes formant le chemin.
                                               Le point de départ du chemin correspond à l'élément
                                               d'indice 0 du vecteur. Le point d'arrivée correspond
                                               au dernier élément du vecteur. */

   float dureeTotale; /*!< Durée totale du vol du chemin en heures incluant le temps d'escale */
   float coutTotal;   /*!< Cout total en dollars du chemin entre la ville de départ et la ville
                           de destination */
   int nsTotal;       /*!< Niveau de sécurité total du chemin */
   bool reussi;       /*!< Un booléen qui vaut true si chemin a été trouvé, false sinon */
};

/**
 * \class ReseauAerien
 * \brief Cette classe sert à représenter un réseau aérien.
 *
 * Le réseau aérien est un graphe (orienté, pondéré et étiqueté) constitué d'un ensemble de villes
 * (sommet du graphe) et un ensemble de trajets d'avions reliant ces villes (arcs du graphe).
 */
class ReseauAerien
{

public:

   /**
    * \brief Constructeur par défaut.
    *        Le constructeur ne fait rien vu que le type ReseauAerien est composé d'un graphe.
    *        C'est le constructeur de ce dernier qui sera appelé.
    *
    * \post Un réseau aérien vide est instancié.
    */
   ReseauAerien() {}

   /**
    * \brief Détruit et libère toute la mémoire allouée auparavant pour le réseau aérien.
    *        Le destructeur ne fait rien, c'est celui du type Graphe qui sera appelé implicitement.
    *
    * \post Toute la mémoire allouée auparavant pour le réseau aérien est libérée.
    * \post L'Objet ReseauAerien n'est plus valide.
    */
   ~ReseauAerien() {};

   /**
    * \brief Constructeur de copie.
    *
    * \pre Il y a assez de mémoire.
    *
    * \exception bad_alloc : s'il n'y a pas assez de mémoire.
    */
   ReseauAerien(const ReseauAerien &source);

   /**
    * \brief Surcharge de l'opérateur d'affectation.
    *
    * \pre Il doit y avoir assez de mémoire.
    *
    * \post Le réseau aérien a un contenu identique à src.
    *
    * \exception bad_alloc : s'il n'y a pas assez de mémoire.
    */
   ReseauAerien& operator=(const ReseauAerien& src);

   /**
    * \brief Surcharge de l'opérateur de sortie.
    *
    * \post Le reseau aérien sera affiché.
    */
   friend std::ostream& operator<<(std::ostream& out, const ReseauAerien& g);

   /**
    * \brief Charger un réseau à partir d'un fichier texte en entrée.
    *        Construit un reseau aérien à partir d'une liste de villes ainsi que leurs liens.
    *
    * \pre Il y a assez de mémoire pour charger toutes les villes et les trajets du réseau.
    * \pre fichierEntree est ouvert corectement.
    *
    * \post fichierEntree n'est pas fermé par la fonction.
    * \post Si les préconditions sont respectées, les données du réseau contenu
    *       dans le fichier en entrée sont organisées dans un graphe en mémoire.
    *
    * \exception bad_alloc : si pas assez de mémoire pour contenir toute la liste du fichier.
    * \exception logic_error : si fichierEntree n'est pas ouvert correctement.
    */
   void chargerReseau(std::ifstream & fichierEntree);

   /**
    * \brief Sauvegarder un réseau dans un fichier texte.
    *
    * \pre SortieFichier est ouvert correctement.
    *
    * \post SortieFichier n'est pas fermé par la fonction.
    * \post Si les préconditions sont respectées, les données du réseau sont
    *       sauvegardées dans le fichier.
    *
    * \exception logic_error : si SortieFichier n'est pas ouvert correctement.
    */
   void sauvegarderReseau(std::ofstream & SortieFichier) const;

   /**
    * \brief Vider le réseau.
    *
    * \post Le réseau est détruit.
    */
   void viderReseau();

   /**
    * \brief Déterminer la fermeture transitive du réseau.
    *
    * \pre Le réseau est correctement initialisé.
    *
    * \post La fermeture transitive du réseau est retournée.
    * \post Le réseau original reste inchangé.
    *
    * \exception bad_alloc : si pas assez de mémoire
    */
   ReseauAerien fermetureReseau();

   /**
    * \brief Algorithme du parcours en largeur afin de trouver un chemin entre une ville origine
    *        et une ville destination.
    *
    * \pre La ville origine (le départ) et la ville destination (l'arrivée) doivent faire partie
    *      du réseau aérien.
    *
    * \post Le chemin trouvé est retourné sous forme d'un tableau de chaînes de caractères.
    * \post Le réseau original reste inchangé.
    *
    * \exception logic_error : si le départ ou l'arrivée ne fait pas partie du réseau aérien.
    */
   std::vector<std::string> rechercheCheminLargeur(const std::string& origine,
                                                   const std::string& destination);

   /**
    * \brief Algorithme de Dijkstra afin de retrouver le plus court chemin entre deux villes en
    *        utilisant soit la durée du vol en heures soit le coût du vol en dollars comme
    *        pondérations sur les trajets.
    *
    * \pre La ville origine (le départ) et la ville destination (l'arrivée) doivent faire partie
    *      du réseau aérien.
    *
    * \post Le plus court chemin selon la pondération choisie est retourné dans une structure Chemin.
    * \post Le réseau original reste inchangé.
    *
    * \exception logic_error : si le départ ou l'arrivée ne fait pas partie du réseau aérien.
    */
   Chemin rechercheCheminDijkstra(const std::string& origine, const std::string& destination,
                                  bool dureeCout);

   /**
    * \brief Algorithme de Bellman-Ford afin de retrouver le plus court chemin entre deux villes en
    *        utilisant les trois différents types de pondérations sur les trajets.
    *
    * \pre La ville origine (le départ) et la ville destination (l'arrivée) doivent faire partie
    *      du réseau aérien.
    * \pre dureeCoutNiveau a comme valeur 1, 2 ou 3.
    *
    * \post Le plus court chemin selon la pondération choisie est retourné dans une structure Chemin.
    * \post Le réseau original reste inchangé.
    *
    * \exception logic_error : si le départ ou l'arrivée ne fait pas partie du réseau aérien.
    * \exception logic_error : si dureeCoutNiveau est différent des valeurs 1, 2 ou 3.
    */
   Chemin bellManFord(const std::string& origine, const std::string& destination,
                      int dureeCoutNiveau);

   /**
    * \brief Algorithme A* afin de retrouver le plus court chemin entre deux villes en
    *        utilisant soit la durée du vol en heures soit le coût du vol en dollars comme
    *        pondérations sur les trajets.
    *
    * \pre La ville origine (le départ) et la ville destination (l'arrivée) doivent faire partie
    *      du réseau aérien.
    *
    * \post Le plus court chemin selon la pondération choisie est retourné dans une structure Chemin.
    * \post Le réseau original reste inchangé.
    *
    * \exception logic_error : si le départ ou l'arrivée ne fait pas partie du réseau aérien.
    */
   Chemin algorithmeAstar(const std::string& origine, const std::string& destination,
                          bool dureeCout);

   /**
    * \brief Méthode pour afficher le graphe du réseau aérien dans Graphviz.
    *
    * \pre Le fichier out est ouvert correctement.
    * \pre dureeCoutNiveau a comme valeur 0, 1, 2 ou 3.
    *
    * \post Le réseau original reste inchangé.
    * \post Le réseau est sauvegardé dans le fichier out pour être manipulé par Graphviz.
    *
    * \exception logic_error : si le fichier out est incorrect.
    * \exception logic_error : si dureeCoutNiveau est différent des valeurs 0, 1, 2 ou 3.
    */
   void displayInGraphviz(std::ostream & out, int dureeCoutNiveau);

private:
   Graphe unReseau;        /*!< Le type ReseauAerien est composé d'un graphe. */
   std::string nomReseau;  /*!< Le nom du réseau (exemple: Air Canada). */


   // Vous pouvez définir des constantes ici.

   // Déclaration éventuelles de méthodes privées. À vous de voir!
};

} //Fin du namespace

#endif
