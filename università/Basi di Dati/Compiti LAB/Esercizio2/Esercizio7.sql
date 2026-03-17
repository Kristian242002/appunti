SELECT COUNT(o.giorno) AS TotGiorni FROM museo AS m
JOIN orario o ON m.nome = o.museo AND m.citta = o.citta
WHERE m.nome = 'Arena' AND m.citta = 'Verona'