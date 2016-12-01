cmake_minimum_required(VERSION 2.6)

project(Alerter)

file(
	GLOB_RECURSE
	source_files
	include/*
	src/*
)

include_directories(include)

find_package(Threads)

add_executable(
	AlerterSrv
	${source_files}
)

target_link_libraries(
	AlerterSrv
	${CMAKE_THREAD_LIBS_INIT}
)
