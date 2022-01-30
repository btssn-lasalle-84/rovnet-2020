/**
 * @brief
 * Fichier qui contient la déclaration de la classe rov
 * @file rov.h
 */

#ifndef ROV_H
#define ROV_H

#include <QObject>
#include "camera.h"
#include "communicationrov.h"
#include "manette.h"
#include "capteurs.h"
#include "ihmrov.h"

/**
 * @brief
 * Constante contenant le début de la trame telemetrie selon le protocole
 * @def DEBUT_TRAME_TELEMETRIE
 */
#define DEBUT_TRAME_TELEMETRIE "$TEL"
/**
 * @brief
 * Constante contenant le début de la trame capteur selon le protocole
 * @def DEBUT_TRAME_CAPTEUR
 */
#define DEBUT_TRAME_CAPTEUR    "$ENVI"
/**
 * @brief
 * Constante contenant le début de la trame déplacement selon le protocole
 * @def DEBUT_TRAME_DEPLACEMENT
 */
#define DEBUT_TRAME_DEPLACEMENT "$DEP"
/**
  * @brief
  * Constante contenant le début de la trame pilotage selon le protocole
  * @def DEBUT_TRAME_PILOTAGE
  */
#define DEBUT_TRAME_PILOTAGE "$BRAS"
/**
  * @brief
  * Constante contenant le début de la trame ordre selon le protocole
  * @def DEBUT_TRAME_ORDRE
  */
#define DEBUT_TRAME_ORDRE "$ORDRE"
/**
  * @brief
  * Constante contenant le début de la trame pince selon le protocole
  * @def DEBUT_TRAME_PINCE
  */
#define DEBUT_TRAME_PINCE "$PINCE"
#define TRAME_DEPLACEMENT_IMMOBILE "$DEP;0;0;0\r\n"
/**
  * @brief
  * Constante contenant la trame pilotage à zéro selon le protocole
  * @def TRAME_PILOTAGE_IMMOBILE
  */
#define TRAME_PILOTAGE_IMMOBILE "$BRAS;0\r\n"
/**
  * @brief
  * Constante contenant la trame pince à zéro selon le protocole
  * @def TRAME_PINCE_IMMOBILE
  */
#define TRAME_PINCE_IMMOBILE "$PINCE;0\r\n"
/**
  * @brief
  * Constante contenant le début de la trame caméra selon le protocole
  * @def DEBUT_TRAME_CAMERA
  */
#define DEBUT_TRAME_CAMERA "$CAM"
/**
  * @brief
  * Constante contenant la trame pour immobiliser la caméra
  * @def TRAME_CAMERA_IMMOBILE
  */
#define TRAME_CAMERA_IMMOBILE "$CAM;0;0\r\n"
/**
  * @brief
  * Constante contenant la trame pour allumer la led
  * @def TRAME_LED_ON
  */
#define TRAME_LED_ON "$LED;ON\r\n"
/**
  * @brief
  * Constante contenant la trame pour eteindre la led
  * @def TRAME_LED_OFF
  */
#define TRAME_LED_OFF "$LED;OFF\r\n"

class Camera;
class CommunicationRov;
class Manette;
class Capteurs;
class IHMRov;
class QCameraInfo;

/**
 * @brief
 * Classe controlant tout les traitements en provenance et en direction de la communication avec le rov
 * @class Rov rov.h "rov.h"
 */
class Rov : public QObject
{
    Q_OBJECT
private:
    IHMRov *ihmRov;                         //!< Instance d'un objet ihmRov permettant la connexion entre les autre classe associé aux rov et l'ihm
    Capteurs *capteurs;                     //!< Instance d'un objet contenant les dernières informations issues des capteurs du rov
    Camera *camera;                         //!< Instance d'un objet camera possedant les informations nécessaire à l'affichage du flux vidéo
    CommunicationRov *communicationRov;     //!< Instance d'un objet permettant la récupération des trames envoyé par la liaison série
    QList<int> listeManettes;               //!< Liste des mannettes connecté
    QVector<Manette*> manettes;          //!< Conteneur des manettes
    QString trameDeplacement;               //!< Contenu trame déplacement
    QString tramePrecedenteDeplacement;     //!< Contenu précédente trame déplacement
    QString tramePilotage;                  //!< Contenu trame pilotage
    QString tramePrecedentePilotage;        //!< Contenu précédente trame pilotage
    QString trameOrdre;                     //!< Contenu trame ordre
    QString tramePince;                     //!< Contenu trame pince
    QString tramePrecedentePince;           //!< Contenu précédente trame pince
    QString tramePrecedenteCamera;          //!< Contenu précédente trame caméra
    QString tramePinceImmobile;             //!< Contenu trame pince à zéro
    QTime dureeCampagne;                    //!< Timer lancer au début de la campagne
    bool campagneEnCours;                   //!< Etat de si une campagne est en cour
    bool etatLed;

    /**
     * @brief
     * detecte les mannettes
     */
    void detecterManette();
    /**
     * @brief
     * Initialise les evenement de la manette
     * @param manette
     */
    void initialiserEvenementManette(Manette *manette);
    /**
     * @brief
     * Décode la trame télémetrie reçue selon le protocole
     * @param trameTelemetrie
     */
    void decoderTrameTelemetrie(QString trameTelemetrie);
    /**
     * @brief
     * Décode la trame capteur reçue selon le protocole
     * @param trameCapteur
     */
    void decoderTrameCapteur(QString trameCapteur);
    /**
     * @brief
     * Initialise le(s) Evenement(s)
     */
    void initialiserEvenements();
    /**
     * @brief
     * Supprime les manettes du conteneur des manettes
     */
    void supprimerManette();

public:
    /**
     * @brief
     * Constructeur de la classe Rov
     * @param ihmRov
     * @param parent
     */
    Rov(IHMRov *ihmRov, QObject *parent = nullptr);
    /**
     * @brief
     * Destructeur de la classe Rov
     */
    ~Rov();

    /**
     * @brief
     * Démarre la campagne
     */
    bool demarrerCampagne();
    /**
     * @brief
     * Arrête la campagne
     */
    void arreterCampagne();
    /**
     * @brief
     * Retourne l'objet caméra créée par le rov
     * @return L'objet caméra créée par le rov
     */
    Camera* getCamera();
    /**
     * @brief
     * Retourne l'objet capteurs créée par le rov
     * @return L'objet capteurs créée par le rov
     */
    Capteurs* getCapteurs();
    /**
     * @brief
     * Retourne la durée de la campagne
     * @return La durée de la campagne
     */
    QString getTempsCampagne();
    /**
     * @brief
     * Démarre un nouveau flux vidéo
     * @param nomCamera
     * @param choixResolution
     */
    bool demarrerVideo(QString nomCamera, int choixResolution=-1);
    /**
     * @brief
     * Retourne l'etat de la campagne
     * @return l'etat de campagneEnCours (indiquant si la campagne est en cours ou pas)
     */
    bool getCampagneEncours() const;
    /**
     * @brief
     * Modifie la configuration de la communication
     * @param configuration
     */
    void modifierConfiguration(Configuration &configuration);
    /**
     * @brief
     * Retourne l'objet communicationRov créée par le rov
     * @return L'objet communicationRov créée par le rov
     */
    CommunicationRov* getCommunicationRov();
    /**
     * @brief
     * Retourne le conteneur de manettes créée par le rov
     * @return le conteneur de manettes créée par le rov
     */
    QVector<Manette*> getManettes();

signals:
    /**
     * @brief
     * signal contenant les nouvelle données de télémetrie (pour l'ihm)
     * @param donnes
     */
    void donneesTelemetrieDecode(QString donnes);
    /**
     * @brief
     * signal contenant les nouvelles mesures recus du robot (pour les enregistrer dans la BDD)
     * @param temperature
     * @param humidite
     * @param radiation
     */
    void enregistrerMesures(QString temperature, QString humidite, QString radiation);
    /**
     * @brief
     * signale le style de Radar à afficher
     * @param etat
     */
    void styleRadar(bool etat);

public slots:
    /**
     * @brief
     * Décode la trame réçue par le port série selon le protocole établie
     * @param trame
     */
    void decoderTrame(QString trame);
    /**
     * @brief
     * Crée les trames de déplacement
     */
    void creerTrameDeplacement(char deplacementAxeX, int puissance, char deplacementAxeY);
    /**
     * @brief
     * Crée les trames de pilotage
     * @param deplacement
     */
    void creerTramePilotage(QString deplacement);
    /**
     * @brief
     * Crée les trames d'ordre
     * @param ordre
     */
    void creerTrameOrdre(QString ordre);
    /**
     * @brief
     * Crée les trames de la pince
     * @param mouvementPince
     */
    void creerTramePince(QString mouvementPince);
    /**
     * @brief
     * Crée les trames de la caméra
     * @param axeX
     * @param axeY
     */
    void creerTrameCamera(QString axeX, QString axeY);
    /**
     * @brief
     * Arrete le flux vidéo
     */
    void arreterVideo();
    /**
     * @brief
     * Allume la led
     */
    void allumerLed(bool);
};

#endif // ROV_H
