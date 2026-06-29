# include some defines automatically made by qpm
include(qpm_defines.cmake)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)

cmake_minimum_required(VERSION 3.21)
project(${COMPILE_ID})

# c++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED 23)

# define that stores the actual source directory
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_link_options(-Wl,--exclude-libs,ALL)
# compile options used
add_compile_options(-frtti -fexceptions -fdeclspec -fvisibility=hidden)
add_compile_options(-O3)
# compile definitions used
add_compile_definitions(VERSION="${MOD_VERSION}")
add_compile_definitions(VERSION_LONG=0)
add_compile_definitions(MOD_ID="${MOD_ID}")

# Trim source folder in logcat messages
string(LENGTH "${CMAKE_CURRENT_SOURCE_DIR}/" FOLDER_LENGTH)
add_compile_definitions("PAPER_ROOT_FOLDER_LENGTH=${FOLDER_LENGTH}")

# recursively get all src files
RECURSE_FILES(cpp_file_list ${SOURCE_DIR}/*.cpp)
RECURSE_FILES(c_file_list ${SOURCE_DIR}/*.c)

# add all src files to compile
add_library(${COMPILE_ID} SHARED ${cpp_file_list} ${c_file_list})

# add include dir as include dir
target_include_directories(${COMPILE_ID} PRIVATE ${INCLUDE_DIR})
# add shared dir as include dir
target_include_directories(${COMPILE_ID} PUBLIC ${SHARED_DIR})

target_link_libraries(${COMPILE_ID} PRIVATE -llog)
# add extern stuff like libs and other includes
include(extern.cmake)

add_custom_command(
    TARGET ${COMPILE_ID}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "debug"
    COMMAND ${CMAKE_COMMAND} -E rename "lib${COMPILE_ID}.so" "debug/lib${COMPILE_ID}.so"
    COMMAND ${CMAKE_STRIP} -d --strip-all "debug/lib${COMPILE_ID}.so" -o "lib${COMPILE_ID}.so"
    COMMENT "Create stripped and debug libraries"
)
