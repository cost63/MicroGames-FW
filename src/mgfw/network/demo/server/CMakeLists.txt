cmake_minimum_required(VERSION 2.8.9)
project(mgfw_net_server)
set(CMAKE_BUILD_TYPE Release)

ADD_DEFINITIONS(-std=c++11)

#Bring the headers, such as Student.h into the project
include_directories(include)
include_directories($ENV{HOST_CROSS_SYSROOT_DIR}/usr/include)
link_directories($ENV{HOST_CROSS_SYSROOT_DIR}/usr/lib)


find_package(PkgConfig)


pkg_check_modules(GTHREAD2 REQUIRED gthread-2.0)
add_definitions(${GTHREAD2_CFLAGS})

#However, the file(GLOB...) allows for wildcard additions:

file(GLOB src_cxx *.cpp)

add_executable(server_demo ${src_cxx})

#Generate the shared library from the sources
target_link_libraries(server_demo -lmgfwnet ${GLIB2_LDFLAGS} ${GTHREAD2_LDFLAGS})

#Set the location for library installation -- i.e., /usr/lib in this case
install(TARGETS server_demo DESTINATION /usr/bin/)





