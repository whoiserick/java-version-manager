# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles\\VersionManager_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\VersionManager_autogen.dir\\ParseCache.txt"
  "VersionManager_autogen"
  )
endif()
