SELECT  co.nome , COUNT(*) AS numinsegn FROM corsostudi AS co
JOIN inserogato AS i ON i.id_corsostudi = co.id
JOIN facolta AS f ON f.id = i.id_facolta
WHERE annoaccademico = '2010/2011' AND i.hamoduli!='0' AND i.modulo = 0 AND f.nome NOT LIKE 'Medicina e Chirurgia'
GROUP BY co.nome
ORDER BY co.nome
