SELECT DISTINCT ins.nomeins,d.descrizione,i.crediti,i.annierogazione FROM inserogato AS i
JOIN insegn AS ins ON ins.id = i.id_insegn
JOIN discriminante AS d ON d.id = i.id_discriminante
JOIN corsostudi AS c ON c.id = i.id_corsostudi
WHERE i.annoaccademico = '2010/2011' AND c.nome = 'Laurea in Informatica' AND i.modulo = 0
ORDER BY ins.nomeins

