set(sources
	src/getMemorySize.c
	src/luc.cc
)
set(headers
	inc/getMemorySize.h
	inc/luc.h
)

file(COPY ${headers} DESTINATION "${CMAKE_BINARY_DIR}/include/compat")

include_directories("${CMAKE_BINARY_DIR}/include/compat")

add_library(compat SHARED ${sources} ${headers})