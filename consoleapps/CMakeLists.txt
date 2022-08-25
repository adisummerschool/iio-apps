cmake_minimum_required(VERSION 3.10)
# set the project name
project(iio_raw)

# add the executable
add_executable(${PROJECT_NAME}_hello hello.c)
add_executable(${PROJECT_NAME}_ctxattr ctx_attr.c)
add_executable(${PROJECT_NAME}_ctxgetraw get_raw.c)
add_executable(${PROJECT_NAME}_calibration ctxattr_calibration.c)
add_executable(${PROJECT_NAME}_bufferattr buffer_attr.c)
add_executable(${PROJECT_NAME}_buffeshock detect_shock.c)

#Add dependencies
target_link_libraries(${PROJECT_NAME}_ctxattr iio)
target_link_libraries(${PROJECT_NAME}_ctxgetraw iio)
target_link_libraries(${PROJECT_NAME}_calibration iio)
target_link_libraries(${PROJECT_NAME}_bufferattr iio)
target_link_libraries(${PROJECT_NAME}_buffeshock iio)

