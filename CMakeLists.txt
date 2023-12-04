#CMAKE 3.7
#lsall version 1.6.1


cmake_minimum_required(VERSION 3.7)

project(lsa VERSION 1.6.1)

#standard version
add_compile_options(-Wall -Wextra)
add_compile_options(-std=c++2a -g -Wno-unused-function)
add_compile_options(-I ${CMAKE_CURRENT_SOURCE_DIR}/include)

#Executables
add_executable(lsa src/lsa.cpp src/main.cpp)
add_executable(lsall src/lsa.cpp src/main.cpp)

#include(InstallRequiredSystemLibraries)
#set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
#set(CPACK_PACKAGE_VERSION_MAJOR "${Tutorial_VERSION_MAJOR}")
#set(CPACK_PACKAGE_VERSION_MINOR "${Tutorial_VERSION_MINOR}")
#set(CPACK_SOURCE_GENERATOR "TGZ")
#include(CPack)



