project(cnsc)
cmake_minimum_required(VERSION 2.8)

set(SOURCES
    types.c
    git.c
    menu.c
    log.c
    main.c
)

add_executable(${PROJECT_NAME} ${SOURCES})
