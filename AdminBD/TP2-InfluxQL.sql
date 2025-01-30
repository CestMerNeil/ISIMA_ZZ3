/************************************************************
Langage InfluxQL
*************************************************************/

-- Taper d'abord la commande suivante pour pouvoir lancer des requêtes InfluxQL :
influx v1 shell

/************************************************************
Observer le schéma des données
*************************************************************/
-- Taper les requêtes suivantes pour voir
-- les buckets, les measurements, les tags et les fields :

format column
SHOW DATABASES
use "capteurs"
SHOW MEASUREMENTS
SHOW FIELD KEYS FROM "interieur"
SHOW TAG KEYS FROM "interieur"
SHOW TAG VALUES WITH KEY = "piece"

/************************************************************
Requêtes simples (SELECT, FROM, WHERE par tag ou time)
*************************************************************/
-- Donner les requêtes suivantes en InfluxQL et observer les résultats :

-- 1-Afficher les données de la measurement "interieur"

SELECT * FROM "interieur"

-- 2-Afficher les données des measurements "interieur" et "exterieur"

SELECT * FROM "interieur", "exterieur"

-- 3-Afficher time, maison, piece, temp, hum, pbcapteur, ressenti pour "interieur"

SELECT time, maison, piece, temp, hum, pbcapteur, ressenti FROM "interieur"

-- 4-Afficher uniquement time, maison, piece, temp, hum, ressenti pour "interieur"

SELECT time, maison, piece, temp, hum, ressenti FROM "interieur" WHERE maison = 'maison1'

-- 5-Afficher time, maison, piece, temp, hum, ressenti pour les maisons 1 et 2

SELECT time, maison, piece, temp, hum, ressenti FROM "interieur" WHERE maison = 'maison1' OR maison = 'maison2'

-- 6-Afficher time, maison, piece, temp, hum, ressenti pour la maison 1 et la cuisine

SELECT time, maison, piece, temp, hum, ressenti FROM "interieur" WHERE maison = 'maison1' AND piece = 'cuisine'

-- 7-Afficher time, maison, piece, temp, hum, ressenti uniquement pour le 23 et le 24 novembre

SELECT time, maison, piece, temp, hum, ressenti FROM "interieur" WHERE time >= 1700654400 AND time < 1700784000

-- 8-Afficher time, maison, piece, temp, hum, ressenti pour la maison 1 et la cuisine uniquement pour le 23 et le 24 novembre

SELECT time, maison, piece, temp, hum, ressenti FROM "interieur" WHERE maison = 'maison1' AND piece = 'cuisine' AND time >= 1700654400 AND time < 1700784000

/************************************************************
Requêtes de groupement
*************************************************************/
-- Lancer les requêtes suivantes et indiquer le nombre de groupes :
-- Q1
SELECT time, maison, piece, temp, hum FROM "interieur"
-- Q2
SELECT time, maison, piece, temp, hum FROM "interieur" GROUP BY maison 
-- Q3
SELECT time, maison, piece, temp, hum FROM "interieur" GROUP BY maison, piece
-- Q4
SELECT time, maison, piece, temp, hum FROM "interieur" GROUP BY *

/************************************************************
Requêtes d'aggrégation
*************************************************************/
-- Donner les requêtes suivantes en InfluxQL et observer les résultats :

-- 1-Afficher la moyenne de temp et de hum pour tous les groupes possibles

SELECT mean(temp), mean(hum) FROM "interieur" GROUP BY *

-- 2-Afficher la moyenne de temp par maison

SELECT mean(temp) FROM "interieur" GROUP BY maison

-- 3-Afficher la temp min globale

SELECT min(temp) FROM "interieur"

-- 4-Afficher la temp max globale

SELECT max(temp) FROM "interieur"


-- Taper la commande suivante pour sortir du shell InfluxQL :
ctrl+D
