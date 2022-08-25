cmake_minimum_required(VERSION 3.10)

# set the project name
project(iio-raw)

# add the executable
add_executable(${PROJECT_NAME}_hello hello.c second.c)
add_executable(${PROJECT_NAME}_ctxattr_raw ctxattr_raw.c)
add_executable(${PROJECT_NAME}_ctxattr_attr ctxattr_attr.c)
add_executable(${PROJECT_NAME}_ctxattr_buffer ctxattr_buffer.c)
add_executable(${PROJECT_NAME}_ctxattr_calibration ctxattr_calibration.c)
target_link_libraries(${PROJECT_NAME}_ctxattr_raw iio)
target_link_libraries(${PROJECT_NAME}_ctxattr_calibration iio)
target_link_libraries(${PROJECT_NAME}_ctxattr_attr iio)
target_link_libraries(${PROJECT_NAME}_ctxattr_buffer iio)
