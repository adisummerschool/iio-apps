cmake_minimum_required(VERSION 3.10)

# set the project name
project(iio-raw)

# add the executable
add_executable(${PROJECT_NAME}_hello hello.c)

add_executable(${PROJECT_NAME}_ctxattr ctxattr.c)
target_link_libraries(${PROJECT_NAME}_ctxattr iio)

add_executable(${PROJECT_NAME}_getraw getraw.c)
target_link_libraries(${PROJECT_NAME}_getraw iio)

add_executable(${PROJECT_NAME}_getbuffer getbuffer.c)
target_link_libraries(${PROJECT_NAME}_getbuffer iio)

