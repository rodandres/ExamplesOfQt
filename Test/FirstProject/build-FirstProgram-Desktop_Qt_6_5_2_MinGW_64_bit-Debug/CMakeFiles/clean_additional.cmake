# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\FirstProgram_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\FirstProgram_autogen.dir\\ParseCache.txt"
  "FirstProgram_autogen"
  )
endif()
