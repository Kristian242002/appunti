SELECT AVG((o.orariochiusura::time - o.orarioapertura::time)) AS oreMedie FROM orario AS o
JOIN museo m ON m.nome = o.museo AND m.citta = o.citta
WHERE m.nome = 'Arena' AND m.citta='Verona'