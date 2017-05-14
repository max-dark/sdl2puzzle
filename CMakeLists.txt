project(sdl2puzzle)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)

target_link_libraries(${PROJECT_NAME} SDL2 SDL2_image)

set(NUMBS "numbs.bmp")
configure_file(${NUMBS} ${CMAKE_CURRENT_BINARY_DIR}/${NUMBS} COPYONLY)
