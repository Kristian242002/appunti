SELECT DISTINCT ins.nomeins,d.descrizione FROM inserogato AS i
JOIN insegn AS ins ON ins.id = i.id_insegn
JOIN discriminante AS d ON d.id = i.id_discriminante
WHERE i.annoaccademico = '2009/2010' AND i.crediti IN (3,5,12) AND i.modulo = 0
ORDER BY d.descrizione

