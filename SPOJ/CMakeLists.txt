
cmake_minimum_required (VERSION 3.2.2)
project ( Spoj )

# this is used by DEBUG and RELEASE
list( APPEND CMAKE_CXX_FLAGS "-std=c++1y -Werror -Wno-error=char-subscripts -Wno-char-subscripts" )


set(BinDir ${PROJECT_SOURCE_DIR}/bin)
set(LibDir ${PROJECT_SOURCE_DIR}/lib)


# archive is for static libraries

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BinDir} )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LibDir} )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${LibDir} )
foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
    string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${BinDir} )
    set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${LibDir} )
    set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${LibDir} )
endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )


file(GLOB PROBLEM_FILES "./*.cpp")

foreach(FILE ${PROBLEM_FILES})
    get_filename_component(PROBLEM_NAME ${FILE} NAME_WE)
    add_executable("ex_${PROBLEM_NAME}" ${FILE})
endforeach(FILE)
