--Eseguire questa query e il popolamento per rigenerare il Database
DROP SCHEMA public CASCADE;
CREATE SCHEMA public;
GRANT ALL ON SCHEMA public TO postgres;
GRANT ALL ON SCHEMA public TO public;

--Tabelle
CREATE TABLE utente(
    utente_id integer,
    nome      varchar(100) NOT NULL,
    password  varchar(100) NOT NULL
);

ALTER TABLE utente
    add constraint utente_pk primary key(utente_id),
    add constraint unicita_nome_utente unique(nome),
    add constraint utente_id_non_negativo check(utente_id >= 0);

CREATE TABLE gruppo(
    gruppo_id integer,
    nome      varchar(100) NOT NULL,
    amministratore  integer NOT NULL
);

ALTER TABLE gruppo
    add constraint gruppo_pk primary key(gruppo_id),
    add constraint unicita_nome_gruppo unique(nome),
    add constraint gruppo_id_non_negativo check(gruppo_id >= 0),
    add constraint amministratore_fk foreign key (amministratore) reference utente(utente_id);
    on update CASCADE

CREATE TABLE membership(
    utente_id integer,
    gruppo_id integer
)

ALTER TABLE membership
    add constraint membership_pk primary key (utente_id, gruppo_id),
    add constraint membership_utente_fk foreign key (utente_id) reference utente(utente_id)
    on update CASCADE on delete CASCADE,
    add constraint membership_gruppo_fk foreign key (gruppo_id) reference gruppo(gruppo_id)
    on update CASCADE on delete CASCADE;

CREATE TABLE messaggio(
    messaggio_id serial,
    utente_id integer,
    contenuto varchar(1024),
    data
)