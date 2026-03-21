SELECT annoaccademico,MAX(crediti) AS numero_crediti_max,MIN(crediti) AS numero_crediti_min FROM inserogato
GROUP BY annoaccademico


