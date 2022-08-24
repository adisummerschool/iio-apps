cmake_minimum_required(VERSION 3.3.2)

project(iio_raw)

add_executable(${PROJECT_NAME}_hello hello.c)
add_executable(${PROJECT_NAME}_ctx_attr ctx_attr.c)

target_link_libraries(${PROJECT_NAME}_ctx_attr iio)
