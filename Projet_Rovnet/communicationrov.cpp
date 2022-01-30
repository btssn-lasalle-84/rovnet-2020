    /**
 * @brief
 * Fichier qui contient la définition de la classe CommunicationRov
 * @file communicationRov.cpp
 */

#include "communicationrov.h"

CommunicationRov::CommunicationRov(QObject *parent) : QObject(parent)
{
    qDebug() << Q_FUNC_INFO;
    port = new QSerialPort(this);

    connect(port, SIGNAL(errorOccurred(QSerialPort::SerialPortError)), this, SLOT(gererErreur(QSerialPort::SerialPortError)));
}

CommunicationRov::~CommunicationRov()
{
    if(port->isOpen())
        port->close();
    qDebug() << Q_FUNC_INFO;
}

bool CommunicationRov::ouvrirPort()
{
    if(port->open(QIODevice::ReadWrite))
    {
        qDebug() << Q_FUNC_INFO << "Port ouvert" << port->isOpen();
        if(port->isOpen())
        {
            emit etatPortModifie(true, port->portName());
            connect(port, SIGNAL(readyRead()), this, SLOT(recevoir()));
            return true;
        }
        else
            return false;
    }
    #ifdef MODE_CONNECTE
    else
    {
        if(!port->isOpen())
        {
            QMessageBox::critical(nullptr, "Communication rov", QString::fromUtf8("Erreur ouverture du port série !"));
            return false;
        }
    }
    #endif
}

void CommunicationRov::fermerPort()
{
    port->close();
    disconnect(port, SIGNAL(readyRead()), this, SLOT(recevoir()));
    qDebug() << Q_FUNC_INFO << "Port fermé" << !port->isOpen();
    emit etatPortModifie(false, port->portName());
}

void CommunicationRov::setConfiguration(Configuration maConfiguration)
{
    port->setPortName(maConfiguration.port);
    port->setBaudRate(maConfiguration.debit);
    port->setDataBits((QSerialPort::DataBits)maConfiguration.bitsDonnees);
    port->setStopBits((QSerialPort::StopBits)maConfiguration.bitStop);
    port->setParity(QSerialPort::NoParity);
    port->setFlowControl(QSerialPort::NoFlowControl);
}

int CommunicationRov::emettreTrame(QString trame)
{
    int nombresOctets = -1;

    if (port == NULL || !port->isOpen())
    {
       return -1;
    }

    nombresOctets = port->write(trame.toLatin1());
    return nombresOctets;
}

void CommunicationRov::recevoir()
{
    while(port->bytesAvailable())
    {
        donnees += port->readAll();
        //qDebug() << Q_FUNC_INFO << "bytesAvailable" << port->bytesAvailable() << "donnees" << donnees;
    }

    if(donnees.startsWith("$") && donnees.endsWith("\r\n"))
    {
        trameRecue = QString(donnees.data());
        //qDebug() << Q_FUNC_INFO << "trameRecue" << trameRecue;
        emit nouvelleTrame(trameRecue);
        donnees.clear();
    }
}

QStringList CommunicationRov::detecterPortsDisponibles()
{
    QStringList listePortsDetectes;

    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        listePortsDetectes.push_back(info.portName());
    }

    return listePortsDetectes;
}

bool CommunicationRov::getEtatPort()
{
    return port->isOpen();
}

void CommunicationRov::gererErreur(QSerialPort::SerialPortError erreur)
{
    switch(erreur)
    {
        case QSerialPort::ResourceError : fermerPort();
            break;
    }
}

