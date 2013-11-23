project (AIMLib_Altova)

include_directories ("${CMAKE_CURRENT_SOURCE_DIR}")

set (ALTOVA_SRC
  AltovaException.cpp
  SchemaTypes.cpp
  StdAfx.cpp
  StructInfo.cpp
  xs-datetime.cpp
  xs-types.cpp
  )

add_library (Altova STATIC ${ALTOVA_SRC})
