/**
* @brief
* Fichier qui contient la définition de la classe BaseDeDonnees
* @file basededonnees.cpp
*/

#include "basededonnees.h"
#include <QDebug>
#include <QMessageBox>

BaseDeDonnees* BaseDeDonnees::baseDeDonnees = nullptr;
QString BaseDeDonnees::typeBase = "QSQLITE";
int BaseDeDonnees::nbAcces = 0;

BaseDeDonnees::BaseDeDonnees(QString type)
{
    #ifdef DEBUG_BASEDEDONNEES
    qDebug() << Q_FUNC_INFO << type;
    #endif
    db = QSqlDatabase::addDatabase(type);
    typeBase = type;
}

BaseDeDonnees::~BaseDeDonnees()
{
    #ifdef DEBUG_BASEDEDONNEES
    qDebug() << Q_FUNC_INFO;
    #endif
}

BaseDeDonnees* BaseDeDonnees::getInstance(QString type)
{
    if(baseDeDonnees == nullptr)
        baseDeDonnees = new BaseDeDonnees(type);

    nbAcces++;
    #ifdef DEBUG_BASEDEDONNEES
    qDebug() << Q_FUNC_INFO << "nbAcces" << nbAcces;
    #endif

    return baseDeDonnees;
}

void BaseDeDonnees::detruireInstance()
{
    if(baseDeDonnees != nullptr)
    {
        if(nbAcces > 0)
            nbAcces--;

        #ifdef DEBUG_BASEDEDONNEES
        qDebug() << Q_FUNC_INFO << "nbAcces restants" << nbAcces;
        #endif

        if(nbAcces == 0)
        {
            delete baseDeDonnees;
            baseDeDonnees = nullptr;
        }
    }
}

bool BaseDeDonnees::ouvrir(QString fichierBase)
{
    if(typeBase != "QSQLITE")
        return false;
    QMutexLocker verrou(&mutex);
    if(!db.isOpen())
    {
       db.setDatabaseName(fichierBase);

       #ifdef DEBUG_BASEDEDONNEES
       qDebug() << Q_FUNC_INFO << db.databaseName();
        #endif

       if(db.open())
       {

           #ifdef DEBUG_BASEDEDONNEES
           qDebug() << Q_FUNC_INFO << QString::fromUtf8("Ouverture réussie à %1").arg(db.databaseName());
           #endif

           return true;
       }
       else
       {
           #ifdef DEBUG_BASEDEDONNEES
           qDebug() << Q_FUNC_INFO << QString::fromUtf8("Erreur : impossible d'ouvrir la base de données !");
           #endif
           QMessageBox::critical(nullptr, QString::fromUtf8("BaseDeDonnees"), QString::fromUtf8("Impossible d'ouvrir la base de données !"));
           return false;
       }
    }
    else
        return true;
}

bool BaseDeDonnees::estOuvert()
{
    QMutexLocker verrou(&mutex);
    return db.isOpen();
}

bool BaseDeDonnees::executer(QString requete)
{
    QMutexLocker verrou(&mutex);
    QSqlQuery r;
    bool retour;

    if(db.isOpen())
    {
        if(requete.contains("UPDATE") || requete.contains("INSERT") || requete.contains("DELETE"))
        {
            retour = r.exec(requete);
            #ifdef DEBUG_BASEDEDONNEES
            qDebug() << Q_FUNC_INFO << QString::fromUtf8("Retour %1 pour la requete : %2").arg(QString::number(retour)).arg(requete);
            #endif
            if(retour)
            {
                return true;
            }
            else
            {
                qDebug() << Q_FUNC_INFO << QString::fromUtf8("Erreur : %1 pour la requête %2").arg(r.lastError().text()).arg(requete);
                return false;
            }
        }
        else
        {
            qDebug() << Q_FUNC_INFO << QString::fromUtf8("Erreur : requête %1 non autorisée !").arg(requete);
            return false;
        }
    }
    else
        return false;

}

bool BaseDeDonnees::recuperer(QString requete, QString &donnees)
{
    QMutexLocker verrou(&mutex);
    QSqlQuery r;
    bool retour;

    if(db.isOpen())
    {
        if(requete.contains("SELECT"))
        {
            retour = r.exec(requete);
            #ifdef DEBUG_BASEDEDONNEES
            qDebug() << Q_FUNC_INFO << QString::fromUtf8("Retour %1 pour la requete : %2").arg(QString::number(retour)).arg(requete);
            #endif
            if(retour)
            {
                r.first();

                if(!r.isValid())
                {
                    #ifdef DEBUG_BASEDEDONNEES
                    qDebug() << Q_FUNC_INFO << QString::fromUtf8("Résultat non valide !");
                    #endif
                    return false;
                }

                if(r.isNull(0))
                {
                    #ifdef DEBUG_BASEDEDONNEES
                    qDebug() << Q_FUNC_INFO << QString::fromUtf8("Aucun résultat !");
                    #endif
                    return false;
                }
                donnees = r.value(0).toString();
                #ifdef DEBUG_BASEDEDONNEES
                qDebug() << Q_FUNC_INFO << "Enregistrement -> " << donnees;
                #endif
                return true;
            }
            else
            {
                qDebug() << Q_FUNC_INFO << QString::fromUtf8("Erreur : %1 pour la requête %2").arg(r.lastError().text()).arg(requete);
                return false;
            }
        }
        else
        {
            qDebug() << Q_FUNC_INFO << QString::fromUtf8("Erreur : requête %1 non autorisée !").arg(requete);
            return false;
        }
    }
    else
        return false;
}

bool BaseDeDonnees::recuperer(QString requete, QStringList &donnees)
{
    QMutexLocker verrou(&mutex);
    QSqlQuery r;
    bool retour;

    if(db.isOpen())
    {
        if(requete.contains("SELECT"))
        {
            retour = r.exec(requete);
            #ifdef DEBUG_BASEDEDONNEES
            qDebug() << QString::fromUtf8("<BaseDeDonnees::recuperer(QString, QStringList)> retour %1 pour la requete : %2").arg(QString::number(retour)).arg(requete);
            #endif
            if(retour)
            {
                r.first();

                if(!r.isValid())
                {
                    #ifdef DEBUG_BASEDEDONNEES
                    qDebug() << Q_FUNC_INFO << QString::fromUtf8("Résultat non valide !");
                    #endif
                    return false;
                }

                for(int i=0;i<r.record().count();i++)
                    if(!r.isNull(i))
                        donnees << r.value(i).toString();
                #ifdef DEBUG_BASEDEDONNEES
                qDebug() << Q_FUNC_INFO << "Enregistrement -> " << donnees;
                #endif
                return true;
            }
            else
            {
                qDebug() << Q_FUNC_INFO << QString::fromUtf8("Erreur : %1 pour la requête %2").arg(r.lastError().text()).arg(requete);
                return false;
            }
        }
        else
        {
            qDebug() << Q_FUNC_INFO << QString::fromUtf8("Erreur : requête %1 non autorisée !").arg(requete);
            return false;
        }
    }
    else
        return false;
}

bool BaseDeDonnees::recuperer(QString requete, QVector<QString> &donnees)
{
    QMutexLocker verrou(&mutex);
    QSqlQuery r;
    bool retour;
    QString data;

    if(db.isOpen())
    {
        if(requete.contains("SELECT"))
        {
            retour = r.exec(requete);
            #ifdef DEBUG_BASEDEDONNEES
            qDebug() << Q_FUNC_INFO << QString::fromUtf8("Retour %1 pour la requete : %2").arg(QString::number(retour)).arg(requete);
            #endif
            if(retour)
            {
                while ( r.next() )
                {
                    data = r.value(0).toString();

                    #ifdef DEBUG_BASEDEDONNEES
                    qDebug() << Q_FUNC_INFO << "Enregistrement -> " << data;
                    #endif

                    donnees.push_back(data);
                }
                #ifdef DEBUG_BASEDEDONNEES
                qDebug() << Q_FUNC_INFO << "Enregistrement -> " << donnees;
                #endif
                return true;
            }
            else
            {
                qDebug() << Q_FUNC_INFO << QString::fromUtf8("Erreur : %1 pour la requête %2").arg(r.lastError().text()).arg(requete);
                return false;
            }
        }
        else
        {
            qDebug() << Q_FUNC_INFO << QString::fromUtf8("Erreur : requête %1 non autorisée !").arg(requete);
            return false;
        }
    }
    else
        return false;
}

bool BaseDeDonnees::recuperer(QString requete, QVector<QStringList> &donnees)
{
    QMutexLocker verrou(&mutex);
    QSqlQuery r;
    bool retour;
    QStringList data;

    if(db.isOpen())
    {
        if(requete.contains("SELECT"))
        {
            retour = r.exec(requete);
            #ifdef DEBUG_BASEDEDONNEES
            qDebug() << Q_FUNC_INFO << QString::fromUtf8("Retour %1 pour la requete : %2").arg(QString::number(retour)).arg(requete);
            #endif
            if(retour)
            {
                while ( r.next() )
                {
                    for(int i=0;i<r.record().count();i++)
                        data << r.value(i).toString();

                    #ifdef DEBUG_BASEDEDONNEES
                    qDebug() << Q_FUNC_INFO << "Enregistrement -> " << data;
                    for(int i=0;i<r.record().count();i++)
                        qDebug() << r.value(i).toString();
                    #endif

                    donnees.push_back(data);

                    data.clear();
                }
                #ifdef DEBUG_BASEDEDONNEES
                qDebug() << Q_FUNC_INFO << "Enregistrement -> " << donnees;
                #endif
                return true;
            }
            else
            {
                qDebug() << Q_FUNC_INFO << QString::fromUtf8("Erreur : %1 pour la requête %2").arg(r.lastError().text()).arg(requete);
                return false;
            }
        }
        else
        {
            qDebug() << Q_FUNC_INFO << QString::fromUtf8("Erreur : requête %1 non autorisée !").arg(requete);
            return false;
        }
    }
    else
        return false;
}
