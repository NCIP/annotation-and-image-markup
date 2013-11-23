project (AIMLib_AIMLibTest)

include_directories ("${CMAKE_CURRENT_SOURCE_DIR}")
include_directories ("${DCMTK_INCLUDE_DIRECTORIES}")

set (AIMLIBTEST_SRC
  AIMLibTest.cpp
  )

set (AIMLIBTEST_LIBS
  ${AIMLIB_LIBRARY}
  ${DCMTK_LIBRARIES}
  ${XERCES_LIBRARIES})
if (NOT WIN32)
  set (AIMLIBTEST_LIBS
    ${AIMLIBTEST_LIBS}
    -lpthread)
endif ()

link_directories ("${CMAKE_BINARY_DIR}/DCMTK-prefix/lib")

add_executable (AIMLibTest ${AIMLIBTEST_SRC})

target_link_libraries (AIMLibTest ${AIMLIBTEST_LIBS})
  
install (TARGETS AIMLibTest DESTINATION bin)

add_dependencies (AIMLibTest 
  ${AIMLIB_LIBRARY} AIMXML AltovaXML Altova DCMTK)
