CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
AUX_SOURCE_DIRECTORY( . SOURCE_DIRECTORY)	
ADD_EXECUTABLE(proxy ${SOURCE_DIRECTORY})
INCLUDE_DIRECTORIES( ../common ../../easy/src/base ../../tinynet ../../easy/dep/protobuf/src ../../easy/dep/jansson/src)

IF(UNIX)
	OPTION(USE_32BITS "Compile for 32bits processors(linux only)" OFF)
	#	32 bit
	IF(USE_32BITS)  
		message(STATUS "using 32bits")  
		SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32")  
		SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32")   
	#	64 bit
	ELSE()  
		message(STATUS "using 64bits")  
		SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m64")  
		SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64")    
	ENDIF(USE_32BITS)  
	SET(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb -fpermissive -L../../easy/dep/protobuf/src/.libs")
ELSE(WIN32)

ENDIF(UNIX)

ADD_DEFINITIONS(-D__PROXY)
	
IF(UNIX)
	TARGET_LINK_LIBRARIES(proxy tinynet easy protobuf proto jansson  )
ELSEIF(WIN32)
	#	64 bit
	TARGET_LINK_LIBRARIES(proxy ws2_32 tinynet easy ../../easy/dep/protobuf/vsprojects/x64/Debug/libprotobuf proto ../../easy/dep/jansson/win32/vs2012/x64/Debug/jansson)
	#	32 bit
	#TARGET_LINK_LIBRARIES(proxy tinynet ../../easy/dep/protobuf/vsprojects/Debug/libprotobuf proto ws2_32)
ENDIF(UNIX)
SET(EXECUTABLE_OUTPUT_PATH ../bin)


