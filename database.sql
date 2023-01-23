--Eseguire questa query e il popolamento per rigenerare il Database
DROP SCHEMA public CASCADE;
CREATE SCHEMA public;
GRANT ALL ON SCHEMA public TO postgres;
GRANT ALL ON SCHEMA public TO public;

--Tabelle
CREATE TABLE utente(
    nome      varchar(100) NOT NULL,
    password  varchar(100) NOT NULL, 
    connessione    integer
);

ALTER TABLE utente
    add constraint utente_pk primary key(nome),
    add constraint unicita_nome_password unique (nome, password);

CREATE TABLE gruppo(
    nome      varchar(100) NOT NULL,
    amministratore  varchar(100) NOT NULL
);

ALTER TABLE gruppo
    add constraint gruppo_pk primary key(nome),
    add constraint amministratore foreign key (amministratore) references utente(nome)
    on update CASCADE;

CREATE TABLE membership(
    nome_utente varchar(100),
    nome_gruppo varchar(100)
);

ALTER TABLE membership
    add constraint membership_pk primary key (nome_utente, nome_gruppo),
    add constraint membership_utente_fk foreign key (nome_utente) references utente(nome)
    on update CASCADE on delete CASCADE,
    add constraint membership_gruppo_fk foreign key (nome_gruppo) references gruppo(nome)
    on update CASCADE on delete CASCADE;

CREATE TABLE messaggio(
    messaggio_id serial,
    nome_utente varchar(100) NOT NULL,
    nome_gruppo varchar(100) NOT NULL,
    contenuto varchar(1024) NOT NULL,
    minutaggio bigint NOT NULL
);

ALTER TABLE messaggio
    add constraint messaggio_pk primary key (messaggio_id),
    add constraint minutaggio_positivo check (minutaggio > 0),
    add constraint messaggio_utente_fk foreign key (nome_utente) references utente(nome)
    on update CASCADE,
    add constraint messaggio_gruppo_fk foreign key (nome_gruppo) references gruppo(nome)
    on update CASCADE on delete CASCADE;

CREATE TABLE notifica(
    nome_utente varchar(100) NOT NULL,
    nome_gruppo varchar(100) NOT NULL
);

ALTER TABLE notifica
    add constraint notifica_pk primary key (nome_utente, nome_gruppo),
    add constraint notifica_utente_notificante_fk foreign key (nome_utente) references utente(nome)
    on update CASCADE on delete CASCADE,
    add constraint notifica_gruppo_fk foreign key (nome_gruppo) references gruppo(nome)
    on update CASCADE on delete CASCADE;
