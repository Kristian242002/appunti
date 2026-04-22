DROP INDEX index_i;
EXPLAIN SELECT i.nomeins,ie.id_facolta 
FROM insegn AS i
JOIN inserogato AS ie ON ie.id_insegn = i.id
WHERE ie.annoaccademico = '2013/2014';
CREATE INDEX index_i ON inserogato (annoaccademico varchar_pattern_ops);
ANALYZE inserogato;
EXPLAIN SELECT i.nomeins,ie.id_facolta 
FROM insegn AS i
JOIN inserogato AS ie ON ie.id_insegn = i.id
WHERE ie.annoaccademico = '2013/2014';

