/**
 * @brief
 * Fichier qui contient la déclaration de la classe Manette
 * @file manette.h
 */

#ifndef MANETTE_H
#define MANETTE_H

#include <QObject>
#include <QtCore/QCoreApplication>
#include <QtGamepad/QGamepad>
#include <QDebug>

/**
 * @brief
 * défini le taux d'acceptation de la valeur du joystick
 * @def TAUX_VALIDITE_JOYSTICK
 */
#define TAUX_VALIDITE_JOYSTICK 0.50
/**
 * @brief
 * défini le taux de reduction de la puissance lors d'un mouvement
 * @def REDUCTION_VITESSE
 */
#define REDUCTION_VITESSE 0.75
/**
 * @brief
 * défini la valeur du paramètre de la trame lors du mouvement IMMOBILE
 * @def IMMOBILE
 */
#define IMMOBILE "0"
/**
 * @brief
 * défini la valeur du paramètre de la trame lors du mouvement AVANCER
 * @def AVANCER
 */
#define AVANCER "AVANCER"
/**
 * @brief
 * défini la valeur du paramètre de la trame lors du mouvement RECULER
 * @def RECULER
 */
#define RECULER "RECULER"
/**
 * @brief
 * défini la valeur du paramètre de la trame lors du mouvement DESCENDRE
 * @def DESCENDRE
 */
#define DESCENDRE "DESCENDRE"
/**
 * @brief
 * défini la valeur du paramètre de la trame lors du mouvement MONTER
 * @def MONTER
 */
#define MONTER "MONTER"
/**
 * @brief
 * défini la valeur du paramètre de la trame lors du mouvement GAUCHE
 * @def GAUCHE
 */
#define GAUCHE "GAUCHE"
/**
 * @brief
 * défini la valeur du paramètre de la trame lors du mouvement DROITE
 * @def DROITE
 */
#define DROITE "DROITE"
/**
 * @brief
 * défini la valeur du paramètre de la trame lors d'un retour à l'etat initial
 * @def RETOUR_ETAT_INITIAL
 */
#define RETOUR_ETAT_INITIAL "INIT"
/**
 * @brief
 * défini la valeur du paramètre de la trame lors de l'ouverture de la pince
 * @def OUVERTURE_PINCE
 */
#define OUVERTURE_PINCE "O"
/**
 * @brief
 * défini la valeur du paramètre de la trame lors de la fermeture de la pince
 * @def FERMETURE_PINCE
 */
#define FERMETURE_PINCE "F"
/**
 * @brief
 * défini la valeur du paramètre de la trame lorsque l'on pose l'objet dans le bac
 * @def POSER_OBJET_DANS_BAC
 */
#define POSER_OBJET_DANS_BAC "BAC"
/**
 * @brief
 * défini la valeur du double retourné par le signal lorsque le joystick de la manette est poussé a fond sur la droite
 * @def CAMERA_DROITE
 */
#define CAMERA_DROITE  1
/**
 * @brief
 * défini la valeur du double retourné par le signal lorsque le joystick de la manette est poussé a fond sur la gauche
 * @def CAMERA_GAUCHE
 */
#define CAMERA_GAUCHE -1
/**
 * @brief
 * défini la valeur du double retourné par le signal lorsque le joystick de la manette est poussé a fond sur le haut
 * @def CAMERA_HAUT
 */
#define CAMERA_HAUT   -1
/**
 * @brief
 * défini la valeur du double retourné par le signal lorsque le joystick de la manette est poussé a fond sur le bass
 * @def CAMERA_HAUT
 */
#define CAMERA_BAS     1

/**
 * @brief
 * Structure qui définit l'état de la manette en mode pilotage de la pince
 */
struct EtatManetteBouton
{
    bool boutonA;                       //!< Membre définissant l'état du bouton A
    bool boutonB;                       //!< Membre définissant l'état du bouton B
    bool boutonX;                       //!< Membre définissant l'état du bouton X
    bool boutonY;                       //!< Membre définissant l'état du bouton Y

    /**
     * @brief
     * Surcharge de l'opérateur == afin de comparer un état de manette prédéfini avec l'état actuel de la manette
     * @param maStructure
     * @return Si l'opération est possible ou pas
     */
    bool operator==(const EtatManetteBouton &maStructure) const;
    /**
     * @brief
     * Surcharge de l'opérateur != afin de comparer un état de manette prédéfini avec l'état actuel de la manette
     * @param maStructure
     * @return Si l'opération est possible ou pas
     */
    bool operator!=(const EtatManetteBouton &maStructure) const;
};

/**
 * @brief
 * Structure qui définit l'état de la manette en mode pilotage de la pince
 * @struct EtatManettePilotage
 */
struct EtatManettePilotage
{
    bool flecheEnAvant;                 //!< Membre définissant l'état de la flèche du haut
    bool flecheEnArriere;               //!< Membre définissant l'état de la flèche du bas
    bool flecheAGauche;                 //!< Membre définissant l'état de la flèche de gauche
    bool flecheADroite;                 //!< Membre définissant l'état de la flèche de droite
    bool boutonHautGauche;              //!< Membre définissant l'état du bouton L1
    bool boutonHautDroit;               //!< Membre définissant l'état du bouton R1

    /**
     * @brief
     * Surcharge de l'opérateur == afin de comparer un état de manette prédéfini avec l'état actuel de la manette
     * @param maStructure
     * @return Si l'opération est possible ou pas
     */
    bool operator==(const EtatManettePilotage &maStructure) const;
    /**
     * @brief
     * Surcharge de l'opérateur != afin de comparer un état de manette prédéfini avec l'état actuel de la manette
     * @param maStructure
     * @return Si l'opération est possible ou pas
     */
    bool operator!=(const EtatManettePilotage &maStructure) const;
};
/**
 * @brief Structure qui définit l'état de la manette en mode déplacement du robot
 * @struct EtatManetteDeplacement
 */
struct EtatManetteDeplacement
{
    bool joystickGaucheEnAvant;         //!< Membre définissant l'état du joystick sur l'axe Y
    bool joystickGaucheEnArriere;       //!< Membre définissant l'état du joystick sur l'axe Y
    bool joystickGaucheAGauche;         //!< Membre définissant l'état du joystick sur l'axe X
    bool joystickGaucheADroite;         //!< Membre définissant l'état du joystick sur l'axe X
    bool gachetteBasGauche;             //!< Membre définissant l'état du bouton L2
    bool gachetteBasDroit;              //!< Membre définissant l'état du bouton R2
    /**
     * @brief
     * Surcharge de l'opérateur == afin de comparer un état de manette prédéfini avec l'état actuel de la manette
     * @param maStructure
     * @return Si l'opération est possible ou pas
     */
    bool operator==(const EtatManetteDeplacement &maStructure) const;
    /**
     * @brief
     * Surcharge de l'opérateur != afin de comparer un état de manette prédéfini avec l'état actuel de la manette
     * @param maStructure
     * @return Si l'opération est possible ou pas
     */
    bool operator!=(const EtatManetteDeplacement &maStructure) const;
};

class Rov;


/**
 * @brief
 * Classe permettant une communication entre le rov et la manette
 * @class Manette manette.h "manette.h"
 */
class Manette : public QGamepad
{
    Q_OBJECT

private:
    EtatManetteBouton maManetteBouton;                        //!< Structure définissant l'etat des bouton A, B, X, Y de la manette
    EtatManetteBouton ouvrirPince;                            //!< Structure définissant l'etat des bouton A, B, X, Y de la manette pour ouvrir la pince
    EtatManetteBouton fermerPince;                            //!< Structure définissant l'etat des bouton A, B, X, Y de la manette pour fermer la pince
    EtatManetteBouton poserObjetDansBac;                      //!< Structure définissant l'etat des bouton A, B, X, Y de la manette pour poser l'objet dans le bac
    EtatManetteBouton revenirEtatInitial;                     //!< Structure définissant l'etat des bouton A, B, X, Y de la manette pour revenir à l'etat initiale du bras
    EtatManetteDeplacement maManetteDeplacement;              //!< Structure définissant l'état des bouton de la manette en mode deplacement du robot
    EtatManetteDeplacement enAvantCas1;                       //!< Structure définissant l'état des bouton de la manette en mode deplacement du robot pour avancer
    EtatManetteDeplacement enAvantCas2;                       //!< Structure définissant l'état des bouton de la manette en mode deplacement du robot pour avancer
    EtatManetteDeplacement enAvantCas3;                       //!< Structure définissant l'état des bouton de la manette en mode deplacement du robot pour avancer
    EtatManetteDeplacement enArriereCas1;                     //!< Structure définissant l'état des bouton de la manette en mode deplacement du robot pour reculer
    EtatManetteDeplacement enArriereCas2;                     //!< Structure définissant l'état des bouton de la manette en mode deplacement du robot pour reculer
    EtatManetteDeplacement enArriereCas3;                     //!< Structure définissant l'état des bouton de la manette en mode deplacement du robot pour reculer
    EtatManetteDeplacement rotationAGauche;                   //!< Structure définissant l'état des bouton de la manette en mode deplacement du robot pour tourner à gauche
    EtatManetteDeplacement rotationAGaucheDoucementCas1;      //!< Structure définissant l'état des bouton de la manette en mode deplacement du robot pour tourner à gauche doucement
    EtatManetteDeplacement rotationAGaucheDoucementCas2;      //!< Structure définissant l'état des bouton de la manette en mode deplacement du robot pour tourner à gauche doucement
    EtatManetteDeplacement rotationADroite;                   //!< Structure définissant l'état des bouton de la manette en mode deplacement du robot pour tourner à droite
    EtatManetteDeplacement rotationADroiteDoucementCas1;      //!< Structure définissant l'état des bouton de la manette en mode deplacement du robot pour tourner à droite doucement
    EtatManetteDeplacement rotationADroiteDoucementCas2;      //!< Structure définissant l'état des bouton de la manette en mode deplacement du robot pour tourner à droite doucement
    EtatManetteDeplacement virageAvantAGauche;                //!< Structure définissant l'état des bouton de la manette en mode deplacement du robot pour avancer et tourner à gauche
    EtatManetteDeplacement virageAvantAGaucheDoucementCas1;   //!< Structure définissant l'état des bouton de la manette en mode deplacement du robot pour avancer et tourner à gauche doucement
    EtatManetteDeplacement virageAvantAGaucheDoucementCas2;   //!< Structure définissant l'état des bouton de la manette en mode deplacement du robot pour avancer et tourner à gauche doucement
    EtatManetteDeplacement virageAvantADroite;                //!< Structure définissant l'état des bouton de la manette en mode deplacement du robot pour avancer et tourner à droite
    EtatManetteDeplacement virageAvantADroiteDoucementCas1;   //!< Structure définissant l'état des bouton de la manette en mode deplacement du robot pour avancer et tourner à droite doucement
    EtatManetteDeplacement virageAvantADroiteDoucementCas2;   //!< Structure définissant l'état des bouton de la manette en mode deplacement du robot pour avancer et tourner à droite doucement
    EtatManetteDeplacement virageArriereAGauche;              //!< Structure définissant l'état des bouton de la manette en mode deplacement du robot pour reculer et tourner à gauche
    EtatManetteDeplacement virageArriereAGaucheDoucementCas1; //!< Structure définissant l'état des bouton de la manette en mode deplacement du robot pour reculer et tourner à gauche doucement
    EtatManetteDeplacement virageArriereAGaucheDoucementCas2; //!< Structure définissant l'état des bouton de la manette en mode deplacement du robot pour reculer et tourner à gauche doucement
    EtatManetteDeplacement virageArriereADroite;              //!< Structure définissant l'état des bouton de la manette en mode deplacement du robot pour reculer et tourner à droite
    EtatManetteDeplacement virageArriereADroiteDoucementCas1; //!< Structure définissant l'état des bouton de la manette en mode deplacement du robot pour reculer et tourner à droite doucement
    EtatManetteDeplacement virageArriereADroiteDoucementCas2; //!< Structure définissant l'état des bouton de la manette en mode deplacement du robot pour reculer et tourner à droite doucement

    EtatManettePilotage maManettePilotage;   //!< Structure définissant l'état des bouton de la manette en mode pilotage du bras
    EtatManettePilotage avance;             //!< Structure définissant l'état des bouton de la manette pour avancer
    EtatManettePilotage recule;             //!< Structure définissant l'état des bouton de la manette pour reculer
    EtatManettePilotage gauche;              //!< Structure définissant l'état des bouton de la manette pour aller à gauche
    EtatManettePilotage droite;              //!< Structure définissant l'état des bouton de la manette pour aller à droite
    EtatManettePilotage monte;              //!< Structure définissant l'état des bouton de la manette pour monter
    EtatManettePilotage descend;           //!< Structure définissant l'état des bouton de la manette pour descendre
    bool modeDeplacement;                    //!< Attribut définissant l'état du mode de déplacement
    bool modePilotageBras;                   //!< Attribut définissant l'état du mode pilotage du bras articulé
    int puissanceGachetteDroite;             //!< Attribut définissant la valeur de la puissance de la gachette droite
    int puissanceGachetteGauche;             //!< Attribut définissant la valeur de la puissance de la gachette gauche
    QString joystickAxeXCamera;              //!< Attribut contenant l'etat actuel du joystick droite sur l'axe des x
    QString joystickAxeYCamera;              //!< Attribut contenant l'etat actuel du joystick droite sur l'axe des y

    /**
     * @brief
     * Initialise les états de la manette
     */
    void initialiserEtats();
    /**
     * @brief
     * Initialise les états de la manette pour le pilotage
     */
    void initialiserTypesPilotage();
    /**
     * @brief
     * Initialise les états de la manette pour le déplacement
     */
    void initialiserTypesDeplacement();
    /**
     * @brief
     * Initialise les états de la structures enAvant
     */
    void initialisationStructuresEnAvant();
    /**
     * @brief
     * Initialise les états de la structures enArriere
     */
    void initialisationStructuresEnArriere();
    /**
     * @brief
     * Initialise les états de la structures rotationAGauche
     */
    void initialisationStructureRotationAGauche();
    /**
     * @brief
     * Initialise les états de la structures rotationAGaucheDoucement
     */
    void initialisationStructuresRotationAGaucheDoucement();
    /**
     * @brief
     * Initialise les états de la structures rotationADroite
     */
    void initialisationStructureRotationADroite();
    /**
     * @brief
     * Initialise les états de la structures rotationADroiteDoucement
     */
    void initialisationStructuresRotationADroiteDoucement();
    /**
     * @brief
     * Initialise les états de la structures virageAvantAGauche
     */
    void initialisationStructureVirageAvantAGauche();
    /**
     * @brief
     * Initialise les états de la structures virageAvantAGaucheDoucement
     */
    void initialisationStructuresVirageAvantAGaucheDoucement();
    /**
     * @brief
     * Initialise les états de la structures
     */
    void initialisationStructureVirageAvantADroite();
    /**
     * @brief
     * Initialise les états de la structures virageAvantADroite
     */
    void initialisationStructuresVirageAvantADroiteDoucement();
    /**
     * @brief
     * Initialise les états de la structures virageArriereAGauche
     */
    void initialisationStructureVirageArriereAGauche();
    /**
     * @brief
     * Initialise les états de la structures virageArriereAGaucheDoucement
     */
    void initialisationStructuresVirageArriereAGaucheDoucement();
    /**
     * @brief
     * Initialise les états de la structures virageArriereADroite
     */
    void initialisationStructureVirageArriereADroite();
    /**
     * @brief
     * Initialise les états de la structures virageArriereADroiteDoucement
     */
    void initialisationStructuresVirageArriereADroiteDoucement();
    /**
     * @brief
     * Initialise les états des structures EtatBouton
     */
    void initialiserEtatBouton();

public:
    /**
     * @brief
     * Contructeur de la classe Manette
     * @param deviceId
     */
    explicit Manette(int deviceId);
    /**
     * @brief
     * Destructeur de la classe Manette
     */
    ~Manette();

    /**
     * @brief
     * Verifie l'etat de la manette et creer la trame correspondante
     */
    void determinerTrameDeplacementRobot();
    /**
     * @brief
     * Verifie l'etat de la manette et creer la trame correspondante
     */
    void determinerTramePilotageBras();
    /**
     * @brief
     * Verifie l'etat de la manette et creer la trame correspondante
     */
    void determinerTrameBouton();
    /**
     * @brief
     * Change de mode en fonction du bouton SELECT
     */
    void changerMode();
    /**
     * @brief
     * Retourne le nom de la manette
     * @return le nom de la manette
     */
    QString getNom();

signals:
    /**
     * @brief
     * Envoye des élément de la trame pour la création de la trame de déplacement
     * @param deplacementAxeX
     * @param puissance
     * @param deplacementAxeY
     */
    void creationTrameDeplacement(char deplacementAxeX, int puissance, char deplacementAxeY);
    /**
     * @brief
     * Envoye des élément de la trame pour la création de la trame de pilotage
     * @param direction
     */
    void creationTramePilotage(QString direction);
    /**
     * @brief
     * Envoi un signal indiquant que le bouton photo est pressé
     */
    void prendrePhoto();
    /**
     * @brief
     * Envoye des élément de la trame pour la création de la trame des ordres
     * @param ordre
     */
    void creationTrameOrdre(QString ordre);
    /**
     * @brief
     * Envoye des élément de la trame pour la création de la trame d'ouverture et fermeture de la pince
     */
    void creationTramePince(QString mouvementPince);
    /**
     * @brief
     * Nouvelle trame de commande de la caméra disponible
     * @param axeY
     * @param axeX
     */
    void nouvelleTrameCamera(QString axeY, QString axeX);

public slots:
    /**
     * @brief
     * change l'etat des attributs joystickGaucheAGauche et joystickGaucheADroite en fonction du signe de "valeur"
     * @param valeur
     */
    void changerAxeXJoystickGauche(double valeur);
    /**
     * @brief
     * change l'etat des attributs joystickGaucheEnAvant et joystickGaucheEnArriere en fonction du signe de "valeur"
     * @param valeur
     */
    void changerAxeYJoystickGauche(double valeur);
    /**
     * @brief
     * change l'etat de l'attribut joystickAxeXCamera en fonction du signe de "valeur"
     * @param valeur
     */
    void changerAxeXJoystickDroit(double valeur);
    /**
     * @brief
     * change l'etat de l'attribut joystickAxeYCamera en fonction du signe de "valeur"
     * @param valeur
     */
    void changerAxeYJoystickDroit(double valeur);
    /**
     * @brief
     * change l'etat des attributs boutonHautGauche
     */
    void changerBoutonHautGauche(bool etat);
    /**
     * @brief
     * change l'etat des attributs boutonHautDroit
     */
    void changerBoutonHautDroit(bool etat);
    /**
     * @brief
     * change l'etat des attributs gachetteBasGauche et puissance en fonction de "valeur"
     * @param valeur
     */
    void changerGachetteBasGauche(double valeur);
    /**
     * @brief
     * change l'etat des attributs gachetteBasDroit et puissance en fonction de "valeur"
     * @param valeur
     */
    void changerGachetteBasDroit(double valeur);
    /**
     * @brief
     * change l'etat de l'attribut flecheEnAvant en fonction de "valeur"
     * @param etat
     */
    void changerFlecheEnAvant(bool etat);
    /**
     * @brief
     * change l'etat de l'attribut flecheEnArriere en fonction de "valeur"
     * @param etat
     */
    void changerFlecheEnArriere(bool etat);
    /**
     * @brief
     * change l'etat de l'attribut flecheAGauche en fonction de "valeur"
     * @param etat
     */
    void changerFlecheAGauche(bool etat);
    /**
     * @brief
     * change l'etat de l'attribut flecheADroite en fonction de "etat"
     * @param etat
     */
    void changerFlecheADroite(bool etat);
    /**
     * @brief
     * change l'état du membre boutonA
     */
    void changerBoutonA(bool);
    /**
     * @brief
     * change l'état du membre boutonB
     */
    void changerBoutonB(bool);
    /**
     * @brief
     * change l'état du membre boutonX
     */
    void changerBoutonX(bool);
    /**
     * @brief
     * change l'état du membre boutonY
     */
    void changerBoutonY(bool);
    /**
     * @brief
     * change l'etat des attributs modeDeplacement modePilotageBras en fonction de "etat"
     * @param etat
     */
    void changerBoutonSelect(bool etat);
    /**
     * @brief
     * ferme l'application
     * @param etat
     */
    void fermerApplication(bool etat);
};

#endif // MANETTE_H
