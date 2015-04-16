CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
AUX_SOURCE_DIRECTORY( . SOURCE_DIRECTORY)	
ADD_EXECUTABLE(core ${SOURCE_DIRECTORY})
INCLUDE_DIRECTORIES( ../common ../../easy/src/base ../../tinynet ../../easy/dep/protobuf/src ../../easy/dep/mongo-cxx-driver/src)

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
	SET(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb -fpermissive -L../dep/protobuf/x64/lib -L../dep/mongocxx/x64/lib")
ELSE(WIN32)

ENDIF(UNIX)

IF(UNIX)
	TARGET_LINK_LIBRARIES(core tinynet easy protobuf proto pthread mongoclient boost_thread boost_regex)
ELSEIF(WIN32)
	#	64 bit
	TARGET_LINK_LIBRARIES(core ws2_32 tinynet easy ../dep/protobuf/x64/lib/libprotobuf proto ../dep/mongoc/x64/lib/bson-1.0 ../dep/mongoc/x64/lib/mongoc-1.0 ../dep/mongocxx/x64/lib/mongoclient-gd 
	#	absolute path should add .lib, just like as follows:
	c:/local/boost_1_53_0/lib64-msvc-11.0/libboost_thread-vc110-mt-gd-1_53.lib 
	c:/local/boost_1_53_0/lib64-msvc-11.0/libboost_system-vc110-mt-gd-1_53.lib  
	c:/local/boost_1_53_0/lib64-msvc-11.0/libboost_date_time-vc110-mt-gd-1_53.lib 
	c:/local/boost_1_53_0/lib64-msvc-11.0/libboost_chrono-vc110-mt-gd-1_53.lib)
	#	32 bit
	#TARGET_LINK_LIBRARIES(core tinynet ../../easy/dep/protobuf/vsprojects/Debug/libprotobuf proto ../dep/mongoc/x86/lib/bson-1.0 ../dep/mongoc/x86/lib/mongoc-1.0 ws2_32)
ENDIF(UNIX)
SET(EXECUTABLE_OUTPUT_PATH ../bin)


