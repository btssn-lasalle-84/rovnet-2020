/**
 * @brief
 * Fichier qui contient la déclaration de la classe IHMRov
 * @file ihmrov.h
 */

#ifndef IHMROV_H
#define IHMROV_H

#include <QtWidgets>
#include <QMessageBox>
#include <qwt/qwt_thermo.h>
#include <qwt/qwt_color_map.h>
#include <QColor>

#define PAS_DE_MANETTE

/**
 * @brief
 * Défini le nom du projet
 * @def NOM_FENETRE_ROV
 */
#define NOM_FENETRE_ROV "Projet Rovnet 2020"

/**
 * @brief
 * Défini le ratio pour la taille de l'affichage du flux vidéo
 * @def RATIO
 */
#define RATIO           0.75
/**
 * @brief
 * Défini la distance max supporté pas le radar
 * @def DISTANCE_MAX_RADAR
 */
#define DISTANCE_MAX_RADAR      150
/**
 * @brief
 * Défini l'angle max supporté pas le radar
 * @def ANGLE_MAX_RADAR
 */
#define ANGLE_MAX_RADAR      180
/**
 * @brief
 * Défini l'angle min supporté pas le radar
 * @def ANGLE_MIN_RADAR
 */
#define ANGLE_MIN_RADAR      0
/**
 * @brief
 * Défini le seuil à partir duquel la température positive n'est plus acceptable en °C
 * @def SEUIL_TEMPERATURE_ACCEPTABLE
 */
#define SEUIL_TEMPERATURE_POSITIVE_ACCEPTABLE 40
/**
 * @brief
 * Défini le seuil à partir duquel la température négative n'est plus acceptable en °C
 * @def SEUIL_TEMPERATURE_ACCEPTABLE
 */
#define SEUIL_TEMPERATURE_NEGATIVE_ACCEPTABLE -40
/**
 * @brief
 * Défini le seuil à partir duquel la radiation n'est plus acceptable en microsievert
 * @def SEUIL_RADIATION_ACCEPTABLE
 */
#define SEUIL_RADIATION_ACCEPTABLE 0.1


class IHMAlbumPhoto;
class IHMReglageVideo;
class Rov;
class IHMAccueil;
class Campagne;
class IHMConfiguration;

/**
 * @brief
 * IHM permettant d'obtenir le flux vidéo en direct placé sur le robot et d'obtenir les informations relatifs à ses capteurs
 * @class IHMRov ihmrov.h "ihmrov.h"
 */
class IHMRov : public QWidget
{
    Q_OBJECT
private:
    Campagne *campagneEnCours;       //!< Instance d'un objet Campagne possédant les informations de la campagne en cours
    IHMAccueil *ihmAccueil;          //!< Relation entre l'ihmAccueil et l'ihmRov
    Rov *rov;                        //!< Instance d'un objet rov possédant le controle sur les autres classes
    IHMReglageVideo *reglageVideo;   //!< Instance d'un objet reglageVidéo permettant de modifier les reglages du flux vidéo
    IHMConfiguration *configuration; //!< Instance d'un objet IHMConfiguration permettant de modifier les reglages de la communication
    QLabel *fluxVideo;               //!< Emplacement permettant d'accueiller le flux vidéo
    QPushButton *photosEnCours;      //!< Bouton permettant d'accéder aux photo prise en cours de campagne
    QPushButton *boutonReglageVideo; //!< Bouton permettant d'accéder aux reglage de la vidéo
    QPixmap derniereImageVideo;      //!< Dernière image reçue du flux vidéo
    #ifdef PAS_DE_MANETTE
    QPushButton *testCapturePhoto;   //!< Bouton de simulation de prise de photo
    #endif
    QPushButton *boutonCampagne;     //!< Bouton permettant de mettre en pause la campagne en cours
    QPushButton *boutonConfiguration;//!< Bouton permettant d'accéder à la configuration de la communication
    QLabel *hautDePage;              //!< Emplacement permettant de créer un espace en haut de la page
    QLabel *basDePage;               //!< Emplacement permettant de créer un espace en bas de la page
    QLabel *logoEtatPortSerie;       //!< Emplacement permettant de visualiser l'état du port série à l'aide d'un logo
    QLabel *logoEtatCamera;          //!< Emplacement permettant de visualiser l'état de la caméra à l'aide d'un logo
    QLabel *logoEtatManette;         //!< Emplacement permettant de visualiser l'état de la manette à l'aide d'un logo
    QLabel *etatPortSerie;           //!< Emplacement permettant de visualiser l'état du port série
    QLabel *etatCamera;              //!< Emplacement permettant de visualiser l'état de la caméra
    QLabel *etatManette;             //!< Emplacement permettant de visualiser l'état de la manette
    QLabel *portSerie;               //!< Emplacement permettant de définir le type de matériel
    QLabel *camera;                  //!< Emplacement permettant de définir le type de matériel
    QLabel *manette;                 //!< Emplacement permettant de définir le type de matériel
    bool etatRadar;                  //!< Dertermine si on affiche un radar
    QwtThermo *indicateurTemperature;//!< Indicateur permettant de visualiser l'etat de la temperature actuel avec indication de dépassement de seuil
    QwtThermo *indicateurRadiation;  //!< Indicateur permettant de visualiser l'etat de la radiation actuel avec indication de dépassement de seuil
    QLabel *temperature;             //!< Emplacement permettant de définir le type de seuil
    QLabel *radiation;               //!< Emplacement permettant de définir le type de seuil
    QGroupBox *zoneEtatMateriel;     //!< Zone regroupant les informations sur l'état du matériel
    QGroupBox *zoneInformationSeuils;//!< Zone regroupant les informations sur l'état des seuils de dépassement
    QVector<QPoint> pointsRadar;        //!< Conteneur des points du radar

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
    /**
     * @brief
     * Actualise les informations incrusté dans l'image (heure, données capteur, durée missions)
     * @param image
     */
    void actualiserInformations(QPixmap &image);
    /**
     * @brief
     * Arrête la campagne et ferme l'ihmRov
     */
    void fermer();
    /**
     * @brief
     * Calcule les coordonnées x de l'obstacle pour le radar
     * @return entier correspondant à la valeur sur l'axe des x du radar d'un objet detecté
     * @param image
     */
    double calculCoordonneesX(QPixmap &image);
    /**
     * @brief
     * Calcule les coordonnées y de l'obstacle pour le radar
     * @return entier correspondant à la valeur sur l'axe des y du radar d'un objet detecté
     * @param image
     */
    double calculCoordonneesY(QPixmap &image);

protected:
    /**
     * @brief
     * Gêre l'état de la campagne lors de la fermeture forcé de la fenêtre ihmRov
     * @param event
     */
    void closeEvent(QCloseEvent *event);

public:
    /**
     * @brief
     * Constructeur de la classe IHMRov
     * @param ihmAccueil
     * @param parent
     */
    IHMRov(IHMAccueil *ihmAccueil, QWidget *parent = nullptr);
    /**
     * @brief
     * Destructeur de la classe IHMRov
     */
    ~IHMRov();
    /**
     * @brief
     * Associe une campagne a la campagne en cours du rov
     * @param campagne
     */
    void setCampagne(Campagne *campagne);
    /**
     * @brief
     * Retourne l'objet campagne en cours
     * @return l'objet campagne en cours
     */
    Campagne* getCampagne();
    /**
     * @brief
     * Dertermine l'etat de etatRadar
     * @param etatRadar
     */
    void setEtatRadar(bool etatRadar);
    /**
     * @brief
     * Donne l'etat de etatRadar
     */
    bool getEtatRadar();
    /**
     * @brief
     * Actualise les informations affichés des indicateur de dépassement des seuils acceptable
     */
    void actualiserInformationsSeuils();

public slots:
    /**
     * @brief
     * Affiche la nouvelle image du flux vidéo dans l'ihm
     * @param image
     */
    void afficherImage(QPixmap image);
    /**
     * @brief
     * Ouvre une nouvelle fenetre permettant de régler l'affichage vidéo
     */
    void reglerVideo();
    /**
     * @brief
     * Ouvre une nouvelle fenetre permettant de régler la communication
     */
    void reglerConfiguration();
    /**
     * @brief
     * Enregistre la dernière image du flux vidéo
     * @param etat
     */
    void capturerImage(bool etat=false);
    /**
     * @brief
     * Arrête la campagne en cours
     */
    void gererCampagne();
    /**
     * @brief
     * Charge les photos disponible dans le conteneur albumPhoto de la classe campagne pour les afficher dans l'IHMAlbumPhoto
     */
    void chargerPhotos();
    /**
     * @brief
     * Initialise les événements liés à la caméra
     */
    void initialiserEvenementsCamera();
    /**
     * @brief
     * Déconnecte les événements liés à la caméra et modifie l'état des boutons de l'IHM
     */
    void arreterVideo();
    /**
     * @brief
     * Modifie l'affichage de l'état du port série
     * @param etat
     * @param information
     */
    void modifieEtatPortSerie(bool etat, QString information);
    /**
     * @brief
     * Modifie l'affichage de l'état de la caméra
     * @param etat
     */
    void modifieEtatCamera(bool etat, QString information);
    /**
     * @brief
     * Modifie l'affichage de l'état de la manette
     * @param etat
     */
    void modifieEtatManette(bool etat);

};

#endif // IHMROV_H
