cmake_minimum_required(VERSION 3.10)

# set the project name
project(iio-raw)

# add the executable
add_executable(${PROJECT_NAME}_hello hello.c)

add_executable(${PROJECT_NAME}_ctxattr ctxattr.c)
target_link_libraries(${PROJECT_NAME}_ctxattr iio)
