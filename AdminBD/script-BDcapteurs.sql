SET default_storage_engine=InnoDB;
DROP DATABASE IF EXISTS BDcapteurs;
CREATE DATABASE BDcapteurs;
USE BDcapteurs;

CREATE TABLE isolation(
niveau INT(3) PRIMARY KEY,
nom VARCHAR(20)
);

CREATE TABLE maison(
id VARCHAR(50) PRIMARY KEY,
centreville BOOLEAN,
anneeconstruction INT(4),
isolation INT(3),
ville VARCHAR(50),
FOREIGN KEY (isolation) REFERENCES isolation (niveau)
);

INSERT INTO isolation VALUES
(0, 'mal isolee'),
(1, 'peu isolee'),
(2, 'bien isolee');

INSERT INTO maison VALUES
('maison1', 1, 2004, 2, 'clermont'),
('maison2', 0, 2022, 1, 'clermont'),
('maison3', 1, 1995, 2, 'paris');

COMMIT;
