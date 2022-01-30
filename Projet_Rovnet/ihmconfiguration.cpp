/**
 * @brief
 * Fichier qui contient la définition de la classe IHMConfiguration
 * @file ihmconfiguration.cpp
 */

#include "ihmconfiguration.h"

IHMConfiguration::IHMConfiguration(Rov *rov, QWidget *parent) : QWidget(parent), rov(rov)
{
    qDebug() << Q_FUNC_INFO;

    initialiserWidgets();
    configurerWidgets();
    initialiserLayouts();
    initialiserEvenements();

    modifierConfiguration();
    rov->getCommunicationRov()->ouvrirPort();
    modifieEtatBoutons();
}

IHMConfiguration::~IHMConfiguration()
{
    qDebug() << Q_FUNC_INFO;
}

void IHMConfiguration::initialiserWidgets()
{
    listePortsDisponibles = new QComboBox(this);
    listeDebit = new QComboBox(this);
    listeBitsDonnees = new QComboBox(this);
    listeBitsStop = new QComboBox(this);
    boutonGererPort = new QPushButton("Fermer", this);
}

void IHMConfiguration::configurerWidgets()
{
    listePortsDisponibles->addItems(CommunicationRov::detecterPortsDisponibles());
    if(listePortsDisponibles->currentText() == "")
        listePortsDisponibles->addItem("Aucun port détécté");
    listeDebit->addItem("9600");
    listeDebit->addItem("115200");

    listeBitsDonnees->addItem("7");
    listeBitsDonnees->addItem("8");
    listeBitsDonnees->setCurrentIndex(1);

    listeBitsStop->addItem("1");
    listeBitsStop->addItem("2");
}

void IHMConfiguration::initialiserLayouts()
{
    QVBoxLayout *layoutPrincipal = new QVBoxLayout;
    QHBoxLayout *layoutInformation = new QHBoxLayout;
    QFormLayout *layoutConfiguration = new QFormLayout;
    QVBoxLayout *layoutCommande = new QVBoxLayout;

    layoutCommande->setAlignment(Qt::AlignTop);

    layoutPrincipal->addLayout(layoutInformation);
    layoutInformation->addLayout(layoutConfiguration);
    layoutInformation->addLayout(layoutCommande);
    layoutConfiguration->addRow("Port:", listePortsDisponibles);
    layoutConfiguration->addRow("Débit:", listeDebit);
    layoutConfiguration->addRow("Bits de données:", listeBitsDonnees);
    layoutConfiguration->addRow("Bits de stop:", listeBitsStop);
    layoutCommande->addWidget(boutonGererPort);

    setLayout(layoutPrincipal);
    setStyleSheet("background:#202020;color:white;");
}

void IHMConfiguration::initialiserEvenements()
{
    connect(listePortsDisponibles, SIGNAL(currentIndexChanged(int)), this, SLOT(modifierConfiguration()));
    connect(listeDebit, SIGNAL(currentIndexChanged(int)), this, SLOT(modifierConfiguration()));
    connect(listeBitsDonnees, SIGNAL(currentIndexChanged(int)), this, SLOT(modifierConfiguration()));
    connect(listeBitsStop, SIGNAL(currentIndexChanged(int)), this, SLOT(modifierConfiguration()));
    connect(boutonGererPort, SIGNAL(clicked()), this, SLOT(modifierEtatPort()));
}

void IHMConfiguration::modifieEtatBoutons()
{
    if(rov->getCommunicationRov()->getEtatPort())
    {
        listePortsDisponibles->setDisabled(true);
        listeDebit->setDisabled(true);
        listeBitsDonnees->setDisabled(true);
        listeBitsStop->setDisabled(true);
    }
    else
    {
        boutonGererPort->setText("Ouvrir");
        listePortsDisponibles->setEnabled(true);
        listeDebit->setEnabled(true);
        listeBitsDonnees->setEnabled(true);
        listeBitsStop->setEnabled(true);
    }
}

void IHMConfiguration::modifierConfiguration()
{
    Configuration configuration;

    configuration.port = listePortsDisponibles->currentText();
    configuration.debit = listeDebit->currentText().toInt();
    configuration.bitsDonnees = listeBitsDonnees->currentText().toInt();
    configuration.bitStop = listeBitsStop->currentText().toInt();

    rov->modifierConfiguration(configuration);
}

void IHMConfiguration::modifierEtatPort()
{
    if(boutonGererPort->text() == "Ouvrir")
    {
        if(rov->getCommunicationRov()->ouvrirPort())
        {
            boutonGererPort->setText("Fermer");
            listePortsDisponibles->setDisabled(true);
            listeDebit->setDisabled(true);
            listeBitsDonnees->setDisabled(true);
            listeBitsStop->setDisabled(true);
        }
    }
    else
    {
        rov->getCommunicationRov()->fermerPort();
        boutonGererPort->setText("Ouvrir");
        listePortsDisponibles->setEnabled(true);
        listeDebit->setEnabled(true);
        listeBitsDonnees->setEnabled(true);
        listeBitsStop->setEnabled(true);
    }
}

void IHMConfiguration::actualisePortsDisponibles()
{
    listePortsDisponibles->clear();
    listePortsDisponibles->addItems(CommunicationRov::detecterPortsDisponibles());
    if(listePortsDisponibles->currentText() == "")
        listePortsDisponibles->addItem("Aucun port détécté");
}
