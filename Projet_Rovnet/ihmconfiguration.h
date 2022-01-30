/**
 * @brief
 * Fichier qui contient la déclaration de la classe IHMConfiguration
 * @file ihmconfiguration.h
 */

#ifndef IHMCONFIGURATION_H
#define IHMCONFIGURATION_H

#include <QWidget>
#include "rov.h"

class Rov;

/**
 * @brief
 * Class permettant de configurer la communication avec le rov
 * @class IHMConfiguration ihmconfiguration.h "ihmconfiguration.h"
 */
class IHMConfiguration : public QWidget
{
    Q_OBJECT
private:
    Rov *rov;                           //!< Objet rov permettant de mofidier les reglage de la communication
    QComboBox *listePortsDisponibles;   //!< Liste des ports détéctés
    QComboBox *listeDebit;              //!< Liste permettant de configurer le debit de la communication
    QComboBox *listeBitsDonnees;        //!< Liste permettant de configurer le nombre de bits de données de la communication
    QComboBox *listeBitsStop;           //!< Liste permettant de configurer le nombre de bits de stop de la communication
    QPushButton *boutonGererPort;       //!< Bouton permettant de gerer le port sélectionné

    /**
     * @brief
     * Initialise les widgets de l'IHM
     */
    void initialiserWidgets();
    /**
     * @brief
     * Configure l'état des widgets à la création de l'IHM
     */
    void configurerWidgets();
    /**
     * @brief
     * Initialise les layouts de l'IHM
     */
    void initialiserLayouts();
    /**
     * @brief
     * Initialise les événements de l'IHM
     */
    void initialiserEvenements();

public:
    /**
     * @brief
     * Constructeur de la classe IHMConfiguration
     * @param rov
     * @param parent
     */
    IHMConfiguration(Rov *rov, QWidget *parent = nullptr);
    /**
     * @brief
     * Destructeur de la classe IHMConfiguration
     */
    ~IHMConfiguration();

public slots:
    /**
     * @brief
     * Envoie au rov la nouvelle configuration de la communication
     */
    void modifierConfiguration();
    /**
     * @brief
     * Modifie l'état du port
     */
    void modifierEtatPort();
    /**
     * @brief
     * Modifie l'état des boutons en fonction du port
     */
    void modifieEtatBoutons();
    /**
     * @brief
     * Actualise la liste des ports disponible
     */
    void actualisePortsDisponibles();

signals:


};

#endif // IHMCONFIGURATION_H
