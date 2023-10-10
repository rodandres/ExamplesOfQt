# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\SerialExample_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\SerialExample_autogen.dir\\ParseCache.txt"
  "SerialExample_autogen"
  )
endif()
