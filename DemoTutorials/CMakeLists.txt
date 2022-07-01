cmake_minimum_required(VERSION 3.0)

set(PACKAGE_VERSION 0.0.0 CACHE STRING "")

project(DemoTutorials  VERSION ${PACKAGE_VERSION})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/Install)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)
set(EXTERNAL_PACKAGES_DIR ${CMAKE_CURRENT_LIST_DIR}/external CACHE STRING "Base dir for third-party libs")
MESSAGE("EXTERNAL_PACKAGES_DIR: " ${EXTERNAL_PACKAGES_DIR})

set(CMAKE_PREFIX_PATH ${EXTERNAL_PACKAGES_DIR} CACHE INTERNAL "")

include(${CMAKE_MODULE_PATH}/download_external_packages.cmake)

file(GLOB_RECURSE SRC_LIST ${CMAKE_SOURCE_DIR}/src/*.cpp
                         ${CMAKE_SOURCE_DIR}/src/*.h

)

add_executable(${PROJECT_NAME} ${SRC_LIST})

target_include_directories(${PROJECT_NAME} 
          PRIVATE
            ${GLFW3_INCLUDE_PATH}
            ${GLM_INCLUDE_PATH}
          )

target_link_libraries(${PROJECT_NAME} 
                PRIVATE 
                  ${GLFW3_LIBRARIES}
                  glad
              )

add_subdirectory(${CMAKE_SOURCE_DIR}/src/resources)

# Instal
install(TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)

include(cmake/Packaging.cmake)
