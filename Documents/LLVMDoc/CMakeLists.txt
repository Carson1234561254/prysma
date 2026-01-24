cmake_minimum_required(VERSION 3.10)
project(LLVMMethodeDoc)

# Configuration du standard C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Générer compile_commands.json pour clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Par défaut, si aucun type de build n'est fourni, utiliser Debug
if(NOT CMAKE_BUILD_TYPE)
    message(STATUS "CMAKE_BUILD_TYPE non défini -> configuration par défaut: Debug")
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build type" FORCE)
endif()

# --- CONFIGURATION LLVM ---
# Localisation du paquet LLVM
find_package(LLVM REQUIRED CONFIG)

# Définition des macros de préprocesseur LLVM
add_definitions(${LLVM_DEFINITIONS})

# Sélection des composants LLVM
llvm_map_components_to_libnames(llvm_libs core support irreader bitwriter)

# --- CHEMINS D'INCLUSION ---
# Ajouter les répertoires include du projet principal
include_directories(${CMAKE_SOURCE_DIR}/../../include ${LLVM_INCLUDE_DIRS})

# --- SOURCES ---
set(SOURCES
    LLVMMethodeDoc.cpp
    ../../src/Compilateur/LLVM/LLVMSerializer.cpp
)

# --- CRÉER L'EXÉCUTABLE ---
add_executable(LLVMMethodeDoc ${SOURCES})

# --- LIER LES BIBLIOTHÈQUES ---
target_link_libraries(LLVMMethodeDoc ${llvm_libs})

# --- FLAGS DE COMPILATION ---
if(MSVC)
    target_compile_options(LLVMMethodeDoc PRIVATE /W4)
else()
    target_compile_options(LLVMMethodeDoc PRIVATE -Wall -Wextra -Wpedantic -g -O0)
endif()

# Message de confirmation
message(STATUS "Projet LLVMMethodeDoc configuré avec succès")
message(STATUS "LLVM version: ${LLVM_PACKAGE_VERSION}")
message(STATUS "LLVM dir: ${LLVM_DIR}")
