/**
 * @brief
 * Fichier qui contient la définition de la classe IHMGraphiques
 * @file ihmgraphiques.cpp
 */

#include "ihmgraphiques.h"

IHMGraphiques::IHMGraphiques(QVector<QStringList> mesures, QWidget *parent) : QWidget(parent), mesures(mesures), valeurMaxRadiation(0.0), valeurMaxTemperature(0.0), valeurMaxHumidite(0.0)
{
    QVBoxLayout *layoutPrincipal = new QVBoxLayout;
    QHBoxLayout *layoutGrapheRadiation = new QHBoxLayout;
    QHBoxLayout *layoutGrapheHumidite = new QHBoxLayout;
    QHBoxLayout *layoutGrapheTemperature = new QHBoxLayout;

    initialisationGraphiqueRadiation();
    initialisationGraphiqueHumidite();
    initialisationGraphiqueTemperature();

    resize(640, 480);
    setStyleSheet("background:#202020");

    layoutPrincipal->addLayout(layoutGrapheRadiation);
    layoutPrincipal->addLayout(layoutGrapheHumidite);
    layoutPrincipal->addLayout(layoutGrapheTemperature);
    layoutGrapheRadiation->addWidget(graphiqueRadiation);
    layoutGrapheHumidite->addWidget(graphiqueHumidite);
    layoutGrapheTemperature->addWidget(graphiqueTemperature);
    setLayout(layoutPrincipal);
    showMaximized();
}

void IHMGraphiques::initialisationGraphiqueRadiation()
{
    courbeRadiation = new QLineSeries();
    doseLimiteRadiation = new QLineSeries();

    for(QVector<QStringList>::iterator it = mesures.begin(); it != mesures.end(); it++)
    {
        courbeRadiation->append(QDateTime::fromString((*it).at(0)).toMSecsSinceEpoch(), (*it).at(1).toFloat());
        if((*it).at(1).toFloat() > valeurMaxRadiation)
            valeurMaxRadiation = (*it).at(1).toFloat();
    }

    doseLimiteRadiation->append(QDateTime::fromString(mesures[0].at(0)).toMSecsSinceEpoch(), 0.1);
    doseLimiteRadiation->append(QDateTime::fromString(mesures[mesures.size() - 1].at(0)).toMSecsSinceEpoch(), 0.1);

    courbeRadiation->setName(QString::fromUtf8("<font color=\"#FFFFFF\">Radiation</font>"));
    doseLimiteRadiation->setName(QString::fromUtf8("<font color=\"#FFFFFF\">Dose limite</font>"));
    QPen pen;
    pen.setColor(QColor(Qt::darkGreen));
    pen.setWidth(2);
    courbeRadiation->setPen(pen);
    pen.setColor(QColor(Qt::darkRed));
    pen.setStyle(Qt::DashLine);
    doseLimiteRadiation->setPen(pen);

    grapheRadiation = new QChart();
    grapheRadiation->setBackgroundVisible(false);
    grapheRadiation->addSeries(courbeRadiation);
    grapheRadiation->addSeries(doseLimiteRadiation);
    grapheRadiation->setBackgroundBrush(QColor(0xFFFFFF));

    QDateTimeAxis *axeXRadiation = new QDateTimeAxis;
    axeXRadiation->setTickCount(10);
    axeXRadiation->setFormat("hh:mm:ss");
    axeXRadiation->setTitleText("Heure");
    axeXRadiation->setLabelsColor(0xFFFFFF);
    axeXRadiation->setTitleBrush(QColor(0xFFFFFF));
    axeXRadiation->setMin(QDateTime::fromString(mesures[0].at(0)));
    axeXRadiation->setMax(QDateTime::fromString(mesures[mesures.size()-1].at(0)));
    grapheRadiation->addAxis(axeXRadiation, Qt::AlignBottom);
    courbeRadiation->attachAxis(axeXRadiation);
    doseLimiteRadiation->attachAxis(axeXRadiation);

    QValueAxis *axeYRadiation = new QValueAxis;
    axeYRadiation->setRange(0, int(valeurMaxRadiation) + 0.2);
    axeYRadiation->setLabelFormat("%.2f");
    axeYRadiation->setTitleText(QString::fromUtf8("Radiation en µsV/h"));
    axeYRadiation->setLabelsColor(0xFFFFFF);
    axeYRadiation->setTitleBrush(QColor(0xFFFFFF));
    grapheRadiation->addAxis(axeYRadiation, Qt::AlignLeft);

    doseLimiteRadiation->setPointsVisible(true);
    doseLimiteRadiation->setPointLabelsFormat("@yPoint" ESPACE_LISIBILITE);
    doseLimiteRadiation->setPointLabelsVisible(true);
    doseLimiteRadiation->attachAxis(axeYRadiation);

    courbeRadiation->setPointsVisible(true);
    courbeRadiation->setPointLabelsFormat("@yPoint" ESPACE_LISIBILITE);
    courbeRadiation->setPointLabelsVisible(true);
    courbeRadiation->attachAxis(axeYRadiation);

    courbeRadiation->setPointLabelsColor(0xFFFFFF);
    doseLimiteRadiation->setPointLabelsColor(0xFFFFFF);

    graphiqueRadiation = new QChartView(grapheRadiation);
    graphiqueRadiation->setRenderHint(QPainter::Antialiasing);
}

void IHMGraphiques::initialisationGraphiqueHumidite()
{
    courbeHumidite = new QLineSeries();

    for(QVector<QStringList>::iterator it = mesures.begin(); it != mesures.end(); it++)
    {
        courbeHumidite->append(QDateTime::fromString((*it).at(0)).toMSecsSinceEpoch(), (*it).at(3).toFloat());
        if((*it).at(1).toFloat() > valeurMaxHumidite)
            valeurMaxHumidite = (*it).at(3).toFloat();
    }

    courbeHumidite->setName(QString::fromUtf8("<font color=\"#FFFFFF\">Humidité</font>"));
    QPen pen;
    pen.setColor(QColor(Qt::darkGreen));
    pen.setWidth(2);
    courbeHumidite->setPen(pen);

    grapheHumidite = new QChart();
    grapheHumidite->setBackgroundVisible(false);
    grapheHumidite->addSeries(courbeHumidite);
    grapheHumidite->setBackgroundBrush(QColor(0xFFFFFF));

    QDateTimeAxis *axeXHumidite = new QDateTimeAxis;
    axeXHumidite->setTickCount(10);
    axeXHumidite->setFormat("hh:mm:ss");
    axeXHumidite->setTitleText("Heure");
    axeXHumidite->setLabelsColor(0xFFFFFF);
    axeXHumidite->setTitleBrush(QColor(0xFFFFFF));
    axeXHumidite->setMin(QDateTime::fromString(mesures[0].at(0)));
    axeXHumidite->setMax(QDateTime::fromString(mesures[mesures.size()-1].at(0)));
    grapheHumidite->addAxis(axeXHumidite, Qt::AlignBottom);
    courbeHumidite->attachAxis(axeXHumidite);

    QValueAxis *axeYHumidite = new QValueAxis;
    axeYHumidite->setRange(0, 100);
    axeYHumidite->setLabelFormat("%d");
    axeYHumidite->setTitleText(QString::fromUtf8("Humidité en %"));
    axeYHumidite->setLabelsColor(0xFFFFFF);
    axeYHumidite->setTitleBrush(QColor(0xFFFFFF));
    grapheHumidite->addAxis(axeYHumidite, Qt::AlignLeft);
    courbeHumidite->setPointsVisible(true);
    courbeHumidite->setPointLabelsFormat("@yPoint" ESPACE_LISIBILITE);
    courbeHumidite->setPointLabelsVisible(true);
    courbeHumidite->attachAxis(axeYHumidite);

    courbeHumidite->setPointLabelsColor(0xFFFFFF);

    graphiqueHumidite = new QChartView(grapheHumidite);
    graphiqueHumidite->setRenderHint(QPainter::Antialiasing);
}

void IHMGraphiques::initialisationGraphiqueTemperature()
{
    courbeTemperature = new QLineSeries();

    for(QVector<QStringList>::iterator it = mesures.begin(); it != mesures.end(); it++)
    {
        courbeTemperature->append(QDateTime::fromString((*it).at(0)).toMSecsSinceEpoch(), (*it).at(2).toFloat());
        if((*it).at(2).toFloat() > valeurMaxTemperature)
            valeurMaxTemperature = (*it).at(2).toFloat();
    }

    courbeTemperature->setName(QString::fromUtf8("<font color=\"#FFFFFF\">Température</font>"));
    QPen pen;
    pen.setColor(QColor(Qt::darkGreen));
    pen.setWidth(2);
    courbeTemperature->setPen(pen);

    grapheTemperature = new QChart();
    grapheTemperature->setBackgroundVisible(false);
    grapheTemperature->addSeries(courbeTemperature);
    grapheTemperature->setBackgroundBrush(QColor(0xFFFFFF));

    QDateTimeAxis *axeXTemperature = new QDateTimeAxis;
    axeXTemperature->setTickCount(10);
    axeXTemperature->setFormat("hh:mm:ss");
    axeXTemperature->setTitleText("Heure");
    axeXTemperature->setLabelsColor(0xFFFFFF);
    axeXTemperature->setTitleBrush(QColor(0xFFFFFF));
    axeXTemperature->setMin(QDateTime::fromString(mesures[0].at(0)));
    axeXTemperature->setMax(QDateTime::fromString(mesures[mesures.size()-1].at(0)));
    grapheTemperature->addAxis(axeXTemperature, Qt::AlignBottom);
    courbeTemperature->attachAxis(axeXTemperature);

    QValueAxis *axeYTemperature = new QValueAxis;
    axeYTemperature->setRange(0, int(valeurMaxTemperature) + 5);
    axeYTemperature->setLabelFormat("%.1f");
    axeYTemperature->setTitleText(QString::fromUtf8("Temperature en °C"));
    axeYTemperature->setLabelsColor(0xFFFFFF);
    axeYTemperature->setTitleBrush(QColor(0xFFFFFF));
    grapheTemperature->addAxis(axeYTemperature, Qt::AlignLeft);
    courbeTemperature->setPointsVisible(true);
    courbeTemperature->setPointLabelsFormat("@yPoint" ESPACE_LISIBILITE);
    courbeTemperature->setPointLabelsVisible(true);
    courbeTemperature->attachAxis(axeYTemperature);

    courbeTemperature->setPointLabelsColor(0xFFFFFF);

    graphiqueTemperature = new QChartView(grapheTemperature);
    graphiqueTemperature->setRenderHint(QPainter::Antialiasing);
}
