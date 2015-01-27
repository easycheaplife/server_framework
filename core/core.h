/****************************************************************************
 Copyright (c) 2013-2014 King Lee

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
#ifndef core_h__
#define core_h__
#include "server_impl.h"

class Packet_Handle;
class Reactor;

class Core : public Server_Impl
{
public:
	Core(const easy_char* __host = "0.0.0.0",easy_uint32 __port = 9876);

    ~Core();

	//	called at a packet to be handle
	//	for protobuf
	virtual easy_int32 handle_packet(easy_int32 __fd,const std::string& __string_packet,void* __user_data);

	//	for byte stream, it is the  default way;it use protobuf, just return it.
	virtual easy_int32 handle_packet(easy_int32 __fd,const easy_char* __packet,easy_int32 __length) { return -1;}

	//	called at a connection coming
	virtual	void connected(easy_int32 __fd);

	//	called at a connection leaving
	virtual	void dis_connected(easy_int32 __fd) ;

	easy_int32 event_loop();

	static Core* instance(const easy_char* __host = "0.0.0.0",easy_uint32 __port = 9876);

	static void	destroy();
private:

	const easy_char*		host_;

	easy_uint32				port_; 

	Packet_Handle*			packet_handle_;

	//	i/o multiplexing reactor
	Reactor*				reactor_;

	static Core*			inst_;
};
#endif // core_h__