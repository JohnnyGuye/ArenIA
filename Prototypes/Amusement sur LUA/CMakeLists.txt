# Nom du projet
project(CLuaTests)

#Inclusion de la lib lua
find_package(Lua51 REQUIRED) 

include_directories(${LUA_INCLUDE_DIR})

#Lister les fichiers sources
file(

        GLOB_RECURSE

        source_files

        src/*

)

#Création du fichier executable
add_executable(

        exec

        ${source_files}

)

#Configuration de l'édition de liens
target_link_libraries(

        exec

        ${LUA_LIBRARIES}

)

target_compile_features(exec PRIVATE cxx_range_for)