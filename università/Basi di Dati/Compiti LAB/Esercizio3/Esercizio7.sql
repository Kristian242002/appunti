SELECT i.nomemodulo,i.modulo,ins.nomeins,d.descrizione FROM inserogato AS i
JOIN insegn AS ins ON ins.id = i.id_insegn
JOIN discriminante AS d ON d.id = i.id_discriminante
JOIN corsostudi c ON c.id = i.id_corsostudi
JOIN corsoinfacolta cf ON cf.id_corsostudi = c.id
JOIN facolta f ON f.id = cf.id_facolta
WHERE i.annoaccademico = '2010/2011' AND i.modulo > 0 AND f.nome = 'Economia'
