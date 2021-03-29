# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("eVTOLSimulation")
# flags

# files

# include

include_directories( ./include ./src )


find_package( Threads )

# target
add_executable( binary ./src/eVTOLSimulation.cpp ./src/AircraftManager.cpp ./src/Aircraft.cpp ./src/SimManager.cpp ./src/Charger.cpp ./src/Time.cpp) 

# external libs
target_link_libraries ( binary ${CMAKE_THREAD_LIBS_INIT})
