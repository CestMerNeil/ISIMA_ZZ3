/************************************************************
Importation de données à partir d'une tâche
*************************************************************/
-- 1-Créer une tâche "Collect airsensors data" qui va aller chercher des données d'exemple toutes les 5 minutes
-- (pensez à créer le bucket avant)
import "influxdata/influxdb/sample"
sample.data(set: "airSensor")
    |> to(bucket: "airsensorsstreaming")

-- 2-Observer les données.
-- Choisir l'heure Local pour cette partie
-- Quels sont les tags ? les fields ? (vous pouvez utiliser InfluxQL)
-- Quel est le pas de temps ?

/************************************************************
Agrégation en fonction du temps
*************************************************************/
-- Pour agréger en fonction du temps, on utilise :
    |> aggregateWindow(every: 1h, fn: mean)
-- On parle de downsampling ou réduction temporelle.
-- En effet,le principe est de diminuer le nombre de données
-- en étant moins précis. Par exemple on fait la moyenne chaque heure.

-- 3-Utiliser cette fonction pour réduire (comme vous le souhaitez)
-- le nombre de données de airsensorsstreaming
-- et observer les graphiques pour la température.

/************************************************************
Création d'alerte
*************************************************************/
-- Lors de l'installation de InfluxDB, plusieurs éléments ont été créés :
-- un bucket (mybucket),
-- un scraper qui récupère les données système toutes les 10 secondes et
-- un tableau de bord InfluxDB 2.0 OSS Metrics .

-- 4-Observez le bucket et le tableau de bord (choisir le bon bucket).

-- 5- Dans le tableau de bord, regarder la cellule montrant le nombre de buckets.
-- Afficher la requête derrière cette cellule (Configure)
-- A quoi correspond v.bucket ?

-- 6-Créer une alerte (Threshold Check) sur le nombre de buckets :
-- Mettre last en fonction d'agrégation
-- Vérifiée l'alerte toutes les 15 secondes
-- Warning si plus de 6 buckets
-- Alerte critique si plus de 8 buckets (nb de buckets à ajuster si besoin)
-- Message : 
-- L'alerte ${ r._check_name } est ${ r._level } :
-- Le nombre de bucket est ${string(v: r.counter)}.

-- 7-Vérifier que l'alerte est ok pour le moment (Alert History).
-- Puis créer des buckets jusqu'à atteindre la limite.
-- PS : Cette alerte n'a pas grand intérêt, c'est juste pour faire un exercice.
/************************************************************/
