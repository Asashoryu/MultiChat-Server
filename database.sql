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
    add constraint amministratore_fk foreign key (amministratore) references utente(utente_id)
    on update CASCADE;

CREATE TABLE membership(
    utente_id integer,
    gruppo_id integer
);

ALTER TABLE membership
    add constraint membership_pk primary key (utente_id, gruppo_id),
    add constraint membership_utente_fk foreign key (utente_id) references utente(utente_id)
    on update CASCADE on delete CASCADE,
    add constraint membership_gruppo_fk foreign key (gruppo_id) references gruppo(gruppo_id)
    on update CASCADE on delete CASCADE;

CREATE TABLE messaggio(
    messaggio_id serial,
    utente_notificante_id integer NOT NULL,
    contenuto varchar(1024) NOT NULL,
    minutaggio bigint NOT NULL,
    gruppo_id integer NOT NULL
);

ALTER TABLE messaggio
    add constraint messaggio_pk primary key (messaggio_id),
    add constraint messaggio_utente_fk foreign key (utente_notificante_id) references utente(utente_id)
    on update CASCADE,
    add constraint minutaggio_positivo check (minutaggio > 0),
    add constraint messaggio_gruppo_fk foreign key (gruppo_id) references gruppo(gruppo_id)
    on update CASCADE on delete CASCADE;

CREATE TABLE notifica(
    notifica_id serial,
    gruppo_id integer NOT NULL
);

ALTER TABLE notifica
    add constraint notifica_pk primary key (notifica_id),
    add constraint notifica_gruppo_fk foreign key (gruppo_id) references gruppo(gruppo_id)
    on update CASCADE on delete CASCADE;

    