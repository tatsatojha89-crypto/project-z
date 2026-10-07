cmake_minimum_required(VERSION 3.20)
project(projectz)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(EXISTS "C:/sfml/lib/cmake/SFML")
    set(SFML_DIR "C:/sfml/lib/cmake/SFML")
endif()
find_package(SFML 2.6 QUIET COMPONENTS graphics window system )
if(NOT SFML_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        sfml
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.1
    )
    FetchContent_MakeAvailable(sfml)
endif()
add_executable(${PROJECT_NAME}
    src/main.cpp
)
target_link_libraries(${PROJECT_NAME}
    sfml-graphics
    sfml-window
    sfml-system
)
if(EXISTS "C:/sfml/bin")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "C:/sfml/bin"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
    )
endif()

