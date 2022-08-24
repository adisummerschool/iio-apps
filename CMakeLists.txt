cmake_minimum_required(VERSION 3.10)

# set the project name
project(iio-raw)

# add the executables
add_executable(${PROJECT_NAME}_hello hello.c)
add_executable(${PROJECT_NAME}_ctx_read_attr ctx_read_attr.c)
add_executable(${PROJECT_NAME}_ctx_read_raw ctx_read_raw.c)

# link libraries to executable files
target_link_libraries(${PROJECT_NAME}_ctx_read_attr iio)
target_link_libraries(${PROJECT_NAME}_ctx_read_raw iio)
