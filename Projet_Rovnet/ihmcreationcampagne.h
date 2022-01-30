/**
 * @brief
 * Fichier qui contient la déclaration de la classe IHMCreationCampagne
 * @file ihmcreationcampagne.h
 */

#ifndef IHMCREATIONCAMPAGNE_H
#define IHMCREATIONCAMPAGNE_H

#include <QtWidgets>

#define NOM_FENETRE_CREATIONCAMPAGNE "Projet Rovnet 2020"

class IHMAccueil;
class BaseDeDonnees;

/**
 * @brief
 * Class permettant de créer une nouvelle campagne
 * @class IHMCreationCampagne IHMCreationCampagne.h "ihmcreationcampagne.h"
 */
class IHMCreationCampagne : public QDialog
{
    Q_OBJECT
private:
    IHMAccueil *ihmAccueil;                 //!< Association avec la classe IHMAccueil
    QLineEdit *nomCampagne;                 //!< Ligne editable permettant de rentrer le nom de la campagne à créer
    QLineEdit *nomTechnicien;               //!< Ligne editable permettant de rentrer le nom du technicien à créer
    QLineEdit *prenomTechnicien;            //!< Ligne editable permettant de rentrer le prenom du technicien à créer
    QLineEdit *lieu;                        //!< Ligne editable permettant de rentrer le lieu de la campagne à créer
    QLineEdit *cheminSauvegarde;            //!< Ligne editable permettant de choisir le chemin de sauvegarde des photos
    QPushButton *boutonValider;             //!< Bouton permettant de valider la création de la campagne
    QPushButton *boutonAnnuler;             //!< Bouton permettant d'annuler la création de la campagne
    QPushButton *boutonChoixChemin;         //!< Bouton permettant de choisir le chemin de sauvegarde des photos
    QComboBox *techniciens;                 //!< Liste déroulantes contenant tous les technicien connus
    QVector<QStringList> listeTechniciens;  //!< Conteneur de liste des informations des techniciens présent dans la base de données

    /**
     * @brief
     * Initialise les widgets de l'IHM
     */
    void initialisationWidgets();
    /**
     * @brief
     * Initialise le design des widgets de l'IHM
     */
    void initialisationDesignWidgets();
    /**
     * @brief
     * Initialise les événements de l'IHM
     */
    void initialiserEvenements();
    /**
     * @brief
     * Initialise les layouts de l'IMH
     */
    void initialiserLayouts();
    /**
     * @brief
     * Configure les différents widgets
     */
    void configurerWidgets();
    /**
     * @brief
     * Charge la liste des techniciens connus de la bdd dans la liste déroulante
     */
    void chargerListeTechniciens();

public:
    /**
     * @brief
     * Constructeur de la classe IHMCreationCampagne
     * @param ihmAccueil
     * @param listeTechniciens
     */
    explicit IHMCreationCampagne(IHMAccueil *ihmAccueil, QVector<QStringList> &listeTechniciens);
    /**
     * @brief
     * Destructeur de la classe IHMCreationCampagne
     */
    ~IHMCreationCampagne();

signals:

public slots:
    /**
     * @brief
     * Créer un nouvel objet Campagne et l'ajoute dans la liste des campagnes disponibles
     */
    void validerCampagne();
    /**
     * @brief
     * Modifie l'état des boutons de la boite de dialogue "création d'une nouvelle campagne" si un technicien connue est choisi les ligne permettant de rentrer un nouveau technicien deviennent non-éditables
     * @param index
     */
    void modifierEtatBouton(int index);
    /**
     * @brief
     * Permet de choisir le chemin de sauvegarde des photos
     */
    void choixCheminSauvegarde();
};

#endif // IHMCREATIONCAMPAGNE_H
