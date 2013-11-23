if (NOT EXISTS "@CMAKE_CURRENT_BINARY_DIR@/install_manifest.txt")
  message (FATAL_ERROR "Cannot find install manifest: \"@CMAKE_CURRENT_BINARY_DIR@/install_manifest.txt\"")
endif ()

file (READ "@CMAKE_CURRENT_BINARY_DIR@/install_manifest.txt" files)
string (REGEX REPLACE "\n" ";" files "${files}")
foreach (file ${files})
  message (STATUS "Uninstalling \"$ENV{DESTDIR}${file}\"")

  # GCS 2013-06-03.  CMake incorrectly reports that dangling symlinks 
  # do not exist.  So we need to try delete the file even if 
  # CMake reports that it doesn't exist.
  # cf. http://www.cmake.org/Bug/print_bug_page.php?bug_id=14022

  # if (EXISTS "$ENV{DESTDIR}${file}")
    execute_process(
      COMMAND @CMAKE_COMMAND@ -E remove "$ENV{DESTDIR}${file}"
      OUTPUT_VARIABLE rm_out
      RESULT_VARIABLE rm_retval
      )
  #   if (NOT ${rm_retval} EQUAL 0)
  #     message(FATAL_ERROR "Problem when removing \"$ENV{DESTDIR}${file}\"")
  #   endif ()
  # else ()
  #   message (STATUS "File \"$ENV{DESTDIR}${file}\" does not exist.")
  # endif (EXISTS "$ENV{DESTDIR}${file}")

endforeach ()
