/**
 * @brief
 * Fichier qui contient la déclaration de la classe IHMGraphiques
 * @file ihmgraphiques.h
 */

#ifndef IHMGRAPHIQUES_H
#define IHMGRAPHIQUES_H

#include <QtWidgets>
#include <QtCharts>

#define ESPACE_LISIBILITE "              "

/**
 * @brief
 * Class permettant de visualiser les graphiques des campagnes archivés
 * @class IHMGraphiques IHMGraphiques.h "ihmgraphiques.h"
 */
class IHMGraphiques : public QWidget
{
    Q_OBJECT
private:
    QVector<QStringList> mesures;    //!< Conteneur des mesures de la base de données pour une campagne donnée
    QChartView *graphiqueRadiation;  //!< widget pour afficher le graphe radiation
    QChart *grapheRadiation;         //!< la représentation du graphe radiation
    QLineSeries *courbeRadiation;    //!< Les données de radiation sous forme de courbe
    QLineSeries *doseLimiteRadiation;//!< Le sueil de radiation acceptable

    QChartView *graphiqueHumidite;  //!< widget pour afficher le graphe humidite
    QChart *grapheHumidite;         //!< la représentation du graphe humidite
    QLineSeries *courbeHumidite;    //!< Les données d'humidite sous forme de courbe

    QChartView *graphiqueTemperature;  //!< widget pour afficher le graphe temperature
    QChart *grapheTemperature;         //!< la représentation du graphe temperature
    QLineSeries *courbeTemperature;    //!< Les données de temperature sous forme de courbe

    float valeurMaxRadiation;        //!< La valeur max de la radiation du graphique Radiation
    float valeurMaxTemperature;      //!< La valeur max de la température du graphique Température
    float valeurMaxHumidite;         //!< La valeur max de l'humidité du graphique Humidité

    void initialisationGraphiqueRadiation();
    void initialisationGraphiqueHumidite();
    void initialisationGraphiqueTemperature();
    
public:
    /**
     * @brief
     * Constructeur de la classe IHMGraphiques
     * @param mesures
     * @param parent
     */
    IHMGraphiques(QVector<QStringList> mesures, QWidget *parent = nullptr);

signals:

};

#endif // IHMGRAPHIQUES_H
