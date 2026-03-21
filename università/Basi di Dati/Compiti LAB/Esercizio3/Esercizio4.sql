SELECT  DISTINCT c.nome,c.codice,c.abbreviazione FROM corsostudi AS c -- nb anche qua distinct perchè un corso puo venir gestito da piu facolta
JOIN corsoinfacolta AS cf ON cf.id_corsostudi = c.id
JOIN facolta AS f ON cf.id_facolta = f.id
WHERE f.nome = 'Medicina e Chirurgia';