SELECT DISTINCT ins.nomeins,i.nomeunita FROM inserogato AS i
JOIN insegn AS ins ON ins.id = i.id_insegn
JOIN corsostudi AS c ON c.id = i.id_corsostudi
WHERE i.modulo<0 AND i.annoaccademico = '2010/2011' AND c.id = 420 AND
((EXISTS(
	SELECT * FROM inserogato AS i2
	JOIN lezione AS l2 ON l2.id_inserogato = i2.id
	WHERE l2.giorno = 2   AND i2.id_corsostudi = i.id_corsostudi AND i2.id = i.id)
AND NOT EXISTS(
	SELECT * FROM inserogato AS i3
	JOIN lezione AS l3 ON l3.id_inserogato = i3.id
	WHERE l3.giorno = 3 AND i3.id_corsostudi = i.id_corsostudi AND i3.id = i.id))OR(
NOT EXISTS(
	SELECT * FROM inserogato AS i4
	JOIN lezione AS l4 ON l4.id_inserogato = i4.id
	WHERE l4.giorno =2  AND i4.id_corsostudi = i.id_corsostudi AND i4.id = i.id) 
AND EXISTS(
	SELECT * FROM inserogato AS i5
	JOIN lezione AS l5 ON l5.id_inserogato = i5.id
	WHERE l5.giorno = 3  AND i5.id_corsostudi = i.id_corsostudi AND i5.id = i.id
)))

ORDER BY ins.nomeins

  
