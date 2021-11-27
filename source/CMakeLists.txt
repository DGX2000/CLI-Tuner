find_package(SFML 2 REQUIRED COMPONENTS audio)
set(sfml_libs sfml-audio)

file(GLOB source_files CONFIGURE_DEPENDS "*.cpp")
add_executable(CliTuner ${source_files})
target_link_libraries(CliTuner PRIVATE ${sfml_libs} -lcurses)

add_subdirectory(unittest)
