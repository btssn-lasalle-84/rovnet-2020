/**
 * @brief
 * Fichier qui contient la définition de la classe IHMRov
 * @file ihmrov.cpp
 */

#include "ihmrov.h"
#include "rov.h"
#include "ihmreglagevideo.h"
#include "ihmalbumphoto.h"
#include "ihmaccueil.h"
#include "campagne.h"
#include "ihmconfiguration.h"
#include <QtMath>

IHMRov::IHMRov(IHMAccueil *ihmAccueil, QWidget *parent) : QWidget(parent), campagneEnCours(nullptr), ihmAccueil(ihmAccueil), etatRadar(true)
{
    qDebug() << Q_FUNC_INFO << this << "width" << qApp->desktop()->screen()->width() << "height" << qApp->desktop()->screen()->height();
    rov = new Rov(this);
    reglageVideo = nullptr;
    configuration = nullptr;

    initialiserWidgets();
    configurerWidgets();
    initialiserLayouts();
    initialiserEvenements();

    if(!rov->getManettes().isEmpty())
        modifieEtatManette(true);
}

IHMRov::~IHMRov()
{
    qDebug() << Q_FUNC_INFO;
}

void IHMRov::initialiserWidgets()
{
    fluxVideo = new QLabel("Aucune image détéctée",this);
    photosEnCours = new QPushButton("Album Photo", this);
    boutonReglageVideo = new QPushButton("Réglages Vidéo", this);
    boutonCampagne = new QPushButton(QString::fromUtf8("Démarrer"), this);
    boutonConfiguration = new QPushButton("Communication", this);
    hautDePage = new QLabel(this);
    basDePage = new QLabel(this);
    logoEtatPortSerie = new QLabel(this);
    logoEtatCamera = new QLabel(this);
    logoEtatManette = new QLabel(this);
    etatPortSerie = new QLabel(this);
    etatCamera = new QLabel(this);
    etatManette = new QLabel(this);
    portSerie = new QLabel("Port série :", this);
    camera = new QLabel("Caméra :", this);
    manette = new QLabel("Manette :", this);
    indicateurTemperature = new QwtThermo(this);
    indicateurRadiation = new QwtThermo(this);
    zoneEtatMateriel = new QGroupBox(this);
    zoneInformationSeuils = new QGroupBox(this);
    temperature = new QLabel("Température\n", this);
    radiation = new QLabel("Radiation\n", this);

    QFont police1("", 15, 75, false);
    QFont police2("Cursive", 12, 40, true);

    portSerie->setFont(police1);
    camera->setFont(police1);
    manette->setFont(police1);
    etatPortSerie->setFont(police2);
    etatCamera->setFont(police2);
    etatManette->setFont(police2);
    temperature->setFont(police2);
    radiation->setFont(police2);

    fluxVideo->setFixedSize(230,50);
    fluxVideo->setFont(police1);

    photosEnCours->setFixedSize(230,50);
    photosEnCours->setFont(police1);
    photosEnCours->setStyleSheet("QPushButton {border-image: url(design/bouton_230x50.png)}" "QPushButton:hover {border-image: url(design/bouton_230x50_survole.png)}");
    //photosEnCours->setStyleSheet("QPushButton {border-image: url(design/bouton_230x50_survole.png)}" "QPushButton:hover {border-image: url(design/bouton_230x50.png)}");

    boutonReglageVideo->setFixedSize(230,50);
    boutonReglageVideo->setFont(police1);
    boutonReglageVideo->setStyleSheet("QPushButton {border-image: url(design/bouton_230x50.png)}" "QPushButton:hover {border-image: url(design/bouton_230x50_survole.png)}");
    //boutonReglageVideo->setStyleSheet("QPushButton {border-image: url(design/bouton_230x50_survole.png)}" "QPushButton:hover {border-image: url(design/bouton_230x50.png)}");

    boutonCampagne->setFixedSize(230,50);
    boutonCampagne->setFont(police1);
    boutonCampagne->setStyleSheet("QPushButton {border-image: url(design/bouton_230x50.png)}" "QPushButton:hover {border-image: url(design/bouton_230x50_survole.png)}");
    //boutonCampagne->setStyleSheet("QPushButton {border-image: url(design/bouton_230x50_survole.png)}" "QPushButton:hover {border-image: url(design/bouton_230x50.png)}");

    boutonConfiguration->setFixedSize(230,50);
    boutonConfiguration->setFont(police1);
    boutonConfiguration->setStyleSheet("QPushButton {border-image: url(design/bouton_230x50.png)}" "QPushButton:hover {border-image: url(design/bouton_230x50_survole.png)}");
    //boutonConfiguration->setStyleSheet("QPushButton {border-image: url(design/bouton_230x50_survole.png)}" "QPushButton:hover {border-image: url(design/bouton_230x50.png)}");

    hautDePage->setMinimumHeight(1);
    //hautDePage->setStyleSheet("QLabel {border-image: url(design/fond_noir.png)}");
    basDePage->setMinimumHeight(1);
    //basDePage->setStyleSheet("QLabel {border-image: url(design/fond_noir.png)}");

    #ifdef PAS_DE_MANETTE
    testCapturePhoto = new QPushButton("Capturer", this);
    testCapturePhoto->setFixedSize(230,50);
    //testCapturePhoto->setFont(police);
    testCapturePhoto->setStyleSheet("QPushButton {border-image: url(design/bouton_230x50.png)}" "QPushButton:hover {border-image: url(design/bouton_230x50_survole.png)}");
    QAction *actionCapturerPhoto = new QAction(this);
    actionCapturerPhoto->setShortcut(QKeySequence(Qt::Key_C));
    addAction(actionCapturerPhoto);
    connect(actionCapturerPhoto, SIGNAL(triggered()), this, SLOT(capturerImage()));
    #endif
}

void IHMRov::configurerWidgets()
{
    int width = int(qApp->desktop()->screen()->width() * RATIO);
    int height = int(qApp->desktop()->screen()->height() * RATIO);
    fluxVideo->setFixedSize(width, height);
    fluxVideo->setScaledContents(true);
    fluxVideo->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    fluxVideo->setPixmap(QPixmap(qApp->applicationDirPath() +  "/images/signal-interrompu.jpg"));

    logoEtatPortSerie->setPixmap(QPixmap(qApp->applicationDirPath() + "/images/inactif.png").scaled(qApp->desktop()->screen()->width()*0.01, qApp->desktop()->screen()->width()*0.01));
    etatPortSerie->setText("Fermé");

    logoEtatCamera->setPixmap(QPixmap(qApp->applicationDirPath() + "/images/inactif.png").scaled(qApp->desktop()->screen()->width()*0.01, qApp->desktop()->screen()->width()*0.01));
    etatCamera->setText("Eteinte");

    logoEtatManette->setPixmap(QPixmap(qApp->applicationDirPath() + "/images/inactif.png").scaled(qApp->desktop()->screen()->width()*0.01, qApp->desktop()->screen()->width()*0.01));
    etatManette->setText("Déconnectée");

    indicateurTemperature->setScale(QwtInterval(SEUIL_TEMPERATURE_NEGATIVE_ACCEPTABLE,SEUIL_TEMPERATURE_POSITIVE_ACCEPTABLE));
    indicateurRadiation->setScale(QwtInterval(0,SEUIL_RADIATION_ACCEPTABLE));

    indicateurTemperature->setOrigin(0.);
    indicateurTemperature->setOriginMode(QwtThermo::OriginMode::OriginCustom);

    zoneEtatMateriel->setStyleSheet("QGroupBox {background: white} QGroupBox{border: 2px solid black}");
    zoneInformationSeuils->setStyleSheet("QGroupBox {background: white} QGroupBox{border: 2px solid black}");
    portSerie->setStyleSheet("QLabel {background: white}");
    camera->setStyleSheet("QLabel {background: white}");
    manette->setStyleSheet("QLabel {background: white}");
    etatPortSerie->setStyleSheet("QLabel {background: white}");
    etatCamera->setStyleSheet("QLabel {background: white}");
    etatManette->setStyleSheet("QLabel {background: white}");
    logoEtatPortSerie->setStyleSheet("QLabel {background: white}");
    logoEtatCamera->setStyleSheet("QLabel {background: white}");
    logoEtatManette->setStyleSheet("QLabel {background: white}");
    indicateurRadiation->setStyleSheet("QwtThermo {background: white}");
    indicateurTemperature->setStyleSheet("QwtThermo {background: white}");
    temperature->setStyleSheet("QLabel {background: white}");
    radiation->setStyleSheet("QLabel {background: white}");
}

void IHMRov::initialiserLayouts()
{
    QVBoxLayout *layoutPrincipal = new QVBoxLayout;
    QHBoxLayout *layoutInformationRov = new QHBoxLayout;
    QVBoxLayout *layoutCamera = new QVBoxLayout;
    QVBoxLayout *layoutOptionVideo = new QVBoxLayout;
    QVBoxLayout *layoutGestionCampagne = new QVBoxLayout;
    QVBoxLayout *layoutReglageVideo = new QVBoxLayout;
    QVBoxLayout *layoutInformationMateriel = new QVBoxLayout;
    QHBoxLayout *layoutEtatPortSerie = new QHBoxLayout;
    QHBoxLayout *layoutEtatCamera = new QHBoxLayout;
    QHBoxLayout *layoutEtatManette = new QHBoxLayout;
    QHBoxLayout *layoutInformationSeuils = new QHBoxLayout;
    QVBoxLayout *layoutSeuilTemperature = new QVBoxLayout;
    QVBoxLayout *layoutSeuilRadiation = new QVBoxLayout;

    layoutOptionVideo->setAlignment(Qt::AlignTop);
    layoutGestionCampagne->setAlignment(Qt::AlignBottom);
    layoutInformationMateriel->setAlignment(Qt::AlignTop);
    layoutCamera->addWidget(fluxVideo);

    layoutOptionVideo->addWidget(boutonReglageVideo);
    layoutOptionVideo->addWidget(boutonConfiguration);
    layoutOptionVideo->addWidget(photosEnCours);
    #ifdef PAS_DE_MANETTE
    layoutOptionVideo->addWidget(testCapturePhoto);
    #endif

    layoutInformationMateriel->addWidget(portSerie);
    layoutInformationMateriel->addLayout(layoutEtatPortSerie);
    layoutInformationMateriel->addWidget(camera);
    layoutInformationMateriel->addLayout(layoutEtatCamera);
    layoutInformationMateriel->addWidget(manette);
    layoutInformationMateriel->addLayout(layoutEtatManette);

    layoutEtatPortSerie->setAlignment(Qt::AlignLeft);
    layoutEtatCamera->setAlignment(Qt::AlignLeft);
    layoutEtatManette->setAlignment(Qt::AlignLeft);

    layoutEtatPortSerie->addWidget(logoEtatPortSerie);
    layoutEtatPortSerie->addWidget(etatPortSerie);

    layoutEtatCamera->addWidget(logoEtatCamera);
    layoutEtatCamera->addWidget(etatCamera);

    layoutEtatManette->addWidget(logoEtatManette);
    layoutEtatManette->addWidget(etatManette);

    layoutSeuilTemperature->addWidget(temperature);
    layoutSeuilTemperature->addWidget(indicateurTemperature);

    layoutSeuilRadiation->addWidget(radiation);
    layoutSeuilRadiation->addWidget(indicateurRadiation);

    layoutInformationSeuils->addLayout(layoutSeuilTemperature);
    layoutInformationSeuils->addLayout(layoutSeuilRadiation);

    layoutPrincipal->addWidget(hautDePage);
    layoutPrincipal->addLayout(layoutInformationRov);
    layoutInformationRov->addLayout(layoutCamera);
    layoutInformationRov->addStretch();
    layoutInformationRov->addLayout(layoutReglageVideo);
    layoutReglageVideo->addLayout(layoutOptionVideo);

    //layoutReglageVideo->addLayout(layoutInformationMateriel);
    zoneEtatMateriel->setLayout(layoutInformationMateriel);
    layoutReglageVideo->addWidget(zoneEtatMateriel);
    //layoutReglageVideo->addLayout(layoutInformationSeuils);
    zoneInformationSeuils->setLayout(layoutInformationSeuils);
    layoutReglageVideo->addWidget(zoneInformationSeuils);

    layoutReglageVideo->addLayout(layoutGestionCampagne);
    layoutGestionCampagne->addWidget(boutonCampagne);
    layoutPrincipal->addWidget(basDePage);

    setLayout(layoutPrincipal);
    resize(width(), fluxVideo->maximumHeight());
    //setStyleSheet("background:#101010;");
    setStyleSheet("background:#C1BEBE;");

    setWindowFlags(windowFlags() & ~Qt::WindowCloseButtonHint);
    showMinimized();
}

void IHMRov::initialiserEvenements()
{
    connect(boutonReglageVideo, SIGNAL(clicked()), this, SLOT(reglerVideo()));
    connect(boutonConfiguration, SIGNAL(clicked()), this, SLOT(reglerConfiguration()));
    connect(photosEnCours, SIGNAL(clicked()), this, SLOT(chargerPhotos()));
    #ifdef PAS_DE_MANETTE
    connect(testCapturePhoto, SIGNAL(clicked(bool)), this, SLOT(capturerImage(bool)));
    #endif
    connect(boutonCampagne, SIGNAL(clicked()), this, SLOT(gererCampagne()));
    connect(rov, SIGNAL(enregistrerMesures(QString, QString, QString)), ihmAccueil, SLOT(enregisterMesureBDD(QString, QString, QString)));
}

void IHMRov::actualiserInformations(QPixmap &image)
{
    QPainter p(&image);
    QPen pen;
    QPen penCadre;
    QFont fontHaut("Open Sans");
    QFont fontBas("Open Sans");
    int marge = 0;
    pen.setWidth(qApp->desktop()->screen()->width() * 0.005);

    //QFontDatabase fontDatabase;
    //qDebug() << fontDatabase.families();

    // règle la taille de police
    fontHaut.setPixelSize(image.height()*0.045); // 4.5 % de la hauteur de l'image en pixel
    fontBas.setPixelSize(fontHaut.pixelSize()*0.75); // 75% de la hauteur normale

    /*
    // pour le dessin du bandeau
    penCadre.setWidth(1);
    penCadre.setBrush(Qt::lightGray);
    penCadre.setCapStyle(Qt::RoundCap);
    penCadre.setJoinStyle(Qt::RoundJoin);
    p.setPen(penCadre);
    // dessine un bandeau en haut (hauteur 5% de la hauteur de l'image)
    p.drawLine( 0, (image.height()*0.05)+1, image.width(), (image.height()*0.05)+1 );
    // dessine un bandeau en bas (hauteur 5% de la hauteur de l'image)
    p.drawLine( 0, (image.height()*0.95)-1, image.width(), (image.height()*0.95)-1 );
    */
    QRect bandeauHaut( 0, 0, image.width(), image.height()*0.05 );
    QRect bandeauBas( 0, image.height()*0.95, image.width(), image.height()*0.05 );
    penCadre.setBrush(QBrush(QColor(255, 255, 255, 255)));
    p.setPen(penCadre);
    p.fillRect(bandeauHaut, QBrush(QColor(128, 128, 128, 64)));
    p.fillRect(bandeauBas, QBrush(QColor(128, 128, 128, 64)));

    // découpe le bandeau en trois cadres (largeurs : 25 % 50 % 25% de la largeur de l'image)
    QRect bandeauHautGauche( 0, 0, image.width()*0.25, image.height()*0.05 );
    QRect bandeauHautCentre( image.width()*0.25, 0, image.width()*0.5, image.height()*0.05 );
    QRect bandeauHautDroite( image.width()*0.75, 0, image.width()*0.25, image.height()*0.05 );

    // découpe le bandeau en trois cadres (largeurs : 25 % 25 % 25% 25% de la largeur de l'image)
    QRect bandeauBasGauche( 0, image.height()*0.95, image.width()*0.25, image.height()*0.05 );
    QRect bandeauBasCentreGauche( image.width()*0.25, image.height()*0.95, image.width()*0.25, image.height()*0.05 );
    QRect bandeauBasCentreDroite( image.width()*0.50, image.height()*0.95, image.width()*0.25, image.height()*0.05 );
    QRect bandeauRadar( image.width()*0.75, image.height() - image.width()*0.25, image.width()*0.25, image.width()*0.25);
    QRect bandeauBasDroite( image.width()*0.75, image.height()*0.95, image.width()*0.25, image.height()*0.05 );

    /*
    // pour le dessin des cadres
    p.setPen(pen);
    // dessine les trois cadres du haut
    p.drawRect( bandeauHautGauche ); // haut gauche
    p.fillRect(bandeauHautGauche, QBrush(QColor(128, 128, 128, 64)));
    p.drawRect( bandeauHautCentre ); // haut centre
    p.fillRect(bandeauHautCentre, QBrush(QColor(128, 128, 128, 64)));
    p.drawRect( bandeauHautDroite ); // haut droite
    p.fillRect(bandeauHautDroite, QBrush(QColor(128, 128, 128, 64)));
    // dessine les quatres cadres du bas
    p.drawRect( bandeauBasGauche ); // bas gauche
    p.fillRect(bandeauBasGauche, QBrush(QColor(128, 128, 128, 64)));
    p.drawRect( bandeauBasCentreGauche ); // bas centre gauche
    p.fillRect(bandeauBasCentreGauche, QBrush(QColor(128, 128, 128, 64)));
    p.drawRect( bandeauBasCentreDroite ); // bas centre droite
    p.fillRect(bandeauBasCentreDroite, QBrush(QColor(128, 128, 128, 64)));
    p.drawRect( bandeauBasDroite ); // bas droite
    p.fillRect(bandeauBasDroite, QBrush(QColor(128, 128, 128, 64)));
    */

    // pour le dessin des textes et images
    pen.setBrush(Qt::darkRed);
    p.setPen(pen);
    p.setFont(fontHaut);

    marge = image.width()*0.0025;
    QRect cadreLogoHorloge( bandeauHautGauche.x(), bandeauHautGauche.y(), bandeauHautGauche.width()*0.1, bandeauHautGauche.height() ); // 10% du bandeau
    cadreLogoHorloge.adjust(marge, marge, -marge, -marge);
    QImage logoHeure(qApp->applicationDirPath() + "/images/logo_heure.png");
    p.drawImage(cadreLogoHorloge, logoHeure);
    p.drawText(bandeauHautGauche, Qt::AlignHCenter|Qt::AlignVCenter, QTime::currentTime().toString());

    QRect cadreLogoDuree( bandeauHautDroite.x(), bandeauHautDroite.y(), bandeauHautDroite.width()*0.1, bandeauHautGauche.height() ); // 10% du bandeau
    cadreLogoDuree.adjust(marge, marge, -marge, -marge);
    QImage logoDuree(qApp->applicationDirPath() + "/images/logo_duree.png");
    p.drawImage(cadreLogoDuree, logoDuree);
    p.drawText(bandeauHautDroite, Qt::AlignHCenter|Qt::AlignVCenter, rov->getTempsCampagne());

    p.setFont(fontBas);
    QRect cadreLogoTemperature( bandeauBasGauche.x(), bandeauBasGauche.y(), bandeauBasGauche.width()*0.1, bandeauBasGauche.height() ); // 10% du bandeau
    cadreLogoTemperature.adjust(marge, marge, -marge, -marge);
    QImage logoTemperature(qApp->applicationDirPath() + "/images/logo_temperature.png");
    p.drawImage(cadreLogoTemperature, logoTemperature);
    p.drawText(bandeauBasGauche, Qt::AlignHCenter|Qt::AlignVCenter, rov->getCapteurs()->getTemperature() + " °C");

    QRect cadreLogoHumidite( bandeauBasCentreGauche.x(), bandeauBasCentreGauche.y(), bandeauBasCentreGauche.width()*0.1, bandeauBasCentreGauche.height() ); // 10% du bandeau
    cadreLogoHumidite.adjust(marge, marge, -marge, -marge);
    QImage logoHumditie(qApp->applicationDirPath() + "/images/logo_humidite.png");
    p.drawImage(cadreLogoHumidite, logoHumditie);
    p.drawText(bandeauBasCentreGauche, Qt::AlignHCenter|Qt::AlignVCenter, rov->getCapteurs()->getHumidite() + "%");

    QRect cadreLogoRadiation( bandeauBasCentreDroite.x(), bandeauBasCentreDroite.y(), bandeauBasCentreDroite.width()*0.1, bandeauBasCentreDroite.height() ); // 10% du bandeau
    cadreLogoRadiation.adjust(marge, marge, -marge, -marge);
    QImage logoRadiation(qApp->applicationDirPath() + "/images/logo_radiation.png");
    p.drawImage(cadreLogoRadiation, logoRadiation);
    p.drawText(bandeauBasCentreDroite, Qt::AlignHCenter|Qt::AlignVCenter, rov->getCapteurs()->getRadiation() + " uS/h");

    if(getEtatRadar())
    {
        pen.setBrush(Qt::green);
        p.setPen(pen);
        //p.drawPoint(image.width()*0.875, image.height() - image.width()*0.125); // placement du point 0 sur le radar
        p.drawImage(bandeauRadar, QImage(qApp->applicationDirPath() + "/images/RADAR.png"));

        if(rov->getCapteurs()->getTelemetrie().toInt() <= DISTANCE_MAX_RADAR && rov->getCapteurs()->getTelemetrie().toInt() >= 0 && rov->getCapteurs()->getAngle().toInt() >= 0 && rov->getCapteurs()->getAngle().toInt() <= ANGLE_MAX_RADAR && rov->getCapteurs()->getAngle() != "" && rov->getCapteurs()->getTelemetrie() != "")
        {
            if(rov->getCapteurs()->getAngle().toInt() == ANGLE_MAX_RADAR || rov->getCapteurs()->getAngle().toInt() == ANGLE_MIN_RADAR)
            {
                pointsRadar.clear();
            }
            pointsRadar.push_back(QPoint(calculCoordonneesX(image),calculCoordonneesY(image)));
            for (QVector<QPoint>::iterator it = pointsRadar.begin(); it != pointsRadar.end(); ++it)
            {
               p.drawPoint((*it).x(),(*it).y());
            }
        }
    }
    else
    {
        QRect cadreLogoObstacle( bandeauBasDroite.x(), bandeauBasDroite.y(), bandeauBasDroite.width()*0.1, bandeauBasDroite.height() ); // 10% du bandeau
        cadreLogoObstacle.adjust(marge, marge, -marge, -marge);
        QImage logoObstacle(qApp->applicationDirPath() + "/images/logo_telemetrie.png");
        p.drawImage(cadreLogoObstacle, logoObstacle);
        p.drawText(bandeauBasDroite, Qt::AlignHCenter|Qt::AlignVCenter, "Obstacle : " + rov->getCapteurs()->getTelemetrie() + " cm");

    }
    p.end();
}

void IHMRov::actualiserInformationsSeuils()
{   
    if(rov->getCapteurs()->getRadiation().toDouble() > SEUIL_RADIATION_ACCEPTABLE)
    {
        indicateurRadiation->setFillBrush(QBrush(QColor(Qt::GlobalColor::darkRed)));
    }
    else
    {
        indicateurRadiation->setFillBrush(QBrush(QColor(Qt::GlobalColor::darkGreen)));
    }

    if(rov->getCapteurs()->getTemperature().toDouble() > SEUIL_TEMPERATURE_POSITIVE_ACCEPTABLE || rov->getCapteurs()->getTemperature().toDouble() < SEUIL_TEMPERATURE_NEGATIVE_ACCEPTABLE)
    {
        indicateurTemperature->setFillBrush(QBrush(QColor(Qt::GlobalColor::darkRed)));
    }
    else
    {
        indicateurTemperature->setFillBrush(QBrush(QColor(Qt::GlobalColor::darkGreen)));
    }

    indicateurRadiation->setValue(rov->getCapteurs()->getRadiation().toDouble());
    indicateurTemperature->setValue(rov->getCapteurs()->getTemperature().toDouble());
}

double IHMRov::calculCoordonneesX(QPixmap &image)
{
    if(rov->getCapteurs()->getAngle().toDouble() > 90)
        return image.width()*(0.875 - 0.125*qSin(qDegreesToRadians(90.0 - (rov->getCapteurs()->getAngle().toDouble() - 2 * (rov->getCapteurs()->getAngle().toDouble() - 90))))* rov->getCapteurs()->getTelemetrie().toDouble()/DISTANCE_MAX_RADAR);
    else
        return image.width()*(0.875 + 0.125*qSin(qDegreesToRadians(90.0 - rov->getCapteurs()->getAngle().toDouble()))* rov->getCapteurs()->getTelemetrie().toDouble()/DISTANCE_MAX_RADAR);
}

double IHMRov::calculCoordonneesY(QPixmap &image)
{
    return (image.height() - image.width()*0.125) - image.width()*0.125*qSin(qDegreesToRadians(rov->getCapteurs()->getAngle().toDouble()))*rov->getCapteurs()->getTelemetrie().toDouble()/DISTANCE_MAX_RADAR;
}

void IHMRov::setCampagne(Campagne *campagne)
{
    campagneEnCours = campagne;
    setWindowTitle(NOM_FENETRE_ROV  " " + campagne->getNomCampagne() + " " + campagne->getDate().toString());
}

Campagne* IHMRov::getCampagne()
{
    return campagneEnCours;
}

void IHMRov::setEtatRadar(bool etatRadar)
{
    this->etatRadar = etatRadar;
}

bool IHMRov::getEtatRadar()
{
    return etatRadar;
}

void IHMRov::afficherImage(QPixmap image)
{
    derniereImageVideo = image;
    actualiserInformations(image);
    fluxVideo->setPixmap(image);
}

void IHMRov::reglerVideo()
{
    if(reglageVideo != nullptr)
    {
        reglageVideo->show();
        reglageVideo->raise();
    }
}

void IHMRov::reglerConfiguration()
{
    if(configuration != nullptr)
    {
        configuration->actualisePortsDisponibles();
        configuration->show();
        configuration->raise();
    }
}

void IHMRov::capturerImage(bool etat)
{
    #ifndef PAS_DE_MANETTE
    if(etat)
    #endif
    //Q_UNUSED(etat)
    {
        Photo photo;

        photo.image = derniereImageVideo;
        photo.dateheure = QDateTime::currentDateTime();
        photo.aGarder = true;
        photo.cheminSauvegarde = campagneEnCours->getCheminSauvegarde() + "/" + campagneEnCours->getNomCampagne() + "/" + "Capture_" + QString::number(campagneEnCours->incrementeNombrePhoto());

        campagneEnCours->ajouterPhoto(photo);
        qDebug() << Q_FUNC_INFO << "Photo capturée";

        photo.image.save(photo.cheminSauvegarde, "PNG");

        ihmAccueil->ajouterPhotoBDD(photo, campagneEnCours);
    }
}

void IHMRov::gererCampagne()
{
    qDebug() << Q_FUNC_INFO << boutonCampagne->text();
    if(boutonCampagne->text() == QString::fromUtf8("Démarrer"))
    {
        if(reglageVideo == nullptr)
            reglageVideo = new IHMReglageVideo(rov);
        if(configuration == nullptr)
            configuration = new IHMConfiguration(rov);
        if(rov->demarrerCampagne())
        {
            boutonCampagne->setText(QString::fromUtf8("Arrêter"));
        }
    }
    else if(boutonCampagne->text() == QString::fromUtf8("Arrêter"))
    {
        fermer();
        //this->close();
    }
}

void IHMRov:: chargerPhotos()
{
    IHMAlbumPhoto *ihmAlbumPhoto = new IHMAlbumPhoto(this);
    ihmAlbumPhoto->ouvrirAlbumPhotos(campagneEnCours->getAlbumPhoto());
}

void IHMRov::initialiserEvenementsCamera()
{
    reglageVideo->initialiserEvenementsCamera();
}

void IHMRov::arreterVideo()
{
    reglageVideo->modifierEtatBoutons();
    fluxVideo->setPixmap(QPixmap(qApp->applicationDirPath() +  "/images/signal-interrompu.jpg"));
}

void IHMRov::closeEvent(QCloseEvent *event)
{
    qDebug() << Q_FUNC_INFO << rov->getCampagneEncours();
    if(rov->getCampagneEncours())
    {
        fermer();
        event->accept(); // -> close
    }
    else
    {
        event->ignore();
    }
}

void IHMRov::fermer()
{
    rov->arreterCampagne();
    delete reglageVideo;
    delete configuration;
    reglageVideo = nullptr;
    configuration = nullptr;
    boutonCampagne->setText(QString::fromUtf8("Démarrer"));
    ihmAccueil->modifierCampagneBDD(campagneEnCours);
    this->setVisible(false);
    ihmAccueil->setVisible(true);
}

void IHMRov::modifieEtatPortSerie(bool etat, QString information)
{
    if(etat)
    {
        logoEtatPortSerie->setPixmap(QPixmap(qApp->applicationDirPath() + "/images/actif.png").scaled(qApp->desktop()->screen()->width()*0.01, qApp->desktop()->screen()->width()*0.01));
        etatPortSerie->setText(information);
    }
    else
    {
        configuration->modifieEtatBoutons();
        logoEtatPortSerie->setPixmap(QPixmap(qApp->applicationDirPath() + "/images/inactif.png").scaled(qApp->desktop()->screen()->width()*0.01, qApp->desktop()->screen()->width()*0.01));
        etatPortSerie->setText("Fermé");
    }
}

void IHMRov::modifieEtatCamera(bool etat, QString information)
{
    if(etat)
    {
        logoEtatCamera->setPixmap(QPixmap(qApp->applicationDirPath() + "/images/actif.png").scaled(qApp->desktop()->screen()->width()*0.01, qApp->desktop()->screen()->width()*0.01));
        etatCamera->setText(information);
    }
    else
    {
        logoEtatCamera->setPixmap(QPixmap(qApp->applicationDirPath() + "/images/inactif.png").scaled(qApp->desktop()->screen()->width()*0.01, qApp->desktop()->screen()->width()*0.01));
        etatCamera->setText("Eteinte");
    }
}

void IHMRov::modifieEtatManette(bool etat)
{
    if(etat)
    {
        logoEtatManette->setPixmap(QPixmap(qApp->applicationDirPath() + "/images/actif.png").scaled(qApp->desktop()->screen()->width()*0.01, qApp->desktop()->screen()->width()*0.01));
        etatManette->setText("Connectée");
    }
    else
    {
        logoEtatManette->setPixmap(QPixmap(qApp->applicationDirPath() + "/images/inactif.png").scaled(qApp->desktop()->screen()->width()*0.01, qApp->desktop()->screen()->width()*0.01));
        etatManette->setText("Déconnectée");
    }
}
