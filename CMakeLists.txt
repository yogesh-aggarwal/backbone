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

set(DNS_DEBUG_AS_APPLICATION ON)
# set(DNS_DEBUG_AS_APPLICATION OFF)

if(DNS_DEBUG_AS_APPLICATION)
   add_compile_definitions(DNS_DEBUG_AS_APPLICATION)
endif()

add_compile_definitions(
   DEBUG

   # DNS_DISABLE_LOGGING
   # DNS_DISABLE_LOGGING_OUTPUT_TO_FILE
)

# ----------------------------------------------------------------------------------------------------------------------
# ---- Project Setup ---------------------------------------------------------------------------------------------------
# ----------------------------------------------------------------------------------------------------------------------

project(DNS)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "-pthread")
set(NO_DEFAULT_PATH true)
set(CMAKE_MAKE_PROGRAM "make -j 16")

# ----------------------------------------------------------------------------------------------------------------------
# ---- Files -----------------------------------------------------------------------------------------------------------
# ----------------------------------------------------------------------------------------------------------------------

FILE(GLOB_RECURSE DNS_HEADER_FILES Source/*.hpp)
FILE(GLOB_RECURSE DNS_SOURCE_FILES Source/*.cpp)
FILE(GLOB_RECURSE DNS_TEMPLATE_FILES Source/*.tcc)

set(DNS_ALL_FILES ${DNS_HEADER_FILES} ${DNS_SOURCE_FILES} ${DNS_TEMPLATE_FILES})

# ----------------------------------------------------------------------------------------------------------------------
# ---- Product ---------------------------------------------------------------------------------------------------------
# ----------------------------------------------------------------------------------------------------------------------

include_directories(Source)

if(DNS_DEBUG_AS_APPLICATION)
   add_executable(${PROJECT_NAME} ${DNS_ALL_FILES})
else()
   add_library(${PROJECT_NAME} ${DNS_ALL_FILES})
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

# FILE(GLOB_RECURSE DNS_PCH_FILES Source/DNS/Core/*.hpp)
# target_precompile_headers(${PROJECT_NAME} PUBLIC ${DNS_PCH_FILES})

# ----------------------------------------------------------------------------------------------------------------------
# ---- Installation ----------------------------------------------------------------------------------------------------
# ----------------------------------------------------------------------------------------------------------------------
set(CMAKE_INSTALL_PREFIX "/usr")
install(DIRECTORY Source/DNS
   DESTINATION include
   FILES_MATCHING
   PATTERN "*.hpp"
   PATTERN "*.tcc")
install(TARGETS ${PROJECT_NAME}
   LIBRARY DESTINATION lib)
