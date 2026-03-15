UPDATE mostra 
SET prezzoridotto = NULL
WHERE titolo = 'Ciao2';
-- SELECT * FROM museo mu
-- JOIN mostra mo ON mu.nome = mo.museo AND mu.citta=mo.citta
-- WHERE prezzoridotto = NULL
-- IN QUESTO CASO NON MI DA NESSUNA RIGA PROVIAMO CON IS NULL
-- In SQL NULL non è un valore, rappresenta assenza di valore.
SELECT * FROM museo mu
JOIN mostra mo ON mu.nome = mo.museo AND mu.citta=mo.citta
WHERE prezzoridotto IS NULL

