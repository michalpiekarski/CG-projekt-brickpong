#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "glfw" for configuration "Debug"
set_property(TARGET glfw APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(glfw PROPERTIES
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "/System/Library/Frameworks/Cocoa.framework;/System/Library/Frameworks/OpenGL.framework;/System/Library/Frameworks/IOKit.framework;/System/Library/Frameworks/CoreFoundation.framework;/System/Library/Frameworks/CoreVideo.framework"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib64/libglfw.3.1.dylib"
  IMPORTED_SONAME_DEBUG "/Users/michalpiekarski/Documents/WSNHiD/Projekty/CG-projekt-brickpong/biblioteki/build/glfw/osx/lib64/libglfw.3.dylib"
  )

list(APPEND _IMPORT_CHECK_TARGETS glfw )
list(APPEND _IMPORT_CHECK_FILES_FOR_glfw "${_IMPORT_PREFIX}/lib64/libglfw.3.1.dylib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
