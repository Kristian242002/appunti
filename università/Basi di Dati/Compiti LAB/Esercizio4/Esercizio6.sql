
SELECT f.nome,SUM(i.crediti) AS crediti_totali ,COUNT(*) AS nrunita_logiche FROM facolta AS f
JOIN inserogato AS i ON i.id_facolta = f.id
WHERE i.annoaccademico = '2010/2011' AND i.modulo< 0
GROUP BY f.nome
