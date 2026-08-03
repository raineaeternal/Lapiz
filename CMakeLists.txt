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

# common per-target setup, shared between the main library and the test library below
function(shared_setup TARGET)
    # add include dir as include dir
    target_include_directories(${TARGET} PRIVATE ${INCLUDE_DIR})
    # add shared dir as include dir
    target_include_directories(${TARGET} PUBLIC ${SHARED_DIR})

    target_link_libraries(${TARGET} PRIVATE -llog)

    # add extern stuff like libs and other includes, using the target's own compile id
    set(OLD_COMPILE_ID ${COMPILE_ID})
    set(COMPILE_ID ${TARGET})
    include(extern.cmake)
    set(COMPILE_ID ${OLD_COMPILE_ID})

    add_custom_command(
        TARGET ${TARGET}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory "debug"
        COMMAND ${CMAKE_COMMAND} -E rename "lib${TARGET}.so" "debug/lib${TARGET}.so"
        COMMAND ${CMAKE_STRIP} -d --strip-all "debug/lib${TARGET}.so" -o "lib${TARGET}.so"
        COMMENT "Create stripped and debug libraries"
    )
endfunction()

# recursively get all src files, excluding src/test which is built as its own test library below
RECURSE_FILES(cpp_file_list ${SOURCE_DIR}/*.cpp)
RECURSE_FILES(c_file_list ${SOURCE_DIR}/*.c)
list(FILTER cpp_file_list EXCLUDE REGEX "${SOURCE_DIR}/test/.*")
list(FILTER c_file_list EXCLUDE REGEX "${SOURCE_DIR}/test/.*")

# add all src files to compile
add_library(${COMPILE_ID} SHARED ${cpp_file_list} ${c_file_list})

shared_setup(${COMPILE_ID})

# Create test target: a separate mod that links against ${COMPILE_ID} and exercises it at runtime
set(TEST_ID test-${COMPILE_ID})

RECURSE_FILES(cpp_test_list ${SOURCE_DIR}/test/*.cpp)
RECURSE_FILES(c_test_list ${SOURCE_DIR}/test/*.c)

add_library(${TEST_ID} SHARED ${cpp_test_list} ${c_test_list})

shared_setup(${TEST_ID})

add_dependencies(${TEST_ID} ${COMPILE_ID})
target_link_libraries(${TEST_ID} PRIVATE ${COMPILE_ID})
