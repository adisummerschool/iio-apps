cmake_minimum_required(VERSION 3.10)

# set the project name
project(iio_raw)

# add the executable
add_executable(${PROJECT_NAME}_hello hello.c )

add_executable(${PROJECT_NAME}_ctx-attr ctx-attr.c )
target_link_libraries(${PROJECT_NAME}_ctx-attr iio )

add_executable(${PROJECT_NAME}_raw raw.c)
target_link_libraries(${PROJECT_NAME}_raw iio )

add_executable(${PROJECT_NAME}_buffer buffer.c)
target_link_libraries(${PROJECT_NAME}_buffer iio )

