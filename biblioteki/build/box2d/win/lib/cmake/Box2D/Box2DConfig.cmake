#                                               -*- cmake -*-
#
#  Box2dConfig.cmake(.in)
#

# Use the following variables to compile and link against Box2d:
#  BOX2D_FOUND          - True if Box2d was found on your system
#  BOX2D_USE_FILE       - The file making Box2d usable
#  BOX2D_DEFINITIONS    - Definitions needed to build with Box2d
#  BOX2D_INCLUDE_DIR    - Box2d headers location
#  BOX2D_INCLUDE_DIRS   - List of directories where Box2d header file are
#  BOX2D_LIBRARY        - Library name
#  BOX2D_LIBRARIES      - List of libraries to link against
#  BOX2D_LIBRARY_DIRS   - List of directories containing Box2d libraries
#  BOX2D_ROOT_DIR       - The base directory of Box2d
#  BOX2D_VERSION_STRING - A human-readable string containing the version

set ( BOX2D_FOUND 1 )
set ( BOX2D_USE_FILE     "C:/Users/michalpiekarski/Documents/WSNHiD/CG-projekt-brickpong/biblioteki/build/box2d/win/lib/cmake/Box2D/UseBox2D.cmake" )

set ( BOX2D_DEFINITIONS  "" )
set ( BOX2D_INCLUDE_DIR  "C:/Users/michalpiekarski/Documents/WSNHiD/CG-projekt-brickpong/biblioteki/build/box2d/win/include" )
set ( Box2D_INCLUDE_DIRS "C:/Users/michalpiekarski/Documents/WSNHiD/CG-projekt-brickpong/biblioteki/build/box2d/win/include" ) # deprecated
set ( BOX2D_INCLUDE_DIRS "C:/Users/michalpiekarski/Documents/WSNHiD/CG-projekt-brickpong/biblioteki/build/box2d/win/include" )
set ( BOX2D_LIBRARY      "Box2D" )
set ( BOX2D_LIBRARIES    "Box2D" )
set ( BOX2D_LIBRARY_DIRS "C:/Users/michalpiekarski/Documents/WSNHiD/CG-projekt-brickpong/biblioteki/build/box2d/win/lib" )
set ( BOX2D_ROOT_DIR     "C:/Users/michalpiekarski/Documents/WSNHiD/CG-projekt-brickpong/biblioteki/build/box2d/win" )

set ( BOX2D_VERSION_STRING "2.3.0" )

