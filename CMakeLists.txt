cmake_minimum_required(VERSION 3.15)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)

project(MagicHandSolitary)

add_executable(solitui main.c menu.c cards.c magichandsolitary.c uiterm.c inputcontrols.c)
