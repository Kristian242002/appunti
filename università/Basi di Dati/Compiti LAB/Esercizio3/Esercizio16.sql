SELECT p.nome,p.cognome FROM persona AS p
JOIN docenza AS d ON d.id_persona = p.id
JOIN inserogato AS i ON i.id = d.id_inserogato
WHERE i.annoaccademico = '2010/2011'  
GROUP BY p.id,p.nome,p.cognome
HAVING COUNT(DISTINCT i.id_corsostudi)>=2