/************************************************************
Langage Flux
*************************************************************/

-- Pour utiliser Flux, il faut entourer les requêtes de la façon suivante :
influx query '
from...
'
-- Liens utiles :
-- https://www.sqlpac.com/fr/documents/influxdb-passer-du-langage-influxql-au-langage-flux.html
-- https://www.sqlpac.com/fr/documents/influxdb-v2-langage-flux-guide-pratique-aide-memoire.html

/************************************************************
Requêtes simples
*************************************************************/
-- Donner les requêtes suivantes en Flux et observer les résultats :

-- 1-Afficher les données de la measurement "interieur"

from(bucket: "capteurs")
    |> range(start: 2023-11-20T00:00:00Z, stop: 2023-11-24T00:00:01Z)
    |> filter(fn: (r) => r._measurement == "interieur")

-- 2-Afficher les données des measurements "interieur" et "exterieur"

from(bucket: "capteurs")
    |> range(start: 2023-11-20T00:00:00Z, stop: 2023-11-24T00:00:01Z)
    |> filter(fn: (r) => r._measurement == "interieur" or r._measurement == "exterieur")

-- 3-Afficher time, maison, piece, temp, hum, pbcapteur, ressenti pour "interieur"

from(bucket: "capteurs")
    |> range(start: 2023-11-20T00:00:00Z, stop: 2023-11-24T00:00:01Z)
    |> filter(fn: (r) => r._measurement == "interieur")
    |> filter(fn: (r) => r._field == "temp" or r._field == "hum" or r._field == "pbcapteur" or r._field == "ressenti")
    |> pivot(rowKey: ["_time"], columnKey: ["_field"], valueColumn: "_value")
    |> keep(columns: ["_time", "maison", "piece", "temp", "hum", "pbcapteur", "ressenti"])

-- 4-Afficher uniquement time, maison, piece, temp, hum, ressenti pour "interieur"

from(bucket: "capteurs")
    |> range(start: 2023-11-20T00:00:00Z, stop: 2023-11-24T00:00:01Z)
    |> filter(fn: (r) => r._measurement == "interieur")
    |> filter(fn: (r) => r._field == "temp" or r._field == "hum" or r._field == "ressenti")
    |> pivot(rowKey: ["_time"], columnKey: ["_field"], valueColumn: "_value")
    |> keep(columns: ["_time", "maison", "piece", "temp", "hum", "ressenti"])
    |> filter(fn: (r) => r.maison == "maison1")

-- 5-Afficher time, maison, piece, temp, hum, ressenti pour les maisons 1 et 2

from(bucket: "capteurs")
    |> range(start: 2023-11-20T00:00:00Z, stop: 2023-11-24T00:00:01Z)
    |> filter(fn: (r) => r._measurement == "interieur")
    |> filter(fn: (r) => r._field == "temp" or r._field == "hum" or r._field == "ressenti")
    |> pivot(rowKey: ["_time"], columnKey: ["_field"], valueColumn: "_value")
    |> keep(columns: ["_time", "maison", "piece", "temp", "hum", "ressenti"])
    |> filter(fn: (r) => r.maison == "maison1" or r.maison == "maison2")

-- 6-Afficher time, maison, piece, temp, hum, ressenti pour la maison 1 et la cuisine

from(bucket: "capteurs")
    |> range(start: 2023-11-20T00:00:00Z, stop: 2023-11-24T00:00:01Z)
    |> filter(fn: (r) => r._measurement == "interieur")
    |> filter(fn: (r) => r._field == "temp" or r._field == "hum" or r._field == "ressenti")
    |> pivot(rowKey: ["_time"], columnKey: ["_field"], valueColumn: "_value")
    |> keep(columns: ["_time", "maison", "piece", "temp", "hum", "ressenti"])
    |> filter(fn: (r) => r.maison == "maison1" and r.piece == "cuisine")

-- 7-Afficher time, maison, piece, temp, hum, ressenti uniquement pour le 23 et le 24 novembre

from(bucket: "capteurs")
    |> range(start: 2023-11-23T00:00:00Z, stop: 2023-11-24T00:00:01Z)
    |> filter(fn: (r) => r._measurement == "interieur")
    |> filter(fn: (r) => r._field == "temp" or r._field == "hum" or r._field == "ressenti")
    |> pivot(rowKey: ["_time"], columnKey: ["_field"], valueColumn: "_value")
    |> keep(columns: ["_time", "maison", "piece", "temp", "hum", "ressenti"])

-- 8-Afficher time, maison, piece, temp, hum, ressenti pour la maison 1 et la cuisine uniquement pour le 23 et le 24 novembre

from(bucket: "capteurs")
    |> range(start: 2023-11-23T00:00:00Z, stop: 2023-11-24T00:00:01Z)
    |> filter(fn: (r) => r._measurement == "interieur")
    |> filter(fn: (r) => r._field == "temp" or r._field == "hum" or r._field == "ressenti")
    |> pivot(rowKey: ["_time"], columnKey: ["_field"], valueColumn: "_value")
    |> keep(columns: ["_time", "maison", "piece", "temp", "hum", "ressenti"])
    |> filter(fn: (r) => r.maison == "maison1" and r.piece == "cuisine")

/************************************************************
Requêtes de groupement
*************************************************************/
-- Lancer les requêtes suivantes et indiquer le nombre de groupes :
-- Q1
from(bucket: "capteurs")
    |> range(start: 2023-11-20T00:00:00Z, stop: 2023-11-24T00:00:01Z)
    |> filter(fn: (r) => r._measurement == "interieur")
    |> filter(fn: (r) => r._field == "temp" or r._field == "hum")
    |> keep(columns: ["maison", "piece", "_time", "_field", "_value"])
-- Q2
from(bucket: "capteurs")
    |> range(start: 2023-11-20T00:00:00Z, stop: 2023-11-24T00:00:01Z)
    |> filter(fn: (r) => r._measurement == "interieur")
    |> filter(fn: (r) => r._field == "temp" or r._field == "hum")
    |> keep(columns: ["maison", "piece", "_time", "_field", "_value"])
    |> toFloat()
    |> group(columns: ["maison"])
-- Q3
from(bucket: "capteurs")
    |> range(start: 2023-11-20T00:00:00Z, stop: 2023-11-24T00:00:01Z)
    |> filter(fn: (r) => r._measurement == "interieur")
    |> filter(fn: (r) => r._field == "temp" or r._field == "hum")
    |> keep(columns: ["maison", "piece", "_time", "_field", "_value"])
    |> toFloat()
    |> group(columns: ["_field"])
-- Q4
from(bucket: "capteurs")
    |> range(start: 2023-11-20T00:00:00Z, stop: 2023-11-24T00:00:01Z)
    |> filter(fn: (r) => r._measurement == "interieur")
    |> filter(fn: (r) => r._field == "temp" or r._field == "hum")
    |> keep(columns: ["maison", "piece", "_time", "_field", "_value"])
    |> toFloat()
    |> group(columns: ["_field", "maison"])
-- Q5
from(bucket: "capteurs")
    |> range(start: 2023-11-20T00:00:00Z, stop: 2023-11-24T00:00:01Z)
    |> filter(fn: (r) => r._measurement == "interieur")
    |> filter(fn: (r) => r._field == "temp" or r._field == "hum")
    |> keep(columns: ["maison", "piece", "_time", "_field", "_value"])
    |> toFloat()
    |> group()

-- Comparer les 2 langages pour les requêtes de regroupement

/************************************************************
Requêtes d'aggrégation
*************************************************************/
-- Donner les requêtes suivantes en Flux et observer les résultats :

-- 1-Afficher la moyenne de temp et de hum pour tous les groupes possibles

from(bucket: "capteurs")
    |> range(start: 2023-11-20T00:00:00Z, stop: 2023-11-24T00:00:01Z)
    |> filter(fn: (r) => r._measurement == "interieur")
    |> filter(fn: (r) => r._field == "temp" or r._field == "hum")
    |> keep(columns: ["maison", "piece", "_time", "_field", "_value"])
    |> toFloat()
    |> group()
    |> mean()

-- 2-Afficher la moyenne de temp par maison

from(bucket: "capteurs")
    |> range(start: 2023-11-20T00:00:00Z, stop: 2023-11-24T00:00:01Z)
    |> filter(fn: (r) => r._measurement == "interieur")
    |> filter(fn: (r) => r._field == "temp")
    |> keep(columns: ["maison", "piece", "_time", "_field", "_value"])
    |> toFloat()
    |> group(columns: ["maison"])

-- 3-Afficher la temp min globale

from(bucket: "capteurs")
    |> range(start: 2023-11-20T00:00:00Z, stop: 2023-11-24T00:00:01Z)
    |> filter(fn: (r) => r._measurement == "interieur")
    |> filter(fn: (r) => r._field == "temp")
    |> keep(columns: ["_value"])
    |> toFloat()
    |> min()
    
-- 4-Afficher la temp max globale

from(bucket: "capteurs")
    |> range(start: 2023-11-20T00:00:00Z, stop: 2023-11-24T00:00:01Z)
    |> filter(fn: (r) => r._measurement == "interieur")
    |> filter(fn: (r) => r._field == "temp")
    |> keep(columns: ["_value"])
    |> toFloat()
    |> max()

/************************************************************
Modification/ajout de données à l'affichage - map()
*************************************************************/
-- Lancer les requêtes suivantes et expliquer le résultat obtenu :
-- Q1
from(bucket: "capteurs")
    |> range(start: 2023-11-20T00:00:00Z, stop: 2023-11-24T00:00:01Z)
    |> filter(fn: (r) => r._measurement == "interieur")
    |> filter(fn: (r) => r._field == "temp")
    |> filter(fn: (r) => r.maison == "maison1")
    |> drop(columns: ["_start", "_stop", "_measurement", "_field"])
    |> map(fn: (r) => ({r with _value: (r._value * 1.8) + 32.0}))
-- Q2
from(bucket: "capteurs")
    |> range(start: 2023-11-20T00:00:00Z, stop: 2023-11-24T00:00:01Z)
    |> filter(fn: (r) => r._measurement == "interieur")
    |> filter(fn: (r) => r._field == "hum")
    |> filter(fn: (r) => r.maison == "maison1")
    |> drop(columns: ["_start", "_stop", "_measurement", "_field"])
    |> map(fn: (r) => ({r with state: if r._value < 80 then "ok" else "warning"}))


-- Taper la commande suivante pour sortir d'InfluxDB :
exit

