/**
 * @brief
 * Fichier qui contient la définition de la classe Manette
 * @file manette.cpp
 */

#include "manette.h"

Manette::Manette(int deviceID) : QGamepad(deviceID), modeDeplacement(true), modePilotageBras(false), puissanceGachetteDroite(0), puissanceGachetteGauche(0), joystickAxeXCamera("0"), joystickAxeYCamera("0")
{
    qDebug() << Q_FUNC_INFO << this;
    initialiserEtats();
    initialiserEtatBouton();
    initialiserTypesPilotage();
    initialiserTypesDeplacement();
}

Manette::~Manette()
{
    qDebug() << Q_FUNC_INFO << this;
}

void Manette::initialiserEtats()
{
    maManettePilotage.flecheADroite = false;
    maManettePilotage.flecheAGauche = false;
    maManettePilotage.flecheEnArriere = false;
    maManettePilotage.flecheEnAvant = false;
    maManettePilotage.boutonHautDroit = false;
    maManettePilotage.boutonHautGauche = false;

    maManetteDeplacement.joystickGaucheADroite = false;
    maManetteDeplacement.joystickGaucheAGauche = false;
    maManetteDeplacement.joystickGaucheEnArriere = false;
    maManetteDeplacement.joystickGaucheEnAvant = false;
    maManetteDeplacement.gachetteBasDroit = false;
    maManetteDeplacement.gachetteBasGauche = false;
}

void Manette::initialiserTypesPilotage()
{
    avance.flecheADroite = false;
    avance.flecheAGauche = false;
    avance.flecheEnArriere = false;
    avance.flecheEnAvant = true;
    avance.boutonHautDroit = false;
    avance.boutonHautGauche = false;

    recule.flecheADroite = false;
    recule.flecheAGauche = false;
    recule.flecheEnArriere = true;
    recule.flecheEnAvant = false;
    recule.boutonHautDroit = false;
    recule.boutonHautGauche = false;

    gauche.flecheADroite = false;
    gauche.flecheAGauche = true;
    gauche.flecheEnArriere = false;
    gauche.flecheEnAvant = false;
    gauche.boutonHautDroit = false;
    gauche.boutonHautGauche = false;

    droite.flecheADroite = true;
    droite.flecheAGauche = false;
    droite.flecheEnArriere = false;
    droite.flecheEnAvant = false;
    droite.boutonHautDroit = false;
    droite.boutonHautGauche = false;

    monte.flecheADroite = false;
    monte.flecheAGauche = false;
    monte.flecheEnArriere = false;
    monte.flecheEnAvant = false;
    monte.boutonHautDroit = true;
    monte.boutonHautGauche = false;

    descend.flecheADroite = false;
    descend.flecheAGauche = false;
    descend.flecheEnArriere = false;
    descend.flecheEnAvant = false;
    descend.boutonHautDroit = false;
    descend.boutonHautGauche = true;
}

void Manette::initialiserTypesDeplacement()
{
    initialisationStructuresEnAvant();
    initialisationStructuresEnArriere();
    initialisationStructureRotationAGauche();
    initialisationStructuresRotationAGaucheDoucement();
    initialisationStructureRotationADroite();
    initialisationStructuresRotationADroiteDoucement();
    initialisationStructureVirageAvantAGauche();
    initialisationStructuresVirageAvantAGaucheDoucement();
    initialisationStructureVirageAvantADroite();
    initialisationStructuresVirageAvantADroiteDoucement();
    initialisationStructureVirageArriereAGauche();
    initialisationStructuresVirageArriereAGaucheDoucement();
    initialisationStructureVirageArriereADroite();
    initialisationStructuresVirageArriereADroiteDoucement();
}

void Manette::initialisationStructuresEnAvant()
{
    enAvantCas1.joystickGaucheEnAvant = false;
    enAvantCas1.joystickGaucheEnArriere = false;
    enAvantCas1.joystickGaucheAGauche = false;
    enAvantCas1.joystickGaucheADroite = false;
    enAvantCas1.gachetteBasGauche = false;
    enAvantCas1.gachetteBasDroit = true;

    enAvantCas2.joystickGaucheEnAvant = true;
    enAvantCas2.joystickGaucheEnArriere = false;
    enAvantCas2.joystickGaucheAGauche = false;
    enAvantCas2.joystickGaucheADroite = false;
    enAvantCas2.gachetteBasGauche = false;
    enAvantCas2.gachetteBasDroit = true;

    enAvantCas3.joystickGaucheEnAvant = false;
    enAvantCas3.joystickGaucheEnArriere = true;
    enAvantCas3.joystickGaucheAGauche = false;
    enAvantCas3.joystickGaucheADroite = false;
    enAvantCas3.gachetteBasGauche = false;
    enAvantCas3.gachetteBasDroit = true;
}

void Manette::initialisationStructuresEnArriere()
{
    enArriereCas1.joystickGaucheEnAvant = false;
    enArriereCas1.joystickGaucheEnArriere = false;
    enArriereCas1.joystickGaucheAGauche = false;
    enArriereCas1.joystickGaucheADroite = false;
    enArriereCas1.gachetteBasGauche = true;
    enArriereCas1.gachetteBasDroit = false;

    enArriereCas2.joystickGaucheEnAvant = true;
    enArriereCas2.joystickGaucheEnArriere = false;
    enArriereCas2.joystickGaucheAGauche = false;
    enArriereCas2.joystickGaucheADroite = false;
    enArriereCas2.gachetteBasGauche = true;
    enArriereCas2.gachetteBasDroit = false;

    enArriereCas3.joystickGaucheEnAvant = false;
    enArriereCas3.joystickGaucheEnArriere = true;
    enArriereCas3.joystickGaucheAGauche = false;
    enArriereCas3.joystickGaucheADroite = false;
    enArriereCas3.gachetteBasGauche = true;
    enArriereCas3.gachetteBasDroit = false;
}

void Manette::initialisationStructureRotationAGauche()
{
    rotationAGauche.joystickGaucheEnAvant = false;
    rotationAGauche.joystickGaucheEnArriere = false;
    rotationAGauche.joystickGaucheAGauche = true;
    rotationAGauche.joystickGaucheADroite = false;
    rotationAGauche.gachetteBasGauche = false;
    rotationAGauche.gachetteBasDroit = false;
}

void Manette::initialisationStructuresRotationAGaucheDoucement()
{
    rotationAGaucheDoucementCas1.joystickGaucheEnAvant = false;
    rotationAGaucheDoucementCas1.joystickGaucheEnArriere = true;
    rotationAGaucheDoucementCas1.joystickGaucheAGauche = true;
    rotationAGaucheDoucementCas1.joystickGaucheADroite = false;
    rotationAGaucheDoucementCas1.gachetteBasGauche = false;
    rotationAGaucheDoucementCas1.gachetteBasDroit = false;

    rotationAGaucheDoucementCas2.joystickGaucheEnAvant = true;
    rotationAGaucheDoucementCas2.joystickGaucheEnArriere = false;
    rotationAGaucheDoucementCas2.joystickGaucheAGauche = true;
    rotationAGaucheDoucementCas2.joystickGaucheADroite = false;
    rotationAGaucheDoucementCas2.gachetteBasGauche = false;
    rotationAGaucheDoucementCas2.gachetteBasDroit = false;
}

void Manette::initialisationStructureRotationADroite()
{
    rotationADroite.joystickGaucheEnAvant = false;
    rotationADroite.joystickGaucheEnArriere = false;
    rotationADroite.joystickGaucheAGauche = false;
    rotationADroite.joystickGaucheADroite = true;
    rotationADroite.gachetteBasGauche = false;
    rotationADroite.gachetteBasDroit = false;
}

void Manette::initialisationStructuresRotationADroiteDoucement()
{
    rotationADroiteDoucementCas1.joystickGaucheEnAvant = false;
    rotationADroiteDoucementCas1.joystickGaucheEnArriere = true;
    rotationADroiteDoucementCas1.joystickGaucheAGauche = false;
    rotationADroiteDoucementCas1.joystickGaucheADroite = true;
    rotationADroiteDoucementCas1.gachetteBasGauche = false;
    rotationADroiteDoucementCas1.gachetteBasDroit = false;

    rotationADroiteDoucementCas2.joystickGaucheEnAvant = true;
    rotationADroiteDoucementCas2.joystickGaucheEnArriere = false;
    rotationADroiteDoucementCas2.joystickGaucheAGauche = false;
    rotationADroiteDoucementCas2.joystickGaucheADroite = true;
    rotationADroiteDoucementCas2.gachetteBasGauche = false;
    rotationADroiteDoucementCas2.gachetteBasDroit = false;
}

void Manette::initialisationStructureVirageAvantAGauche()
{
    virageAvantAGauche.joystickGaucheEnAvant = false;
    virageAvantAGauche.joystickGaucheEnArriere = false;
    virageAvantAGauche.joystickGaucheAGauche = true;
    virageAvantAGauche.joystickGaucheADroite = false;
    virageAvantAGauche.gachetteBasGauche = false;
    virageAvantAGauche.gachetteBasDroit = true;
}

void Manette::initialisationStructuresVirageAvantAGaucheDoucement()
{
    virageAvantAGaucheDoucementCas1.joystickGaucheEnAvant = true;
    virageAvantAGaucheDoucementCas1.joystickGaucheEnArriere = false;
    virageAvantAGaucheDoucementCas1.joystickGaucheAGauche = true;
    virageAvantAGaucheDoucementCas1.joystickGaucheADroite = false;
    virageAvantAGaucheDoucementCas1.gachetteBasGauche = false;
    virageAvantAGaucheDoucementCas1.gachetteBasDroit = true;

    virageAvantAGaucheDoucementCas2.joystickGaucheEnAvant = false;
    virageAvantAGaucheDoucementCas2.joystickGaucheEnArriere = true;
    virageAvantAGaucheDoucementCas2.joystickGaucheAGauche = true;
    virageAvantAGaucheDoucementCas2.joystickGaucheADroite = false;
    virageAvantAGaucheDoucementCas2.gachetteBasGauche = false;
    virageAvantAGaucheDoucementCas2.gachetteBasDroit = true;
}

void Manette::initialisationStructureVirageAvantADroite()
{
    virageAvantADroite.joystickGaucheEnAvant = false;
    virageAvantADroite.joystickGaucheEnArriere = false;
    virageAvantADroite.joystickGaucheAGauche = false;
    virageAvantADroite.joystickGaucheADroite = true;
    virageAvantADroite.gachetteBasGauche = false;
    virageAvantADroite.gachetteBasDroit = true;
}

void Manette::initialisationStructuresVirageAvantADroiteDoucement()
{
    virageAvantADroiteDoucementCas1.joystickGaucheEnAvant = true;
    virageAvantADroiteDoucementCas1.joystickGaucheEnArriere = false;
    virageAvantADroiteDoucementCas1.joystickGaucheAGauche = false;
    virageAvantADroiteDoucementCas1.joystickGaucheADroite = true;
    virageAvantADroiteDoucementCas1.gachetteBasGauche = false;
    virageAvantADroiteDoucementCas1.gachetteBasDroit = true;

    virageAvantADroiteDoucementCas2.joystickGaucheEnAvant = false;
    virageAvantADroiteDoucementCas2.joystickGaucheEnArriere = true;
    virageAvantADroiteDoucementCas2.joystickGaucheAGauche = false;
    virageAvantADroiteDoucementCas2.joystickGaucheADroite = true;
    virageAvantADroiteDoucementCas2.gachetteBasGauche = false;
    virageAvantADroiteDoucementCas2.gachetteBasDroit = true;
}

void Manette::initialisationStructureVirageArriereAGauche()
{
    virageArriereAGauche.joystickGaucheEnAvant = false;
    virageArriereAGauche.joystickGaucheEnArriere = false;
    virageArriereAGauche.joystickGaucheAGauche = true;
    virageArriereAGauche.joystickGaucheADroite = false;
    virageArriereAGauche.gachetteBasGauche = true;
    virageArriereAGauche.gachetteBasDroit = false;
}

void Manette::initialisationStructuresVirageArriereAGaucheDoucement()
{
    virageArriereAGaucheDoucementCas1.joystickGaucheEnAvant = true;
    virageArriereAGaucheDoucementCas1.joystickGaucheEnArriere = false;
    virageArriereAGaucheDoucementCas1.joystickGaucheAGauche = true;
    virageArriereAGaucheDoucementCas1.joystickGaucheADroite = false;
    virageArriereAGaucheDoucementCas1.gachetteBasGauche = true;
    virageArriereAGaucheDoucementCas1.gachetteBasDroit = false;

    virageArriereAGaucheDoucementCas2.joystickGaucheEnAvant = false;
    virageArriereAGaucheDoucementCas2.joystickGaucheEnArriere = true;
    virageArriereAGaucheDoucementCas2.joystickGaucheAGauche = true;
    virageArriereAGaucheDoucementCas2.joystickGaucheADroite = false;
    virageArriereAGaucheDoucementCas2.gachetteBasGauche = true;
    virageArriereAGaucheDoucementCas2.gachetteBasDroit = false;
}

void Manette::initialisationStructureVirageArriereADroite()
{
    virageArriereADroite.joystickGaucheEnAvant = false;
    virageArriereADroite.joystickGaucheEnArriere = false;
    virageArriereADroite.joystickGaucheAGauche = false;
    virageArriereADroite.joystickGaucheADroite = true;
    virageArriereADroite.gachetteBasGauche = true;
    virageArriereADroite.gachetteBasDroit = false;
}

void Manette::initialisationStructuresVirageArriereADroiteDoucement()
{
    virageArriereADroiteDoucementCas1.joystickGaucheEnAvant = true;
    virageArriereADroiteDoucementCas1.joystickGaucheEnArriere = false;
    virageArriereADroiteDoucementCas1.joystickGaucheAGauche = false;
    virageArriereADroiteDoucementCas1.joystickGaucheADroite = true;
    virageArriereADroiteDoucementCas1.gachetteBasGauche = true;
    virageArriereADroiteDoucementCas1.gachetteBasDroit = false;

    virageArriereADroiteDoucementCas2.joystickGaucheEnAvant = false;
    virageArriereADroiteDoucementCas2.joystickGaucheEnArriere = true;
    virageArriereADroiteDoucementCas2.joystickGaucheAGauche = false;
    virageArriereADroiteDoucementCas2.joystickGaucheADroite = true;
    virageArriereADroiteDoucementCas2.gachetteBasGauche = true;
    virageArriereADroiteDoucementCas2.gachetteBasDroit = false;
}

void Manette::initialiserEtatBouton()
{
    maManetteBouton.boutonA = false;
    maManetteBouton.boutonB = false;
    maManetteBouton.boutonX = false;
    maManetteBouton.boutonY = false;

    ouvrirPince.boutonA = false;
    ouvrirPince.boutonB = false;
    ouvrirPince.boutonX = true;
    ouvrirPince.boutonY = false;

    fermerPince.boutonA = false;
    fermerPince.boutonB = true;
    fermerPince.boutonX = false;
    fermerPince.boutonY = false;

    poserObjetDansBac.boutonA = true;
    poserObjetDansBac.boutonB = false;
    poserObjetDansBac.boutonX = false;
    poserObjetDansBac.boutonY = false;

    revenirEtatInitial.boutonA = false;
    revenirEtatInitial.boutonB = false;
    revenirEtatInitial.boutonX = false;
    revenirEtatInitial.boutonY = true;
}

void Manette::determinerTrameDeplacementRobot()
{
    if(maManetteDeplacement == enAvantCas1 || maManetteDeplacement == enAvantCas2 || maManetteDeplacement == enAvantCas3)
        emit creationTrameDeplacement('A', puissanceGachetteDroite, '0');
    else if(maManetteDeplacement == enArriereCas1 || maManetteDeplacement == enArriereCas2 || maManetteDeplacement == enArriereCas3)
        emit creationTrameDeplacement('R', puissanceGachetteGauche, '0');
    else if(maManetteDeplacement == rotationAGauche)
        emit creationTrameDeplacement('0', 100, 'G');
    else if(maManetteDeplacement == rotationAGaucheDoucementCas1 || maManetteDeplacement == rotationAGaucheDoucementCas2)
        emit creationTrameDeplacement('0', int(100 * REDUCTION_VITESSE), 'G');
    else if(maManetteDeplacement == rotationADroite)
        emit creationTrameDeplacement('0', 100, 'D');
    else if(maManetteDeplacement == rotationADroiteDoucementCas1 || maManetteDeplacement == rotationADroiteDoucementCas2)
        emit creationTrameDeplacement('0', int(100 * REDUCTION_VITESSE), 'D');
    else if(maManetteDeplacement == virageAvantAGauche)
        emit creationTrameDeplacement('A', puissanceGachetteDroite, 'G');
    else if(maManetteDeplacement == virageAvantAGaucheDoucementCas1 || maManetteDeplacement == virageAvantAGaucheDoucementCas2)
        emit creationTrameDeplacement('A', int(puissanceGachetteDroite * REDUCTION_VITESSE), 'G');
    else if(maManetteDeplacement == virageAvantADroite)
        emit creationTrameDeplacement('A', puissanceGachetteDroite, 'D');
    else if(maManetteDeplacement == virageAvantADroiteDoucementCas1 || maManetteDeplacement == virageAvantADroiteDoucementCas2)
        emit creationTrameDeplacement('A', int(puissanceGachetteDroite * REDUCTION_VITESSE), 'D');
    else if(maManetteDeplacement == virageArriereAGauche)
        emit creationTrameDeplacement('R', puissanceGachetteGauche, 'G');
    else if(maManetteDeplacement == virageArriereAGaucheDoucementCas1 || maManetteDeplacement == virageArriereAGaucheDoucementCas2)
        emit creationTrameDeplacement('R', int(puissanceGachetteGauche * REDUCTION_VITESSE), 'G');
    else if(maManetteDeplacement == virageArriereADroite)
        emit creationTrameDeplacement('R', puissanceGachetteGauche, 'D');
    else if(maManetteDeplacement == virageArriereADroiteDoucementCas1 || maManetteDeplacement == virageArriereADroiteDoucementCas2)
        emit creationTrameDeplacement('R', int(puissanceGachetteGauche * REDUCTION_VITESSE), 'D');
    else
        emit creationTrameDeplacement('0', 0, '0');
}

void Manette::determinerTramePilotageBras()
{
    if(maManettePilotage == avance)
        emit creationTramePilotage(AVANCER);
    else if(maManettePilotage == recule)
        emit creationTramePilotage(RECULER);
    else if(maManettePilotage == gauche)
        emit creationTramePilotage(GAUCHE);
    else if(maManettePilotage == droite)
        emit creationTramePilotage(DROITE);
    else if(maManettePilotage == monte)
        emit creationTramePilotage(MONTER);
    else if(maManettePilotage == descend)
        emit creationTramePilotage(DESCENDRE);
    else
        emit creationTramePilotage(IMMOBILE);
}

void Manette::determinerTrameBouton()
{
    if(maManetteBouton == ouvrirPince)
        emit creationTramePince(OUVERTURE_PINCE);
    else if(maManetteBouton == fermerPince)
        emit creationTramePince(FERMETURE_PINCE);
    else if(maManetteBouton == revenirEtatInitial)
        emit creationTrameOrdre(RETOUR_ETAT_INITIAL);
    else if(maManetteBouton == poserObjetDansBac)
        emit creationTrameOrdre(POSER_OBJET_DANS_BAC);
    else
        emit creationTramePince(IMMOBILE);
}

void Manette::changerMode()
{
    if(modeDeplacement)
    {
        modePilotageBras = true;
        modeDeplacement = false;
    }
    else
    {
        modePilotageBras = false;
        modeDeplacement = true;
    }
}

void Manette::changerAxeXJoystickGauche(double valeur)
{
    if(modeDeplacement)
    {
        if(valeur <= -TAUX_VALIDITE_JOYSTICK)
            maManetteDeplacement.joystickGaucheAGauche = true;
        else if(valeur >= TAUX_VALIDITE_JOYSTICK)
            maManetteDeplacement.joystickGaucheADroite = true;
        else if(valeur > -TAUX_VALIDITE_JOYSTICK && valeur < TAUX_VALIDITE_JOYSTICK)
        {
            maManetteDeplacement.joystickGaucheADroite = false;
            maManetteDeplacement.joystickGaucheAGauche = false;
        }
        determinerTrameDeplacementRobot();
    }
}

void Manette::changerAxeYJoystickGauche(double valeur)
{
    if(modeDeplacement)
    {
        if(valeur >= TAUX_VALIDITE_JOYSTICK)
            maManetteDeplacement.joystickGaucheEnAvant = true;
        else if(valeur <= -TAUX_VALIDITE_JOYSTICK)
            maManetteDeplacement.joystickGaucheEnArriere = true;
        else if(valeur > -TAUX_VALIDITE_JOYSTICK && valeur < TAUX_VALIDITE_JOYSTICK)
        {
            maManetteDeplacement.joystickGaucheEnAvant = false;
            maManetteDeplacement.joystickGaucheEnArriere = false;
        }
        determinerTrameDeplacementRobot();
    }
}

void Manette::changerAxeXJoystickDroit(double valeur)
{
    if(valeur >= TAUX_VALIDITE_JOYSTICK)
        joystickAxeXCamera = "D";
    else if(valeur <= -TAUX_VALIDITE_JOYSTICK)
        joystickAxeXCamera = "G";
    else
        joystickAxeXCamera = "0";

    emit nouvelleTrameCamera(joystickAxeXCamera, joystickAxeYCamera);
}

void Manette::changerAxeYJoystickDroit(double valeur)
{
    if(valeur >= TAUX_VALIDITE_JOYSTICK)
        joystickAxeYCamera = "B";
    else if(valeur <= -TAUX_VALIDITE_JOYSTICK)
        joystickAxeYCamera = "H";
    else
        joystickAxeYCamera = "0";

    emit nouvelleTrameCamera(joystickAxeXCamera, joystickAxeYCamera);
}

void Manette::changerBoutonHautGauche(bool etat)
{
    maManettePilotage.boutonHautGauche = etat;
    if(modePilotageBras)
        determinerTramePilotageBras();
}

void Manette::changerBoutonHautDroit(bool etat)
{
    maManettePilotage.boutonHautDroit = etat;
    if(modePilotageBras)
        determinerTramePilotageBras();
}

void Manette::changerGachetteBasGauche(double valeur)
{
    puissanceGachetteGauche = int(valeur*100);
    if (valeur > 0)
        maManetteDeplacement.gachetteBasGauche = true;
    else
        maManetteDeplacement.gachetteBasGauche = false;
    if(modeDeplacement)
        determinerTrameDeplacementRobot();
}

void Manette::changerGachetteBasDroit(double valeur)
{
    puissanceGachetteDroite = int(valeur*100);
    if (valeur > 0)
        maManetteDeplacement.gachetteBasDroit = true;
    else
        maManetteDeplacement.gachetteBasDroit = false;
    if(modeDeplacement)
        determinerTrameDeplacementRobot();
}

void Manette::changerFlecheEnAvant(bool etat)
{
    maManettePilotage.flecheEnAvant = etat;
    if(modeDeplacement)
        determinerTrameDeplacementRobot();
    else
        determinerTramePilotageBras();
}

void Manette::changerFlecheEnArriere(bool etat)
{
    maManettePilotage.flecheEnArriere = etat;
    if(modeDeplacement)
        determinerTrameDeplacementRobot();
    else
        determinerTramePilotageBras();
}

void Manette::changerFlecheAGauche(bool etat)
{
    maManettePilotage.flecheAGauche = etat;
    if(modeDeplacement)
        determinerTrameDeplacementRobot();
    else
        determinerTramePilotageBras();
}

void Manette::changerFlecheADroite(bool etat)
{
    maManettePilotage.flecheADroite = etat;
    if(modeDeplacement)
        determinerTrameDeplacementRobot();
    else
        determinerTramePilotageBras();
}

void Manette::changerBoutonA(bool etat)
{
    maManetteBouton.boutonA = etat;
    if(modePilotageBras)
        determinerTrameBouton();
}

void Manette::changerBoutonB(bool etat)
{
    maManetteBouton.boutonB = etat;
    if(modePilotageBras)
        determinerTrameBouton();
}

void Manette::changerBoutonX(bool etat)
{
    maManetteBouton.boutonX = etat;
    if(modePilotageBras)
        determinerTrameBouton();
}

void Manette::changerBoutonY(bool etat)
{
    maManetteBouton.boutonY = etat;
    if(modePilotageBras)
        determinerTrameBouton();
}

void Manette::changerBoutonSelect(bool etat)
{
    if(etat)
    {
        changerMode();
    }
    qDebug() << Q_FUNC_INFO << "Button Select" << etat ;
}

void Manette::fermerApplication(bool etat)
{
    Q_UNUSED(etat);
    QCoreApplication::quit();
}

bool EtatManetteBouton::operator==(const EtatManetteBouton &maStructure) const
{
    if(this->boutonA != maStructure.boutonA)
        return false;
    else if(this->boutonB != maStructure.boutonB)
        return false;
    else if(this->boutonX != maStructure.boutonX)
        return false;
    else if(this->boutonY != maStructure.boutonY)
        return false;
    else
        return true;
}

bool EtatManetteBouton::operator!=(const EtatManetteBouton &maStructure) const
{
    return !(*this == maStructure);
}

bool EtatManettePilotage::operator==(const EtatManettePilotage &maStructure) const
{
    if(this->flecheEnAvant != maStructure.flecheEnAvant)
        return false;
    else if(this->flecheEnArriere != maStructure.flecheEnArriere)
        return false;
    else if(this->flecheAGauche != maStructure.flecheAGauche)
        return false;
    else if(this->flecheADroite != maStructure.flecheADroite)
        return false;
    else if(this->boutonHautGauche != maStructure.boutonHautGauche)
        return false;
    else if(this->boutonHautDroit != maStructure.boutonHautDroit)
        return false;
    else
        return true;
}

bool EtatManettePilotage::operator!=(const EtatManettePilotage &maStructure) const
{
    return !(*this == maStructure);
}

bool EtatManetteDeplacement::operator==(const EtatManetteDeplacement &maStructure) const
{
    if(this->gachetteBasDroit != maStructure.gachetteBasDroit)
        return false;
    else if(this->gachetteBasGauche != maStructure.gachetteBasGauche)
        return false;
    else if(this->joystickGaucheADroite != maStructure.joystickGaucheADroite)
        return false;
    else if(this->joystickGaucheAGauche != maStructure.joystickGaucheAGauche)
        return false;
    else if(this->joystickGaucheEnArriere != maStructure.joystickGaucheEnArriere)
        return false;
    else if(this->joystickGaucheEnAvant != maStructure.joystickGaucheEnAvant)
        return false;
    else
        return true;
}

bool EtatManetteDeplacement::operator!=(const EtatManetteDeplacement &maStructure) const
{
    return !(*this == maStructure);
}

QString Manette::getNom()
{
    return name();
}
