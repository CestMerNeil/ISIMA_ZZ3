# Sujet blanc de C++ pour les ZZ3

Ce dépôt contient un TP d'entrainement pour l'examen de C++ de dernière année à l'ISIMA. Il a été écrit par un étudiant sans aucun lien avec les professeurs ou l'école. Il ne garantit donc pas que le contenu est réellement ce qu'il faut réviser pour le vrai examen sur machine. Le sujet a été écrit pour la session de Décembre 2020 (visant le standard C++14).

## Organisation

Le sujet a été prévu pour être fait uniquement à partir des tests unitaires présents dans le dossier `test`. En effet le jour de l'exament vous gagnerez du temps si vous êtes capable de comprendre le code attendu (ou au moins une intuition) à partir des tests uniquements.

Cependant après avoir obtenu des retours de la part des étudiants l'ayant fait, certains passages sont trop flous pour être fais sans aide. C'est pourquoi j'ai ajouté un document `Sujet.md`. Je recommande néanmoins de s'en passer le plus possible ! Des commentaires dans les tests peuvent donner de petites indications.

Certains tests peuvent probablement être passés, mais cela n'a pas été testé. De plus, plusieurs solutions d'implémentations sont possibles, il n'y en a pas de bonnes ou de mauvaises dans le cadre de ce TP. Les indications données dans le sujet reflète l'idée avec laquelle j'avais pensé le TP, si vous avez une autre implémentation le sujet peut ne pas correspondre à votre code.

Enfin ma solution au TP est disponible sur la branche solution. Je recommande évidemment de ne pas y aller avant d'avoir fini le TP.

## Pré-requis

Le TP a été prévu pour être fait avec g++ en version 8.0.3 (version utilisée par l'ISIMA en 2020). Les messages d'erreurs pouvant changer d'une version à l'autre, il est plus intéressant de rester sur la version disponible le jour de l'examen.

Un CMake a été fourni pour compiler les sources, il n'est pas nécessaire mais fortement recommandé. Ainsi les commandes suivantes devront être effectué une fois en début de TP.

```bash
git clone https://gitlab.com/gagoi_/examen-blanc-cpp-zz3.git
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug
```

Ensuite deux commandes uniquement seront utiles.

```bash
make -j $(nproc)
./test
```

## Outils autorisés

Internet ne devrait pas être utilisé librement lors de la réalisation de ce travail afin de se mettre dans les conditions les plus proches de celles de l'examen. Une exception est faite pour https://en.cppreference.com/w/ qui peut être utilisé mais sans la barre de recherche. La version offline du site ne permettant pas la recherche.

`Valgrind` est un outil important pour détecter une multitude d'erreurs, il est autorisé tout comme le jour de l'examen. Dans ce TP, il est possible de l'utiliser sur l'exécutable des tests, et aucune fuite de mémoire ne doit être présente.

## Bonus

Les tests bonus ont été rajoutés afin de compléter le sujet d'origine. Il sont encore moins représentatifs de ce qui peut être demandé au TP.