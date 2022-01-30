/**
 * @brief
 * Fichier qui contient la définition de la classe IHMCreationCampagne
 * @file ihmcreationcampagne.cpp
 */

#include "ihmcreationcampagne.h"
#include "campagne.h"
#include "ihmaccueil.h"

IHMCreationCampagne::IHMCreationCampagne(IHMAccueil *ihmAccueil, QVector<QStringList> &listeTechniciens) : QDialog(ihmAccueil, Qt::Dialog), ihmAccueil(ihmAccueil), listeTechniciens(listeTechniciens)
{
    qDebug() << Q_FUNC_INFO;

    initialisationWidgets();
    initialisationDesignWidgets();
    initialiserEvenements();
    initialiserLayouts();
    configurerWidgets();
    chargerListeTechniciens();
}

IHMCreationCampagne::~IHMCreationCampagne()
{
    qDebug() << Q_FUNC_INFO;
}

void IHMCreationCampagne::initialisationWidgets()
{
    nomCampagne = new QLineEdit(this);
    nomTechnicien = new QLineEdit(this);
    prenomTechnicien = new QLineEdit(this);
    lieu = new QLineEdit(this);
    cheminSauvegarde = new QLineEdit(this);
    boutonValider = new QPushButton("Valider", this);
    boutonAnnuler = new QPushButton("Annuler", this);
    boutonChoixChemin = new QPushButton("...", this);
    techniciens = new QComboBox(this);
}

void IHMCreationCampagne::initialisationDesignWidgets()
{
    QFont policeBouton("", 13, 75, false);
    QFont policeText("", 13, 0, false);

    nomCampagne->setFixedSize(194,30);
    nomCampagne->setFont(policeText);
    nomCampagne->setStyleSheet("QLineEdit {border-image: url(design/QLine_194x30.png)}" "QLineEdit:hover {border-image: url(design/QLine_194x30_survole.png)}");

    nomTechnicien->setFixedSize(194,30);
    nomTechnicien->setFont(policeText);
    nomTechnicien->setStyleSheet("QLineEdit {border-image: url(design/QLine_194x30.png)}" "QLineEdit:hover {border-image: url(design/QLine_194x30_survole.png)}" "QLineEdit:disable {border-image: url(design/QLine_194x30_grise.png)}");

    prenomTechnicien->setFixedSize(194,30);
    prenomTechnicien->setFont(policeText);
    prenomTechnicien->setStyleSheet("QLineEdit {border-image: url(design/QLine_194x30.png)}" "QLineEdit:hover {border-image: url(design/QLine_194x30_survole.png)}");

    lieu->setFixedSize(194,30);
    lieu->setFont(policeText);
    lieu->setStyleSheet("QLineEdit {border-image: url(design/QLine_194x30.png)}" "QLineEdit:hover {border-image: url(design/QLine_194x30_survole.png)}");

    cheminSauvegarde->setFixedSize(108,30);
    cheminSauvegarde->setFont(policeText);
    cheminSauvegarde->setStyleSheet("QLineEdit {border-image: url(design/QLine_108x30.png)}" "QLineEdit:hover {border-image: url(design/QLine_108x30_survole.png)}" );

    boutonValider->setFixedSize(194,40);
    boutonValider->setFont(policeBouton);
    boutonValider->setStyleSheet("QPushButton {border-image: url(design/bouton_194x40.png)}" "QPushButton:hover {border-image: url(design/bouton_194x40_survole.png)}");

    boutonAnnuler->setFixedSize(194,40);
    boutonAnnuler->setFont(policeBouton);
    boutonAnnuler->setStyleSheet("QPushButton {border-image: url(design/bouton_194x40.png)}" "QPushButton:hover {border-image: url(design/bouton_194x40_survole.png)}");

    boutonChoixChemin->setFixedSize(80,30);
    boutonChoixChemin->setFont(policeText);
    boutonChoixChemin->setStyleSheet("QPushButton {border-image: url(design/bouton_80x30.png)}" "QPushButton:hover {border-image: url(design/bouton_80x30_survole.png)}");

    techniciens->setMinimumSize(194,30);
    techniciens->setFont(policeText);
    techniciens->setStyleSheet("QComboBox {border-image: url(design/combobox_194x30.png)}" "QComboBox:hover {border-image: url(design/combobox_194x30_survole.png)}" "QComboBox::drop-down {border-image: url(rien.png)}" "QComboBox {padding: 0 0 0 10px}");

    qDebug() << "nomCampagne" << nomCampagne->size();

}

void IHMCreationCampagne::initialiserEvenements()
{
    connect(boutonValider, SIGNAL(clicked()), this, SLOT(validerCampagne()));
    connect(boutonAnnuler, SIGNAL(clicked()), this, SLOT(close()));
    connect(boutonChoixChemin, SIGNAL(clicked()), this, SLOT(choixCheminSauvegarde()));
    connect(techniciens, SIGNAL(currentIndexChanged(int)), this, SLOT(modifierEtatBouton(int)));
}

void IHMCreationCampagne::initialiserLayouts()
{
    QVBoxLayout *layoutPrincipal = new QVBoxLayout;
    QFormLayout *layoutFormulaireCampagne = new QFormLayout;
    QHBoxLayout *layoutValidation = new QHBoxLayout;
    QHBoxLayout *layoutChoixChemin = new QHBoxLayout;

    layoutPrincipal->addLayout(layoutFormulaireCampagne);
    layoutPrincipal->addLayout(layoutValidation);
    layoutChoixChemin->addWidget(cheminSauvegarde);
    layoutChoixChemin->addWidget(boutonChoixChemin);

    layoutFormulaireCampagne->addRow("Nom campagne : ", nomCampagne);
    layoutFormulaireCampagne->addRow("Techniciens : ", techniciens);
    layoutFormulaireCampagne->addRow("Nom technicien : ", nomTechnicien);
    layoutFormulaireCampagne->addRow("Prenom technicien : ", prenomTechnicien);
    layoutFormulaireCampagne->addRow("Lieu campagne : ", lieu);
    layoutFormulaireCampagne->addRow("Chemin sauvegarde photos : ", layoutChoixChemin);

    layoutValidation->addWidget(boutonValider);
    layoutValidation->addWidget(boutonAnnuler);

    layoutValidation->setAlignment(Qt::AlignBottom);

    setLayout(layoutPrincipal);
}

void IHMCreationCampagne::configurerWidgets()
{
    nomCampagne->setTextMargins(10,0,0,0);
    nomTechnicien->setTextMargins(10,0,0,0);
    prenomTechnicien->setTextMargins(10,0,0,0);
    lieu->setTextMargins(10,0,0,0);
    cheminSauvegarde->setTextMargins(10,0,0,0);
}

void IHMCreationCampagne::chargerListeTechniciens()
{
    techniciens->addItem("Ajouter technicien");

    for(QVector<QStringList>::iterator it = listeTechniciens.begin(); it != listeTechniciens.end(); ++it)
    {
        techniciens->addItem((*it).at(0) + " " + (*it).at(1));
    }
}

void IHMCreationCampagne::validerCampagne()
{
    if(nomCampagne->text().isEmpty() || nomTechnicien->text().isEmpty() || prenomTechnicien->text().isEmpty() || lieu->text().isEmpty() || cheminSauvegarde->text().isEmpty())
    {
        QMessageBox::critical(nullptr, "Création campagne", "Informations incomplètes !");
        return;
    }

    Campagne *campagne = new Campagne(nomCampagne->text(), lieu->text(), nomTechnicien->text(), prenomTechnicien->text(), QDateTime::currentDateTime(), this);
    campagne->setCheminSauvegarde(cheminSauvegarde->text());
    ihmAccueil->ajouterCampagne(campagne, true);
    ihmAccueil->enregistrerCampagneBDD(campagne);
    close();
}

void IHMCreationCampagne::modifierEtatBouton(int index)
{
    if(index > 0)
    {
        nomTechnicien->setDisabled(true);
        nomTechnicien->setText(listeTechniciens[index - 1].at(0));
        nomTechnicien->setStyleSheet("QLineEdit {border-image: url(design/QLine_194x30_grise.png)}");
        prenomTechnicien->setDisabled(true);
        prenomTechnicien->setText(listeTechniciens[index - 1].at(1));
        prenomTechnicien->setStyleSheet("QLineEdit {border-image: url(design/QLine_194x30_grise.png)}");
    }
    else
    {
        nomTechnicien->clear();
        prenomTechnicien->clear();
        nomTechnicien->setEnabled(true);
        nomTechnicien->setStyleSheet("QLineEdit {border-image: url(design/QLine_194x30.png)}");
        prenomTechnicien->setEnabled(true);
        prenomTechnicien->setStyleSheet("QLineEdit {border-image: url(design/QLine_194x30.png)}");
    }
}

void IHMCreationCampagne::choixCheminSauvegarde()
{
    cheminSauvegarde->setText(QFileDialog::getExistingDirectory(this, "Choix du chemin de sauvegarde des photos"));
}
