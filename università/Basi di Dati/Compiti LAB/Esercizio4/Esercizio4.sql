SELECT co.nome FROM corsostudi AS co
WHERE NOT EXISTS (
    SELECT * FROM inserogato AS i
    JOIN corsostudi AS co2 ON co2.id = i.id_corsostudi
    JOIN insegn AS ins ON ins.id = i.id_insegn
    WHERE ins.nomeins ILIKE '%matematica%' AND co.id = co2.id

)