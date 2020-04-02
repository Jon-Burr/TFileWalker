cmake_minimum_required( VERSION 3.9 )
project( TFileWalker LANGUAGES CXX )

find_package( Boost COMPONENTS program_options regex filesystem REQUIRED )
find_package( ROOT COMPONENTS Core Hist REQUIRED )
include (${ROOT_USE_FILE})

add_library( TFileWalker )
target_include_directories( TFileWalker
  PUBLIC include )
target_sources( TFileWalker
  PRIVATE
    src/FileHandler.cxx
    src/HistoTarget.cxx
    src/OutputHandler.cxx
    src/Path.cxx
    src/RegexRule.cxx
    src/Rule.cxx
    src/RuleParser.cxx
    src/Target.cxx
    src/TDirHandle.cxx
    src/TFileHandle.cxx
    src/Walker.cxx)
target_link_libraries( TFileWalker
  PUBLIC
    ROOT::Hist
  PRIVATE
    Boost::regex
    Boost::filesystem)

add_executable( tfile-walk )
target_sources( tfile-walk
  PRIVATE
    util/tfile-walk.cxx)
target_link_libraries( tfile-walk
  PRIVATE
    TFileWalker
    Boost::program_options)
