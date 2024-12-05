cmake_minimum_required(VERSION 3.28)
# Modifier ces variables si vous avez des fichiers à ajouter.
set(ZZ_SRC
    #src/item.cpp
    src/arme.cpp
    #src/enchantement.cpp
    #src/inventaire.cpp
)
set(ZZ_HEADER
    src/item.hpp
    #src/arme.hpp
    #src/enchantement.hpp
    #src/inventaire.hpp
    #src/fabricant.hpp
    #src/adaptateur.hpp # Seulement pour les tests bonus
)

# Ne pas toucher le reste.

set(TEST_SRC 
    test/catch.cpp 
    test/test_examen.cpp
)
set(TEST_HEADER 
    test/catch.hpp
)

set(TEST_BONUS_SRC 
    test/catch.cpp
    test/test_bonus.cpp
)
set(TEST_BONUS_HEADER 
    test/catch.hpp
    bonus_src/activateur.hpp
)

project(examen_blanc)

add_library(inventaire ${ZZ_SRC} ${ZZ_HEADER})
target_compile_options(inventaire PUBLIC -g -Wall -Wextra -pedantic)
target_compile_features(inventaire PUBLIC cxx_std_14)
message(${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(inventaire PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(test ${TEST_SRC} ${TEST_HEADER})
#target_link_libraries(test PRIVATE inventaire)

add_executable(test_bonus ${TEST_BONUS_SRC} ${TEST_BONUS_HEADER})
target_link_libraries(test_bonus PRIVATE inventaire)
target_include_directories(test_bonus PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/bonus_src)

set(CMAKE_CXX_STANDARD 14)