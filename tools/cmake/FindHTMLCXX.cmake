# - Try to find HTMLCXX
# Once done this will define
#  HTMLCXX_FOUND - System has HTMLCXX
#  HTMLCXX_INCLUDE_DIRS - The HTMLCXX include directories
#  HTMLCXX_LIBRARIES - The libraries needed to use HTMLCXX
#  HTMLCXX_DEFINITIONS - Compiler switches required for using HTMLCXX

find_package (PkgConfig)
pkg_check_modules (PC_HTMLCXX QUIET libhtmlcxx)
set (HTMLCXX_DEFINITIONS ${PC_HTMLCXX_CFLAGS_OTHER})

find_path (HTMLCXX_INCLUDE_DIR html/CharsetConverter.h
  HINTS ${PC_HTMLCXX_INCLUDEDIR} ${PC_HTMLCXX_INCLUDE_DIRS}
  PATH_SUFFIXES htmlcxx)

find_library (HTMLCXX_LIBRARY NAMES htmlcxx
  HINTS ${PC_HTMLCXX_LIBDIR} ${PC_HTMLCXX_LIBRARY_DIRS})

include (FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set HTMLCXX_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args (HTMLCXX DEFAULT_MSG
  HTMLCXX_LIBRARY HTMLCXX_INCLUDE_DIR)

mark_as_advanced (HTMLCXX_INCLUDE_DIR HTMLCXX_LIBRARY)

set (HTMLCXX_LIBRARIES ${HTMLCXX_LIBRARY})
set (HTMLCXX_INCLUDE_DIRS ${HTMLCXX_INCLUDE_DIR})
