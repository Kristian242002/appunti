SELECT titolo || '-' ||citta as mostra FROM mostra -- L'operatore || || serve per concatenare
WHERE titolo LIKE 'R%' -- % serve per dire tutte le stringhe che iniziano con R