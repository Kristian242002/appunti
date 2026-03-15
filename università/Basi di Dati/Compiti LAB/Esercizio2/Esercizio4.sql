SELECT m.nome,o.orarioapertura,o.orariochiusura FROM orario o
JOIN museo m ON o.museo = m.nome AND o.citta = m.citta
WHERE giorno = 'MAR' AND m.giornochiusura <> 'mar'