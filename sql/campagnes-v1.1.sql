-- Projet-Rovnet
-- V1.1
-- Base de donnees: `campagnes`
--

PRAGMA foreign_keys = ON;

-- --------------------------------------------------------

--
-- Structure de la table `campagne`
--

CREATE TABLE IF NOT EXISTS `campagne` (
	`IdCampagne`	INTEGER PRIMARY KEY AUTOINCREMENT,
	`IdTechnicien`	INTEGER NOT NULL,
	`nom`	TEXT NOT NULL UNIQUE,
	`lieu`	TEXT NOT NULL,
	`cheminSauvegarde`	TEXT NOT NULL,
	`date`	DATETIME NOT NULL,
	`duree`	INTEGER NOT NULL,
	`enCours` NUMERIC NOT NULL,
	UNIQUE(`IdCampagne`, `IdTechnicien`),
	FOREIGN KEY(IdTechnicien) REFERENCES technicien(IdTechnicien)
);

--
-- Structure de la table `mesure`
--

CREATE TABLE IF NOT EXISTS `mesure` (
	`IdMesure`	INTEGER PRIMARY KEY AUTOINCREMENT,
	`IdCampagne`	INTEGER NOT NULL,
	`heure`	DATETIME NOT NULL,
	`temperature`	REAL NOT NULL,
	`radiation`	REAL NOT NULL,
	`humidite`	REAL NOT NULL,	
	UNIQUE(`IdMesure`, `IdCampagne`),
	FOREIGN KEY(IdCampagne) REFERENCES campagne(IdCampagne)
);

--
-- Structure de la table `photo`
--

CREATE TABLE IF NOT EXISTS `photo` (
	`IdPhoto`	INTEGER PRIMARY KEY AUTOINCREMENT,
	`IdCampagne`	INTEGER NOT NULL,
	`cheminImage`	TEXT NOT NULL,
	`dateHeure`	DATETIME NOT NULL,
	`aGarder`	NUMERIC NOT NULL,
	UNIQUE(`IdPhoto`, `IdCampagne`),
	FOREIGN KEY(IdCampagne) REFERENCES campagne(IdCampagne)	
);

--
-- Structure de la table `technicien`
--

CREATE TABLE IF NOT EXISTS `technicien` (
	`IdTechnicien`	INTEGER PRIMARY KEY AUTOINCREMENT,
	`nom`	TEXT NOT NULL,
	`prenom`	TEXT NOT NULL
);
