cmake_minimum_required(VERSION 3.10)

# set the project name
project(iio-raw)


# add the executable
add_executable(${PROJECT_NAME}_hello hello.c )

add_executable(${PROJECT_NAME}_ctx_attr ctx_attr.c )

add_executable(${PROJECT_NAME}_get_raw get_raw.c)

add_executable(${PROJECT_NAME}_buffer buffer.c)
target_link_libraries(${PROJECT_NAME}_buffer iio)



target_link_libraries(${PROJECT_NAME}_get_raw iio)


target_link_libraries(${PROJECT_NAME}_ctx_attr iio)

add_executable(${PROJECT_NAME}_ctx_attr_calib ctx_attr_calib.c)
target_link_libraries(${PROJECT_NAME}_ctx_attr_calib iio)

