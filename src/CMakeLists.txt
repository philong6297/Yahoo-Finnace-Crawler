add_subdirectory (base)
add_subdirectory (crawler)
longlp_make_exec (
  TARGET_NAME ${LONGLP_PROJECT_TARGET_NAME}
  COMPILE_OPTIONS PRIVATE ${LONGLP_COMPILE_OPTIONS}
  COMPILE_FEATURES PRIVATE ${LONGLP_COMPILE_FEATURES}
  SOURCES
  #[[]] PRIVATE
  #[[]]   main.cpp
  INCLUDE_DIRECTORIES
  #[[]] PRIVATE ${LONGLP_PROJECT_SRC_DIR}
  LINK_LIBRARIES
  #[[]] ${HTMLCXX_LIBRARIES}
  #[[]] cpr
  #[[]] Qt5::Core
  #[[]] pthread
  #[[]] Base
  #[[]] Crawler
)

