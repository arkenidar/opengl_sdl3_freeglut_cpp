# CMakeLists.txt

cmake_minimum_required(VERSION 3.10)

project(app VERSION 1.0)

# Source files
file(GLOB SOURCES
    *.cpp
)
# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# sdl 3 begin ----------------------------------------------
# Find SDL3
#find_package(SDL3 REQUIRED)

# By configuring CMake with -DDOWNLOAD_DEPENDENCIES=ON/OFF,
# users can choose between downloading dependencies or using system libraries
option(DOWNLOAD_DEPENDENCIES "Download dependencies" FALSE)

if(DOWNLOAD_DEPENDENCIES)
    # FetchContent downloads and configures dependencies
    include(FetchContent)
    FetchContent_Declare(
        SDL3
        GIT_REPOSITORY "https://github.com/libsdl-org/SDL.git"
        GIT_TAG "main"
        EXCLUDE_FROM_ALL
    )
    FetchContent_MakeAvailable(SDL3)
else()
    # find_package looks for already-installed system packages.
    # Configure with `-DCMAKE_PREFIX_PATH="/path/to/package1;/path/to/package2"`
    # to add search paths.
    find_package(SDL3 CONFIG REQUIRED)
endif()
# sdl 3 end --------------------------------------------

# Link SDL3
target_link_libraries(${PROJECT_NAME} SDL3::SDL3)

# Set OpenGL policy to fix warning
cmake_policy(SET CMP0072 NEW)

# Find OpenGL and GLUT
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories(
    ${OPENGL_INCLUDE_DIRS}
    ${GLUT_INCLUDE_DIRS}
    )
 
target_link_libraries(${PROJECT_NAME} 
${OPENGL_LIBRARIES}
${GLUT_LIBRARIES}
)
