SELECT DISTINCT p.id,p.cognome,p.nome FROM docenza AS d
JOIN persona AS p ON p.id=d.id_persona
JOIN inserogato AS i ON i.id = d.id_inserogato
JOIN insegn AS ins ON ins.id = i.id_insegn
WHERE i.annoaccademico = '2010/2011' AND NOT EXISTS (
	SELECT * FROM docenza AS d2
	JOIN inserogato AS i2 ON i2.id = d2.id_inserogato
	JOIN insegn AS ins2 ON ins2.id = i2.id_insegn
	WHERE i2.annoaccademico = '2009/2010' AND ins2.nomeins = ins.nomeins AND d2.id_persona = d.id_persona
)
ORDER BY p.id ASC 

