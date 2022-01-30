/**
 * @brief
 * Fichier qui contient la déclaration de la classe IHMAccueil
 * @file ihmaccueil.h
 */

#ifndef IHMACCUEIL_H
#define IHMACCUEIL_H

#include <QVector>
#include <QtWidgets>
#include <QString>

#define NOM_FENETRE_ACCUEIL "Projet Rovnet 2020"
#define RATIO30 0.3
#define RATIO40 0.4
#define RATIO50 0.5

class Campagne;
class BaseDeDonnees;
class IHMRov;
struct Photo;

/**
 * @brief
 * Class permettant de créer une nouvelle campagne, reprendre une campagne mise en pause, archiver une campagne, supprimer une campagne, accéder à la base de données et configurer le matériel
 * @class IHMAccueil ihmaccueil.h "ihmaccueil.h"
 */
class IHMAccueil : public QWidget
{
    Q_OBJECT

private:
    QPushButton *boutonImagesArchives;      //!< Bouton permettant d'accéder aux archives
    QPushButton *boutonStatistiquesArchives;//!< Bouton permettant de configurer le matériel
    QPushButton *boutonCreationCampagne;    //!< Bouton permettant de créer une nouvelle campagne
    QPushButton *boutonDemarrerCampagne;    //!< Bouton permettant de démarrer ou reprendre la campagne seléctionner
    QPushButton *boutonArchiverCampagne;    //!< Bouton permettant d'archiver la campagne sélectionner
    QPushButton *boutonSupprimerCampagne;   //!< Bouton permettant de supprimmer la campagne sélectionner
    QComboBox *listeCampagne;               //!< Liste des campagnes créer et non archivés
    QLineEdit *rechercheCampagneArchive;    //!< Zone de recherche des campagnes archivés
    QLabel *logoAccueil;                    //!< Logo de l'IHM accueil
    QLabel *archives;                       //!< Texte indiquant la zone de gestation des archives
    QVector<Campagne*> campagnesEnCours;    //!< Conteneur des campagnes non archivés
    BaseDeDonnees *baseDeDonnees;           //!< Instance d'un objet BaseDeDonnees permettant d'acceder a la BDD
    IHMRov *ihmRov;                         //!< Instance d'un objet ihmRov

    /**
     * @brief
     * Initialise les widgets de l'IHM
     */
    void initialisationWidgets();
    /**
     * @brief
     * Initialise les design des widgets de l'IHM
     */
    void initialisationDesignWidgets();
    /**
     * @brief
     * Initialise les layouts de l'IHM
     */
    void initialiserLayouts();
    /**
     * @brief
     * Configure les widgets de l'IHM
     */
    void configurerWidgets();
    /**
     * @brief
     * Initialise les evenements de l'IHM
     */
    void initialiserEvenements();
    /**
     * @brief
     * Recharge la liste des campagnes en cours
     */
    void rechargerListeCampagnes();
    /**
     * @brief
     * Récupere la liste des noms de campagne non terminés et ajoute les nom de la liste des campagnes disponibles
     */
    void chargerCampagnes();
    /**
     * @brief
     * Permet de supprimer de lq liste la campagne selectionné
     */
    void supprimerCampagneListe();
    /**
     * @brief
     * Recupere l'id de la campagne séléctionné dans la liste
     * @return L'id sous forme de QString
     */
    QString recupererIdCampagne();
    /**
     * @brief
     * Selectionne les chemin d'accès des photo à supprimer dans la base de données et les supprime en local
     * @param requete
     */
    void supprimerPhotoLocal(QString requete);
    /**
     * @brief
     * Supprime le dossier photo si il est vide
     */
    void supprimerDossierPhotoLocal();

    /**
     * @brief
     * Récupère le nombre de photos dans la base de données, le paramètre nombrePhotos passé en référence récupère la valeur
     * @param nombrePhotos
     * @param requeteNombrePhotos
     */
    void recupererNbPhotos(QString &nombrePhotos, QString &requeteNombrePhotos);
    /**
     * @brief
     * Récupère les campagnes en cours dans la base de données, le paramètre campagnesEnCours passé en référence récupère les valeurs
     * @param retourCampagne
     * @param requeteInformationsCampagne
     * @param campagnesEnCours
     */
    void recupererCampagneEnCours(bool &retourCampagne, QString &requeteInformationsCampagne, QVector<QStringList> &campagnesEnCours);
    /**
     * @brief
     * Récupère les photos associés a une campagne dans la base de données, le paramètre informationsPhotos passé en référence récupère les valeurs
     * @param retourPhoto
     * @param requeteInformationsPhotos
     * @param informationsPhotos
     */
    void recupererPhotos(bool &retourPhoto, QString &requeteInformationsPhotos, QVector<QStringList> &informationsPhotos);
    /**
     * @brief
     * Construit la liste déroulante des campagnes sélectionnées
     * @param liste des campagnes sélectionnées
     */
    void construireListe(QVector<QString> liste);

public:
    /**
     * @brief
     * Constructeur de la classe IHMAccueil
     * @param parent
     */
    explicit IHMAccueil(QWidget *parent = nullptr);
    /**
     * @brief
     * Destructeur de la classe IHMAccueil
     */
    ~IHMAccueil();
    /**
     * @brief
     * Ajoute une nouvelle campagne dans la liste des campagne non archivés
     * @param campagne
     * @param verification
     */
    void ajouterCampagne(Campagne *campagne, bool verification=false);
    /**
     * @brief
     * Enregistre les informations de la campagne dans la BDD
     * @param campagne
     */
    void enregistrerCampagneBDD(Campagne *campagne);
    /**
     * @brief
     * Met à jour les informations de la campagne lors de l'arret de celle-ci dans la BDD
     * @param campagne
     */
    void modifierCampagneBDD(Campagne *campagne);
    /**
     * @brief
     * Ajoute la photo prise dans la BDD associé a la campagne
     * @param photo
     * @param campagne
     */
    void ajouterPhotoBDD(Photo &photo, Campagne *campagne);


signals:

public slots:
    /**
     * @brief
     * Permet de démarrer ou reprendre une campagne non archivé
     */
    void demarrerCampagne();
    /**
     * @brief
     * Permet de créer une nouvelle campagne
     */
    void creerCampagne();
    /**
     * @brief
     * Permet d'archiver la campagne selectionner
     */
    void archiverCampagne();
    /**
     * @brief
     * Permet d'archiver la campagne dans la base de données
     */
    void supprimerCampagne();
    /**
     * @brief
     * enregistre les mesures recues dans la base de données
     * @param temperature
     * @param humidite
     * @param radiation
     */
    void enregisterMesureBDD(QString temperature, QString humidite, QString radiation);
    /**
     * @brief
     * Fait une recherche des noms dans la base de données correspondants au texte
     * @param texte
     */
    void rechercherCampagne(QString texte);
    /**
     * @brief
     * Ouvre le dossier des archvies correspondante à la mission saisie
     */
    void ouvrirArchive();
    /**
     * @brief
     * Ouvre l'ihm des graphiques correspondant à la misssion saisie
     */
    void ouvrirGraphiques();
};

#endif // IHMACCUEIL_H
