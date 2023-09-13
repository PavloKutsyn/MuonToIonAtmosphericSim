#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 3.22 FATAL_ERROR)
project(MuonToIonAtmosphericSim)

#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
#
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
#
include(${Geant4_USE_FILE})

#----------------------------------------------------------------------------
# Locate sources and headers for this project
#
include_directories(${PROJECT_SOURCE_DIR}/include 
                    ${Geant4_INCLUDE_DIR})
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

##Setup CRY-----------------------------------
#find_library( CRY NAMES CRY PATHS $ENV{CRYHOME}/lib NO_DEFAULT_PATH )
#
#set(CRY_INCLUDE_DIRS $ENV{CRYHOME}/src)
#MESSAGE ("Cry setup: " ${CRY_INCLUDE_DIRS} )
#set(CRY_LIBRARY_DIR ${CRYHOME}/lib)
#
#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
add_executable(execute main.cc ${sources} ${headers})
target_link_libraries(execute ${Geant4_LIBRARIES} )
target_link_libraries(execute /home/pavlo/GEANT4_ROOT/cry_v1.7/lib/libCRY.a)

#----------------------------------------------------------------------------
# Copy all scripts to the build directory, i.e. the directory in which we
# build TestEm17. This is so that we can run the executable directly because it
# relies on these scripts being in the current working directory.
#
set(execute_SCRIPTS
    run.f vis.mac
  )

foreach(_script ${execute_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()

#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
install(TARGETS execute DESTINATION bin)
