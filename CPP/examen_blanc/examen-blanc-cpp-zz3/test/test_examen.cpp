#include "catch.hpp"

#include <array>

#include <item.hpp>
#include <arme.hpp>
// #include <inventaire.hpp>
// #include <enchantement.hpp>
// #include <fabricant.hpp>

// using Inv = Inventaire;
// using Inv = Inventaire<TrieurAlphabetique>;

/*
 Tests 1 et 2 : Constructeurs d'items
 */
TEST_CASE("Item:Constructeur")
{
    const char *nom = "Baton";
    const Item baton(nom);

    REQUIRE(baton.getNom() == "Baton");
    REQUIRE(baton.getNom() == nom);
    REQUIRE(baton.estVendable() == false);
    REQUIRE(baton.getPrix() == 0);

    const Item livre("Livre", 12);

    REQUIRE(livre.getNom() == "Livre");
    REQUIRE(livre.estVendable() == true);
    REQUIRE(livre.getPrix() == 12);
}

TEST_CASE("Item:ConstructeurParCopie")
{
    const Item item("Livre", 12);
    const Item copie(item);

    REQUIRE(item.getNom() == copie.getNom());
    REQUIRE(item.estVendable() == copie.estVendable());
    REQUIRE(item.getPrix() == copie.getPrix());
}

TEST_CASE("Arme:Item")
{
    Item a = Arme("Baton de combat", 0, 10);
}

TEST_CASE("Arme:Utilisation")
{
    Arme arme("Baton de combat", 0, 10);

    REQUIRE(arme.getNom() == "Baton de combat [10]");
    REQUIRE(arme.estVendable() == false);

    for (unsigned i = 0; i < 10; ++i)
    {
        REQUIRE(arme.getNom() == "Baton de combat [" + std::to_string(10 - i) + "]");
        arme.utiliser();
    }

    REQUIRE_THROWS(arme.utiliser());
}

/*
 * Test 5 : Exception
 */
TEST_CASE("Arme:Exception")
{
    Arme item("Petard mouillé", 0, 0);

    REQUIRE_THROWS_AS(item.utiliser(), Arme::DestroyedItemException);
}

/*
 * Test 6 & 7 : Enchantement
 * Le paramètre est la puissance de l'enchantement.
 */
TEST_CASE("Arme:Enchantement")
{
    Enchantement *enchantement = new Enchantement(3.2f);
    Arme epee("Epee", 0, 10);

    REQUIRE(epee.getEnchantement() == nullptr);
    epee.enchanter(enchantement);

    REQUIRE(epee.getEnchantement() == enchantement);
}

TEST_CASE("Arme:Constructeur copie")
{
    Enchantement *enchantement = new Enchantement(3.2f);
    Arme epee("Excalibur", 0, 10);

    epee.enchanter(enchantement);
    Arme copie = epee;

    REQUIRE(copie.getEnchantement() != epee.getEnchantement());
    REQUIRE(copie.getEnchantement()->getPuissance() == epee.getEnchantement()->getPuissance());
}

/*
 * Test 8 & 9 : Déplacement
 * Cette partie n'est pas au programme pour le TP noté (Décembre 2020)
 */
TEST_CASE("Arme:Constructeur déplacement")
{
    Enchantement *enchantement = new Enchantement(3.2f);
    Arme epeeVictime("Excalibur", 3, 10);

    epeeVictime.enchanter(enchantement);
    Arme epee(std::move(epeeVictime));

    REQUIRE(epee.getEnchantement() == enchantement);
    REQUIRE(epee.getNom() == "Excalibur [10]");
    REQUIRE(epee.getPrix() == 3);

    // Autre manière de vérifier la présence du constructeur, mais pas de vérifier son bon fonctionnement.
    REQUIRE(std::is_move_constructible<Arme>::value);
}

TEST_CASE("Arme:Affectation par déplacement")
{
    // J'ai pas trouver mieux, essayer de la faire bien cette redéfinition d'opérateur.
    REQUIRE(std::is_move_assignable<Arme>::value);
}

/*
 * Test 10 : Un container
 */
TEST_CASE("Inventaire:Stokage")
{
    Inv inventaire;
    Item bestBook("Effectiv Modern C++", 15);
    const Inv inventaire2;

    REQUIRE(inventaire.getTaille() == 0);

    inventaire.ajouter(&bestBook);
    REQUIRE(inventaire.getTaille() == 1);

    REQUIRE(inventaire2.getTaille() == 0);
}

/*
 * Test 11 : Enum
 */
TEST_CASE("Inventaire:Catégorie")
{
    Inv::Categorie categorie = Inv::Categorie::ARME;

    REQUIRE(static_cast<char>(categorie) == 'A');
    REQUIRE(static_cast<char>(Inv::Categorie::CONSOMMABLE) == 'C');
    REQUIRE(static_cast<char>(Inv::Categorie::RARE) == 'R');
}

/*
 * Test 12 : Catégorisation des items de l'inventaire
 *
 * AIDE : Chaque catégorie d'item est stockée dans son propre container.
 * On ne touche pas à autre chose qu'à Inventaire.
 */
TEST_CASE("Inventaire:Catégorisation")
{
    Inv inventaire;
    Item graal("Graal");
    Item baton("Bâton");

    Inv::list_t const &itemsRares = inventaire.getItemsParCategorie(Inv::Categorie::RARE);
    Inv::list_t const &itemsNormaux = inventaire.getItemsParCategorie(Inv::Categorie::NORMAL);
    Inv::list_t const &itemsArmes = inventaire.getItemsParCategorie(Inv::Categorie::ARME);
    Inv::list_t const &itemsConsommables = inventaire.getItemsParCategorie(Inv::Categorie::CONSOMMABLE);

    inventaire.ajouter(&graal, Inv::Categorie::RARE);
    inventaire.ajouter(&baton);

    REQUIRE(itemsRares.size() == 1);
    REQUIRE(itemsNormaux.size() == 1);
    REQUIRE(itemsArmes.size() == 0);
    REQUIRE(itemsConsommables.size() == 0);

    REQUIRE(inventaire.getTaille() == 2);
}

/*
 * Test 13 : Tri
 */
TEST_CASE("Inventaire:Tri")
{
    Inv inventaire;

    Item baton("Bâton");
    Item livre("Livre");
    Item amulette("Amulette");
    Item xylophone("Xylophone");

    std::array<std::string, 4> array = {"Amulette", "Bâton", "Livre", "Xylophone"};

    Inv::list_t const &itemsNormaux = inventaire.getItemsParCategorie(Inv::Categorie::NORMAL);

    inventaire.ajouter(&baton);
    inventaire.ajouter(&livre);
    inventaire.ajouter(&amulette);
    inventaire.ajouter(&xylophone); // Grave chelou d'avoir un xylophone...

    unsigned i = 0;
    std::for_each(itemsNormaux.cbegin(), itemsNormaux.cend(), [&array, &i](Item *item)
                  { REQUIRE(item->getNom() == array[i++]); });
}

/*
 * Test 14 : Plus de tris
 */
TEST_CASE("Inventaire:Tris sélectifs")
{
    Item baton("Bâton", 89);
    Item livre("Livre", 19);
    Item amulette("Amulette", 35);
    Item xylophone("Xylophone", 465);

    Inventaire<TrieurAlphabetique> inventaire;
    std::array<std::string, 4> array = {"Amulette", "Bâton", "Livre", "Xylophone"};

    Inv::list_t const &itemsNormaux = inventaire.getItemsParCategorie(Inv::Categorie::NORMAL);

    inventaire.ajouter(&baton);
    inventaire.ajouter(&livre);
    inventaire.ajouter(&amulette);
    inventaire.ajouter(&xylophone); // Grave chelou d'avoir un xylophone...

    unsigned i = 0;
    std::for_each(itemsNormaux.cbegin(), itemsNormaux.cend(), [&array, &i](Item *item)
                  { REQUIRE(item->getNom() == array[i++]); });

    Inventaire<TrieurPrix> inventaire2;
    std::array<std::string, 4> array2 = {"Livre", "Amulette", "Bâton", "Xylophone"};

    Inventaire<TrieurPrix>::list_t const &itemsNormaux2 = inventaire2.getItemsParCategorie(Inventaire<TrieurPrix>::Categorie::NORMAL);

    inventaire2.ajouter(&baton);
    inventaire2.ajouter(&livre);
    inventaire2.ajouter(&amulette);
    inventaire2.ajouter(&xylophone); // Grave cher en plus...

    i = 0;
    std::for_each(itemsNormaux2.cbegin(), itemsNormaux2.cend(), [&array2, &i](Item *item)
                  { REQUIRE(item->getNom() == array2[i++]); });
}

/*
 * Test 15 : Item ou arme ?
 */
TEST_CASE("Inventaire:Item ou Arme")
{
    Inv inventaire;

    Arme gourdin("Gourdin");

    inventaire.ajouter(static_cast<Item *>(&gourdin));
    Inv::list_t const &itemsNormaux = inventaire.getItemsParCategorie(Inv::Categorie::NORMAL);
    Inv::list_t const &itemsArmes = inventaire.getItemsParCategorie(Inv::Categorie::ARME);

    REQUIRE(itemsNormaux.size() == 0);
    REQUIRE(itemsArmes.size() == 1);
}

/*
 * Test 16 : Fabricant
 * Il a un nom et un conteneur. Ce conteneur contient la liste des noms d'items qu'il peut produire.
 */
TEST_CASE("Fabricant:Initial")
{
    const Fabricant marcorporate("Marcorporate");

    REQUIRE(marcorporate.getNom() == "Marcorporate");
    REQUIRE(marcorporate.hasItemsEnProduction() == false);
}

/*
 * Test 17 : Production d'item
 * On peut indiquer a un fabricant les items qu'il peut fabriquer. Il peut ensuite les fabriquer.
 */
TEST_CASE("Fabricant:Production")
{
    Fabricant marcorporate("Marcorporate");
    marcorporate.ajouterProduction("Faucille");
    marcorporate.ajouterProduction("Marteau");

    REQUIRE(marcorporate.hasItemsEnProduction() == true);

    Item *faucille = marcorporate.produire("Faucille");
    Item *porteFeuille = marcorporate.produire("Porte-feuille");

    REQUIRE(faucille != nullptr);
    REQUIRE(porteFeuille == nullptr);

    REQUIRE(faucille->getNom() == "[Marcorporate] Faucille");

    delete faucille;
    delete porteFeuille;
}

/*
 * Test 18 : Fabricant de l'item
 * L'item garde une trace de son fabricant.
 *
 * Setter dans l'item appelé par produire().
 */
TEST_CASE("Fabricant:Appartenance")
{
    Fabricant marcorporate("Marcorporate");
    marcorporate.ajouterProduction("Faucille");

    Item porteFeuille("Porte-Feuille");
    REQUIRE(porteFeuille.getFabricant() == nullptr);

    Item *faucille = marcorporate.produire("Faucille");
    REQUIRE(faucille->getFabricant() == &marcorporate);

    delete faucille;
}
