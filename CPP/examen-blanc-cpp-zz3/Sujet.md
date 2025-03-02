# Sujet du TP

L'objectif de ce TP est d'implémenté un système d'inventaire pouvant contenir des `Item`s et des `Arme`s. Le reste du document donne des indications pour chaque test.

## Test 1
Les `Item`s ont un nom et un prix qui sont définit via le constructeur. Un `Item` n'est vendable que si son prix est positif. C'est 3 éléments sont accessibles via des `getters` dont les noms sont visibles dans les tests.

Le prix par défaut d'un item est 0, il n'est donc pas vendable.

## Test 2
Un item doit être copiable à partir d'un autre item.

## Test 3
On ajoute les `Arme`s, ce sont des items (héritage). La différence avec un item normal c'est qu'on peut l'utiliser un nombre de fois prédéterminé. Ce nombre doit être indiqué dans le constructeur.

## Test 4
Les utilisations des `Arme`s étant limitées, il faut indiquer dans le nom combien d'utilisation il reste. A chaque utilisation de l'arme, le nombre d'utilisations restantes diminues (le nom est mis à jour).

Si une `Arme` n'est plus utilisable, une exception doit être levée.

## Test 5
Il faut créer une exception. En regardant le code du test, on se rend compte que l'exception s'appelle `Arme::DestroyedItemException`. Le `::` signifie que l'exception `DestroyedItemException` doit se trouver dans la classe `Arme`.

Cette exception est celle qui sera renvoyée lorsque l'`Arme` ne peut plus être utilisée.

## Test 6
Les enchantements seront représentés par un nouvel objet à créer. On peut enchanter une `Arme` (il faut modifier la classe). Au départ une arme ne possède aucun enchantement.

## Test 7
Lorsqu'on copie une arme l'enchantement est copié. Il faut bien créer un nouvel enchantement identique (constructeur par copie) et associé ce nouvel enchantement à la nouvelle arme.

## Test 8
Ce test peut être passé sans impacter la suite.

Il faut ici redéfinir le constructeur par déplacement de l'`Arme`. L'`Arme` victime donne tous ces attributs à la nouvelle arme.

Le test ne vérifie pas que des valeurs "sûres" sont mises dans la victime. Il faudrait théoriquement le faire.

## Test 9
Ce test doit être passé si le précédent l'a été. Il peut également l'être même si le précédent a été fait.

Il faut créer l'opérateur d'affectation par déplacement (appelant le constructeur lié).

## Test 10
Implémentation du conteneur que l'on va traiter comme un inventaire. Les `using`s en début du fichier de tests permettent de faire les tests malgrés les modifications que l'on devra faire plus tard. Il faut donc décommenter le premier.

On peut obtenir la taille de l'`Inv` et également y insérer des éléments.

## Test 11
L'inventaire contient plusieurs catégories. Elles sont représentées par une `enum` (cf. titre du test). Il y a 3 catégories : `ARME`, `CONSOMMABLE`, `RARE`. On remarque que toutes ces possibilités sont dans `Inv::Categorie::<........>`, c'est parce qu'on utilise une `enum class` dans `Inv`. D'autres solutions sont possibles, mais celle-ci est la plus proche des guidelines.

Chaque catégorie est représentée par un caractère, on peut pour cela utiliser l'héritage dans les `enum class`.

## Test 12

Il y a plusieurs choses à faire ici.

Tout d'abord on change `Inv` pour qu'il contienne en réalité plusieurs conteneurs, un par catégorie. Ces conteneurs doivent pouvoir être utilisé en dehors de la classe, on ressort donc leur type : `list_t`.

La méthode `getItemsParCategorie()` permet de récupérer la liste des items d'une catégorie.

On modifie l'ajout d'item pour permettre de spécifier la catégorie de l'item. Si rien n'est spécifié on ajoute dans les items normaux.

La taille de l'inventaire est la somme de ces sous-listes.

## Test 13

On veut maintenant trier l'inventaire. Pour cela on ne tri que les sous-listes, un conteneur standard adapté peut aider pour cette étape (on peut changer ce qu'est `Inv::list_t`).

Le tri doit se faire par ordre alphabétique. Un comparateur doit être créé pour cela.

## Test 14

On passe maintenant l'inventaire en template. Ce template représente le tri à utiliser pour les éléments de l'inventaire. 

Comme on intègre une nouvelle classe, on peut modifier les `using`s en début de fichier.

Le tri par défaut doit être l'ordre alphabétique pour que le test précédent fonctionne toujours.

On ajout un second comparateur qui tri selon le prix des items (ordre croissant).

## Test 15

On veut ici modifier la manière dont les items sont ajouter à l'inventaire pour que si l'on ajoute une `Arme`, la catégorie soit automatiquement : `Inv::Categorie::Arme`). Il faut donc savoir si un `Item` est ou non une `Arme`.