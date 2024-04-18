cmake_minimum_required (VERSION 3.8 FATAL_ERROR)

project (HashTableBenchmark LANGUAGES CXX ASM)

set (DEBUG_FLAGS -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wno-format-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wno-switch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wno-unused-parameter -Wstack-protector -Werror=vla -Wno-write-strings -fsanitize=address)

set (COMMON_FLAGS -g -std=c++17 -march=native -flto=auto -fno-omit-frame-pointer -rdynamic)
set (NO_OPTIMIZATIONS_FLAGS -O0 -DNDEBUG)
set (OPTIMIZATIONS_FLAGS -O3 -DNDEBUG)

add_executable (${PROJECT_NAME})
target_compile_options (${PROJECT_NAME} PRIVATE ${COMMON_FLAGS})
target_compile_options (${PROJECT_NAME} PRIVATE $<$<CONFIG:Debug>:${DEBUG_FLAGS}>)
target_compile_options (${PROJECT_NAME} PRIVATE $<$<CONFIG:NoOptimizations>:${NO_OPTIMIZATIONS_FLAGS}>)
target_compile_options (${PROJECT_NAME} PRIVATE $<$<CONFIG:Optimizations>:${OPTIMIZATIONS_FLAGS}>)

if (${PGO_GENERATE} STREQUAL 1)
    target_compile_options (${PROJECT_NAME} PRIVATE -fprofile-generate)
    target_link_options    (${PROJECT_NAME} PRIVATE -fprofile-generate)
endif ()

if (${PGO_USE} STREQUAL 1)
    target_compile_options (${PROJECT_NAME} PRIVATE -fprofile-use)
    target_link_options    (${PROJECT_NAME} PRIVATE -fprofile-use)
endif ()

target_link_options (${PROJECT_NAME} PRIVATE ${COMMON_FLAGS})
target_link_options (${PROJECT_NAME} PRIVATE $<$<CONFIG:Debug>:${DEBUG_FLAGS}>)
target_link_options (${PROJECT_NAME} PRIVATE $<$<CONFIG:NoOptimizations>:${NO_OPTIMIZATIONS_FLAGS}>)
target_link_options (${PROJECT_NAME} PRIVATE $<$<CONFIG:Optimizations>:${OPTIMIZATIONS_FLAGS}>)

target_compile_definitions (${PROJECT_NAME} PRIVATE TRACY_ENABLE)

add_subdirectory (src)
add_subdirectory (libs)
target_include_directories (${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries (${PROJECT_NAME} PUBLIC HashTable Buffer ${CMAKE_DL_LIBS} pthread)

set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set_target_properties (${PROJECT_NAME} PROPERTIES
                       ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
                       LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
                       RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

configure_file (${CMAKE_CURRENT_SOURCE_DIR}/TextTransformer/text_out.txt ${CMAKE_BINARY_DIR}/bin/words.txt COPYONLY)

unset (PGO_GENERATE)
unset (PGO_USE)
