find_package(Catch2 REQUIRED)

file(GLOB test_files CONFIGURE_DEPENDS "*.cpp")

add_executable(tests ${test_files})
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
target_include_directories(tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
