SELECT codice,nome,abbreviazione FROM corsostudi
WHERE nome ILIKE '%lingue%' -- Le due percentuali servono per tipo dirti 'qualsiasi sequenza di carrateri'