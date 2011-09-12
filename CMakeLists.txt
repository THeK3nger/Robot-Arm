cmake_minimum_required(VERSION 2.6)

project(RobotArm)
find_package(GLUT)
find_package(OpenGL)

set(CMAKE_CXX_FLAG "-g -Wall")

file(GLOB SOURCE_FILE *.cpp)
add_executable(robotarm ${SOURCE_FILE})
target_link_libraries(robotarm ${OPENGL_LIBRARY} ${GLUT_LIBRARY})

execute_process(COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/res
    ${CMAKE_BINARY_DIR}/res
)
