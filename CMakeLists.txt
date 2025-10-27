cmake_minimum_required(VERSION 3.15)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(MagicHandSolitary)

add_executable(main main.c cards.c magichandsolitary.c uiterm.c)
