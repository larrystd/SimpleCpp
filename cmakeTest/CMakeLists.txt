cmake_minimum_required(VERSION 2.8)
project(helloworld)

# Add the source in project root directory
aux_source_directory(. DIRSRCS)
# Add header file include directories
#include_directories(./ ./hello)
# Add block directories
add_subdirectory(hello)

message(STATUS, ${X})
list(APPEND EXTRA_LIBS hello)
# Target
add_executable(helloworld ${DIRSRCS})
target_link_libraries(helloworld hello)
target_include_directories(helloworld PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/hello"
                          )
install(TARGETS helloworld DESTINATION bin)