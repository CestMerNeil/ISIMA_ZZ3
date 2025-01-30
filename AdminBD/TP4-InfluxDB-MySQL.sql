-- Relancer les commandes pour redémarrer les containers Docker :
-- si besoin : docker-rootless-init.sh
-- (si pb : ouvrir une console, lancer la commande systemctl --user stop docker.service puis relancer la commande docker-rootless-init.sh)
-- si besoin : git clone https://gitlab.isima.fr/maagier/influxdb-mysql.git
cd influxdb-mysql
docker compose up -d
-- Refaire rapidement le TP1-InfluxDB.sql

/************************************************************
Requêter une base SQL
*************************************************************/
-- 1-Créer la base de données BDcapteurs sous MySQL à partir du script sql.
-- Pour aller sur MySQL :
docker exec -it mysql bash
mysql -u root -p
root
Puis création de la bd
exit puis exit pour sortir

-- 2-Lancer les requêtes suivantes pour interroger la BD avec Flux :
docker exec -it influxdb /bin/bash

influx query '
import "sql"
sql.from(
    driverName: "mysql",
    dataSourceName: "root:root@tcp(mysql)/BDcapteurs",
    query: "SELECT * FROM maison",
)
'
-- mysql ici est le nom du container

influx query '
import "sql"
sql.from(
    driverName: "mysql",
    dataSourceName: "root:root@tcp(mysql)/BDcapteurs",
    query: "SELECT * FROM isolation",
)
'

-- Pour éviter de marquer le user et le password en dur dans le code,
-- on peut créer 2 variables Secrets (qui seront visibles dans l'interface : http://localhost:8086/   Settings/Secrets).
-- 3-Lancer la requête suivante :
influx secret update -k MYSQL_USER
influx secret update -k MYSQL_PASS
influx secret update -k MYSQL_USER -v root
influx secret update -k MYSQL_PASS -v root
influx query '
import "sql"
import "influxdata/influxdb/secrets"
MYSQL_USER = secrets.get(key: "MYSQL_USER")
MYSQL_PASS = secrets.get(key: "MYSQL_USER")
sql.from(
    driverName: "mysql",
    dataSourceName: "${MYSQL_USER}:${MYSQL_PASS}@tcp(mysql)/BDcapteurs",
    query: "SELECT * FROM maison",
)
'
/************************************************************
Jointures entre tables MySQL et buckets InfluxDB 
*************************************************************/
-- 1-Lancer et observer la requête suivante qui fait la jointure entre le bucket capteurs et la table maison :
influx query '
import "join"
import "sql"
import "influxdata/influxdb/secrets"
MYSQL_USER = secrets.get(key: "MYSQL_USER")
MYSQL_PASS = secrets.get(key: "MYSQL_PASS")
capteurs = from(bucket: "capteurs")
    |> range(start: 2023-11-20T00:00:00Z, stop: 2023-11-24T00:00:01Z)
    |> filter(fn: (r) => r._measurement == "interieur")
    |> filter(fn: (r) => r._field == "temp")
    |> keep(columns: ["maison", "piece", "_time", "_value"])
    |> group()
maisons = sql.from(
    driverName: "mysql",
    dataSourceName: "${MYSQL_USER}:${MYSQL_PASS}@tcp(mysql)/BDcapteurs",
    query: "SELECT id, ville FROM maison",
)
join.left(
    left: capteurs,
    right: maisons,
    on: (l, r) => l.maison == r.id,
    as: (l, r) => ({l with ville: r.ville}),
)
'

-- 2-Créer la requête qui fait la jointure entre le bucket capteurs, la table maison et la table isolation.

influx query '
import "join"
import "sql"
import "influxdata/influxdb/secrets"

MYSQL_USER = secrets.get(key: "MYSQL_USER")
MYSQL_PASS = secrets.get(key: "MYSQL_PASS")

capteurs = from(bucket: "capteurs")
    |> range(start: 2023-11-20T00:00:00Z, stop: 2023-11-24T00:00:01Z)
    |> filter(fn: (r) => r._measurement == "interieur")
    |> filter(fn: (r) => r._field == "temp")
    |> keep(columns: ["maison", "piece", "_time", "_value", "isolation"])
    |> group()

maisons = sql.from(
    driverName: "mysql",
    dataSourceName: "${MYSQL_USER}:${MYSQL_PASS}@tcp(mysql)/BDcapteurs",
    query: "SELECT id, ville, isolation FROM maison"
)

isolation = sql.from(
    driverName: "mysql",
    dataSourceName: "${MYSQL_USER}:${MYSQL_PASS}@tcp(mysql)/BDcapteurs",
    query: "SELECT niveau, nom FROM isolation"
)

maison_cap = join.left(
    left: capteurs,
    right: maisons,
    on: (l, r) => l.maison == r.id,
    as: (l, r) => ({
        l with 
        ville: r.ville,
        iso_niveau: r.isolation
    })
)

final_result = join.left(
    left: maison_cap,
    right: isolation,
    on: (l, r) => l.iso_niveau == r.niveau,
    as: (l, r) => ({
        l with
        isolation_type: r.nom
    })
)

final_result
'

-- 3-Grouper les données par maison et pièce et ajouter un filtre permettant de ne garder que les maisons peu isolées.
-- Ajouter à la fin :
--     |> group(...)
--     |> filter(...)

influx query '
import "join"
import "sql"
import "influxdata/influxdb/secrets"

MYSQL_USER = secrets.get(key: "MYSQL_USER")
MYSQL_PASS = secrets.get(key: "MYSQL_PASS")

capteurs = from(bucket: "capteurs")
    |> range(start: 2023-11-20T00:00:00Z, stop: 2023-11-24T00:00:01Z)
    |> filter(fn: (r) => r._measurement == "interieur")
    |> filter(fn: (r) => r._field == "temp")
    |> keep(columns: ["maison", "piece", "_time", "_value", "isolation"])
    |> group()

maison = sql.from(
    driverName: "mysql",
    dataSourceName: "${MYSQL_USER}:${MYSQL_PASS}@tcp(mysql)/BDcapteurs",
    query: "SELECT id, ville, isolation FROM maison"
)

isolation = sql.from(
    driverName: "mysql",
    dataSourceName: "${MYSQL_USER}:${MYSQL_PASS}@tcp(mysql)/BDcapteurs",
    query: "SELECT niveau, nom FROM isolation"
)

maison_cap = join.left(
    left: capteurs,
    right: maison,
    on: (l, r) => l.maison == r.id,
    as: (l, r) => ({
        l with
        ville: r.ville,
        iso_niveau: r.isolation
    })
)

final_result = join.left(
    left: maison_cap,
    right: isolation,
    on: (l, r) => l.iso_niveau == r.niveau,
    as: (l, r) => ({
        l with
        isolation_type: r.nom
    })
)

final_result
  |> group(columns: ["maison", "piece"])
  |> filter(fn: (r) => r.isolation_type == "peu isolee")
'

/************************************************************
Création de dashboard
************************************************************/
-- 1-Retourner sur l'interface http://localhost:8086/ puis créer un dashboard nommé "DBcapteurs".



-- 2-Créer une cellule "graphique 1" avec la requête suivante :
--  	Taper la requête dans le SCRIPT EDITOR
--		Choisir l'heure UTC pour cette partie
-- 		Choisir la bonne plage de temps pour l'affichage
-- 		Cliquer sur SUBMIT pour voir le graphique
-- 		View Raw Data permet de voir les données plutôt que le graphique
-- 		CSV permet de voir toutes les données d'un coup d'oeil

--      (bien valider la cellule lorsque l'affichage est correct)

from(bucket: "capteurs")
    |> range(start: v.timeRangeStart, stop: v.timeRangeStop)
    |> filter(fn: (r) => r._measurement == "interieur")
    |> filter(fn: (r) => r._field == "temp")
    |> filter(fn: (r) => r.maison == "maison1")
    |> keep(columns: ["maison", "piece", "_time", "_value"])

-- 3-Dans Settings, créer une variable (nom : maison, type : query) avec les valeurs suivantes :
import "influxdata/influxdb/schema"
schema.tagValues(bucket: "capteurs", tag: "maison", start: 0)

-- 4-Remplacer dans la requête "maison1" par v.maison et tester la variable.
  |> filter(fn: (r) => r.maison == v.maison)

influx query '
import "join"
import "sql"
import "influxdata/influxdb/secrets"

MYSQL_USER = secrets.get(key: "MYSQL_USER")
MYSQL_PASS = secrets.get(key: "MYSQL_PASS")

capteurs = from(bucket: "capteurs")
    |> range(start: 2023-11-20T00:00:00Z, stop: 2023-11-24T00:00:01Z)
    |> filter(fn: (r) => r._measurement == "interieur")
    |> filter(fn: (r) => r._field == "temp")
    |> keep(columns: ["maison", "piece", "_time", "_value", "isolation"])
    |> group()

maison = sql.from(
    driverName: "mysql",
    dataSourceName: "${MYSQL_USER}:${MYSQL_PASS}@tcp(mysql)/BDcapteurs",
    query: "SELECT id, ville, isolation FROM maison"
)

isolation = sql.from(
    driverName: "mysql",
    dataSourceName: "${MYSQL_USER}:${MYSQL_PASS}@tcp(mysql)/BDcapteurs",
    query: "SELECT niveau, nom FROM isolation"
)

maison_cap = join.left(
    left: capteurs,
    right: maison,
    on: (l, r) => l.maison == r.id,
    as: (l, r) => ({
        l with
        ville: r.ville,
        iso_niveau: r.isolation
    })
)

final_result = join.left(
    left: maison_cap,
    right: isolation,
    on: (l, r) => l.iso_niveau == r.niveau,
    as: (l, r) => ({
        l with
        isolation_type: r.nom
    })
)

final_result
  |> group(columns: ["maison", "piece"])
  |> filter(fn: (r) => r.maison == "maison1")
'

-- 5-De la même façon, créer une cellule "graphique 2" avec le résultat de la double jointure créée précédemment dans la partie 2.
-- pour le range, mettre :
-- |> range(start: v.timeRangeStart, stop: v.timeRangeStop)

influx query '
import "join"
import "sql"
import "influxdata/influxdb/secrets"

MYSQL_USER = secrets.get(key: "MYSQL_USER")
MYSQL_PASS = secrets.get(key: "MYSQL_PASS")

capteurs = from(bucket: "capteurs")
    |> range(start: 2023-11-20T00:00:00Z, stop: 2023-11-24T00:00:01Z)
    |> filter(fn: (r) => r._measurement == "interieur")
    |> filter(fn: (r) => r._field == "temp")
    |> keep(columns: ["maison", "piece", "_time", "_value", "isolation"])
    |> group()

maison = sql.from(
    driverName: "mysql",
    dataSourceName: "${MYSQL_USER}:${MYSQL_PASS}@tcp(mysql)/BDcapteurs",
    query: "SELECT id, ville, isolation FROM maison"
)

isolation = sql.from(
    driverName: "mysql",
    dataSourceName: "${MYSQL_USER}:${MYSQL_PASS}@tcp(mysql)/BDcapteurs",
    query: "SELECT niveau, nom FROM isolation"
)

maison_cap = join.left(
    left: capteurs,
    right: maison,
    on: (l, r) => l.maison == r.id,
    as: (l, r) => ({
        l with
        ville: r.ville,
        iso_niveau: r.isolation
    })
)

final_result = join.left(
    left: maison_cap,
    right: isolation,
    on: (l, r) => l.iso_niveau == r.niveau,
    as: (l, r) => ({
        l with
        isolation_type: r.nom
    })
)

final_result
  |> range(start: 2023-11-20T00:00:00Z, stop: 2023-11-24T00:00:01Z)
  |> group(columns: ["maison", "piece"])
'

-- 6-A partir du Data Explorer (SCRIPT EDITOR), créer une requête qui affiche les différentes valeurs d'isolation (peu isolée...)
-- et renommer le résultat en "_value" avec |> rename(columns: { ... : "_value"})
influx query '
import "join"
import "sql"
import "influxdata/influxdb/secrets"

MYSQL_USER = secrets.get(key: "MYSQL_USER")
MYSQL_PASS = secrets.get(key: "MYSQL_PASS")

capteurs = from(bucket: "capteurs")
    |> range(start: 2023-11-20T00:00:00Z, stop: 2023-11-24T00:00:01Z)
    |> filter(fn: (r) => r._measurement == "interieur")
    |> filter(fn: (r) => r._field == "temp")
    |> keep(columns: ["maison", "piece", "_time", "_value", "isolation"])
    |> group()

maison = sql.from(
    driverName: "mysql",
    dataSourceName: "${MYSQL_USER}:${MYSQL_PASS}@tcp(mysql)/BDcapteurs",
    query: "SELECT id, ville, isolation FROM maison"
)

isolation = sql.from(
    driverName: "mysql",
    dataSourceName: "${MYSQL_USER}:${MYSQL_PASS}@tcp(mysql)/BDcapteurs",
    query: "SELECT niveau, nom FROM isolation"
)

maison_cap = join.left(
    left: capteurs,
    right: maison,
    on: (l, r) => l.maison == r.id,
    as: (l, r) => ({
        l with
        ville: r.ville,
        iso_niveau: r.isolation
    })
)

final_result = join.left(
    left: maison_cap,
    right: isolation,
    on: (l, r) => l.iso_niveau == r.niveau,
    as: (l, r) => ({
        l with
        isolation_type: r.nom
    })
)

final_result
  |> range(start: 2023-11-20T00:00:00Z, stop: 2023-11-24T00:00:01Z)
  |> group(columns: ["maison", "piece"])
  |> rename(columns: {piece: "WARMACHINECOWABUNGA"})
'

-- 7-Créer une variable (nom : isolation, type : query) avec la requête précédente.

-- 8-Utiliser la variable dans la requête et tester la variable.

-- 9-Ajouter une autre cellule de votre choix au tableau de bord.
