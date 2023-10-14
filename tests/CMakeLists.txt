
find_package(Catch2 REQUIRED)

include(CTest)
enable_testing()

# Add the executable
add_executable(tests 
    tests.cpp
    test_play_tone.cpp
)

target_include_directories(tests PUBLIC
	${catch2_INCLUDE_DIR}
	${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(tests 
	${catch2_LIBRARIES}
	synthengine
)