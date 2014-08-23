# - Config file for the glfw package
# It defines the following variables
#   GLFW_INCLUDE_DIR, the path where GLFW headers are located
#   GLFW_LIBRARY_DIR, folder in which the GLFW library is located
#   GLFW_LIBRARY, library to link against to use GLFW

set(GLFW_INCLUDE_DIR "C:/Users/michalpiekarski/Documents/WSNHiD/CG-projekt-brickpong/biblioteki/build/glfw/win/include")
set(GLFW_LIBRARY_DIR "C:/Users/michalpiekarski/Documents/WSNHiD/CG-projekt-brickpong/biblioteki/build/glfw/win/lib")

find_library(GLFW_LIBRARY "glfw3" HINTS ${GLFW_LIBRARY_DIR})
