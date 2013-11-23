project (AIMLib_AIMConverter)

include_directories ("${CMAKE_CURRENT_SOURCE_DIR}")
include_directories ("${DCMTK_INCLUDE_DIRECTORIES}")

set (AIMCONVERTER_SRC
  AIMConverter.cpp
  ConverterUtil.cpp
  stdafx.cpp
  )

set (AIMCONVERTER_LIBS
  ${AIMLIB_LIBRARY}
  ${DCMTK_LIBRARIES}
  ${XERCES_LIBRARIES})
if (NOT WIN32)
  set (AIMCONVERTER_LIBS
   ${AIMCONVERTER_LIBS}
    -lpthread)
endif ()

link_directories ("${CMAKE_BINARY_DIR}/DCMTK-prefix/lib")

# For PackageMaker method, do not use MACOSX_BUNDLE option
# For DragNDrop method, use MACOSX_BUNDLE option
add_executable (AIMConverter ${AIMCONVERTER_SRC})
#add_executable (AIMConverter MACOSX_BUNDLE ${AIMCONVERTER_SRC})

target_link_libraries (AIMConverter ${AIMCONVERTER_LIBS})

# For PackageMaker method, do not use BUNDLE option
# For DragNDrop method, use BUNDLE option
install (TARGETS AIMConverter DESTINATION bin)
#install (TARGETS AIMConverter 
#    BUNDLE DESTINATION . COMPONENT Runtime
#    RUNTIME DESTINATION bin COMPONENT Runtime)

add_dependencies (AIMConverter 
  ${AIMLIB_LIBRARY} AIMXML AltovaXML Altova DCMTK)
