DELETE FROM utente
DELETE FROM gruppo
DELETE FROM membership
DELETE FROM messaggio
DELETE FROM notifica

--Inserimenti in utente
INSERT INTO utente
VALUES
('Alessandro','pass1'),
('Oleksandr','pass2'),
('Patroccio','pass3'),
('Pietroclo','pass4'),
('Pino','pass5'),
('Utente','pass6'),
('Eoliche','pass7'),
('Uffi','pass8')

--Inserimenti in gruppi
INSERT INTO gruppo
VALUES
('Gruppo1','Alessandro'),
('Gruppo2','Pino'),
('Gruppo3','Oleksandr'),
('Pale','Eoliche'),
('Mondo','Alessandro')

INSERT INTO membership
VALUES
('Utente','Gruppo1'),
('Eoliche','Mondo'),
('Alessandro','Mondo'),
('Pino','Mondo'),
('Oleksandr','Mondo'),
('Eoliche','Gruppo3')

INSERT INTO messaggio (nome_utente,nome_gruppo,contenuto,minutaggio)
VALUES
('Eoliche','Mondo','Che palle eoliche',1),
('Utente','Gruppo1','Ciao',2),
('Alessandro','Mondo','Salve',3)

INSERT INTO notifica
VALUES
('Uffi','Mondo'),
('Patroccio','Gruppo1'),
('Pino','Mondo')