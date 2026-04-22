DROP INDEX index_corsistudi;
EXPLAIN SELECT c.nome
FROM corsostudi AS c 
WHERE LOWER(c.nome) LIKE '%informatica';
CREATE INDEX index_corsistudi ON corsostudi(LOWER(nome) varchar_pattern_ops);
ANALYZE corsostudi;

SELECT c.nome
FROM corsostudi AS c 
WHERE LOWER(c.nome) LIKE '%informatica'
