/**
 * @brief
 * Fichier main
 * @file main.cpp
 */

#include "ihmaccueil.h"
#include <QApplication>

/**
 * @brief
 * Programme principal qui instancie, affiche l'IHM du Rov et exécute la boucle d'évènements
 * @param argc
 * @param argv
 * @return retourne un entier correspond à l'état de la fermeture de l'application
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    IHMAccueil w;
    w.setFixedSize(633, 489);
    w.show();

    return a.exec();
}

// Pour la documentation Doxygen

/**
 * @brief
 * La classe QObject est la classe de base de tous les objets Qt. Elle permet à ces objets Qt de disposer entre autres du mécanisme de communication signal/slot
 * @class QObject
 */

/**
 * @brief
 * La classe QWidget est la classe de base de tous les objets graphiques d'interface utilisateur
 * @class QWidget
 */

/**
 * @brief
 * La classe QDialog est la classe de base des fenêtres de dialogue
 * @class QDialog
 */

/**
 * @brief
 * La classe QGamepad est utilisée pour accéder à l'état actuel du matériel de la manette de jeu connecté à un système
 * @class QGamepad
 */

/**
 * @brief
 * La classe QThread fournit un moyen indépendant de gérer les threads dans Qt
 * @class QThread
 */
