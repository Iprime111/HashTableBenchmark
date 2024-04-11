add_subdirectory (HashTable)
add_subdirectory (Buffer)

target_sources (${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tracy/public/TracyClient.cpp)
target_include_directories (${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tracy/public/tracy/)
