SELECT l.abbreviazione,d.discriminante,d.inizio,d.fine, COUNT(d.id) AS nr_insegnamenti FROM periododid AS d
JOIN periodolez AS l ON l.id = d.id
JOIN insinperiodo AS ip ON ip.id_periodolez = l.id
JOIN inserogato AS i ON i.id = ip.id_inserogato
WHERE d.annoaccademico = '2010/2011' AND ( d.descrizione ILIKE 'I semestre%' OR d.descrizione ILIKE 'Primo Semestre%')
GROUP BY l.abbreviazione,d.discriminante,d.inizio,d.fine
ORDER BY d.inizio,d.fine

