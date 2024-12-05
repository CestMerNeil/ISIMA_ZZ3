#include "catch.hpp"

#include <arme.hpp>
#include <adaptateur.hpp>
#include <activateur.hpp>

/*
 * Bonus test 1 : Adapter l'arme à une autre API
 *
 * Nous avons une classe Activateur dans le dossier `bonus_src`. Cette classe permet d'activer un nombre de fois prédéfini un objet.
 * On aimerait que l'objet Arme créé au début du TP puisse être utilisé dans l'Activateur. Sans modifier l'objet, trouver une solution pour le rendre compatible.
 *
 * Indice : Patron Adaptateur
 */
/*
TEST_CASE ( "Item:API" ) {
    Arme epee("Grosse épée", 50, 20);

    Activateur<Adaptateur<Arme>>(Adaptateur<Arme>(epee), 10);

    REQUIRE_NOTHROW ( epee.utiliser() );

    Activateur<Adaptateur<Arme>>(Adaptateur<Arme>(epee), 9);

    REQUIRE_THROWS ( epee.utiliser() );
}

*/