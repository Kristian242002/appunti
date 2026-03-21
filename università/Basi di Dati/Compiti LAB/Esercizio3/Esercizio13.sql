SELECT i.annoaccademico,c.nome,SUM(i.crediti) AS somma_crediti ,MAX(i.crediti) AS max_crediti ,MIN(i.crediti) AS min_Crediti FROM inserogato AS i
JOIN corsostudi AS c ON c.id = i.id_corsostudi
WHERE i.modulo = 0 
GROUP BY i.annoaccademico ,c.nome

