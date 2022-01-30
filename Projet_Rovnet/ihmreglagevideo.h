/**
 * @brief
 * Fichier qui contient la déclaration de la classe IHMReglageVideo
 * @file ihmreglagevideo.h
 */

#ifndef REGLAGEVIDEO_H
#define REGLAGEVIDEO_H

#include <QtWidgets>
#include <QCameraInfo>
#include "rov.h"

#define NOM_FENETRE_REGLAGEVIDEO "Réglages vidéo"

class Rov;

/**
 * @brief
 * Classe permettant de regler l'affichage du flux video
 * @class IHMReglageVideo ihmReglageVideo.h "ihmReglageVideo.h"
 */
class IHMReglageVideo : public QWidget
{
    Q_OBJECT
private:
    Rov *rov;                           //!< Objet rov permettant de mofidier les reglage du flux vidéo
    QSlider *sliderLuminositeVideo;     //!< Slider permettant de modifier la luminosite du flux vidéo
    QSlider *sliderContrasteVideo;      //!< Slider permettant de modifier le contraste  du flux vidéo
    QSlider *sliderSaturationVideo;     //!< Slider permettant de modifier la saturation du flux vidéo
    QLabel *luminosite;                 //!< Texte informant le reglage à modifier
    QLabel *contraste;                  //!< Texte informant le reglage à modifier
    QLabel *saturation;                 //!< Texte informant le reglage à modifier
    QSpinBox *luminositeVideo;          //!< Zone de saisie permettant de modifier la luminosite du flux vidéo
    QSpinBox *contrasteVideo;           //!< Zone de saisie permettant de modifier le contraste du flux vidéo
    QSpinBox *saturationVideo;          //!< Zone de saisie permettant de modifier la saturation du flux vidéo
    QLabel *camera;                     //!< Texte informant de l'élément à selectionner (caméra)
    QComboBox *listeCameras;            //!< Liste déroulante déstiné à accueillir la liste des caméra disponible
    QLabel *resolution;                 //!< Texte informant de l'élément à selectionner (résolution)
    QComboBox *listeResolutions;        //!< Liste déroulante déstiné à accueillir la liste des résolutions disponible
    QPushButton *boutonVideo;   //!< Bouton permettant de démarrer le flux vidéo de la caméra selectionner
    QPushButton *boutonArreterVideo;    //!< Bouton permettant d'arrêter le flux vidéo de la caméra selectionner

    /**
     * @brief
     * Initialise les widgets de l'IHM
     */
    void initialiserWidgets();
    /**
     * @brief
     * Configure l'etat des widgets à la création de l'IHM
     */
    void configurerWidgets();
    /**
     * @brief
     * Initialise les layout de l'IHM
     */
    void initialiserLayouts();
    /**
     * @brief
     * Initialise les événements de l'IHM
     */
    void initialiserEvenements();    
    /**
     * @brief
     * Charge la liste des caméras disponibles dans la liste déroulante
     */
    void chargerListeCameraDisponible();

public:
    /**
     * @brief
     * Constructeur de la classe ReglageVideo
     * @param rov
     * @param parent
     */
    IHMReglageVideo(Rov *rov, QWidget *parent = nullptr);
    /**
     * @brief
     * Destructeur de la classe ReglageVideo
     */
    ~IHMReglageVideo();
    /**
     * @brief
     * Initialise les événements liés à la caméra
     */
    void initialiserEvenementsCamera();

signals:

public slots:
    /**
     * @brief
     * Active la caméra
     */
    void activerCamera();
    /**
     * @brief
     * Modifie l'etat des boutons lors du démarrage du flux vidéo
     */
    void modifierEtatBoutons();
    /**
     * @brief
     * Charge les résolutions pour une caméra sélectionnée
     * @param index
     */
    void chargerListeResolutionDisponible(int index);
    /**
     * @brief
     * Charge les résolutions pour une caméra sélectionnée
     * @param nom
     */
    void chargerListeResolutionDisponible(QString nom);
    /**
     * @brief
     * Modifie l'etat de la vidéo en fonction de l'état actuel
     */
    void gererVideo();
};

#endif // REGLAGEVIDEO_H
