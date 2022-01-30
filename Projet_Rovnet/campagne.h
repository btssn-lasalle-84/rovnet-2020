/**
 * @brief
 * Fichier qui contient la déclaration de la classe Campagne
 * @file campagne.h
 */

#ifndef CAMPAGNE_H
#define CAMPAGNE_H

#include <QObject>
#include <QTime>
#include <QVector>

#include "ihmalbumphoto.h"

/**
 * @brief
 * structure permettant de définir les propriété d'une mesure prise à une heure précise
 * @struct Mesure
 */
struct Mesure
{
    QDateTime dateheure;    //!< Date/Heure
    QString humidite;       //!< Donnée humidité
    QString temperature;    //!< Donnée temperature
    QString radiation;      //!< Donnée radiation
};

/**
 * @brief
 * Class contenant les informations de la campagne en cours
 * @class Campagne campagne.h "campagne.h"
 */
class Campagne : public QObject
{
    Q_OBJECT
private:
    QString nomCampagne;               //!< Attribut contenant le nom de la campagne
    QString nomTechnicien;             //!< Attribut contenant le nom du technicien
    QString prenomTechnicien;          //!< Attribut contenant le nom du technicien
    QString lieu;                      //!< Attribut contenant le lieu de la campagne
    QDateTime date;                    //!< Attribut contenant la date de la campagne
    QString cheminSauvegardePhotos;    //!< Attribut contenant le chemin de sauvegarde des photos
    int duree;                         //!< Attribut contenant la durée de la campagne en millisecondes
    bool estArchive;                   //!< Attribut booléen afin de savoir si la campagne est toujours en cours
    QVector<Photo> albumPhoto;         //!< Conteneur des photos prises durant la campagne
    QVector<Mesure> mesures;           //!< Conteneur des mesures enregistrés durant la campagne
    int nombrePhotos;                  //!< Attribut contenant le nombre de photos prise durant la campagne

public:
    /**
     * @brief
     * Constructeur de la classe Campagne
     * @param nomCampagne
     * @param lieu
     * @param nomTechnicien
     * @param prenomTechnicien
     * @param date
     * @param parent
     * @param duree
     */
    Campagne(QString nomCampagne, QString lieu, QString nomTechnicien, QString prenomTechnicien, QDateTime date, QObject *parent = nullptr, int duree = 0);
    /**
     * @brief
     * Destructeur de la classe Campagne
     */
    ~Campagne();
    /**
     * @brief
     * Retourne le nom de la campagne
     * @return nom de la campagne sous forme de QString
     */
    QString getNomCampagne() const;
    /**
     * @brief
     * Retourne le nom du technicien
     * @return nom du technicien sous forme de QString
     */
    QString getNomTechnicien() const;
    /**
     * @brief
     * Retourne le prenom du technicien
     * @return prenom du technicien sous forme de QString
     */
    QString getPrenomTechnicien() const;
    /**
     * @brief
     * Retourne le lieu de la campagne
     * @return lieu de la campagne sous forme de QString
     */
    QString getLieu() const;
    /**
     * @brief
     * Retourne la date de la campagne
     * @return date de la campagne sous forme de QDateTime
     */
    QDateTime getDate() const;
    /**
     * @brief
     * Retourne la durée de la campagne
     * @return durée de la campagne sous forme d'un int
     */
    int getDuree() const;
    /**
     * @brief
     * Modifie la duree de la campagne
     * @param duree
     */
    void setDuree(int duree);
    /**
     * @brief
     * Retourne le chemin du dossier de sauvegarde des photos
     * @return chemin du dossier de sauvegarde des photos sous forme d'un QString
     */
    QString getCheminSauvegarde() const;
    /**
     * @brief
     * Modifie le chemin de sauvegarde des photos
     * @param chemin
     */
    void setCheminSauvegarde(QString chemin);
    /**
     * @brief
     * Modifie le nombre de photos prises durant la campagne
     * @param nombre
     */
    void setNombrePhotos(int nombre);
    /**
     * @brief
     * Retourne l'album photo de la campagne
     * @return album photo de la campagne sous forme d'un QVector de photo
     */
    QVector<Photo> getAlbumPhoto() const;
    /**
     * @brief
     * Retourne les mesures de la campagne
     * @return Mesures de la campagne sous forme d'un QVector de Mesure
     */
    QVector<Mesure> getMesures() const;
    /**
     * @brief
     * Ajoute une photo dans l'album photo
     * @param photo
     */
    void ajouterPhoto(Photo &photo);
    /**
     * @brief
     * Modifie l'état d'archive de la photo correspondant au numéro passé en paramètre
     * @param numeroPhoto
     */
    void modifierArchivePhoto(int numeroPhoto);
    /**
     * @brief
     * Ajoute une mesure dans le conteneur de mesure
     * @param mesure
     */
    void ajouterMesure(Mesure &mesure);
    /**
     * @brief
     * Supprime les mesure du conteneur de Mesure, une fois celles-ci archivés dans la BDD
     */
    void supprimerMesures();
    /**
     * @brief
     * Supprime les photo du conteneur de Photo, une fois celles-ci archivés dans la BDD
     */
    void supprimerPhotos();
    /**
     * @brief
     * Incrémente le nombre de photo prises durant la campagne et retourne son nombre
     * @return nombre de photo prise durant la campagne sous forme d'un int
     */
    int incrementeNombrePhoto();

signals:

public slots:
};

#endif // CAMPAGNE_H
