cmake_minimum_required(VERSION 3.20)

# ------------------------------------------------------------------------------
# Informations sur le projet
# ------------------------------------------------------------------------------
project(AStar VERSION 1.0.0 LANGUAGES CXX)

# ------------------------------------------------------------------------------
# Configuration de la norme C++
# ------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ------------------------------------------------------------------------------
# Fichiers sources et en-têtes pour l'exécutable principal
# ------------------------------------------------------------------------------
set(SOURCES
    src/main.cpp
    src/A_Star.cpp
    src/Grid.cpp
)
set(HEADERS
    include/A_Star.hpp
    include/Grid.hpp
)

# ------------------------------------------------------------------------------
# Création de l'exécutable principal (démonstration)
# ------------------------------------------------------------------------------
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)

# ------------------------------------------------------------------------------
# Optimisations selon le type de build
# ------------------------------------------------------------------------------
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options(${PROJECT_NAME} PRIVATE -O3)
elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(${PROJECT_NAME} PRIVATE -g -O0 -Werror)
endif()

# ------------------------------------------------------------------------------
# Création de l'exécutable pour les tests manuels
# ------------------------------------------------------------------------------
add_executable(tests tests/tests.cpp src/A_Star.cpp src/Grid.cpp)
target_include_directories(tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_options(tests PRIVATE -Wall -Wextra -Wpedantic)