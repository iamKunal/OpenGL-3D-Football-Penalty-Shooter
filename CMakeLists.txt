cmake_minimum_required(VERSION 3.9)
project(Football_Penalty_Shooter)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -lglut -lGLU -lGL")

find_package(Doxygen)


set(SOURCE_FILES main.cpp functionalities.cpp shapes.cpp functionalities.cpp functionalities.h)
FILE(COPY resources DESTINATION "${CMAKE_BINARY_DIR}")

#if(DOXYGEN_FOUND)
#
#    set(DOXYGEN_INPUT ${SOURCE_FILES})
#    set(DOXYGEN_OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
#
#    add_custom_command(
#            OUTPUT ${DOXYGEN_OUTPUT}
#            COMMAND ${CMAKE_COMMAND} -E echo_append "Building API Documentation..."
#            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_INPUT}
#            COMMAND ${CMAKE_COMMAND} -E echo "Done."
#            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
#            DEPENDS ${DOXYGEN_INPUT}
#    )
#
#    add_custom_target(apidoc ALL DEPENDS ${DOXYGEN_OUTPUT})
#
#    add_custom_target(apidoc_forced
#            COMMAND ${CMAKE_COMMAND} -E echo_append "Building API Documentation..."
#            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_INPUT}
#            COMMAND ${CMAKE_COMMAND} -E echo "Done."
#            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
#            )
#
#endif(DOXYGEN_FOUND)

add_executable(Football_Penalty_Shooter ${SOURCE_FILES})
add_custom_target(run
        COMMAND Football_Penalty_Shooter
        DEPENDS Football_Penalty_Shooter
        WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
        )
