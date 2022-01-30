    /**
 * @brief
 * Fichier qui contient la définition de la classe Camera
 * @file camera.cpp
 */

#include "camera.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QMediaRecorder>

Camera::Camera(Rov *rov, int numero, int choixResolution): rov(rov), numero(numero), largeur(LARGEUR_DEFAUT), hauteur(HAUTEUR_DEFAUT), luminosite(SEUIL_DEFAUT), contraste(SEUIL_DEFAUT), saturation(SEUIL_DEFAUT), changementProprietes(false), choixResolution(choixResolution)
{
    #if CV_VERSION_MAJOR == 3
    qDebug() << Q_FUNC_INFO << "OpenCV" << CV_VERSION_MAJOR << CV_VERSION_MINOR;
    #else
    qDebug() << Q_FUNC_INFO << "OpenCV" << CV_MAJOR_VERSION << CV_MINOR_VERSION;
    #endif

    Camera::getNbCameras();

    nomCamera = Camera::creerNomCamera(numero);    
    recupererListeResolutionsCamera();
    if(choixResolution == -1)
        setResolution(largeur, hauteur);
    else
        setResolution(choixResolution);
    qDebug() << Q_FUNC_INFO << this;
    qDebug() << Q_FUNC_INFO << "numero" << numero << "nomCamera" << nomCamera;
    qDebug() << Q_FUNC_INFO << "largeur" << largeur << "hauteur" << hauteur;
    qDebug() << Q_FUNC_INFO << "luminosite" << luminosite << "contraste" << contraste << "saturation" << saturation;
}

Camera::Camera(Rov *rov, QString nomCamera, int choixResolution): rov(rov), nomCamera(nomCamera), largeur(LARGEUR_DEFAUT), hauteur(HAUTEUR_DEFAUT), luminosite(SEUIL_DEFAUT), contraste(SEUIL_DEFAUT), saturation(SEUIL_DEFAUT), changementProprietes(false), choixResolution(choixResolution)
{
    #if CV_VERSION_MAJOR == 3
    qDebug() << Q_FUNC_INFO << "OpenCV" << CV_VERSION_MAJOR << CV_VERSION_MINOR;
    #else
    qDebug() << Q_FUNC_INFO << "OpenCV" << CV_MAJOR_VERSION << CV_MINOR_VERSION;
    #endif

    Camera::getNbCameras();

    numero = Camera::extraireNumero(nomCamera);

    recupererListeResolutionsCamera();
    if(choixResolution == -1)
        setResolution(largeur, hauteur);
    else
        setResolution(choixResolution);

    qDebug() << Q_FUNC_INFO << this;
    qDebug() << Q_FUNC_INFO << "numero" << numero << "nomCamera" << nomCamera;
    qDebug() << Q_FUNC_INFO << "largeur" << largeur << "hauteur" << hauteur;
    qDebug() << Q_FUNC_INFO << "luminosite" << luminosite << "contraste" << contraste << "saturation" << saturation;
}

Camera::~Camera()
{
    qDebug() << Q_FUNC_INFO << this;
}

void Camera::acquerirImageVideo(cv::VideoCapture &camera, cv::Mat &frame)
{
    camera >> frame;
}

void Camera::run()
{
    qDebug() << Q_FUNC_INFO << "start" << "numero" << numero << "nomCamera" << nomCamera;
    this->setPriority(QThread::NormalPriority);

    if(numero < 0)
    {
        qDebug() << Q_FUNC_INFO  << "Erreur numero" << numero << "nomCamera" << nomCamera;
        return;
    }

    cv::VideoCapture camera(numero);
    cv::Mat frame;

    setProprietes(camera);

    while(camera.isOpened() && !isInterruptionRequested())
    {
        acquerirImageVideo(camera, frame);
        if(frame.empty())
            continue;

        QPixmap pixmap = QPixmap::fromImage(QImage(frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888).rgbSwapped());
        emit nouvelleImage(pixmap);

        if(changementProprietes)
            setProprietes(camera);
    }

    camera.release();
    qDebug() << Q_FUNC_INFO << "stop" << "numero" << numero << "nomCamera" << nomCamera;

    emit finVideo();
}

QString Camera::getNom() const
{
    return nomCamera;
}

void Camera::setProprietes(cv::VideoCapture &camera)
{
    qDebug() << Q_FUNC_INFO << "largeur" << largeur << "hauteur" << hauteur;
    camera.set(CV_CAP_PROP_FRAME_WIDTH, largeur);
    camera.set(CV_CAP_PROP_FRAME_HEIGHT, hauteur);

    qDebug() << Q_FUNC_INFO << "luminosite" << luminosite << "contraste" << contraste << "saturation" << saturation;
    camera.set(CV_CAP_PROP_BRIGHTNESS, luminosite);
    camera.set(CV_CAP_PROP_CONTRAST, contraste);
    camera.set(CV_CAP_PROP_SATURATION, saturation);
    
    changementProprietes = false;
}

QSize Camera::getResolution()
{
    if(choixResolution != -1)
        return listeResolutionsCamera.at(choixResolution);
    return QSize(LARGEUR_DEFAUT,HAUTEUR_DEFAUT);
}

int Camera::getChoixResolution()
{
    return choixResolution;
}

void Camera::recupererListeResolutionsCamera()
{
    QCameraInfo cameraInfo(nomCamera.toLatin1());
    recupererListeResolutionsCamera(cameraInfo);
}

void Camera::recupererListeResolutionsCamera(int numero)
{
    QString nom = Camera::creerNomCamera(numero);
    QCameraInfo cameraInfo(nom.toLatin1());
    recupererListeResolutionsCamera(cameraInfo);
}

void Camera::recupererListeResolutionsCamera(QString nomCamera)
{
    QCameraInfo cameraInfo(nomCamera.toLatin1());
    recupererListeResolutionsCamera(cameraInfo);
}

void Camera::recupererListeResolutionsCamera(QCameraInfo &cameraInfo)
{
    #ifndef SANS_DETECTION
    listeResolutionsCamera.clear();
    if(QCameraInfo::availableCameras().count() > 0)
    {
        QCamera *camera = new QCamera(cameraInfo, this);
        QMediaRecorder *mediaRecorder = new QMediaRecorder(camera, this);
        camera->load();
        qDebug() << Q_FUNC_INFO << this << mediaRecorder->supportedResolutions().size();
        if(mediaRecorder->supportedResolutions().size() > 0)
        {
            foreach (const QSize &resolution, mediaRecorder->supportedResolutions())
            {
                qDebug() << Q_FUNC_INFO << resolution.width() << "x" << resolution.height();
                listeResolutionsCamera.push_back(resolution);
            }
        }
        delete mediaRecorder;
        delete camera;
    }
    #else
    Q_UNUSED(cameraInfo);
    listeResolutionsCamera.clear();
    QSize resolutionDefaut(LARGEUR_DEFAUT, HAUTEUR_DEFAUT);
    listeResolutionsCamera.push_back(resolutionDefaut);
    #endif
}

QList<QSize> Camera::getListeResolutionsCamera()
{
    return listeResolutionsCamera;
}

void Camera::setResolution(int largeur, int hauteur)
{    
    qDebug() << Q_FUNC_INFO << "largeur" << largeur << "hauteur" << hauteur;
    QSize size(largeur, hauteur);
    int i = listeResolutionsCamera.indexOf(size);
    if (i != -1)
    {
        choixResolution = i;
        this->largeur = largeur;
        this->hauteur = hauteur;
        changementProprietes = true;
    }
    else
    {
        size = listeResolutionsCamera.last();
        choixResolution = listeResolutionsCamera.indexOf(size);;
        this->largeur = size.width();
        this->hauteur = size.height();
        changementProprietes = true;
    }
    qDebug() << Q_FUNC_INFO << "largeur" << this->largeur << "hauteur" << this->hauteur << "choixResolution" << choixResolution;
}

void Camera::setResolution(QSize resolution)
{
    qDebug() << Q_FUNC_INFO << "largeur" << resolution.width() << "hauteur" << resolution.height();
    int i = listeResolutionsCamera.indexOf(resolution);
    if (i != -1)
    {
        choixResolution = i;
        this->largeur = resolution.width();
        this->hauteur = resolution.height();
        changementProprietes = true;
    }
    else
    {
        QSize size = listeResolutionsCamera.last();
        choixResolution = listeResolutionsCamera.indexOf(size);;
        this->largeur = size.width();
        this->hauteur = size.height();
        changementProprietes = true;
    }
    qDebug() << Q_FUNC_INFO << "largeur" << this->largeur << "hauteur" << this->hauteur << "choixResolution" << choixResolution;
}

void Camera::setResolution(int choix)
{
    qDebug() << Q_FUNC_INFO << "choix" << choix;
    if(choix < listeResolutionsCamera.size())
    {
        choixResolution = choix;
        this->largeur = listeResolutionsCamera.at(choix).width();
        this->hauteur = listeResolutionsCamera.at(choix).height();
        changementProprietes = true;
    }
    else
    {
        QSize size = listeResolutionsCamera.last();
        choixResolution = listeResolutionsCamera.indexOf(size);;
        this->largeur = size.width();
        this->hauteur = size.height();
        changementProprietes = true;
    }
    qDebug() << Q_FUNC_INFO << "largeur" << this->largeur << "hauteur" << this->hauteur << "choixResolution" << choixResolution;
}

void Camera::setLuminosite(int luminosite)
{
    this->luminosite = double(luminosite)/100;
    changementProprietes = true;
}

void Camera::setContraste(int contraste)
{
    this->contraste = double(contraste)/100;
    changementProprietes = true;
}

void Camera::setSaturation(int saturation)
{
    this->saturation = double(saturation)/100;
    changementProprietes = true;
}

int Camera::getNbCameras()
{
    qDebug() << Q_FUNC_INFO  << "Caméra(s) disponible(s)" << QCameraInfo::availableCameras().count();
    return QCameraInfo::availableCameras().count();
}

int Camera::extraireNumero(QString nomCamera)
{
    int numero = -1;
    QString video = "/dev/video";

    if(nomCamera.contains(video))
    {
        QString n = nomCamera.mid(video.length(), nomCamera.length());
        bool ok;
        qDebug() << Q_FUNC_INFO << "nom" << nomCamera << "n" << nomCamera.right(nomCamera.indexOf("/dev/video")) << "index" << nomCamera.indexOf("/dev/video");
        numero = n.toInt(&ok);
        if(ok)
            return numero;
    }
    return numero;
}

QString Camera::creerNomCamera(int numero)
{
    QString nom;

    if(numero >= 0)
    {
        nom = QString("/dev/video") + QString::number(numero);
    }
    return nom;
}

QList<QSize> Camera::lireListeResolutionsCamera(QCameraInfo &cameraInfo)
{
    QList<QSize> listeResolutions;
    listeResolutions.clear();
    if(QCameraInfo::availableCameras().count() > 0)
    {
        QCamera *camera = new QCamera(cameraInfo);
        QMediaRecorder *mediaRecorder = new QMediaRecorder(camera);
        camera->load();
        qDebug() << Q_FUNC_INFO << mediaRecorder->supportedResolutions().size();
        if(mediaRecorder->supportedResolutions().size() > 0)
        {
            foreach (const QSize &resolution, mediaRecorder->supportedResolutions())
            {
                qDebug() << Q_FUNC_INFO << resolution.width() << "x" << resolution.height();
                listeResolutions.push_back(resolution);
            }
        }
        delete mediaRecorder;
        delete camera;
    }
    return listeResolutions;
}
