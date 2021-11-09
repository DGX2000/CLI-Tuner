find_package(SFML 2 REQUIRED COMPONENTS system window graphics audio)
set(sfml_libs sfml-system sfml-window sfml-graphics sfml-audio)

file(GLOB source_files CONFIGURE_DEPENDS "*.cpp")
add_executable(CliTuner ${source_files})
# TODO: Include curses in a more modern way
target_link_libraries(CliTuner PRIVATE ${sfml_libs} -lcurses)

add_subdirectory(unittest)
