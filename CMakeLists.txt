cmake_minimum_required (VERSION 3.8 FATAL_ERROR)

project (HashTableBenchmark)

set (DEBUG_FLAGS -ggdb3 -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wno-format-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wno-switch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wno-unused-parameter -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -fPIC -fno-omit-frame-pointer -pie -fPIE -Werror=vla -Wno-write-strings -march=native)
set (RELEASE_FLAGS -O3 -std=c++17 -march=native)
set (REL_WITH_DEB_INFO_FLAGS -std=c++17 -march=native)


add_executable (${PROJECT_NAME})

target_compile_options (${PROJECT_NAME} PRIVATE $<$<CONFIG:Debug>:${DEBUG_FLAGS}>)
target_compile_options (${PROJECT_NAME} PRIVATE $<$<CONFIG:Release>:${RELEASE_FLAGS}>)
target_compile_options (${PROJECT_NAME} PRIVATE $<$<CONFIG:RelWithDebInfo>:${REL_WITH_DEB_INFO_FLAGS}>)


target_link_options (${PROJECT_NAME} PRIVATE $<$<CONFIG:Debug>:${DEBUG_FLAGS}>)
target_link_options (${PROJECT_NAME} PRIVATE $<$<CONFIG:Release>:${RELEASE_FLAGS}>)
target_link_options (${PROJECT_NAME} PRIVATE $<$<CONFIG:RelWithDebInfo>:${REL_WITH_DEB_INFO_FLAGS}>)

target_compile_definitions (${PROJECT_NAME} PRIVATE TRACY_ENABLE TRACY_NO_EXIT)

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

