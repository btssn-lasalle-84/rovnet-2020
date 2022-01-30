/**
 * @brief
 * Fichier qui contient la définition de la classe Rov
 * @file rov.cpp
 */

#include "rov.h"
#include "campagne.h"
#include <iomanip>

Rov::Rov(IHMRov *ihmRov, QObject *parent) : QObject(parent), ihmRov(ihmRov), camera(nullptr), trameDeplacement("$DEP;0;0;0\r\n"), tramePrecedenteDeplacement("$DEP;0;0;0\r\n"), tramePilotage("$BRAS;0\r\n"), tramePrecedentePilotage("$BRAS;0\r\n"), tramePince("$PINCE;0\r\n"), tramePrecedentePince("$PINCE;0\r\n"), tramePrecedenteCamera(TRAME_CAMERA_IMMOBILE),
campagneEnCours(false), etatLed(false)
{
    qDebug() << Q_FUNC_INFO;
    communicationRov = new CommunicationRov(this);
    capteurs = new Capteurs(this);

    initialiserEvenements();
    detecterManette();
}

Rov::~Rov()
{
    supprimerManette();
    arreterCampagne();
    qDebug() << Q_FUNC_INFO;
}

void Rov::detecterManette()
{
    listeManettes = QGamepadManager::instance()->connectedGamepads();

    if (listeManettes.isEmpty())
    {
        qDebug() << Q_FUNC_INFO << "Aucune manette détectée !";
    }
    else
    {
        qDebug() << Q_FUNC_INFO << "Nombre de manettes" << listeManettes.size();
    }

    for (auto m : listeManettes)
    {
        qDebug() << Q_FUNC_INFO << "-> Manette" << m;
        Manette *manette = new Manette(m);
        manettes.push_back(manette);
        initialiserEvenementManette(manette);
    }
}

void Rov::initialiserEvenementManette(Manette *manette)
{
    connect(manette, SIGNAL(creationTrameDeplacement(char, int, char)), this, SLOT(creerTrameDeplacement(char, int, char)));
    connect(manette, SIGNAL(creationTramePilotage(QString)), this, SLOT(creerTramePilotage(QString)));
    connect(manette, SIGNAL(creationTrameOrdre(QString)), this, SLOT(creerTrameOrdre(QString)));
    connect(manette, SIGNAL(creationTramePince(QString)), this, SLOT(creerTramePince(QString)));
    connect(manette, SIGNAL(nouvelleTrameCamera(QString,QString)), this, SLOT(creerTrameCamera(QString,QString)));

    connect(manette, SIGNAL(axisLeftXChanged(double)), manette, SLOT(changerAxeXJoystickGauche(double)));
    connect(manette, SIGNAL(axisLeftYChanged(double)), manette, SLOT(changerAxeYJoystickGauche(double)));
    connect(manette, SIGNAL(axisRightXChanged(double)), manette, SLOT(changerAxeXJoystickDroit(double)));
    connect(manette, SIGNAL(axisRightYChanged(double)), manette, SLOT(changerAxeYJoystickDroit(double)));
    connect(manette, SIGNAL(buttonL1Changed(bool)), manette, SLOT(changerBoutonHautGauche(bool)));
    connect(manette, SIGNAL(buttonR1Changed(bool)), manette, SLOT(changerBoutonHautDroit(bool)));
    connect(manette, SIGNAL(buttonL2Changed(double)), manette, SLOT(changerGachetteBasGauche(double)));
    connect(manette, SIGNAL(buttonR2Changed(double)), manette, SLOT(changerGachetteBasDroit(double)));
    connect(manette, SIGNAL(buttonUpChanged(bool)), manette, SLOT(changerFlecheEnAvant(bool)));
    connect(manette, SIGNAL(buttonDownChanged(bool)), manette, SLOT(changerFlecheEnArriere(bool)));
    connect(manette, SIGNAL(buttonLeftChanged(bool)), manette, SLOT(changerFlecheAGauche(bool)));
    connect(manette, SIGNAL(buttonRightChanged(bool)), manette, SLOT(changerFlecheADroite(bool)));
    connect(manette, SIGNAL(buttonAChanged(bool)), manette, SLOT(changerBoutonA(bool)));
    connect(manette, SIGNAL(buttonBChanged(bool)), manette, SLOT(changerBoutonB(bool)));
    connect(manette, SIGNAL(buttonXChanged(bool)), manette, SLOT(changerBoutonX(bool)));
    connect(manette, SIGNAL(buttonYChanged(bool)), manette, SLOT(changerBoutonY(bool)));
    connect(manette, SIGNAL(buttonSelectChanged(bool)), manette, SLOT(changerBoutonSelect(bool)));
    connect(manette, SIGNAL(buttonGuideChanged(bool)), manette, SLOT(fermerApplication(bool)));
    connect(manette, SIGNAL(buttonR3Changed(bool)), ihmRov, SLOT(capturerImage(bool)));
    connect(manette, SIGNAL(buttonL3Changed(bool)), this, SLOT(allumerLed(bool)));

    connect(manette, SIGNAL(connectedChanged(bool)), ihmRov, SLOT(modifieEtatManette(bool)));
}

void Rov::allumerLed(bool etat)
{
    if(etat && etatLed)
    {
        communicationRov->emettreTrame(TRAME_LED_OFF);
        etatLed = false;
    }

    if(etat && !etatLed)
    {
        communicationRov->emettreTrame(TRAME_LED_ON);
        etatLed = true;
    }
}

void Rov::decoderTrameTelemetrie(QString trameTelemetrie)
{
    capteurs->setTelemetrie(trameTelemetrie.section(";",1,1));
    capteurs->setAngle(trameTelemetrie.section(";",2,2));
}

void Rov::decoderTrameCapteur(QString trameCapteur)
{
    QString temperature, humidite, radiation;

    temperature = QString::number(trameCapteur.section(";",1,1).toDouble()/10);
    humidite = trameCapteur.section(";",2,2);
    radiation = trameCapteur.section(";",3,3);

    capteurs->setTemperature(temperature);
    capteurs->setHumidite(humidite);
    capteurs->setRadiation(radiation);

    Mesure mesure;
    mesure.dateheure = QDateTime::currentDateTime();
    mesure.temperature = temperature;
    mesure.humidite = humidite;
    mesure.radiation = radiation;

    QDateTime date;

    ihmRov->getCampagne()->ajouterMesure(mesure);
    ihmRov->actualiserInformationsSeuils();

    emit enregistrerMesures(temperature, humidite, radiation);

}

void Rov::initialiserEvenements()
{
    connect(communicationRov, SIGNAL(nouvelleTrame(QString)), this, SLOT(decoderTrame(QString)));
    connect(communicationRov, SIGNAL(etatPortModifie(bool, QString)), ihmRov, SLOT(modifieEtatPortSerie(bool, QString)));
}

void Rov::supprimerManette()
{
    for(int i=0;i<manettes.size();i++)
        delete manettes[i];
}

bool Rov::demarrerCampagne()
{
    qDebug() << Q_FUNC_INFO;
    if(Camera::getNbCameras() > 0)
    {
        dureeCampagne.start();
        QString nom = Camera::creerNomCamera(CAMERA_DEFAUT);
        if(demarrerVideo(nom))
            campagneEnCours = true;
    }
    return campagneEnCours;
}

void Rov::arreterCampagne()
{
    qDebug() << Q_FUNC_INFO;
    ihmRov->getCampagne()->setDuree(dureeCampagne.elapsed());
    arreterVideo();
    campagneEnCours = false;
}

Camera* Rov::getCamera()
{
    return camera;
}

Capteurs* Rov::getCapteurs()
{
    return capteurs;
}

QString Rov::getTempsCampagne()
{
    QTime duree(0,0);
    QTime dureeMission = duree.addMSecs(dureeCampagne.elapsed() + ihmRov->getCampagne()->getDuree());
    return dureeMission.toString("hh:mm:ss");
}

bool Rov::demarrerVideo(QString nomCamera, int choixResolution)
{
    qDebug() << Q_FUNC_INFO << "nomCamera" << nomCamera << "choixResolution" << choixResolution;
    if(camera == nullptr)
    {
        camera = new Camera(this, nomCamera, choixResolution);
        connect(camera, SIGNAL(nouvelleImage(QPixmap)), ihmRov, SLOT(afficherImage(QPixmap)));
        ihmRov->initialiserEvenementsCamera();
        camera->start();
        ihmRov->modifieEtatCamera(true, nomCamera);
        return true;
    }
    return false;
}

bool Rov::getCampagneEncours() const
{
    return campagneEnCours;
}

void Rov::decoderTrame(QString trame)
{
    QString trameTelemetrie, trameCapteur;

    QStringList trames = trame.split("\r\n");
    qDebug() << Q_FUNC_INFO << "trame" << trames.size();
    for(int i = 0; i < trames.size(); i++)
    {
        if(!trames[i].isEmpty())
        {
            if(trames[i].startsWith(DEBUT_TRAME_TELEMETRIE))
            {
                trameTelemetrie = trames[i];
                decoderTrameTelemetrie(trameTelemetrie);
            }
            else if(trames[i].startsWith(DEBUT_TRAME_CAPTEUR))
            {
                trameCapteur = trames[i];
                decoderTrameCapteur(trameCapteur);
            }
        }
        else
        {
            qDebug() << Q_FUNC_INFO << "Trame inconnue !";
        }
    }
}

void Rov::creerTrameDeplacement(char deplacementAxeX, int puissance, char deplacementAxeY)
{
    trameDeplacement = DEBUT_TRAME_DEPLACEMENT ";" + QString(deplacementAxeX) + ";" + QString::number(puissance) + ";" + QString(deplacementAxeY) + "\r\n";

    if(tramePrecedenteDeplacement != trameDeplacement)
    {
        if(TRAME_DEPLACEMENT_IMMOBILE == trameDeplacement)
            ihmRov->setEtatRadar(true);
        else
            ihmRov->setEtatRadar(false);
        qDebug() << Q_FUNC_INFO << "trameDeplacement :" << trameDeplacement;
        tramePrecedenteDeplacement = trameDeplacement;
        communicationRov->emettreTrame(trameDeplacement);
    }
}

void Rov::creerTramePilotage(QString deplacement)
{
    tramePilotage = DEBUT_TRAME_PILOTAGE ";" + deplacement + "\r\n";
    if(tramePrecedentePilotage != tramePilotage && tramePince == TRAME_PINCE_IMMOBILE)
    {
        qDebug() << Q_FUNC_INFO << "tramePilotage :" << tramePilotage;
        tramePrecedentePilotage = tramePilotage;
        communicationRov->emettreTrame(tramePilotage);
    }
}

void Rov::creerTrameOrdre(QString ordre)
{
    trameOrdre = DEBUT_TRAME_ORDRE ";" + ordre + "\r\n";
    if(tramePrecedentePilotage == TRAME_PILOTAGE_IMMOBILE && tramePince == TRAME_PINCE_IMMOBILE)
    {
        qDebug() << Q_FUNC_INFO << "trameOrdre :" << trameOrdre;
        communicationRov->emettreTrame(trameOrdre);
    }
}

void Rov::creerTramePince(QString mouvementPince)
{
    tramePince = DEBUT_TRAME_PINCE ";" + mouvementPince + "\r\n";
    if(tramePrecedentePilotage == TRAME_PILOTAGE_IMMOBILE && tramePrecedentePince != tramePince)
    {
        qDebug() << Q_FUNC_INFO << "tramePince :" << tramePince;
        tramePrecedentePince = tramePince;
        communicationRov->emettreTrame(tramePince);
    }
}

void Rov::creerTrameCamera(QString axeX, QString axeY)
{
    QString trameCamera = DEBUT_TRAME_CAMERA ";" + axeX + ";" + axeY + "\r\n";

    if(tramePrecedenteCamera != trameCamera)
    {
        tramePrecedenteCamera = trameCamera;
        communicationRov->emettreTrame(trameCamera);
        qDebug() << Q_FUNC_INFO << "trame camera" << trameCamera;
    }
}

void Rov::arreterVideo()
{
    if(camera != nullptr)
    {
        qDebug() << Q_FUNC_INFO << "isRunning" << camera->isRunning();
        ihmRov->arreterVideo();
        disconnect(camera, SIGNAL(nouvelleImage(QPixmap)), ihmRov, SLOT(afficherImage(QPixmap)));
        camera->requestInterruption();
        camera->wait();
        delete camera;
        camera = nullptr;
        ihmRov->modifieEtatCamera(false, "");
    }
}

void Rov::modifierConfiguration(Configuration &configuration)
{
    communicationRov->setConfiguration(configuration);
}

CommunicationRov* Rov::getCommunicationRov()
{
    return communicationRov;
}

QVector<Manette*> Rov::getManettes()
{
    return manettes;
}
