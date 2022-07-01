find_path(GLFW3_INCLUDE_PATH 
                glfw/glfw3.h 
                PATHS ${PROJECT_SOURCE_DIR}/external/glfw/include
                DOC "The directory where GLFW/glfw.h resides"
        )

find_library(GLFW3_LIBRARIES 
            NAMES glfw3
            PATHS ${PROJECT_SOURCE_DIR}/external/glfw_build/src
            DOC "The directory where glfw3 library resides"
)
    
set(glfw3_FOUND "NO")
if (GLFW3_INCLUDE_PATH AND GLFW3_LIBRARIES)
	set(glfw3_FOUND "YES")
    message("External library 'GLFW3' found")
else()
    message(WARNING "External library 'GLFW3' not found")
endif(GLFW3_INCLUDE_PATH AND GLFW3_LIBRARIES)