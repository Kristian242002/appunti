SELECT titolo,fine - CURRENT_DATE as giorniMancanti FROM mostra
WHERE fine >= CURRENT_DATE AND inizio <= CURRENT_DATE