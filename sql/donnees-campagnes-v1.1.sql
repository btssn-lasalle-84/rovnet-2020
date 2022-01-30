--
-- Table `technicien`
--

INSERT INTO `technicien` (nom,prenom) VALUES ('BONNET','Anthony');
INSERT INTO `technicien` (nom,prenom) VALUES ('TENAILLE','Servan');

--
-- Table `campagne`
--

INSERT INTO `campagne` (IdTechnicien,nom,lieu,date,duree,enCours) VALUES (1,'Mission n°1','Tchernobyl','2020-03-18 10:00:00',500,1),
 (1,'Mission n°2','Fukushima','2020-03-20 09:00:00',100,1);
