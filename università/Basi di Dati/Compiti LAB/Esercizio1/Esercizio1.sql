-- dominio
CREATE DOMAIN Giorno AS CHAR(3)
CHECK (VALUE IN ('LUN','MAR','MER','GIO','VEN','SAB','DOM'));
-- tabelle
CREATE TABLE Museo(
	nome CHARACTER VARYING(30) default 'MuseoVeronese',
	citta CHARACTER VARYING(20) default 'Verona',
	indirizzo CHARACTER VARYING(50),
	numeroTelefono CHARACTER VARYING(12),
	giornoChiusura CHARACTER(3) not null,
	prezzo NUMERIC(9) default 10 not null,

	PRIMARY KEY(nome,citta)
);
CREATE TABLE Opera(
	nome CHARACTER VARYING(30),
	cognomeAutore CHARACTER VARYING(20),
	nomeAutore CHARACTER VARYING(20),
	museo CHARACTER VARYING(30) NOT NULL, -- NOT NULL per evitare opere senza museo
	citta CHARACTER VARYING(20) NOT NULL, -- NOT NULL per evitare opere senza museo
	epoca CHARACTER VARYING(20),
	anno NUMERIC(4),

	PRIMARY KEY (nome,cognomeAutore,nomeAutore),
	FOREIGN KEY (museo,citta) REFERENCES Museo(nome,citta)
	
);
CREATE TABLE Mostra(
	titolo CHARACTER VARYING(30),
	inizio DATE,
	fine DATE NOT NULL,
	museo CHARACTER VARYING(30) NOT NULL,
	citta CHARACTER VARYING(20) NOT NULL,
	prezzo NUMERIC(9) NOT NULL,

	PRIMARY KEY(titolo,inizio),
	FOREIGN KEY(museo,citta) REFERENCES Museo(nome,citta)
);
CREATE TABLE Orario(
	progressivo INTEGER,
	museo CHARACTER VARYING(30) NOT NULL,
	citta CHARACTER VARYING(20) NOT NULL,
	giorno CHARACTER(3),
	orarioApertura TIME WITH TIME ZONE default '09:00 CET',
	orarioChiusura TIME WITH TIME ZONE default '19:00 CET',

	PRIMARY KEY(progressivo),
	FOREIGN KEY(museo,citta) REFERENCES Museo(nome,citta)
	
);
