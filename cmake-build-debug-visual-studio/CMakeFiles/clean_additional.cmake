# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Dialog_test2_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Dialog_test2_autogen.dir\\ParseCache.txt"
  "Dialog_test2_autogen"
  )
endif()
