project (AIMLib_AltovaXML)

include_directories ("${CMAKE_CURRENT_SOURCE_DIR}")
include_directories ("${XERCES_INCLUDE_DIR}")

set (ALTOVAXML_SRC
  Node.cpp
  StdAfx.cpp
  XmlException.cpp
  )

add_library (AltovaXML STATIC ${ALTOVAXML_SRC})

target_link_libraries (AltovaXML Altova ${XERCES_LIBRARIES})
