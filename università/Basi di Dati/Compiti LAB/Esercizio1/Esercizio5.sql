ALTER TABLE museo ADD COLUMN sitointernet CHARACTER VARYING(50);
UPDATE museo
SET sitoInternet = 'www.arena.it' WHERE nome = 'Arena';
UPDATE Museo
SET sitoInternet = 'www.castelvecchio.it' WHERE nome = 'CastelVecchio';