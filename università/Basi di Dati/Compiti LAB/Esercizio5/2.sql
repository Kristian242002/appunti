DROP INDEX index_ins;
EXPLAIN ANALYZE SELECT nomeins FROM insegn AS i
WHERE nomeins LIKE 'Teoria%';
CREATE INDEX index_ins ON insegn(nomeins varchar_pattern_ops);
EXPLAIN SELECT nomeins FROM insegn AS i
WHERE nomeins LIKE 'Teoria%'

