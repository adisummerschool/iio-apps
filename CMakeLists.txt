cmake_minimum_required(VERSION 3.3.2)

project(iio_raw)

add_executable(${PROJECT_NAME}_hello hello.c)
add_executable(${PROJECT_NAME}_context_attr context_attr.c)
add_executable(${PROJECT_NAME}_calibration calibration.c)
add_executable(${PROJECT_NAME}_buffer buffer.c)

target_link_libraries(${PROJECT_NAME}_context_attr iio)
target_link_libraries(${PROJECT_NAME}_calibration iio)
target_link_libraries(${PROJECT_NAME}_buffer iio)
