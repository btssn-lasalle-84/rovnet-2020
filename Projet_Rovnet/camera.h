/**
 * @brief
 * Fichier qui contient la déclaration de la classe Camera
 * @file camera.h
 */

#ifndef CAMERA_H
#define CAMERA_H

#include <QDebug>
#include <QObject>
#include <QThread>
#include <opencv.hpp>
#include <video/video.hpp>
#include <QPixmap>
#include <QImage>
#include <QTime>
#include <QCameraInfo>

#include "rov.h"

//#define SANS_DETECTION

/**
 * @brief
 * Défini le numéro de la caméra par défaut
 * @def CAMERA_DEFAUT
 */
#define CAMERA_DEFAUT       0
/**
 * @brief
 * Défini la largeur en pixel de la caméra par défaut
 * @def LARGEUR_DEFAUT
 */
#define LARGEUR_DEFAUT      1600 //2048
/**
 * @brief
 * Défini la hauteur en pixel de la caméra par défaut
 * @def HAUTEUR_DEFAUT
 */
#define HAUTEUR_DEFAUT      1200 //1024
/**
 * @brief
 * Défini le seuil du contraste, luminosite et saturation de la caméra par défaut
 * @def SEUIL_DEFAUT
 */
#define SEUIL_DEFAUT        0.5

using namespace cv;

class Rov;

/**
 * @brief
 * Class permettant de mettre en place une communication avec la camera
 * @class Camera camera.h "camera.h"
 */
class Camera : public QThread
{
    Q_OBJECT
private:
    Rov *rov;                            //!< Objet rov permettant de récuperer les dernière mesures issues des capteurs
    QString nomCamera;                   //!< Attribut contenant le nom de la caméra sélectionnée
    int numero;                          //!< Attribut contenant le numéro de la caméra sélectionnée
    int largeur;                         //!< Attribut contenant la largeur (width) en pixels de la vidéo
    int hauteur;                         //!< Attribut contenant la hauteur (heigth) en pixels de la vidéo
    double luminosite;                   //!< Attribut contenant la luminosite de la vidéo
    double contraste;                    //!< Attribut contenant le constraste de la vidéo
    double saturation;                   //!< Attribut contenant la saturation de la vidéo
    bool changementProprietes;           //!< Attribut désignant si une propriete de la caméra doit être modifiée
    QList<QSize> listeResolutionsCamera; //!< Liste contenant les résolutions supportés par la caméra
    int choixResolution;                 //!< Choix dans la liste contenant les résolutions supportés par la caméra

    /**
     * @brief
     * Fait l'acquisition d'une nouvelle frame
     * @param camera
     * @param frame
     */
    void acquerirImageVideo(cv::VideoCapture &camera, cv::Mat &frame);

public:
    /**
     * @brief
     * Constructeur de la classe Camera
     * @param rov
     * @param numero     
     * @param choixResolution
     */
    Camera(Rov *rov, int numero, int choixResolution=-1);
    /**
     * @brief
     * Constructeur de la classe Camera
     * @param rov
     * @param nomCamera
     * @param choixResolution
     */
    Camera(Rov *rov, QString nomCamera, int choixResolution=-1);

    /**
     * @brief
     * Destructeur de la classe Camera
     */
    ~Camera();

    /**
     * @brief
     * Démarre une nouveau thread afin de capturer le flux video et l'envoyer à l'IHM
     */
    void run();

    /**
     * @brief
     * Retourne le nom de la caméra
     * @return nom de la caméra
     */
    QString getNom() const;
    /**
     * @brief
     * Après l'acquisition d'une nouvelle frame modifie les propriété de la caméra si ceux-ci ont été modifié par l'IHM
     * @param camera
     */
    void setProprietes(cv::VideoCapture &camera);
    /**
     * @brief
     * Récupère la resolution active
     * @return la resolution active
     */
    QSize getResolution();
    /**
     * @brief
     * Récupère le choix de la resolution active
     * @return le choix de la resolution active
     */
    int getChoixResolution();
    /**
     * @brief
     * Récupère la liste des résolutions supportées par la caméra sélectionnée
     */
    void recupererListeResolutionsCamera();
    /**
     * @brief
     * Récupère la liste des résolutions supportées par la caméra à partir de son numéro
     * @param numero
     */
    void recupererListeResolutionsCamera(int numero);
    /**
     * @brief
     * Récupère la liste des résolutions supportées par la caméra à partir de son nom
     * @param nomCamera
     */
    void recupererListeResolutionsCamera(QString nomCamera);
    /**
     * @brief
     * Récupère la liste des résolutions supporté par la caméra
     * @param cameraInfo
     */
    void recupererListeResolutionsCamera(QCameraInfo &cameraInfo);
    /**
     * @brief
     * Retourne la liste des résolutions supportées par la caméra
     * @return la liste des résolutions supportées par la caméra
     */
    QList<QSize> getListeResolutionsCamera();
    /**
     * @brief
     * Retourne le nombre de caméras connectés
     * @return le nombre de caméras connectés
     */
    static int getNbCameras();
    /**
     * @brief
     * Retourne le numéro de caméra associé a son nom
     * @return le numéro de caméra associé a son nom
     * @param nomCamera
     */
    static int extraireNumero(QString nomCamera);
    /**
     * @brief
     * Retourne le nom de caméra associé a son numéro
     * @return le nom de caméra associé a son numéro
     * @param numero
     */
    static QString creerNomCamera(int numero);
    /**
     * @brief
     * Retourne la liste des résolutions supportés par la caméra passé en parametre
     * @return la liste des résolutions supportés par la caméra passé en parametre
     * @param cameraInfo
     */
    static QList<QSize> lireListeResolutionsCamera(QCameraInfo &cameraInfo);

signals:
    /**
     * @brief
     * Envoie un signal lorsque une nouvelle image du flux vidéo est disponible
     * @param image
     */
    void nouvelleImage(QPixmap image);
    /**
     * @brief
     * Envoie un signal lorsque la vidéo est interrompu
     */
    void finVideo();

public slots:    
    /**
     * @brief
     * Modifie la résolution (largeur x hauteur)
     * @param largeur
     * @param hauteur
     */
    void setResolution(int largeur, int hauteur);
    /**
     * @brief
     * Modifie la résolution (largeur x hauteur)
     * @param resolution (QSize)
     */
    void setResolution(QSize resolution);
    /**
     * @brief
     * Modifie la résolution (index dans la liste)
     * @param choix
     */
    void setResolution(int choix);
    /**
     * @brief
     * Modifie la luminosite de la caméra
     * @param luminosite
     */
    void setLuminosite(int luminosite);
    /**
     * @brief
     * Modifie le contraste de la caméra
     * @param contraste
     */
    void setContraste(int contraste);
    /**
     * @brief
     * Modifie la saturation de la caméra
     * @param saturation
     */
    void setSaturation(int saturation);
};

#endif // CAMERA_H
