set_property (SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/StreqFast.s APPEND PROPERTY COMPILE_OPTIONS "-x" "assembler-with-cpp")
target_sources (${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
                                        ${CMAKE_CURRENT_SOURCE_DIR}/FileReader.cpp
                                        ${CMAKE_CURRENT_SOURCE_DIR}/DataExporter.cpp
                                        ${CMAKE_CURRENT_SOURCE_DIR}/StreqFast.s)
