# Add subdirectories for each executable
add_subdirectory(run)

# An optional test directory for developers' local run and testing
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/test")
   add_subdirectory(test)
endif()
