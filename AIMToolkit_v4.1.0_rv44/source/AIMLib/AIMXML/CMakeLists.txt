project (AIMLib_AIMXML)

include_directories ("${CMAKE_CURRENT_SOURCE_DIR}")
include_directories ("${XERCES_INCLUDE_DIR}")

set (AIMXML_SRC
  AIMXML.cpp
  AIMXML-typeinfo.cpp
  StdAfx.cpp
  )

add_library (AIMXML STATIC ${AIMXML_SRC})

target_link_libraries (AIMXML Altova AltovaXML ${XERCES_LIBRARIES})
