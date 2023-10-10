# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\ConsoleExample_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\ConsoleExample_autogen.dir\\ParseCache.txt"
  "ConsoleExample_autogen"
  )
endif()
