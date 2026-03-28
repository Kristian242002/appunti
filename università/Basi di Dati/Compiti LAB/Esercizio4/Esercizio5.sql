SELECT DISTINCT p.nome,p.cognome,p.telefono FROM persona AS p
JOIN docenza AS d ON d.id_persona = p.id
JOIN inserogato AS i ON i.id = d.id_inserogato
JOIN corsostudi AS c ON c.id = i.id_corsostudi
WHERE i.annoaccademico = '2009/2010' AND c.id = 4 AND i.modulo >= 0 AND NOT EXISTS (
	SELECT * FROM inserogato AS i2
	JOIN corsostudi AS c2 ON c2.id = i2.id_corsostudi 
	JOIN insegn AS ins2 ON ins2.id = i2.id_insegn
	JOIN docenza AS d2 ON d2.id_inserogato = i2.id
	WHERE i2.modulo > 0 AND ins2.nomeins ILIKE '%Programmazione%' AND c2.id=c.id AND d2.id_persona = d.id_persona
)

