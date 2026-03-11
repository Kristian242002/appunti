ALTER TABLE mostra
RENAME COLUMN prezzo TO prezzoIntero;
ALTER TABLE mostra
ADD COLUMN prezzoRidotto NUMERIC(9) default(5);
ALTER TABLE mostra
ADD CONSTRAINT controllo_prezzo
CHECK (prezzoRidotto<PrezzoIntero);