/**
 * @brief
 * Fichier qui contient la déclaration de la classe CommunicationRov
 * @file communicationRov.h
 */

#ifndef COMMUNICATIONROV_H
#define COMMUNICATIONROV_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QMessageBox>

#define MODE_CONNECTE
#define CONFIGURATION_MANUELLE

/**
 * @brief
 * structure permettant de configurer une communication
 * @struct Configuration
 */
struct Configuration
{
    QString port;    //!< Attribut définissant le nom d'un port
    int debit;       //!< Attribut définissant la vitesse en bits/s de la communication
    int bitsDonnees; //!< Attribut définissant le nombre de bits de données de la communication
    int bitStop;     //!< Attribut définissant le nombre de bits de stop de la communication
};


/**
 * @brief
 * Class permettant de mettre en place une communication avec le rov
 * @class CommunicationRov communicationRov.h "communicationRov.h"
 */
class CommunicationRov : public QObject
{
    Q_OBJECT
private:
    QSerialPort *port;                  //!< accède a la configuration de la liaison série
    QByteArray donnees;                 //!< Tableau contenant les données bruts envoyé depuis la liason série
    QString trameRecue;                 //!< Derniere trameRecue

public:
    /**
     * @brief
     * constructeur de la classe CommunicationRov
     * @param parent
     */
    CommunicationRov(QObject *parent = nullptr);
    /**
     * @brief
     * Destructeur de la classe CommunicationRov
     */
    ~CommunicationRov();
    /**
     * @brief
     * Permet d'ouvrir le port série virtuel
     */
    bool ouvrirPort();
    /**
     * @brief
     * Permet de fermer le port série virtuel
     */
    void fermerPort();
    /**
     * @brief
     * Affecte a l'objet CommunicationRov une configuration du port série virtuel
     * @param maConfiguration
     */
    void setConfiguration(Configuration maConfiguration);
    /**
     * @brief
     * Emet la trame vers le robot
     * @param trame
     * @return un entier correspondant au nombres d'octets envoyé, retourne -1 si la diffusion à échoué
     */
    int emettreTrame(QString trame);
    /**
     * @brief
     * retourne la liste des ports disponibles
     * @return la liste des ports disponibles
     */
    static QStringList detecterPortsDisponibles();
    /**
     * @brief
     * retourne l'etat du port série
     * @return l'etat du port série
     */
    bool getEtatPort();

signals:
    /**
     * @brief
     * Envoie un signal informant qu'une nouvelle trame est disponible
     * @param trame
     */
    void nouvelleTrame(QString trame);
    /**
     * @brief
     * Envoie un signal informant que l'état du port a été modifié
     * @param etat
     * @param information
     */
    void etatPortModifie(bool etat, QString information);

public slots:
    /**
     * @brief
     * Récupere la trame disponible sur le port à la réception du signal ReadyRead et émet un signal nouvelleTrame
     */
    void recevoir();
    void gererErreur(QSerialPort::SerialPortError);
};

#endif // COMMUNICATIONROV_H
