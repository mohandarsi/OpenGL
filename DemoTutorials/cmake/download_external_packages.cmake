
include(ExternalProject)

set(HAS_GLFW OFF)

# Glad requires Python to configure itself and Python is an annoying dependency to have.
# So as an exception to the rule we include the glad src/header files directly
set(HAS_GLAD ON)


include(FetchContent)

MESSAGE("HAS_GLFW: " ${HAS_GLFW})
if (NOT HAS_GLFW)
    FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.3.6
        SOURCE_DIR          ${FETCHCONTENT_SOURCE_DIR}/glfw-src
        SUBBUILD_DIR        ${FETCHCONTENT_SOURCE_DIR}/glfw-subbuild
        UPDATE_COMMAND      ""
        CONFIGURE_COMMAND   ""
        BUILD_COMMAND       ""
        INSTALL_COMMAND     ""
    )
    FetchContent_GetProperties(glfw)
    if (NOT glfw_POPULATED)
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(glfw)
        set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
        set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
        set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
        add_subdirectory(${glfw_SOURCE_DIR} ${glfw_BINARY_DIR})
    endif()
endif()


MESSAGE("HAS_GLAD: " ${HAS_GLAD})
if (NOT HAS_GLAD)
    FetchContent_Declare(
        glad
        GIT_REPOSITORY https://github.com/Dav1dde/glad.git
        GIT_TAG v0.1.36
        SOURCE_DIR          ${FETCHCONTENT_SOURCE_DIR}/glad-src
        SUBBUILD_DIR        ${FETCHCONTENT_SOURCE_DIR}/glad-subbuild
        UPDATE_COMMAND      ""
        CONFIGURE_COMMAND   ""
        BUILD_COMMAND       ""
        INSTALL_COMMAND     ""
    )
    FetchContent_GetProperties(glad)
    if (NOT glad_POPULATED)
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(glad)
        set(GLAD_PROFILE "core" CACHE STRING "OpenGL profile")
        set(GLAD_API "gl=" CACHE STRING "API type/version pairs, like \"gl=3.3,gles=\", no version means latest")
        set(GLAD_GENERATOR "c" CACHE STRING "Language to generate the binding for")
        add_subdirectory(${glad_SOURCE_DIR} ${glad_BINARY_DIR})
    endif()
else()
    add_subdirectory(${FETCHCONTENT_SOURCE_DIR}/glad)
endif()


FetchContent_Declare(
	glm
	GIT_REPOSITORY https://github.com/g-truc/glm.git 
	GIT_TAG		   0.9.9.8
    SOURCE_DIR          ${FETCHCONTENT_SOURCE_DIR}/glm-src
    SUBBUILD_DIR        ${FETCHCONTENT_SOURCE_DIR}/glm-subbuild
)

FetchContent_GetProperties(glm)
if(NOT glm_POPULATED)
	FetchContent_Populate(glm)
	set(GLM_TEST_ENABLE OFF CACHE BOOL "" FORCE)
	add_subdirectory(${glm_SOURCE_DIR} ${glm_BINARY_DIR})
endif()
