/************************************************************
Initialisation de InfluxDB
*************************************************************/
-- Accéder à l'interface d'InfluxDB : http://localhost:8086/
-- Et cliquer sur GET STARTED

-- Créer un utilisateur :
-- aoxie
-- un mot de passe simple: influxdb
-- Initial Organization Name : myorga
-- Initial Bucket Name : mybucket
-- Cliquer sur CONTINUE

-- Copier bien votre token ici puis cliquer sur QUICK START :
k5S7vC20tSk8i54I0wR3TYo1WRVO5rCfeS3BJLn0Qie7NweW12jDW2OFHriiBxiGPHGX3S2SE0ywxnPTtErScg==

/************************************************************
Création d'un bucket et insertion de données
*************************************************************/

-- Cliquer sur la flèche tout en bas à gauche pour voir tout le menu sur la partie gauche.
-- Créer un bucket nommé "capteurs" :
-- Load Data > BUCKETS > + CREATE BUCKET (NEVER).

-- Nous allons maintenant insérer des données dans le bucket "capteurs" :
-- Load Data > Buckets > capteurs > ADD DATA > Line Protocol > ENTER MANUALLY
-- Spécifier bien la précision (secondes)
-- Copier/coller les données suivantes :

exterieur,ville=clermont temp=18.2,temps="nuageux" 1700481600
exterieur,ville=clermont temp=22.1,temps="soleil" 1700568000
exterieur,ville=clermont temp=23.4,temps="soleil" 1700654400
exterieur,ville=clermont temp=17.1,temps="pluie" 1700740800
exterieur,ville=clermont temp=18.4,temps="soleil" 1700827200
exterieur,ville=paris temp=23.0,temps="soleil" 1700481600
exterieur,ville=paris temp=22.2,temps="soleil" 1700568000
exterieur,ville=paris temp=23.5,temps="soleil" 1700654400
exterieur,ville=paris temp=17.9,temps="nuageux" 1700740800
exterieur,ville=paris temp=15.2,temps="nuageux" 1700827200
interieur,maison=maison1,piece=chambre temp=18.8,hum=90i,pbcapteur=f,ressenti="bien" 1700438400
interieur,maison=maison1,piece=chambre temp=19.9,hum=38i,pbcapteur=f,ressenti="chaud" 1700524800
interieur,maison=maison1,piece=chambre temp=20.4,hum=55i,pbcapteur=f,ressenti="chaud" 1700611200
interieur,maison=maison1,piece=chambre temp=14.5,hum=78i,pbcapteur=t,ressenti="froid" 1700697600
interieur,maison=maison1,piece=chambre temp=24.4,hum=13i,pbcapteur=f,ressenti="froid" 1700784000
interieur,maison=maison1,piece=cuisine temp=21.2,hum=30i,pbcapteur=f,ressenti="bien" 1700438400
interieur,maison=maison1,piece=cuisine temp=20.4,hum=79i,pbcapteur=f,ressenti="bien" 1700524800
interieur,maison=maison1,piece=cuisine temp=23.9,hum=38i,pbcapteur=f,ressenti="bien" 1700611200
interieur,maison=maison1,piece=cuisine temp=24.1,hum=59i,pbcapteur=f,ressenti="froid" 1700697600
interieur,maison=maison1,piece=cuisine temp=22.7,hum=19i,pbcapteur=f,ressenti="bien" 1700784000
interieur,maison=maison2,piece=chambre temp=22.7,hum=75i,pbcapteur=f,ressenti="bien" 1700438400
interieur,maison=maison2,piece=chambre temp=25.4,hum=94i,pbcapteur=f,ressenti="bien" 1700524800
interieur,maison=maison2,piece=chambre temp=20.0,hum=22i,pbcapteur=f,ressenti="froid" 1700611200
interieur,maison=maison2,piece=chambre temp=22.7,hum=17i,pbcapteur=f,ressenti="bien" 1700697600
interieur,maison=maison2,piece=chambre temp=23.4,hum=85i,pbcapteur=f,ressenti="chaud" 1700784000
interieur,maison=maison2,piece=cuisine temp=24.6,hum=29i,pbcapteur=f,ressenti="chaud" 1700438400
interieur,maison=maison2,piece=cuisine temp=20.7,hum=14i,pbcapteur=f,ressenti="bien" 1700524800
interieur,maison=maison2,piece=cuisine temp=15.1,hum=91i,pbcapteur=t,ressenti="froid" 1700611200
interieur,maison=maison2,piece=cuisine temp=19.0,hum=72i,pbcapteur=f,ressenti="bien" 1700697600
interieur,maison=maison2,piece=cuisine temp=20.2,hum=92i,pbcapteur=f,ressenti="chaud" 1700784000
interieur,maison=maison3,piece=chambre temp=21.4,hum=90i,pbcapteur=f,ressenti="bien" 1700438400
interieur,maison=maison3,piece=chambre temp=19.2,hum=47i,pbcapteur=f,ressenti="froid" 1700524800
interieur,maison=maison3,piece=chambre temp=25.3,hum=73i,pbcapteur=f,ressenti="bien" 1700611200
interieur,maison=maison3,piece=chambre temp=23.3,hum=45i,pbcapteur=f,ressenti="chaud" 1700697600
interieur,maison=maison3,piece=chambre temp=21.6,hum=50i,pbcapteur=f,ressenti="froid" 1700784000
interieur,maison=maison3,piece=cuisine temp=24.2,hum=69i,pbcapteur=f,ressenti="chaud" 1700438400
interieur,maison=maison3,piece=cuisine temp=23.2,hum=10i,pbcapteur=f,ressenti="bien" 1700524800
interieur,maison=maison3,piece=cuisine temp=25.3,hum=13i,pbcapteur=f,ressenti="chaud" 1700611200
interieur,maison=maison3,piece=cuisine temp=22.5,hum=48i,pbcapteur=f,ressenti="froid" 1700697600
interieur,maison=maison3,piece=cuisine temp=18.4,hum=24i,pbcapteur=f,ressenti="froid" 1700784000

-- Cliquer sur WRITE DATA
-- (Il est aussi possible d'utiliser InfluxQL ou Flux pour insérer des données.)

-- Quelques infos :
-- Types des tags : string
-- Types des fields :
  -- float par défaut
  -- i : entier
  -- entre guillemets : string
  -- t/f : booleen

-- Correspondance des timestamps pour interieur :
-- 1700438400 --> 2023-11-20T00:00:00Z
-- 1700524800 --> 2023-11-21T00:00:00Z
-- 1700611200 --> 2023-11-22T00:00:00Z
-- 1700697600 --> 2023-11-23T00:00:00Z
-- 1700784000 --> 2023-11-24T00:00:00Z

-- Correspondance des timestamps pour exterieur :
-- 1700481600 --> 2023-11-20T12:00:00Z
-- 1700568000 --> 2023-11-21T12:00:00Z
-- 1700654400 --> 2023-11-22T12:00:00Z
-- 1700740800 --> 2023-11-23T12:00:00Z
-- 1700827200 --> 2023-11-24T12:00:00Z


/************************************************************
Utilisation de la ligne de commande InfluxDB
*************************************************************/

-- Lancer la commande suivante pour utiliser la ligne de commande InfluxDB :
docker exec -it influxdb /bin/bash
--influxdb ici est le nom du container

-- Créer une configuration pour éviter de passer les infos avec chaque commande
-- Copier coller votre token entre les guillemets :
influx config create --config-name local-config \
  --host-url "http://localhost:8086" \
  --org myorga \
  --token "k5S7vC20tSk8i54I0wR3TYo1WRVO5rCfeS3BJLn0Qie7NweW12jDW2OFHriiBxiGPHGX3S2SE0ywxnPTtErScg==" \
  --active

