SELECT s.nomestruttura,s.fax,COUNT(c.id) AS nr_corsiStudio FROM strutturaservizio AS s
JOIN corsostudi AS c ON c.id_segreteria = s.id
GROUP BY s.nomestruttura,s.fax
-- ALLORA DIFFERENZA TRA JOIN E LEFT JOIN
-- JOIN NORMALE E UNA INTERSEZIONE
-- LEFT JOIN IDENTIFICA TUTTO A 