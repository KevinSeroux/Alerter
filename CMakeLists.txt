cmake_minimum_required(VERSION 2.6)

project(Alerter)

file(
	GLOB_RECURSE
	source_files
	include/*
	src/*
)

find_package(Threads REQUIRED)
find_package(Boost REQUIRED)

add_executable(
	AlerterSrv
	${source_files}
)

include_directories(
	include
	${Boost_INCLUDE_DIRS}
)

target_link_libraries(
	AlerterSrv
	${CMAKE_THREAD_LIBS_INIT}
	${Boost_LIBRARIES}
)
