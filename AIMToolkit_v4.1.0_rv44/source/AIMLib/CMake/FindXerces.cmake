# - Find xerces
# This will set the following variables
#
#  XERCES_INCLUDE_DIR - where to find include directories
#  XERCES_DEBUG_LIBRARIES   - list of libraries to link with when using xerces
#  XERCES_RELEASE_LIBRARIES   - list of libraries to link with when using xerces
#  XERCES_FOUND       - true if xerces was found

if (NOT XERCES_FOUND AND NOT XERCES_DIR)
  set (XERCES_DIR "" CACHE PATH "Root of Xerces install tree (optional).")
endif()

if (XERCES_INCLUDE_DIR)
  # Already in cache, be silent
  set (xerces_FIND_QUIETLY TRUE)
endif ()

find_path (XERCES_INCLUDE_DIR 
  NAMES
  xercesc/util/XercesVersion.hpp
  PATHS
  ${XERCES_DIR}/include
  /usr/include
  /usr/local/include
  )

find_library (XERCES_LIBRARY 
  NAMES 
  xerces-c
  PATHS
  ${XERCES_DIR}/lib
  /usr/lib64
  )

# handle the QUIETLY and REQUIRED arguments and set XERCES_FOUND to TRUE if 
# all listed variables are TRUE
include (FindPackageHandleStandardArgs)
find_package_handle_standard_args (Xerces 
  DEFAULT_MSG XERCES_LIBRARY XERCES_INCLUDE_DIR)

if (XERCES_FOUND)
  set (XERCES_DEBUG_LIBRARIES ${XERCES_LIBRARY})
  set (XERCES_RELEASE_LIBRARIES ${XERCES_LIBRARY})
else ()
  set (XERCES_DEBUG_LIBRARIES)
  set (XERCES_RELEASE_LIBRARIES)
endif ()

mark_as_advanced (XERCES_LIBRARY XERCES_INCLUDE_DIR)
