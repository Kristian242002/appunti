SELECT DISTINCT I.nomeins, IE.nomeunita
FROM Insegn I JOIN InsErogato IE ON I.id = IE.id_insegn
WHERE IE.id IN (
 SELECT IE.id
 FROM InsErogato IE JOIN Lezione L ON IE.id = L.id_inserogato
 WHERE IE.id_corsostudi = 420
 AND IE.annoaccademico = '2010/2011'
 AND IE.modulo < 0
 AND (L.giorno = 2 OR L.giorno = 3)

 EXCEPT

 SELECT ie.id
 FROM InsErogato IE JOIN Lezione L1 ON IE.id =
L1.id_inserogato
 JOIN Lezione L2 ON IE.id = L2.id_inserogato
 WHERE IE.id_corsostudi = 420
 AND IE.annoaccademico = '2010/2011'
 AND IE.modulo < 0
 AND (L1.giorno = 2 AND L2.giorno = 3)
)
ORDER BY nomeins;
