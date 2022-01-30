/**
 * @brief
 * Fichier qui contient la définition de la classe Capteurs
 * @file capteurs.cpp
 */

#include "capteurs.h"

Capteurs::Capteurs(QObject *parent) : QObject(parent), telemetrie("--,--"), angle(""), temperature("--,--"), humidite("--,--"), radiation("--,--")
{
    qDebug() << Q_FUNC_INFO;
}

Capteurs::~Capteurs()
{
    qDebug() << Q_FUNC_INFO;
}

void Capteurs::setTelemetrie(QString telemetrie)
{
    this->telemetrie = telemetrie;
}

void Capteurs::setTemperature(QString temperature)
{
    this->temperature = temperature;
}

void Capteurs::setHumidite(QString humidite)
{
    this->humidite = humidite;
}

void Capteurs::setRadiation(QString radiation)
{
    this->radiation = radiation;
}

void Capteurs::setAngle(QString angle)
{
    this->angle = angle;
}

QString Capteurs::getAngle() const
{
    return angle;
}

QString Capteurs::getTelemetrie() const
{
    return telemetrie;
}

QString Capteurs::getTemperature() const
{
    return temperature;
}

QString Capteurs::getHumidite() const
{
    return humidite;
}

QString Capteurs::getRadiation() const
{
    return radiation;
}

