longlp_message ("Build Crawler")
longlp_make_library (
  TARGET_NAME Crawler
  LIBRARY_TYPE STATIC
  SOURCES
  #[[]] PRIVATE
  #[[]]   crypto.cpp crypto.hpp crawler_base.hpp currencies.cpp currencies.hpp
  #[[]]   world_indices.cpp world_indices.hpp
  #[[]]   stock_gainer.cpp stock_gainer.hpp
  #[[]]   stock_loser.cpp stock_loser.hpp
  #[[]]   crawler.hpp
  COMPILE_OPTIONS
  #[[]] PRIVATE ${LONGLP_COMPILE_OPTIONS}
  COMPILE_FEATURES
  #[[]] PRIVATE ${LONGLP_COMPILE_FEATURES}
  INCLUDE_DIRECTORIES
  #[[]] PRIVATE ${LONGLP_PROJECT_SRC_DIR}
  LINK_LIBRARIES
  #[[]] ${HTMLCXX_LIBRARIES}
  #[[]] cpr
  #[[]] Qt5::Core
  #[[]] pthread
  #[[]] Base
  DEPENDENCIES
  #[[]] Base
)

