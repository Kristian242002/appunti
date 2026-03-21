SELECT c.nome,COUNT(DISTINCT i.id_insegn) AS numero_insegnamenti FROM corsostudi AS c
JOIN corsoinfacolta as cf ON cf.id_corsostudi = c.id
JOIN facolta AS f ON f.id = cf.id_facolta
JOIN inserogato AS i ON i.id_corsostudi = c.id
WHERE f.nome ILIKE 'Scienze Matematiche Fisiche e Naturali' AND i.annoaccademico = '2009/2010' AND i.modulo = 0
GROUP BY c.nome


