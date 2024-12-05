cmake_minimum_required(VERSION 3.20)

# ----------------------------------------------------------------------------------------------------------------------
# ---- Helper Functions ------------------------------------------------------------------------------------------------
# ----------------------------------------------------------------------------------------------------------------------

function(SUCCESS message)
   message("[SUCCESS] ${message}")
endfunction()

function(LINK_LIBRARY libVendorPath libName)
   add_subdirectory("Vendor/${libVendorPath}")
   target_link_libraries(${PROJECT_NAME} PRIVATE ${libName})
   include_directories("Vendor/${libVendorPath}/include")
   SUCCESS("Linked library: ${libName}")
endfunction()

# ----------------------------------------------------------------------------------------------------------------------
# ---- Compile-Time Defines --------------------------------------------------------------------------------------------
# ----------------------------------------------------------------------------------------------------------------------

set(BACKBONE_DEBUG_AS_APPLICATION ON)
# set(BACKBONE_DEBUG_AS_APPLICATION OFF)

if(BACKBONE_DEBUG_AS_APPLICATION)
   add_compile_definitions(BACKBONE_DEBUG_AS_APPLICATION)
endif()

add_compile_definitions(
   DEBUG

   # BACKBONE_DISABLE_LOGGING
   # BACKBONE_DISABLE_LOGGING_OUTPUT_TO_FILE
)

# ----------------------------------------------------------------------------------------------------------------------
# ---- Project Setup ---------------------------------------------------------------------------------------------------
# ----------------------------------------------------------------------------------------------------------------------

project(backbone)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "-pthread")
set(NO_DEFAULT_PATH true)
set(CMAKE_MAKE_PROGRAM "make -j 16")

# ----------------------------------------------------------------------------------------------------------------------
# ---- Files -----------------------------------------------------------------------------------------------------------
# ----------------------------------------------------------------------------------------------------------------------

FILE(GLOB_RECURSE BACKBONE_HEADER_FILES source/*.hpp)
FILE(GLOB_RECURSE BACKBONE_SOURCE_FILES source/*.cpp)
FILE(GLOB_RECURSE BACKBONE_TEMPLATE_FILES source/*.tcc)

set(BACKBONE_ALL_FILES ${BACKBONE_HEADER_FILES} ${BACKBONE_SOURCE_FILES} ${BACKBONE_TEMPLATE_FILES})

# ----------------------------------------------------------------------------------------------------------------------
# ---- Product ---------------------------------------------------------------------------------------------------------
# ----------------------------------------------------------------------------------------------------------------------

include_directories(source)

if(BACKBONE_DEBUG_AS_APPLICATION)
   add_executable(${PROJECT_NAME} ${BACKBONE_ALL_FILES})
else()
   add_library(${PROJECT_NAME} ${BACKBONE_ALL_FILES})
endif()

# ----------------------------------------------------------------------------------------------------------------------
# ---- Link Libraries --------------------------------------------------------------------------------------------------
# ----------------------------------------------------------------------------------------------------------------------

message("[(---- Linking Libraries ----)]")

# # nanoid_cpp Library
# add_subdirectory("Vendor/nanoid_cpp")
# target_link_libraries(${CMAKE_PROJECT_NAME} nanoid)
# include_directories("Vendor/nanoid_cpp/inc")

message("[(---- Done Linking Libraries ----)]\n")

# ----------------------------------------------------------------------------------------------------------------------
# ---- PCHs ------------------------------------------------------------------------------------------------------------
# ----------------------------------------------------------------------------------------------------------------------

# FILE(GLOB_RECURSE BACKBONE_PCH_FILES source/backbone/Core/*.hpp)
# target_precompile_headers(${PROJECT_NAME} PUBLIC ${BACKBONE_PCH_FILES})

# ----------------------------------------------------------------------------------------------------------------------
# ---- Installation ----------------------------------------------------------------------------------------------------
# ----------------------------------------------------------------------------------------------------------------------
set(CMAKE_INSTALL_PREFIX "/usr")
install(DIRECTORY source/backbone
   DESTINATION include
   FILES_MATCHING
   PATTERN "*.hpp"
   PATTERN "*.tcc")
install(TARGETS ${PROJECT_NAME}
   LIBRARY DESTINATION lib)
