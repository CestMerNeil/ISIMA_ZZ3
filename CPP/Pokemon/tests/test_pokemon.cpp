#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src/Pokemon.hpp"
#include "../src/Pokedex.hpp"
#include "../src/Factory.hpp"
#include "../src/Singleton.hpp"
#include "../src/Box.hpp"

TEST_CASE("Pokemon: Basic Properties")
{
    Pokemon pikachu("Pikachu", 10, 100, 20);

    REQUIRE(pikachu.getName() == "Pikachu");
    REQUIRE(pikachu.getLevel() == 10);
    REQUIRE(pikachu.getHp() == 100);
    REQUIRE(pikachu.getAttack() == 20);
}

TEST_CASE("Pokemon: Take Damage")
{
    Pokemon squirtle("Squirtle", 5, 50, 10);

    SECTION("Normal damage")
    {
        squirtle.takeDamage(30);
        REQUIRE(squirtle.getHp() == 20);
    }

    SECTION("Damage exceeds HP")
    {
        squirtle.takeDamage(60);
        REQUIRE(squirtle.getHp() == 0);
    }
}

TEST_CASE("PokemonFactory: Create Pokemon")
{
    auto charmander = PokemonFactory::createCharmander(5);
    REQUIRE(charmander->getName() == "Charmander");
    REQUIRE(charmander->getLevel() == 5);
    REQUIRE(charmander->getHp() == 75);     // 假设公式：50 + level * 5
    REQUIRE(charmander->getAttack() == 20); // 假设公式：10 + level * 2

    auto bulbasaur = PokemonFactory::createBulbasaur(7);
    REQUIRE(bulbasaur->getName() == "Bulbasaur");
    REQUIRE(bulbasaur->getLevel() == 7);
    REQUIRE(bulbasaur->getHp() == 95);     // 假设公式：60 + level * 5
    REQUIRE(bulbasaur->getAttack() == 22); // 假设公式：8 + level * 2
}

TEST_CASE("Pokedex: Add and Search Pokemon")
{
    Pokedex pokedex;

    SECTION("Add Pokemon")
    {
        auto eevee = std::make_unique<Pokemon>("Eevee", 3, 60, 12);
        pokedex.addPokemon(std::move(eevee));
        REQUIRE(pokedex.contains("Eevee") == true);
    }

    SECTION("Search for non-existing Pokemon")
    {
        REQUIRE(pokedex.contains("Mewtwo") == false);
    }
}

TEST_CASE("Singleton: Global Configuration")
{
    auto *config1 = Singleton::getInstance();
    auto *config2 = Singleton::getInstance();

    REQUIRE(config1 == config2); // 确保只有一个实例
    config1->setValue("game_difficulty", "hard");
    REQUIRE(config2->getValue("game_difficulty") == "hard");
    config1->setValue("game_test", "test");
    REQUIRE(config2->getValue("game_test") == "test");
}

TEST_CASE("Templates: Pokemon Storage")
{
    Box<Pokemon> storage(Pokemon("Charmander", 5, 75, 20));

    SECTION("Retrieve Pokemon")
    {
        Pokemon retrieved = storage.getValue();
        REQUIRE(retrieved.getName() == "Charmander");
        REQUIRE(retrieved.getLevel() == 5);
    }
}

TEST_CASE("Smart Pointers: Factory Integration")
{
    SECTION("Unique Pointer")
    {
        auto charmander = PokemonFactory::createCharmander(10);
        REQUIRE(charmander->getName() == "Charmander");
    }

    SECTION("Shared Pointer")
    {
        auto pikachu = std::make_shared<Pokemon>("Pikachu", 15, 100, 25);
        auto sharedPikachu = pikachu; // 共享所有权
        REQUIRE(sharedPikachu->getHp() == 100);
        REQUIRE(pikachu.use_count() == 2);
    }

    SECTION("Weak Pointer Avoids Cycles")
    {
        std::shared_ptr<Pokemon> bulbasaur = std::make_shared<Pokemon>("Bulbasaur", 10, 80, 18);
        std::weak_ptr<Pokemon> weakBulbasaur = bulbasaur;
        REQUIRE(!weakBulbasaur.expired());
        bulbasaur.reset(); // 销毁 shared_ptr
        REQUIRE(weakBulbasaur.expired());
    }
}

TEST_CASE("Exception Handling: Invalid Pokemon Creation")
{
    REQUIRE_THROWS_AS(PokemonFactory::createPokemon("UnknownType"), std::invalid_argument);
    try
    {
        PokemonFactory::createPokemon("UnknownType");
    }
    catch (const std::invalid_argument &e)
    {
        REQUIRE(std::string(e.what()) == "Unknown Pokemon type");
    }
}

TEST_CASE("Integration Test: Complete Flow")
{
    Pokedex pokedex;

    SECTION("Add factory-created Pokemon to Pokedex")
    {
        auto charmander = PokemonFactory::createCharmander(10);
        pokedex.addPokemon(std::move(charmander));

        auto bulbasaur = PokemonFactory::createBulbasaur(12);
        pokedex.addPokemon(std::move(bulbasaur));

        REQUIRE(pokedex.contains("Charmander") == true);
        REQUIRE(pokedex.contains("Bulbasaur") == true);
        REQUIRE(pokedex.contains("Pikachu") == false);
    }

    SECTION("Battle simulation")
    {
        Pokemon pikachu("Pikachu", 15, 100, 25);
        Pokemon squirtle("Squirtle", 10, 80, 15);

        squirtle.takeDamage(pikachu.getAttack());
        REQUIRE(squirtle.getHp() == 55);

        pikachu.takeDamage(squirtle.getAttack());
        REQUIRE(pikachu.getHp() == 85);
    }
}
