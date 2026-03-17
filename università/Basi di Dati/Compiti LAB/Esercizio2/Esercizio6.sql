SELECT * FROM public.mostra
WHERE fine >= CURRENT_DATE OR fine IS NULL  -- Se “non terminata” significa che la data di fine è ≥ oggi
ORDER BY inizio ASC, fine ASC 