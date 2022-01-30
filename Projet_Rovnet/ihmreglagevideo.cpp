/**
 * @brief
 * Fichier qui contient la définition de la classe ReglageVideo
 * @file ihmreglagevideo.cpp
 */

#include "ihmreglagevideo.h"

IHMReglageVideo::IHMReglageVideo(Rov *rov, QWidget *parent) : QWidget(parent), rov(rov)
{
    qDebug() << Q_FUNC_INFO;
    initialiserWidgets();
    configurerWidgets();
    initialiserLayouts();
    initialiserEvenements();    
}

IHMReglageVideo::~IHMReglageVideo()
{
    qDebug() << Q_FUNC_INFO;
}

void IHMReglageVideo::initialiserWidgets()
{
    sliderLuminositeVideo = new QSlider(Qt::Horizontal, this);
    sliderContrasteVideo = new QSlider(Qt::Horizontal, this);
    sliderSaturationVideo = new QSlider(Qt::Horizontal, this);

    luminosite = new QLabel("Luminosité", this);
    contraste = new QLabel("Contraste", this);
    saturation = new QLabel("Saturation", this);

    luminositeVideo = new QSpinBox(this);
    contrasteVideo = new QSpinBox(this);
    saturationVideo = new QSpinBox(this);

    camera = new QLabel("Camera(s): ", this);
    resolution = new QLabel("Résolution: ", this);

    listeCameras = new QComboBox(this);
    listeResolutions = new QComboBox(this);

    boutonVideo = new QPushButton("Arrêter", this);
}

void IHMReglageVideo::configurerWidgets()
{
    sliderLuminositeVideo->setValue(50);
    sliderContrasteVideo->setValue(50);
    sliderSaturationVideo->setValue(50);

    luminositeVideo->setValue(50);
    contrasteVideo->setValue(50);
    saturationVideo->setValue(50);

    listeCameras->setEnabled(false);
}

void IHMReglageVideo::initialiserLayouts()
{
    QVBoxLayout *layoutPrincipal = new QVBoxLayout;
    QHBoxLayout *layoutReglageVideo = new QHBoxLayout;
    QVBoxLayout *layoutConfigurationLuminosite = new QVBoxLayout;
    QVBoxLayout *layoutConfigurationContraste = new QVBoxLayout;
    QVBoxLayout *layoutConfigurationSaturation = new QVBoxLayout;
    QHBoxLayout *layoutCamera = new QHBoxLayout;
    QHBoxLayout *layoutBoutonCamera = new QHBoxLayout;

    layoutReglageVideo->setAlignment(Qt::AlignLeft);
    layoutConfigurationContraste->setAlignment(Qt::AlignTop);
    layoutConfigurationLuminosite->setAlignment(Qt::AlignTop);
    layoutConfigurationSaturation->setAlignment(Qt::AlignTop);
    layoutBoutonCamera->setAlignment(Qt::AlignLeft);

    layoutPrincipal->addLayout(layoutReglageVideo);
    layoutPrincipal->addLayout(layoutCamera);
    layoutPrincipal->addLayout(layoutBoutonCamera);

    layoutReglageVideo->addLayout(layoutConfigurationLuminosite);
    layoutReglageVideo->addLayout(layoutConfigurationContraste);
    layoutReglageVideo->addLayout(layoutConfigurationSaturation);

    layoutConfigurationLuminosite->addWidget(luminosite);
    layoutConfigurationLuminosite->addWidget(sliderLuminositeVideo);
    layoutConfigurationLuminosite->addWidget(luminositeVideo);
    layoutConfigurationContraste->addWidget(contraste);
    layoutConfigurationContraste->addWidget(sliderContrasteVideo);
    layoutConfigurationContraste->addWidget(contrasteVideo);
    layoutConfigurationSaturation->addWidget(saturation);
    layoutConfigurationSaturation->addWidget(sliderSaturationVideo);
    layoutConfigurationSaturation->addWidget(saturationVideo);
    layoutCamera->addWidget(camera);
    layoutCamera->addWidget(listeCameras);
    layoutCamera->addWidget(resolution);
    layoutCamera->addWidget(listeResolutions);
    layoutBoutonCamera->addWidget(boutonVideo);

    setLayout(layoutPrincipal);
    setWindowTitle(NOM_FENETRE_REGLAGEVIDEO);
    setStyleSheet("background:#202020;color:white;");
}

void IHMReglageVideo::initialiserEvenements()
{
    connect(sliderLuminositeVideo, SIGNAL(valueChanged(int)), luminositeVideo, SLOT(setValue(int)));
    connect(sliderContrasteVideo, SIGNAL(valueChanged(int)), contrasteVideo, SLOT(setValue(int)));
    connect(sliderSaturationVideo, SIGNAL(valueChanged(int)), saturationVideo, SLOT(setValue(int)));
    connect(luminositeVideo, SIGNAL(valueChanged(int)), sliderLuminositeVideo, SLOT(setValue(int)));
    connect(contrasteVideo, SIGNAL(valueChanged(int)), sliderContrasteVideo, SLOT(setValue(int)));
    connect(saturationVideo, SIGNAL(valueChanged(int)), sliderSaturationVideo, SLOT(setValue(int)));
    connect(boutonVideo, SIGNAL(clicked()), this, SLOT(gererVideo()));
}

void IHMReglageVideo::gererVideo()
{
    if(boutonVideo->text() == "Arrêter")
    {
        rov->arreterVideo();
        boutonVideo->setText("Démarrer");
    }
    else
    {
        activerCamera();
        boutonVideo->setText("Arrêter");
    }
}

void IHMReglageVideo::initialiserEvenementsCamera()
{
    if(rov->getCamera() != nullptr)
    {
        if(rov->getCamera()->isRunning())
            return;
        chargerListeCameraDisponible();
        connect(luminositeVideo, SIGNAL(valueChanged(int)), rov->getCamera(), SLOT(setLuminosite(int)));
        connect(contrasteVideo, SIGNAL(valueChanged(int)), rov->getCamera(), SLOT(setContraste(int)));
        connect(saturationVideo, SIGNAL(valueChanged(int)), rov->getCamera(), SLOT(setSaturation(int)));
        connect(listeCameras, SIGNAL(currentIndexChanged(int)), this, SLOT(chargerListeResolutionDisponible(int)));
        connect(listeResolutions, SIGNAL(currentIndexChanged(int)), rov->getCamera(), SLOT(setResolution(int)));
    }
}

void IHMReglageVideo::chargerListeCameraDisponible()
{
    int nbCameras = QCameraInfo::availableCameras().count();
    qDebug() << Q_FUNC_INFO << "Caméra(s) disponible(s)" << QCameraInfo::availableCameras().count();    
    if (nbCameras > 0)
    {
       #ifndef SANS_DETECTION
       QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
       listeCameras->clear();
       int choix = -1, i = 0;
       foreach (const QCameraInfo &cameraInfo, cameras)
       {
           listeCameras->addItem(cameraInfo.deviceName());
           qDebug() << Q_FUNC_INFO << "Device" << cameraInfo.deviceName();
           qDebug() << Q_FUNC_INFO << "Description" << cameraInfo.description();
           if(rov->getCamera() != nullptr)
           {
               if(cameraInfo.deviceName() == rov->getCamera()->getNom())
               {
                   choix = i;
               }
           }
           i++;
       }
       #else
       int choix = 0;
       qDebug() << Q_FUNC_INFO << "Device" << rov->getCamera()->getNom();
       listeCameras->addItem(rov->getCamera()->getNom());
       #endif

       if(choix != -1)
       {
           if(rov->getCamera() != nullptr)
                chargerListeResolutionDisponible(rov->getCamera()->getNom());
           listeCameras->setCurrentIndex(choix);
       }       
    }

}

void IHMReglageVideo::chargerListeResolutionDisponible(int index)
{
    if(index < 0)
        return;
    chargerListeResolutionDisponible(listeCameras->currentText());
}

void IHMReglageVideo::chargerListeResolutionDisponible(QString nom)
{
    #ifndef SANS_DETECTION
    QCameraInfo cameraInfo(nom.toLatin1());
    QList<QSize> liste = Camera::lireListeResolutionsCamera(cameraInfo);
    listeResolutions->clear();
    foreach (const QSize &resolution, liste)
    {
        qDebug() << Q_FUNC_INFO << resolution.width() << "x" << resolution.height();
        listeResolutions->addItem(QString::number(resolution.width()) + QString("x") + QString::number(resolution.height()));
    }
    #else
    listeResolutions->clear();
    QSize resolutionDefaut = rov->getCamera()->getResolution();
    qDebug() << Q_FUNC_INFO << resolutionDefaut.width() << "x" << resolutionDefaut.height();
    listeResolutions->addItem(QString::number(resolutionDefaut.width()) + QString("x") + QString::number(resolutionDefaut.height()));
    #endif
    if(rov->getCamera() != nullptr)
    {
        qDebug() << Q_FUNC_INFO << "choixResolution" << rov->getCamera()->getChoixResolution();
        listeResolutions->setCurrentIndex(rov->getCamera()->getChoixResolution());
    }
}

void IHMReglageVideo::activerCamera()
{
    qDebug() << Q_FUNC_INFO << listeCameras->currentText() << listeResolutions->currentText() << listeResolutions->currentIndex();
    rov->demarrerVideo(listeCameras->currentText(), listeResolutions->currentIndex());
    listeCameras->setEnabled(false);
}

void IHMReglageVideo::modifierEtatBoutons()
{
    if(rov->getCamera() != nullptr)
    {
        disconnect(luminositeVideo, SIGNAL(valueChanged(int)), rov->getCamera(), SLOT(setLuminosite(int)));
        disconnect(contrasteVideo, SIGNAL(valueChanged(int)), rov->getCamera(), SLOT(setContraste(int)));
        disconnect(saturationVideo, SIGNAL(valueChanged(int)), rov->getCamera(), SLOT(setSaturation(int)));
        disconnect(listeCameras, SIGNAL(currentIndexChanged(int)), this, SLOT(chargerListeResolutionDisponible(int)));
        disconnect(listeResolutions, SIGNAL(currentIndexChanged(int)), rov->getCamera(), SLOT(setResolution(int)));
    }
    listeCameras->setEnabled(true);
}
