# CMakeList.txt : CMake project for Roarsomecpp, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

add_compile_definitions(UNICODE)


project ("Roarsome")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:wwinmainCRTStartup")

#find_library(GDIP gdiplus)
find_library(GDIPLUS_LIBRARY NAMES libgdiplus gdiplus)
set(GDIPLUS_LIBRARY gdiplus)

# Add source to this project's executable.
add_executable (Roarsomecpp WIN32 "Roarsomecpp.cpp" "Roarsomecpp.h" "Creature.ixx" "Decisions/Decision.ixx" "UpdateInfo.ixx" "App.ixx" "Decisions/Wander.ixx" "Decisions/ChaseCursor.ixx")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Roarsomecpp PROPERTY CXX_STANDARD 20)
endif()

if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
	set(CMAKE_CXX_FLAGS_DEBUG "/MDd /ZI /Ob0 /Od /RTC1")
endif()

target_link_libraries(Roarsomecpp gdiplus)