#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Box2D_shared" for configuration "Debug"
set_property(TARGET Box2D_shared APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(Box2D_shared PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/Box2D.lib"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/Box2D.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS Box2D_shared )
list(APPEND _IMPORT_CHECK_FILES_FOR_Box2D_shared "${_IMPORT_PREFIX}/lib/Box2D.lib" "${_IMPORT_PREFIX}/bin/Box2D.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)