/**
 * @brief
 * Fichier qui contient la déclaration de la classe IHMAlbumPhoto
 * @file ihmalbumphoto.h
 */

#ifndef ALBUMPHOTO_H
#define ALBUMPHOTO_H

#include <QtWidgets>
#include <QVector>

#define NOM_FENETRE_ALBUMPHOTO "Projet Rovnet 2020"

/**
 * @brief
 * structure contenant les informations d'une photo de campagne
 * @struct Photo
 */
struct Photo
{
    QPixmap image;            //!< Image de la photo
    QDateTime dateheure;      //!< Date/Heure de la photo
    bool aGarder;             //!< Booléen afin de savoir si la photo sera archivé ou non
    QString cheminSauvegarde; //!< Chemin de sauvegarde de la photo
};

class IHMRov;

/**
 * @brief
 * Class permettant de visualiser les photos en cours de campagne
 * @class IHMAlbumPhoto ihmAlbumphoto.h "ihmAlbumphoto.h"
 */
class IHMAlbumPhoto : public QWidget
{
    Q_OBJECT
private:
    QWidget *photos;                  //!< Emplacement permettant d'accueillir les différentes photos
    QHBoxLayout *layoutPhotos;        //!< Layout permettant d'accueillir les différentes photos
    QVBoxLayout *layoutAlbumPhoto;    //!< Layout s'agrandissant selon l'ajout de nouvelle photos
    QScrollArea *scrollArea;          //!< Permet une defilement pour visualiser l'ensemble des photos prises durant la campagne
    QSignalMapper *signalMapper;      //!< Objet de type QSignalMapper, permet d'associer chaque photo de l'IHMAlbumPhoto à un signal
    QVector<Photo> albumPhoto;        //!< Conteneur de photo
    IHMRov *imhRov;                   //!< Association avec l'IHMRov

public:
    /**
     * @brief
     * Constructeur de la classe AlbumPhoto
     * @param ihmRov
     * @param parent
     */
    IHMAlbumPhoto(IHMRov *ihmRov, QWidget *parent = nullptr);
    /**
     * @brief
     * Destructeur de la classe AlbumPhoto
     */
    ~IHMAlbumPhoto();
    /**
     * @brief
     * Ouvre une nouvelle fenetre contenant la liste des photos prises en cours de mission
     */
    void ouvrirAlbumPhotos(QVector<Photo> albumPhoto);

signals:

public slots:
    /**
     * @brief
     * Permet de selectionner la photo indiquer par le signalMapper
     * @param numero
     */
    void selectionnerPhoto(int numero);
};

#endif // ALBUMPHOTO_H
