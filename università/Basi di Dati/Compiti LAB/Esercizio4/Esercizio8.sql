SELECT DISTINCT ins.nomeins,d.nome FROM insegn AS ins
JOIN inserogato AS i ON i.id_insegn = ins.id
JOIN corsostudi AS c ON c.id = i.id_corsostudi
JOIN discriminante AS d ON d.id = i.id_discriminante
JOIN docenza AS doc ON doc.id_inserogato = i.id 
WHERE c.id = 240 AND i.modulo = 0 AND EXISTS (
	SELECT * FROM inserogato AS i2
	WHERE i2.annoaccademico = '2009/2010' AND i2.id_insegn = i.id_insegn AND i2.id_corsostudi = i.id_corsostudi
	
) AND EXISTS (
	SELECT * FROM inserogato AS i3
	WHERE i3.annoaccademico = '2010/2011' AND i3.id_insegn = i.id_insegn AND i3.id_corsostudi = i.id_corsostudi
) AND NOT EXISTS (
	SELECT * FROM docenza AS d4
	JOIN persona AS p4 ON p4.id = d4.id_persona
	JOIN inserogato AS i4 ON i4.id = d4.id_inserogato
	WHERE p4.nome IN ('Roberto','Alberto','Massimo','Luca') AND i4.id_insegn = i.id_insegn AND i4.id_corsostudi = i.id_corsostudi 
)
ORDER BY ins.nomeins
