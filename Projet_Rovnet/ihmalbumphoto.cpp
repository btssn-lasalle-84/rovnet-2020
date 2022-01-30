/**
 * @brief
 * Fichier qui contient la définition de la classe IHMAlbumPhoto
 * @file ihmalbumphoto.cpp
 */

#include "ihmalbumphoto.h"
#include "ihmrov.h"
#include "campagne.h"

IHMAlbumPhoto::IHMAlbumPhoto(IHMRov *ihmRov, QWidget *parent) : QWidget(parent), imhRov(ihmRov)
{
    qDebug() << Q_FUNC_INFO;
    photos = new QWidget();
    layoutPhotos = new QHBoxLayout;
    layoutAlbumPhoto = new QVBoxLayout;
    scrollArea = new QScrollArea();

    layoutPhotos->setAlignment(Qt::AlignCenter);
    layoutAlbumPhoto->setAlignment(Qt::AlignCenter);

    photos->setLayout(layoutAlbumPhoto);
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameStyle(QFrame::Panel);
    scrollArea->setWidget(photos);
    layoutPhotos->addWidget(scrollArea);

    setLayout(layoutPhotos);

    int width = qApp->desktop()->availableGeometry().width();
    int height = qApp->desktop()->availableGeometry().height();
    resize(width, height);
    setStyleSheet("background:#202020;color:white;");
}

IHMAlbumPhoto::~IHMAlbumPhoto()
{
    qDebug() << Q_FUNC_INFO;
}

void IHMAlbumPhoto::ouvrirAlbumPhotos(QVector<Photo> albumPhoto)
{
    if(albumPhoto.isEmpty())
    {
        QMessageBox::critical(this, "Erreur", "Listes photos vide !");
        return;
    }

    QFont police("", 15, 50, false);

    this->albumPhoto = albumPhoto;
    signalMapper = new QSignalMapper(this);
    int numeroPhoto = 0;
    for(QVector<Photo>::iterator it = albumPhoto.begin(); it != albumPhoto.end(); ++it, numeroPhoto++)
    {
        QVBoxLayout *layoutPhoto = new QVBoxLayout;
        QHBoxLayout *layoutInformationsPhotos = new QHBoxLayout;
        QHBoxLayout *layoutPhotoAGArder = new QHBoxLayout;

        QLabel *photo = new QLabel(this);
        photo->setPixmap((*it).image);

        QLabel *dateHeure = new QLabel((*it).dateheure.toString(), this);
        QLabel *chemin = new QLabel((*it).cheminSauvegarde,this);
        QCheckBox *photoGarde = new QCheckBox(this);
        QWidget *information = new QWidget(this);
        QLabel *photoAGarder = new QLabel("Photo à garder :", this);

        layoutPhotoAGArder->setAlignment(Qt::AlignRight);
        information->setFixedWidth((*it).image.width());

        if(albumPhoto[numeroPhoto].aGarder)
            photoGarde->setChecked(true);
        else
            photoGarde->setChecked(false);

        connect(photoGarde, SIGNAL(clicked()), signalMapper, SLOT(map()));
        signalMapper->setMapping(photoGarde, numeroPhoto);

        layoutAlbumPhoto->addLayout(layoutPhoto);
        layoutPhoto->addWidget(information);
        information->setLayout(layoutInformationsPhotos);
        layoutPhoto->addWidget(photo);
        layoutInformationsPhotos->addWidget(dateHeure);
        layoutInformationsPhotos->addWidget(chemin);
        layoutInformationsPhotos->addLayout(layoutPhotoAGArder);
        layoutPhotoAGArder->addWidget(photoAGarder);
        layoutPhotoAGArder->addWidget(photoGarde);

        dateHeure->setFont(police);
        chemin->setFont(police);
        photoAGarder->setFont(police);
        information->setStyleSheet("background-color: white");
        dateHeure->setStyleSheet("color: black");
        chemin->setStyleSheet("color: black");
        photoAGarder->setStyleSheet("color: black");
        photoGarde->setStyleSheet("color: black");
    }
    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(selectionnerPhoto(int)));

    this->show();
}

void IHMAlbumPhoto::selectionnerPhoto(int numeroPhoto)
{
    if(numeroPhoto < albumPhoto.size())
    {
        imhRov->getCampagne()->modifierArchivePhoto(numeroPhoto);
        qDebug() << Q_FUNC_INFO << "numeroPhoto" << numeroPhoto << "A garder" << imhRov->getCampagne()->getAlbumPhoto()[numeroPhoto].aGarder;
    }
}
