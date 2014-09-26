CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
AUX_SOURCE_DIRECTORY( . SOURCE_DIRECTORY)	
ADD_EXECUTABLE(login ${SOURCE_DIRECTORY})
INCLUDE_DIRECTORIES( ../../easy/src/base ../../tinynet ../../easy/dep/protobuf/src ../../easy/dep/mongo-c-driver/src/mongoc ../../easy/dep/mongo-c-driver/src/libbson/src/bson)
SET(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb -fpermissive -L../../easy/dep/protobuf/src/.libs -L../../easy/dep/mongo-c-driver/src/libbson/.libs -L../../easy/dep/mongo-c-driver/.libs")

IF(UNIX)
	TARGET_LINK_LIBRARIES(login tinynet protobuf proto bson pthread mongoc-1.0)
ELSE(WIN32)
	TARGET_LINK_LIBRARIES(login tinynet ../../easy/dep/protobuf/vsprojects/Debug/libprotobuf proto ws2_32)
ENDIF(UNIX)

