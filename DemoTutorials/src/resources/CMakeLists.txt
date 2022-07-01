
set(project_resources)

file(GLOB 
        resources *.vs  *.fs #vertex and fra
    ) 

list(APPEND project_resources ${resources})

# Copy all of the resource files to the build folder
file(COPY ${project_resources} DESTINATION "resources/")

install(FILES ${project_resources} DESTINATION "bin/resources/")
