SELECT DISTINCT i.id_insegn  FROM corsostudi AS c
JOIN inserogato AS i ON i.id_corsostudi = c.id
WHERE c.id = 4 AND i.modulo=0 AND NOT EXISTS (
	SELECT * FROM inserogato AS i2
	JOIN insinperiodo AS ip2 ON ip2.id_inserogato = i2.id
	JOIN periodolez AS p2 ON p2.id = ip2.id_periodolez
	WHERE p2.abbreviazione LIKE '2%' AND i2.id_corsostudi = c.id AND i2.id_insegn = i.id_insegn
)
