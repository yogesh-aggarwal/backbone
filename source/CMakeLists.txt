# Collect all source files
FILE(GLOB_RECURSE BACKBONE_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/backbone/**/*.hpp)
FILE(GLOB_RECURSE BACKBONE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/backbone/**/*.cpp)
FILE(GLOB_RECURSE BACKBONE_TEMPLATES ${CMAKE_CURRENT_SOURCE_DIR}/backbone/**/*.tcc)

# Create a static library
add_library(backbone STATIC ${BACKBONE_HEADERS} ${BACKBONE_SOURCES} ${BACKBONE_TEMPLATES})

# Include directories for the library
target_include_directories(backbone PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Add compile definitions if needed
target_compile_definitions(backbone PRIVATE DEBUG)
