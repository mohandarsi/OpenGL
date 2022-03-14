cmake_minimum_required(VERSION 3.0)
project(helloTraingle)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)
set(FETCHCONTENT_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/external CACHE STRING "Base dir for thirdparty libs" )
MESSAGE("FETCHCONTENT_SOURCE_DIR: " ${FETCHCONTENT_SOURCE_DIR})

include(${CMAKE_MODULE_PATH}/download_external_packages.cmake)

file(GLOB_RECURSE SRC_LIST ${CMAKE_SOURCE_DIR}/src/*.cpp
                         ${CMAKE_SOURCE_DIR}/src/*.h

)

add_executable(${PROJECT_NAME} ${SRC_LIST})

set(project_resources)

# Any any resources
file(GLOB resources ${CMAKE_SOURCE_DIR}/src/resources/*)
list(APPEND project_resources ${resources})

target_include_directories(${PROJECT_NAME} PRIVATE ${glfw_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${glm_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} glfw glad)


# Copy all of the resource files to the destination
file(COPY ${project_resources} DESTINATION "resources/")


