SELECT DISTINCT ins.id AS idInsegnamento , ins.nomeins , p.id AS idProf , p.nome , p.cognome FROM inserogato AS i
JOIN insegn AS ins ON ins.id = i.id_insegn
JOIN docenza AS d ON d.id_inserogato = i.id
JOIN persona AS p ON p.id = d.id_persona
JOIN corsostudi AS c ON c.id = i.id_corsostudi
JOIN corsoinfacolta AS cf ON cf.id_corsostudi = c.id
JOIN facolta AS f ON f.id = cf.id_facolta
WHERE i.modulo=0 AND  f.nome ILIKE '%Scienze Matematiche Fisiche e Naturali%' AND EXISTS (
	SELECT * FROM inserogato AS i2
	JOIN docenza AS d2 ON d2.id_inserogato = i2.id
	WHERE (LEFT (i2.annoaccademico, 4) = RIGHT(i.annoaccademico, 4)) AND i.id_corsostudi = i2.id_corsostudi AND d2.id_persona = d.id_persona AND i2.id_insegn = i.id_insegn 
)
ORDER BY ins.nomeins




