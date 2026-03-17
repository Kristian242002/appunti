SELECT COUNT(DISTINCT(o.nomeautore ,o.cognomeautore)) AS nr_autori FROM opera AS o
JOIN museo m ON m.nome = o.museo AND m.citta = o.citta
