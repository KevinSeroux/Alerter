cmake_minimum_required(VERSION 3.1)
project(Alerter)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_CXX_STANDARD 14)
set("OpenCV_DIR" "." CACHE FILEPATH "Set to the build directory of OpenCV")
set(Boost_USE_STATIC_LIBS ON)

file(
	GLOB_RECURSE
	source_files
	include/*
	src/*
)

set(_src_root_path "${Alerter_SOURCE_DIR}")
foreach(_source IN ITEMS ${source_files})
    get_filename_component(_source_path "${_source}" PATH)
    file(RELATIVE_PATH _source_path_rel "${_src_root_path}" "${_source_path}")
    string(REPLACE "/" "\\" _group_path "${_source_path_rel}")
    source_group("${_group_path}" FILES "${_source}")
endforeach()

find_package(Threads REQUIRED)
find_package(Boost REQUIRED COMPONENTS system date_time regex)
find_package(OpenCV REQUIRED)

add_executable(
	AlerterSrv
	${source_files}
)

include_directories(
	include
	3rdParty/include
	${Boost_INCLUDE_DIRS}
	${OpenCV_INCLUDE_DIRS}
)

target_link_libraries(
	AlerterSrv
	${CMAKE_THREAD_LIBS_INIT}
	${Boost_LIBRARIES}
	${OpenCV_LIBS}
)