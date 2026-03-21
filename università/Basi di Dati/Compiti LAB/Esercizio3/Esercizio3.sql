SELECT DISTINCT c.nome, f.nome FROM corsostudi c -- uso di DISTINCT perchè un corso ha piu insegnamenti
JOIN inserogato i ON c.id = i.id_corsostudi
JOIN corsoinfacolta cf ON c.id = cf.id_corsostudi
JOIN facolta f ON f.id = cf.id_facolta
WHERE i.annoaccademico = '2010/2011'
ORDER BY c.nome