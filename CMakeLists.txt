cmake_minimum_required(VERSION 2.6)
project(game)

# Enable debug symbols by default
if(CMAKE_BUILD_TYPE STREQUAL "")
      set(CMAKE_BUILD_TYPE Debug)
endif()

# Set version information in a config.h file
set(game_VERSION_MAJOR 0)
set(game_VERSION_MINOR 1)
set(RES_X 1024)
set(RES_Y 578)
configure_file(
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
)
include_directories("${PROJECT_BINARY_DIR}")

#Add AdditionalLibraryDirectories for Visual Studio
if(WIN32)
	link_directories("C:/lib/SFML-2.4.2-Win-VC14x32/lib")
endif(WIN32)

# Define sources and executable
set(EXECUTABLE_NAME "game")
add_executable(${EXECUTABLE_NAME}
    main.cpp
    Engine/controls.h
    Engine/controls.cpp
    Engine/drawmap.h
    Engine/drawmap.cpp

)
#Detect and add SFML

set(SFML_ROOT ${SFML_DIR})
if(!STP_SHARED_LIBS)
    add_definitions(-DSFML_STATIC)
endif()
if (SFML_INCLUDE_DIR)
    set(SFML_LIBRARIES sfml-graphics-d sfml-window-d sfml-audio-d sfml-system-d)

else()
	set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
    find_package(SFML 2 COMPONENTS graphics window audio system)
    if(SFML_FOUND)
        # Nothing to do, already there
    elseif(SFML_SOURCE_DIR AND SFML_BINARY_DIR)
        set(SFML_INCLUDE_DIR "${SFML_SOURCE_DIR}/include")
        set(SFML_LIBRARIES sfml-graphics sfml-window sfml-audio sfml-system)
    else()
        message("\n-> SFML directory not found. Put the SFML's top-level path "
                "(containing \"include\" and \"lib\" directories) in the "
                "/extlibs/SFML folder.\n")
    endif()
endif()

include_directories(${SFML_INCLUDE_DIR})
target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES}${SFML_DEPENDENCIES})


# Install target
install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)

# CPack packaging
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/COPYING")
set(CPACK_PACKAGE_VERSION_MAJOR "${game_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${game_VERSION_MINOR}")
include(CPack)
