/**
 * @brief
 * Fichier qui contient la déclaration de la classe Capteurs
 * @file capteurs.h
 */

#ifndef CAPTEURS_H
#define CAPTEURS_H

#include <QObject>
#include <QDebug>

/**
 * @brief
 * Classe contenant les dernières informations issues des capteurs du rov
 * @class Capteurs capteurs.h "capteurs.h"
 */
class Capteurs : public QObject
{
    Q_OBJECT
private:
    QString telemetrie;     //!< Dernière données télémétriques
    QString angle;          //!< Dernière données capteurs de distance
    QString temperature;    //!< Dernière données de température
    QString humidite;       //!< Dernière données de température
    QString radiation;      //!< Dernière données de radiation

public:
    /**
     * @brief
     * Constructeur de la classe Capteurs
     * @param parent
     */
    Capteurs(QObject *parent = nullptr);
    /**
     * @brief
     * Destructeur de la classe Capteurs
     */
    ~Capteurs();
    /**
     * @brief
     * Modifie la dernière information issue du capteur télémétrique
     * @param telemetrie
     */
    void setTelemetrie(QString telemetrie);
    /**
     * @brief
     * Modifie la dernière information issue du capteur de température
     * @param temperature
     */
    void setTemperature(QString temperature);
    /**
     * @brief
     * Modifie la dernière information issue du capteur de humidité
     * @param humidite
     */
    void setHumidite(QString humidite);
    /**
     * @brief
     * Modifie la dernière information issue du capteur de radiation
     * @param radiation
     */
    void setRadiation(QString radiation);
    /**
     * @brief
     * Modifie la dernière information issue du capteur de distance
     * @param angle
     */
    void setAngle(QString angle);
    /**
     * @brief
     * Récupère la dernière information issue du capteur télémétrique
     * @return la dernière information issue du capteur télémétrique
     */
    QString getTelemetrie() const;
    /**
     * @brief
     * Récupère la dernière information issue du capteur de température
     * @return la dernière information issue du capteur de température
     */
    QString getTemperature() const;
    /**
     * @brief
     * Récupère la dernière information issue du capteur de humidité
     * @return la dernière information issue du capteur de humidité
     */
    QString getHumidite() const;
    /**
     * @brief
     * Récupère la dernière information issue du capteur de radiation
     * @return la dernière information issue du capteur de radiation
     */
    QString getRadiation() const;
    /**
     * @brief
     * Récupère la dernière information issue du capteur de distance
     * @return la dernière information issue du capteur de distance
     */
    QString getAngle() const;

signals:

public slots:
};

#endif // CAPTEURS_H
