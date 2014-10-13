PROJECT(server_framework)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

AUX_SOURCE_DIRECTORY( ../easy/src/base EASY_SRC_LIST)
IF(UNIX)
	SET(TINYNET_SRC_LIST ../tinynet/reactor.cc ../tinynet/reactor_impl_select.cc ../tinynet/reactor_impl_poll.cc ../tinynet/reactor_impl_epoll.cc
	../tinynet/event_handle_srv.cc  ../tinynet/server_framework_impl.cc 
	../tinynet/event_handle_cli.cc ../tinynet/client_protobuf_impl.cc)
ELSE(WIN32)
	SET(TINYNET_SRC_LIST ../tinynet/reactor.h ../tinynet/reactor.cc ../tinynet/reactor_impl_select.h ../tinynet/reactor_impl_select.cc ../tinynet/reactor_impl_iocp.h ../tinynet/reactor_impl_iocp.cc
	../tinynet/event_handle_srv.h ../tinynet/event_handle_srv.cc ../tinynet/server_framework_impl.h ../tinynet/server_framework_impl.cc 
	../tinynet/event_handle_cli.h ../tinynet/event_handle_cli.cc ../tinynet/client_protobuf_impl.h ../tinynet/client_protobuf_impl.cc)
ENDIF(UNIX)

AUX_SOURCE_DIRECTORY( ./proto PROTO_SRC_LIST)
INCLUDE_DIRECTORIES( . ../easy/src/base ../tinynet ../easy/dep/protobuf/src ./proto ../easy/dep/mongo-c-driver/src/mongoc ../easy/dep/mongo-c-driver/src/libbson/src/bson ../easy/dep/mongo-cxx-driver/src)

IF(UNIX)
	ADD_DEFINITIONS(-D__HAVE_EPOLL -D__LINUX)
	SET(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
	SET(CMAKE_CXX_FLAGS "-Wl,--no-as-needed -std=c++11 -pthread") 
ELSE(WIN32)
	ADD_DEFINITIONS(-D__HAVE_SELECT -D__WIN32 -DWIN32)
ENDIF(UNIX)

ADD_LIBRARY(easy STATIC ${EASY_SRC_LIST})
ADD_LIBRARY(tinynet STATIC ${TINYNET_SRC_LIST})
ADD_LIBRARY(proto STATIC ${PROTO_SRC_LIST})
SET_TARGET_PROPERTIES(easy PROPERTIES OUTPUT_NAME "easy")
SET_TARGET_PROPERTIES(tinynet PROPERTIES OUTPUT_NAME "tinynet")
SET_TARGET_PROPERTIES(proto PROPERTIES OUTPUT_NAME "proto")
SET(LIBRARY_OUTPUT_PATH lib)
ADD_SUBDIRECTORY( login )
ADD_SUBDIRECTORY(test_client)

