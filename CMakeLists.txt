cmake_minimum_required(VERSION 3.8)

#Global cmake features
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

#Set startup project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT tests)

#set project name
project(CppUtils)

# Set compiler options
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	# MP build for MSVC
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP /EHsc")
endif()

# Set project constants
set(PROJECT_ROOT ${CMAKE_CURRENT_SOURCE_DIR}) # Project dir
set(BINARIES_DIR ${PROJECT_ROOT}/bin) # Binaries dir
set(INTERMEDIATES_DIR ${PROJECT_ROOT}/temp) # Intermediates dir


function(construct_target TARGET_NAME TARGET_PATH)
	set_target_properties(${TARGET_NAME} PROPERTIES 
		ARCHIVE_OUTPUT_DIRECTORY "${BINARIES_DIR}/Lib"
		RUNTIME_OUTPUT_DIRECTORY "${BINARIES_DIR}/Bin"
		LIBRARY_OUTPUT_DIRECTORY "${BINARIES_DIR}/Bin"
		VS_DEBUGGER_WORKING_DIRECTORY "${PROJECT_ROOT}")
	target_include_directories(${TARGET_NAME} PUBLIC ${PROJECT_ROOT}/include)
	target_compile_features(${TARGET_NAME} PUBLIC cxx_std_17)
	set_target_properties(${TARGET_NAME} PROPERTIES CXX_EXTENSIONS OFF)
	IF (WIN32)
	ELSE ()
		target_link_libraries(${TARGET_NAME} -ldl -lpthread)
	ENDIF()
endfunction()

file(GLOB_RECURSE SOURCES src/* include/*)
source_group(TREE . FILES ${SOURCES})
add_library(cpputils ${SOURCES})
construct_target(cpputils . )

file(GLOB_RECURSE SOURCES tests/*.cpp tests/*.h)
add_executable(tests ${SOURCES})
construct_target(tests tests/ ${SOURCES})
target_link_libraries(tests cpputils)
target_include_directories(tests PUBLIC src/public)