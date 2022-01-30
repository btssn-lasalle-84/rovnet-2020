/**
 * @brief
 * Fichier qui contient la définition de la classe Campagne
 * @file campagne.cpp
 */

#include "campagne.h"

Campagne::Campagne(QString nomCampagne, QString lieu, QString nomTechnicien, QString prenomTechnicien, QDateTime date, QObject *parent, int duree) : QObject (parent), nomCampagne(nomCampagne), nomTechnicien(nomTechnicien), prenomTechnicien(prenomTechnicien), lieu(lieu), date(date), duree(duree), estArchive(false), albumPhoto(), mesures(), nombrePhotos(0)
{
    qDebug() << Q_FUNC_INFO;
}

Campagne::~Campagne()
{
    qDebug() << Q_FUNC_INFO;
}

QString Campagne::getNomCampagne() const
{
    return nomCampagne;
}

QString Campagne::getNomTechnicien() const
{
    return nomTechnicien;
}

QString Campagne::getPrenomTechnicien() const
{
    return prenomTechnicien;
}

QString Campagne::getLieu() const
{
    return lieu;
}

QDateTime Campagne::getDate() const
{
    return date;
}

int Campagne::getDuree() const
{
    return duree;
}

void Campagne::setDuree(int duree)
{
    this->duree = this->duree + duree;
}


QString Campagne::getCheminSauvegarde() const
{
    return cheminSauvegardePhotos;
}

void Campagne::setCheminSauvegarde(QString chemin)
{
    cheminSauvegardePhotos = chemin;
}

void Campagne::setNombrePhotos(int nombre)
{
    nombrePhotos = nombre;
}

QVector<Photo> Campagne::getAlbumPhoto() const
{
    return albumPhoto;
}

QVector<Mesure> Campagne::getMesures() const
{
    return mesures;
}

void Campagne::ajouterPhoto(Photo &photo)
{
    albumPhoto.push_back(photo);
}

void Campagne::modifierArchivePhoto(int numeroPhoto)
{
    albumPhoto[numeroPhoto].aGarder = !(albumPhoto[numeroPhoto].aGarder);
}

void Campagne::ajouterMesure(Mesure &mesure)
{
    mesures.push_back(mesure);
}

void Campagne::supprimerMesures()
{
    mesures.clear();
}

void Campagne::supprimerPhotos()
{
    albumPhoto.clear();
}

int Campagne::incrementeNombrePhoto()
{
    nombrePhotos++;
    return nombrePhotos;
}
