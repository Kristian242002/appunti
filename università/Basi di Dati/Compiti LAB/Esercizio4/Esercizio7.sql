CREATE TEMP VIEW vistamaxore (cognome,nome,nomef,maxTempo) AS
SELECT p.cognome,p.nome,f.nome,SUM(d.orelez) AS maxTempo FROM persona AS p
JOIN docenza AS d ON d.id_persona = p.id
JOIN inserogato AS i ON i.id = d.id_inserogato
JOIN facolta AS f ON f.id = i.id_facolta
WHERE i.annoaccademico = '2009/2010' 
GROUP BY p.cognome,p.nome,f.nome;
-- vista
SELECT cognome,nome,nomef,maxTempo FROM vistamaxore AS v1
WHERE maxTempo = (
	SELECT MAX(maxTempo) FROM vistamaxore AS v2
	WHERE v2.nomef = v1.nomef
)
ORDER BY cognome,nome,nomef

