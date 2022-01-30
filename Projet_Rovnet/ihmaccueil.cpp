/**
 * @brief
 * Fichier qui contient la définition de la classe IHMAccueil
 * @file ihmaccueil.cpp
 */

#include "ihmaccueil.h"
#include "ihmrov.h"
#include "ihmcreationcampagne.h"
#include "campagne.h"
#include "basededonnees.h"
#include "ihmgraphiques.h"
#include <QMessageBox>

IHMAccueil::IHMAccueil(QWidget *parent) : QWidget(parent), campagnesEnCours()
{
    qDebug() << Q_FUNC_INFO;
    baseDeDonnees = BaseDeDonnees::getInstance();

    initialisationWidgets();
    initialisationDesignWidgets();
    initialiserEvenements();
    initialiserLayouts();
    configurerWidgets();

    chargerCampagnes();
    rechargerListeCampagnes();

    ihmRov = new IHMRov(this);
    ihmRov->hide();
}

IHMAccueil::~IHMAccueil()
{
    BaseDeDonnees::detruireInstance();
    qDebug() << Q_FUNC_INFO;
}

void IHMAccueil::initialisationWidgets()
{
    archives = new QLabel("Archives :", this);
    rechercheCampagneArchive = new QLineEdit(this);
    boutonImagesArchives = new QPushButton("Photos", this);
    boutonStatistiquesArchives = new QPushButton("Graphiques", this);
    boutonCreationCampagne = new QPushButton("Créer campagne", this);
    boutonDemarrerCampagne = new QPushButton("Démarrer", this);
    boutonArchiverCampagne = new QPushButton("Archiver", this);
    boutonSupprimerCampagne = new QPushButton("Supprimer", this);
    listeCampagne = new QComboBox(this);
    logoAccueil = new QLabel(this);
}

void IHMAccueil::initialisationDesignWidgets()
{
    QFont policeBouton("", 15, 75, false);
    QFont policeTexte("", 13, 75, false);

    archives->setFixedSize(80,50);
    archives->setFont(policeTexte);

    rechercheCampagneArchive->setFixedSize(200,40);
    rechercheCampagneArchive->setFont(policeTexte);
    rechercheCampagneArchive->setStyleSheet("QLineEdit {border-image: url(design/QLine_200x40.png)}" "QLineEdit:hover {border-image: url(design/QLine_200x40_survole.png)}");

    boutonImagesArchives->setFixedSize(157,50);
    boutonImagesArchives->setFont(policeBouton);
    boutonImagesArchives->setStyleSheet("QPushButton {border-image: url(design/bouton_157x50.png)}" "QPushButton:hover {border-image: url(design/bouton_157x50_survole.png)}");

    boutonStatistiquesArchives->setFixedSize(157,50);
    boutonStatistiquesArchives->setFont(policeBouton);
    boutonStatistiquesArchives->setStyleSheet("QPushButton {border-image: url(design/bouton_157x50.png)}" "QPushButton:hover {border-image: url(design/bouton_157x50_survole.png)}");

    boutonCreationCampagne->setFixedSize(302,50);
    boutonCreationCampagne->setFont(policeBouton);
    boutonCreationCampagne->setStyleSheet("QPushButton {border-image: url(design/bouton_302x50.png)}" "QPushButton:hover {border-image: url(design/bouton_302x50_survole.png)}");

    boutonDemarrerCampagne->setFixedSize(302,50);
    boutonDemarrerCampagne->setFont(policeBouton);
    boutonDemarrerCampagne->setStyleSheet("QPushButton {border-image: url(design/bouton_302x50.png)}" "QPushButton:hover {border-image: url(design/bouton_302x50_survole.png)}");

    boutonArchiverCampagne->setFixedSize(199,50);
    boutonArchiverCampagne->setFont(policeBouton);
    boutonArchiverCampagne->setStyleSheet("QPushButton {border-image: url(design/bouton_199x50.png)}" "QPushButton:hover {border-image: url(design/bouton_199x50_survole.png)}");

    boutonSupprimerCampagne->setFixedSize(199,50);
    boutonSupprimerCampagne->setFont(policeBouton);
    boutonSupprimerCampagne->setStyleSheet("QPushButton {border-image: url(design/bouton_199x50.png)}" "QPushButton:hover {border-image: url(design/bouton_199x50_survole.png)}");

    listeCampagne->setFixedSize(199,50);
    listeCampagne->setFont(policeTexte);
    listeCampagne->setStyleSheet("QComboBox {border-image: url(design/combobox_199x50.png)}" "QComboBox:hover {border-image: url(design/combobox_199x50_survole.png)}" "QComboBox::drop-down {border-image: url(rien.png)}" "QComboBox {padding: 0 0 0 15px}");


}

void IHMAccueil::initialiserLayouts()
{
    QVBoxLayout *layoutPrincipal = new QVBoxLayout;
    QHBoxLayout *layoutSuperieur = new QHBoxLayout;
    QVBoxLayout *layoutCentral = new QVBoxLayout;
    QHBoxLayout *layoutConfigurationCampagne = new QHBoxLayout;
    QHBoxLayout *layoutCampagne = new QHBoxLayout;

    layoutPrincipal->addLayout(layoutSuperieur);
    layoutSuperieur->addWidget(archives);
    layoutSuperieur->addWidget(rechercheCampagneArchive);
    layoutSuperieur->addWidget(boutonImagesArchives);
    layoutSuperieur->addWidget(boutonStatistiquesArchives);

    layoutPrincipal->addLayout(layoutCentral);
    layoutCentral->setAlignment(Qt::AlignCenter);
    layoutCentral->addWidget(logoAccueil);

    layoutPrincipal->addLayout(layoutConfigurationCampagne);
    layoutConfigurationCampagne->addWidget(listeCampagne);
    layoutConfigurationCampagne->addWidget(boutonArchiverCampagne);
    layoutConfigurationCampagne->addWidget(boutonSupprimerCampagne);

    layoutPrincipal->addLayout(layoutCampagne);
    layoutCampagne->addWidget(boutonCreationCampagne);
    layoutCampagne->addWidget(boutonDemarrerCampagne);

    setLayout(layoutPrincipal);
    setWindowTitle(NOM_FENETRE_ACCUEIL);
    setStyleSheet("background:#C1BEBE;");
}

void IHMAccueil::configurerWidgets()
{
    qDebug() << Q_FUNC_INFO << qApp->applicationDirPath() + "/images/Robot.png";
    logoAccueil->setPixmap(QPixmap(qApp->applicationDirPath() + "/images/Robot.png"));
    listeCampagne->setEditable(false);
    rechercheCampagneArchive->setPlaceholderText("Nom de la campagne");
    rechercheCampagneArchive->setTextMargins(10,0,0,0);
}

void IHMAccueil::initialiserEvenements()
{
    connect(rechercheCampagneArchive, SIGNAL(textChanged(QString)), this, SLOT(rechercherCampagne(QString)));
    connect(boutonDemarrerCampagne, SIGNAL(clicked()), this, SLOT(demarrerCampagne()));
    connect(boutonCreationCampagne, SIGNAL(clicked()), this, SLOT(creerCampagne()));
    connect(boutonSupprimerCampagne, SIGNAL(clicked()), this, SLOT(supprimerCampagne()));
    connect(boutonArchiverCampagne, SIGNAL(clicked()), this, SLOT(archiverCampagne()));
    connect(boutonImagesArchives, SIGNAL(clicked()), this, SLOT(ouvrirArchive()));
    connect(boutonStatistiquesArchives, SIGNAL(clicked()), this, SLOT(ouvrirGraphiques()));
}

void IHMAccueil::rechargerListeCampagnes()
{
    listeCampagne->clear();

    for(QVector<Campagne*>::iterator it = campagnesEnCours.begin(); it != campagnesEnCours.end(); it++)
    {
        listeCampagne->addItem((*it)->getNomCampagne());
    }

    if(listeCampagne->currentText().isEmpty())
    {
        boutonDemarrerCampagne->setDisabled(true);
        boutonDemarrerCampagne->setStyleSheet("QPushButton {border-image: url(design/bouton_302x50_grise.png)}");

        boutonArchiverCampagne->setDisabled(true);
        boutonArchiverCampagne->setStyleSheet("QPushButton {border-image: url(design/bouton_199x50_grise.png)}");

        boutonSupprimerCampagne->setDisabled(true);
        boutonSupprimerCampagne->setStyleSheet("QPushButton {border-image: url(design/bouton_199x50_grise.png)}");
    }
    else
    {
        boutonDemarrerCampagne->setEnabled(true);
        boutonDemarrerCampagne->setStyleSheet("QPushButton {border-image: url(design/bouton_302x50.png)}" "QPushButton:hover {border-image: url(design/bouton_302x50_survole.png)}");

        boutonArchiverCampagne->setEnabled(true);
        boutonArchiverCampagne->setStyleSheet("QPushButton {border-image: url(design/bouton_199x50.png)}" "QPushButton:hover {border-image: url(design/bouton_199x50_survole.png)}");

        boutonSupprimerCampagne->setEnabled(true);
        boutonSupprimerCampagne->setStyleSheet("QPushButton {border-image: url(design/bouton_199x50.png)}" "QPushButton:hover {border-image: url(design/bouton_199x50_survole.png)}");
    }
}

void IHMAccueil::recupererNbPhotos(QString &nombrePhotos, QString &requeteNombrePhotos)
{
    baseDeDonnees->recuperer(requeteNombrePhotos, nombrePhotos);
}

void IHMAccueil::recupererCampagneEnCours(bool &retourCampagne, QString &requeteInformationsCampagne, QVector<QStringList> &campagnesEnCours)
{
    retourCampagne = baseDeDonnees->recuperer(requeteInformationsCampagne, campagnesEnCours);
}

void IHMAccueil::recupererPhotos(bool &retourPhoto, QString &requeteInformationsPhotos, QVector<QStringList> &informationsPhotos)
{
    retourPhoto = baseDeDonnees->recuperer(requeteInformationsPhotos, informationsPhotos);
}

void IHMAccueil::construireListe(QVector<QString> liste)
{
    QCompleter *completeur = new QCompleter(liste.toList(),this);
    rechercheCampagneArchive->setCompleter(completeur);
}

void IHMAccueil::chargerCampagnes()
{
    baseDeDonnees->ouvrir("campagnes.sqlite");

    bool retourCampagne, retourPhoto;
    QVector<QStringList> campagnesEnCours;
    QString nombrePhotos;
    QVector<QStringList> informationsPhotos;

    QString requeteInformationsCampagne = "SELECT campagne.idCampagne, campagne.nom, campagne.lieu, technicien.nom, technicien.prenom, campagne.date, campagne.duree, campagne.cheminSauvegarde FROM campagne INNER JOIN technicien ON campagne.idTechnicien = technicien.idTechnicien WHERE campagne.enCours = '1' ORDER BY campagne.date DESC";

    #ifdef DEBUG_BASEDEDONNEES
    qDebug() << Q_FUNC_INFO << QString::fromUtf8("requête : ") << requeteInformationsCampagne;
    #endif

    recupererCampagneEnCours(retourCampagne, requeteInformationsCampagne, campagnesEnCours);
    if(retourCampagne)
    {
        for(int i=0; i < campagnesEnCours.size(); i++)
        {
            QStringList informationsCampagne = campagnesEnCours.at(i);
            QString requeteNombrePhotos = "SELECT COUNT(IdPhoto) FROM photo INNER JOIN campagne ON photo.IdCampagne = campagne.IdCampagne WHERE campagne.IdCampagne = '" + informationsCampagne.at(0) + "' ";
            recupererNbPhotos(nombrePhotos, requeteNombrePhotos);

            #ifdef DEBUG_BASEDEDONNEES
            qDebug() << Q_FUNC_INFO << QString::fromUtf8("%0 %1 %2 %3 %4 %5 %6 %7").arg(informationsCampagne.at(0)).arg(informationsCampagne.at(1)).arg(informationsCampagne.at(2)).arg(informationsCampagne.at(3)).arg(informationsCampagne.at(4)).arg(informationsCampagne.at(5)).arg(informationsCampagne.at(6)).arg(informationsCampagne.at(7));
            #endif
            Campagne *campagne = new Campagne(informationsCampagne.at(1), informationsCampagne.at(2), informationsCampagne.at(3), informationsCampagne.at(4), QDateTime::fromString(informationsCampagne.at(5)), this, informationsCampagne.at(6).toInt());

            campagne->setCheminSauvegarde(informationsCampagne.at(7));
            campagne->setNombrePhotos(nombrePhotos.toInt());

            QString requeteInformationsPhotos ="SELECT cheminImage, aGarder, dateHeure FROM photo INNER JOIN campagne ON photo.IdCampagne = campagne.IdCampagne WHERE campagne.enCours = '1' AND photo.IdCampagne = '" + informationsCampagne.at(0) + "'";
            recupererPhotos(retourPhoto, requeteInformationsPhotos, informationsPhotos);
            if(retourPhoto)
            {
                for(int i=0; i < informationsPhotos.size(); i++)
                {
                    QStringList informationPhoto = informationsPhotos.at(i);
                    Photo photo;
                    photo.cheminSauvegarde = informationPhoto.at(0);
                    photo.aGarder = informationPhoto.at(1).toInt();
                    photo.image = QPixmap(informationPhoto.at(0));
                    photo.dateheure = QDateTime::fromString(informationPhoto.at(2));

                    campagne->ajouterPhoto(photo);
                }
            }
            ajouterCampagne(campagne);
            informationsPhotos.clear();
        }
     }
     else
     {
        #ifdef DEBUG_BASEDEDONNEES
        qDebug() << Q_FUNC_INFO << QString::fromUtf8("erreur !");
        #endif
     }
}

void IHMAccueil::supprimerCampagneListe()
{
    int nbCampagnes = campagnesEnCours.size();
    int n = 0;
    for(QVector<Campagne*>::iterator it = campagnesEnCours.begin(); n < nbCampagnes; it++)
    {
        if((*it)->getNomCampagne() == listeCampagne->currentText())
        {
            delete (*it);
            campagnesEnCours.erase(it);
        }
        n++;
    }
    rechargerListeCampagnes();
}

QString IHMAccueil::recupererIdCampagne()
{
    bool retourRequeteIdCampagne;
    QString idCampagne;
    QString requeteIdCampagne = "SELECT idCampagne FROM campagne WHERE campagne.nom = '" + listeCampagne->currentText() + "'";

    retourRequeteIdCampagne = baseDeDonnees->recuperer(requeteIdCampagne, idCampagne);

    if(!retourRequeteIdCampagne)
    {
        #ifdef DEBUG_BASEDEDONNEES
            qDebug() << Q_FUNC_INFO << QString::fromUtf8("erreur !");
        #endif
        return "0";
    }
    else
        return idCampagne;
}

void IHMAccueil::supprimerPhotoLocal(QString requete)
{
    QVector<QString> photoASupprimer;
    baseDeDonnees->recuperer(requete, photoASupprimer);
    for(QVector<QString>::Iterator it = photoASupprimer.begin(); it != photoASupprimer.end(); ++it)
    {
       QFile::remove((*it));
    }
}

void IHMAccueil::supprimerDossierPhotoLocal()
{
    QDir qDir;

    for(QVector<Campagne*>::Iterator it = campagnesEnCours.begin(); it != campagnesEnCours.end(); ++it)
    {
        if((*it)->getNomCampagne() == listeCampagne->currentText())
        {
            if(qDir.exists((*it)->getCheminSauvegarde() + "/" + (*it)->getNomCampagne()))
            {
                if(!qDir.rmdir((*it)->getCheminSauvegarde() + "/" + (*it)->getNomCampagne()))
                {
                    qDebug() << Q_FUNC_INFO << "Erreur : impossible de supprimer le dossier" << (*it)->getCheminSauvegarde() + "/" + (*it)->getNomCampagne();
                    QMessageBox::critical(this, "Erreur", "Erreur : impossible de supprimer le dossier " + (*it)->getCheminSauvegarde() + "/" + (*it)->getNomCampagne() + " !");
                }
            }
        }
    }
}

void IHMAccueil::ajouterCampagne(Campagne *campagne, bool verification)
{
    QDir dossierCampagne(campagne->getCheminSauvegarde());
    if(dossierCampagne.exists())
    {
        if(!dossierCampagne.mkdir(campagne->getNomCampagne()))
        {
            qDebug() << Q_FUNC_INFO << "Erreur : impossible de créer le dossier" << campagne->getCheminSauvegarde() << "campagne" << campagne->getNomCampagne();
            if(verification)
            {
                QMessageBox::critical(this, "Erreur", "Erreur : impossible de créer le dossier " + campagne->getCheminSauvegarde() + " !");
                return;
            }
        }
    }
    campagnesEnCours.push_back(campagne);
    rechargerListeCampagnes();
}

void IHMAccueil::enregistrerCampagneBDD(Campagne *campagne)
{
    #ifdef DEBUG_BASEDEDONNEES
    qDebug() << Q_FUNC_INFO << campagne->getNomCampagne();
    #endif

    baseDeDonnees->ouvrir("campagnes.sqlite");

    QString idTechnicien;
    QString requeteId = "SELECT technicien.IdTechnicien FROM technicien WHERE technicien.nom = '" + campagne->getNomTechnicien() + "' AND technicien.prenom = '" + campagne->getPrenomTechnicien() + "'";
    bool retour = baseDeDonnees->recuperer(requeteId, idTechnicien);
    if(!retour)
    {
        QString requeteInformation = "INSERT INTO technicien (nom, prenom) VALUES ('" + campagne->getNomTechnicien() + "','" + campagne->getPrenomTechnicien() + "')";
        baseDeDonnees->executer(requeteInformation);
        baseDeDonnees->recuperer(requeteId, idTechnicien);
    }

    QString requeteInsertionCampagne = "INSERT INTO campagne (idTechnicien, nom, lieu, date, duree, enCours, cheminSauvegarde) VALUES ('" + idTechnicien + "', '" + campagne->getNomCampagne() + "', '" + campagne->getLieu() + "', '" + campagne->getDate().toString() + "', '" + QString::number(campagne->getDuree()) + "', '1', '" + campagne->getCheminSauvegarde() + "')";
    baseDeDonnees->executer(requeteInsertionCampagne);
}

void IHMAccueil::modifierCampagneBDD(Campagne *campagne)
{
    QString idCampagne, requeteUpdateDuree, requeteIdCampagne, requeteInsertionMesures, requeteModifierPhotos;

    requeteUpdateDuree = "UPDATE campagne SET duree = '"+ QString::number(campagne->getDuree()) + "' WHERE campagne.nom = '" + campagne->getNomCampagne() + "'";
    baseDeDonnees->executer(requeteUpdateDuree);

    requeteIdCampagne = "SELECT campagne.idCampagne FROM campagne WHERE campagne.nom = '" + campagne->getNomCampagne() + "'";
    baseDeDonnees->recuperer(requeteIdCampagne, idCampagne);

    for(int i =0; i < campagne->getAlbumPhoto().size(); ++i)
    {
        requeteModifierPhotos = "UPDATE photo set aGarder = '" + QString::number(campagne->getAlbumPhoto()[i].aGarder) + "' WHERE cheminImage = '" + campagne->getAlbumPhoto()[i].cheminSauvegarde + "'";
        baseDeDonnees->executer(requeteModifierPhotos);
    }
    campagne->supprimerMesures();
}

void IHMAccueil::ajouterPhotoBDD(Photo &photo, Campagne *campagne)
{
    QString idCampagne;
    QString requeteIdCampagne = "SELECT IdCampagne FROM campagne WHERE campagne.nom = '" + campagne->getNomCampagne() + "'";
    baseDeDonnees->recuperer(requeteIdCampagne, idCampagne);

    QString requeteInsertion = "INSERT INTO photo (idCampagne, cheminImage, aGarder, dateHeure) VALUES ('" + idCampagne + "', '" + photo.cheminSauvegarde + "', '1', '" + photo.dateheure.toString() + "')";
    baseDeDonnees->executer(requeteInsertion);
}

void IHMAccueil::demarrerCampagne()
{
    for(QVector<Campagne*>::iterator it = campagnesEnCours.begin(); it != campagnesEnCours.end(); it++)
    {
        if((*it)->getNomCampagne() == listeCampagne->currentText())
        {
            qDebug() << Q_FUNC_INFO << listeCampagne->currentText();
            ihmRov->setCampagne(*it);
            ihmRov->showMinimized();
            ihmRov->gererCampagne();
            this->setVisible(false);
            break;
        }
    }    
}

void IHMAccueil::creerCampagne()
{
    QVector<QStringList> listeTechniciens;
    QString requete = "SELECT technicien.nom, technicien.prenom FROM technicien";

    baseDeDonnees->recuperer(requete, listeTechniciens);

    IHMCreationCampagne *ihmCreationCampagne = new IHMCreationCampagne(this, listeTechniciens);
    ihmCreationCampagne->setFixedSize(416,278);
    ihmCreationCampagne->exec();
}

void IHMAccueil::archiverCampagne()
{
    baseDeDonnees->ouvrir("campagnes.sqlite");
    bool retourRequeteArchiver;
    bool retourRequeteSuppressionPhoto;
    QString requeteArchiver, requeteSuppressionPhoto;

    supprimerPhotoLocal("SELECT photo.cheminImage FROM photo WHERE photo.IdCampagne = '" + recupererIdCampagne() + "' AND photo.aGarder = '0'");

    requeteArchiver = "UPDATE campagne SET enCours = '0' WHERE campagne.nom = '" + listeCampagne->currentText() + "'";
    requeteSuppressionPhoto = "DELETE FROM photo WHERE photo.IdCampagne = '" + recupererIdCampagne() + "' AND photo.aGarder = '0'";

    retourRequeteArchiver = baseDeDonnees->executer(requeteArchiver);
    retourRequeteSuppressionPhoto = baseDeDonnees->executer(requeteSuppressionPhoto);

    if(!retourRequeteArchiver && !retourRequeteSuppressionPhoto)
    {
        #ifdef DEBUG_BASEDEDONNEES
            qDebug() << Q_FUNC_INFO << QString::fromUtf8("erreur !");
        #endif
    }
    else
        supprimerCampagneListe();
}

void IHMAccueil::supprimerCampagne()
{
    baseDeDonnees->ouvrir("campagnes.sqlite");
    bool retourRequeteSuppressionMesures;
    bool retourRequeteSuppressionPhotos;
    bool retourRequeteSuppressionCampagne;

    supprimerPhotoLocal("SELECT photo.cheminImage FROM photo WHERE photo.IdCampagne = '" + recupererIdCampagne() + "'");

    supprimerDossierPhotoLocal();

    QString requeteSuppressionMesures = "DELETE FROM mesure WHERE mesure.IdCampagne = '" + recupererIdCampagne() + "'";
    QString requeteSuppressionPhotos = "DELETE FROM photo WHERE photo.IdCampagne = '" + recupererIdCampagne() + "'";
    QString requeteSuppressionCampagne = "DELETE FROM campagne WHERE campagne.IdCampagne = '" + recupererIdCampagne() + "'";

    retourRequeteSuppressionMesures = baseDeDonnees->executer(requeteSuppressionMesures);
    retourRequeteSuppressionPhotos = baseDeDonnees->executer(requeteSuppressionPhotos);
    retourRequeteSuppressionCampagne = baseDeDonnees->executer(requeteSuppressionCampagne);

    if(!retourRequeteSuppressionMesures && !retourRequeteSuppressionPhotos && !retourRequeteSuppressionCampagne)
    {
        #ifdef DEBUG_BASEDEDONNEES
            qDebug() << Q_FUNC_INFO << QString::fromUtf8("erreur !");
        #endif
    }
    else
        supprimerCampagneListe();
}

void IHMAccueil::enregisterMesureBDD(QString temperature, QString humidite, QString radiation)
{
    baseDeDonnees->ouvrir("campagnes.sqlite");
    bool retourRequeteEnregistrementMesure;

    QString requeteEnregistrementMesure = "INSERT INTO mesure (idCampagne, heure, temperature, radiation, humidite) VALUES (" + recupererIdCampagne() + ",'" + QDateTime::currentDateTime().toString() + "'," + temperature + "," + radiation + "," + humidite + ")";

    retourRequeteEnregistrementMesure = baseDeDonnees->executer(requeteEnregistrementMesure);

    if(!retourRequeteEnregistrementMesure)
    {
        #ifdef DEBUG_BASEDEDONNEES
            qDebug() << Q_FUNC_INFO << QString::fromUtf8("erreur !");
        #endif
    }
}

void IHMAccueil::rechercherCampagne(QString texte)
{
    #ifdef DEBUG_BASEDEDONNEES
        qDebug() << Q_FUNC_INFO;
    #endif

    baseDeDonnees->ouvrir("campagnes.sqlite");
    QVector<QString> listeCampagnesRecherchees;

    bool retourRequeteRechercheCampagne;

    QString requeteRechercheCampagne = "SELECT campagne.nom FROM campagne WHERE campagne.nom LIKE '" + texte + "%' AND campagne.enCours = '0'";

    retourRequeteRechercheCampagne = baseDeDonnees->recuperer(requeteRechercheCampagne, listeCampagnesRecherchees);

    if(!retourRequeteRechercheCampagne)
    {
        #ifdef DEBUG_BASEDEDONNEES
            qDebug() << Q_FUNC_INFO << QString::fromUtf8("erreur !");
        #endif
    }
    else
    {
        construireListe(listeCampagnesRecherchees);
    }
}

void IHMAccueil::ouvrirArchive()
{    
    QStringList cheminSauvegarde;
    QString requete = "SELECT campagne.cheminSauvegarde, campagne.nom FROM campagne WHERE campagne.nom = '" + rechercheCampagneArchive->text() + "'";

    baseDeDonnees->ouvrir("campagnes.sqlite");
    bool retour = baseDeDonnees->recuperer(requete, cheminSauvegarde);
    if(retour)
    {
        if(!(QDesktopServices::openUrl(QUrl(cheminSauvegarde.at(0) + "/" + cheminSauvegarde.at(1), QUrl::TolerantMode))))
            QMessageBox::critical(this, "Erreur", "Erreur : Chemin introuvable ");
    }
    else
    {
        QMessageBox::critical(this, "Erreur", "Erreur : Nom de campagne introuvable ");
    }
}

void IHMAccueil::ouvrirGraphiques()
{
    QVector<QStringList> mesures;
    QString requete = "SELECT mesure.heure, mesure.radiation, mesure.temperature, mesure.humidite FROM mesure INNER JOIN campagne ON campagne.IdCampagne = mesure.IdCampagne WHERE campagne.nom = '" + rechercheCampagneArchive->text() + "'";

    baseDeDonnees->ouvrir("campagnes.sqlite");
    bool retour = baseDeDonnees->recuperer(requete, mesures);
    if(retour)
    {
        if(!mesures.isEmpty())
        {
            IHMGraphiques *ihmGraphique = new IHMGraphiques(mesures);
            ihmGraphique->show();
        }
        else
        {
            QMessageBox::critical(this, "Erreur", "Erreur : Aucune données trouvées !");
        }
    }
}
