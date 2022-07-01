find_path(GLM_INCLUDE_PATH glm/glm.hpp 
                PATHS 
                ${PROJECT_SOURCE_DIR}/external/glm
                DOC "The directory where glm/glm.hpp resides"
        )

set(glm_FOUND "NO")
if(GLM_INCLUDE_PATH)
	set(glm_FOUND "YES")
    message("External library 'GLM' found")
else()
    message(WARNING "External library 'GLM' not found")
endif(GLM_INCLUDE_PATH)