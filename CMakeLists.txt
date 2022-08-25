cmake_minimum_required(VERSION 3.10)

# set the project name
project(iio-raw)


find_library(LIBIIO iio NAMES libiio)

# add the executable
add_executable(${PROJECT_NAME}_hello hello.c)

add_executable(${PROJECT_NAME}_ctxattr ctxattr.c )
target_link_libraries(${PROJECT_NAME}_ctxattr iio)

add_executable(${PROJECT_NAME}_get_raw get_raw.c)
target_link_libraries(${PROJECT_NAME}_get_raw iio)

add_executable(${PROJECT_NAME}_buffer buffer.c)
target_link_libraries(${PROJECT_NAME}_buffer iio)
