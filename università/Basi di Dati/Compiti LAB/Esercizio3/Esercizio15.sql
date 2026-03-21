SELECT DISTINCT c.nome,c.durataanni  FROM inserogato AS i
JOIN corsostudi AS c ON c.id = i.id_corsostudi
WHERE i.annoaccademico = '2010/2011' AND (i.crediti IN (4,6,8,10,12) OR (i.creditilab > 10 AND i.creditilab<15)) 


