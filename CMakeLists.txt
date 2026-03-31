cmake_minimum_required(VERSION 3.15)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)

project(MagicHandSolitary)

if(CMAKE_SYSTEM MATCHES Windows)
  set(CMAKE_C_FLAGS -DWINDOWS)
add_executable(solitui main.c menu.c cards.c magichandsolitary.c uiterm.c inputcontrols_win.c)
else()
add_executable(solitui main.c menu.c cards.c magichandsolitary.c uiterm.c inputcontrols.c)
endif()
