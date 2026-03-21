SELECT DISTINCT i.id,ins.nomeins,d.descrizione FROM inserogato AS i
JOIN insegn AS ins ON ins.id = i.id_insegn
JOIN discriminante AS d ON d.id = i.id_discriminante
WHERE i.annoaccademico = '2008/2009' AND i.crediti > 9 AND modulo = 0
ORDER BY ins.nomeins

