# See building.txt for details on tested platforms
project (AIM)
cmake_minimum_required (VERSION 2.8)

# Here you set the version number which will be used to create 
# the filenames for versioned shared libraries (e.g. libAIM.so.4.1)
# and binary packages (e.g. AIM-4.1.0-x86_64.tar.gz)
set (AIM_VERSION_MAJOR "4")
set (AIM_VERSION_MINOR "1")
set (AIM_VERSION_PATCH "0")

# User options 
option (BUILD_SHARED_LIBS 
  "Build aim as shared library" ON)

# Check for unsupported compilers
if (WIN32 AND NOT MSVC90 AND NOT MSVC10)
  message (WARNING 
    "AIMLib has only been tested on Microsoft Visual Studio 2008 and 2010.  Proceed with caution.")
endif ()

# Default to release build
if (NOT MSVC AND NOT CMAKE_BUILD_TYPE)
  set (CMAKE_BUILD_TYPE "Release" CACHE STRING
    "Choose the type of build, options are: Debug Release
      RelWithDebInfo MinSizeRel." FORCE)
endif ()

# Add the path to AIM-specific cmake code
set (CMAKE_MODULE_PATH 
  "${CMAKE_SOURCE_DIR}/AIMLib/CMake" ${CMAKE_MODULE_PATH})

### DCMTK section
# These flags are for C & C++
set (DCMTK_C_FLAGS "${CMAKE_C_FLAGS} -DHAVE_STL -DHAVE_STD_STRING -DLOG4CPLUS_DISABLE_WARN")
set (DCMTK_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DHAVE_STL -DHAVE_STD_STRING -DLOG4CPLUS_DISABLE_WARN")

set (DCMTK_CMAKE_OPTIONS
  -DBUILD_APPS:BOOL=OFF
  -DBUILD_SHARED_LIBS:BOOL=OFF
  -DDCMTK_FORCE_FPIC_ON_UNIX:BOOL=ON
  -DDCMTK_OVERWRITE_WIN32_COMPILER_FLAGS:BOOL=OFF
  -DDCMTK_WITH_OPENSSL:BOOL=OFF
  -DDCMTK_WITH_PNG:BOOL=OFF
  -DDCMTK_WITH_TIFF:BOOL=OFF
  -DDCMTK_WITH_XML:BOOL=OFF
  -DDCMTK_WITH_ZLIB:BOOL=OFF
  -DCMAKE_C_FLAGS:STRING=${DCMTK_C_FLAGS}
  -DCMAKE_CXX_FLAGS:STRING=${DCMTK_CXX_FLAGS}
#  -DCMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE}
  )

include(ExternalProject)
ExternalProject_Add (
  DCMTK
  SOURCE_DIR "${CMAKE_SOURCE_DIR}/dcmtk-3.6.1_20121102"
  CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
  ${DCMTK_CMAKE_OPTIONS}
  )
set (DCMTK_INCLUDE_DIRECTORIES "${CMAKE_BINARY_DIR}/DCMTK-prefix/include")
set (DCMTK_LIBRARIES dcmdata dcmsr dcmimgle dcmimage oflog ofstd)
set (DCMTK_DIR ${CMAKE_BINARY_DIR}/${proj}-install)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${DCMTK_CXX_FLAGS}")

# GCS FIX: On OSX, DCMTK depends on iconv.  Presumably this is true 
# for linux too, but why don't I get need to include in the build list?
if (APPLE)
  set (DCMTK_LIBRARIES ${DCMTK_LIBRARIES} iconv)
endif ()

if (WIN32)
  set (DCMTK_LIBRARIES ${DCMTK_LIBRARIES} netapi32 wsock32)
endif ()

# Find Xerces
if (WIN32)
  if (CMAKE_SIZEOF_VOID_P EQUAL 8)
    # 64-bit windows build
    set (XERCES_RELEASE_LIBRARIES
      "${CMAKE_SOURCE_DIR}/xercesc-3.1/x64/lib/xerces-c_3.lib")
    set (XERCES_DEBUG_LIBRARIES
      "${CMAKE_SOURCE_DIR}/xercesc-3.1/x64/lib/xerces-c_3D.lib")
    set (XERCES_INCLUDE_DIR
      "${CMAKE_SOURCE_DIR}/xercesc-3.1/x64/include")
    install (
      PROGRAMS "${CMAKE_SOURCE_DIR}/xercesc-3.1/x64/bin/xerces-c_3_1.dll"
      DESTINATION "bin")
  else ()
    # 32-bit windows build
    set (XERCES_RELEASE_LIBRARIES
      "${CMAKE_SOURCE_DIR}/xercesc-3.1/x86/lib/xerces-c_3.lib")
    set (XERCES_DEBUG_LIBRARIES
      "${CMAKE_SOURCE_DIR}/xercesc-3.1/x86/lib/xerces-c_3D.lib")
    set (XERCES_INCLUDE_DIR
      "${CMAKE_SOURCE_DIR}/xercesc-3.1/x86/include")
    install (
      PROGRAMS "${CMAKE_SOURCE_DIR}/xercesc-3.1/x86/bin/xerces-c_3_1.dll"
      DESTINATION "bin")
  endif ()
  set (XERCES_FOUND 1)
else ()
  find_package (Xerces)
endif ()

# Famously, gcc needs this
if ("${CMAKE_SYSTEM_PROCESSOR}" STREQUAL "x86_64")
  set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
endif ()

# Check for prerequisites
if (NOT XERCES_FOUND)
  message (SEND_ERROR "Xerces was not found.  Please install Xerces, and/or set XERCES_DIR.")
endif ()

# Configure the name of the AIMLib library.
# For windows, we will give the library a version name, 
# so that different versions of the library can co-exist
if (WIN32)
  set (AIMLIB_LIBRARY "AIMLib-${AIM_VERSION_MAJOR}.${AIM_VERSION_MINOR}")
else ()
  set (AIMLIB_LIBRARY AIMLib)
endif ()

# Configure subdirectories
if (XERCES_FOUND)
  add_subdirectory (AIMLib/Altova)
  add_subdirectory (AIMLib/AltovaXML)
  add_subdirectory (AIMLib/AIMXML)
  add_subdirectory (AIMLib/AIMLib)
  add_subdirectory (AIMLib/AIMLibTest)
  add_subdirectory (AIMLib/AIMConverter)
endif ()

# make uninstall
if (UNIX)
  configure_file (
    "${CMAKE_CURRENT_SOURCE_DIR}/AIMLib/CMake/cmake_uninstall.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

  add_custom_target (uninstall COMMAND 
    ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
endif ()

# packaging
set (CPACK_PACKAGE_VERSION 
  "${AIM_VERSION_MAJOR}.${AIM_VERSION_MINOR}.${AIM_VERSION_PATCH}")
set (CPACK_PACKAGE_CONTACT "aimteam@northwestern.edu")
set (CPACK_MONOLITHIC_INSTALL 1)
if (WIN32)
  # windows
  set (CPACK_GENERATOR "ZIP")
  if (CMAKE_SIZEOF_VOID_P EQUAL 8)
    set (CPACK_SYSTEM_NAME "windows-x64")
  else ()
    set (CPACK_SYSTEM_NAME "windows-x86")
  endif ()
elseif (APPLE)
  # osx
  set (CPACK_SYSTEM_NAME "osx-x86_64")

  # For PackageMaker method
  set (CPACK_GENERATOR "PackageMaker")

  # For Bundle method
  #set (CPACK_GENERATOR "Bundle")
  #set (CPACK_BUNDLE_NAME "AIM Library ${CPACK_PACKAGE_VERSION}")

  # For DragNDropMethod
  #set (CPACK_GENERATOR "DragNDrop")

elseif ("${CMAKE_SYSTEM_NAME}" MATCHES "Linux")
  # linux
  set (CPACK_DEBIAN_PACKAGE_NAME "AIM")
  set (CPACK_RPM_PACKAGE_NAME "AIM")
  set (CPACK_GENERATOR "TGZ;DEB;RPM")
  if ("${CMAKE_SYSTEM_PROCESSOR}" STREQUAL "x86_64")
    set (CPACK_SYSTEM_NAME "linux-x86_64")
  else ()
    set (CPACK_SYSTEM_NAME "linux-i386")
  endif ()
else ()
  # something else
  set (CPACK_GENERATOR "TGZ")
endif ()
set (CPACK_PACKAGE_FILE_NAME 
  "${PROJECT_NAME}-${CPACK_PACKAGE_VERSION}-${CPACK_SYSTEM_NAME}")
include (CPack)
