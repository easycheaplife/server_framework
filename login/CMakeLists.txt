CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
AUX_SOURCE_DIRECTORY( . SOURCE_DIRECTORY)	
ADD_EXECUTABLE(login ${SOURCE_DIRECTORY})
INCLUDE_DIRECTORIES( ../../easy/src/base ../../tinynet ../../easy/dep/protobuf/src ../../easy/dep/mongo-cxx-driver/src )
SET(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb -L../../easy/dep/protobuf/src/.libs -L../../easy/dep/mongo-cxx-driver/build/linux2/normal")

IF(UNIX)
	TARGET_LINK_LIBRARIES(login tinynet protobuf proto mongoclient boost_thread boost_regex)
ELSE(WIN32)
	TARGET_LINK_LIBRARIES(login tinynet ../../easy/dep/protobuf/vsprojects/Debug/libprotobuf proto ws2_32)
ENDIF(UNIX)

