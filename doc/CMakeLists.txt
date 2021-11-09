find_package(Doxygen 1.9.1)

if(DOXYGEN_FOUND)
  set(doxyfile ${CMAKE_CURRENT_SOURCE_DIR}/../doc/Doxyfile)

  add_custom_target(doc COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile}
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../doc
                        VERBATIM)
endif()
