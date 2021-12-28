cmake_minimum_required (VERSION 3.8)
project(project_CubeModLoader)
add_subdirectory(CWSDK)
add_library (CubeModLoader SHARED 
    crc.cpp
    DLL.cpp
    main.cpp
    mutex.cpp "macros.h" "callbacks/gui/cube__StartMenuWidget__Draw.h" "callbacks/game/cube__Game__MouseUp.h" "callbacks/gui/cube__GUI__Load.h" "ModWidget.h" "ModWidget.cpp" "callbacks/world/cube__World__SpawnCreaturesMaybe.h" "callbacks/creature/cube__Creature__OnPlayerDeath.h")
target_link_libraries (CubeModLoader LINK_PUBLIC CWSDK)