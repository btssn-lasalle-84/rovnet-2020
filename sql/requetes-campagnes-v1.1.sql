--
-- Récupère les campagnes en cours (les plus récentes en premier)
--

SELECT campagne.nom, campagne.lieu, technicien.nom, technicien.prenom, campagne.date, campagne.duree, campagne.enCours FROM campagne INNER JOIN technicien ON campagne.idTechnicien = technicien.idTechnicien WHERE campagne.enCours = '1' ORDER BY campagne.date DESC

