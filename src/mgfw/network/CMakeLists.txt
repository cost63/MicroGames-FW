cmake_minimum_required(VERSION 2.8.9)
project(mgfw_network_lib)
set(CMAKE_BUILD_TYPE Release)

#Bring the headers, such as Student.h into the project
include_directories(include)
ADD_DEFINITIONS(-std=c++11)

find_package(PkgConfig)

pkg_check_modules(GLIB2 REQUIRED glib-2.0)
add_definitions(${GLIB2_CFLAGS})

pkg_check_modules(GTHREAD2 REQUIRED gthread-2.0)
add_definitions(${GTHREAD2_CFLAGS})

#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "src/*.cpp")

#Generate the shared library from the sources
add_library(mgfwnet SHARED ${SOURCES})

#Set the location for library installation -- i.e., /usr/lib in this case
# not really necessary in this example. Use "sudo make install" to apply
install(TARGETS mgfwnet DESTINATION /usr/lib)

install(DIRECTORY inc/ DESTINATION /usr/include/mgfw)
