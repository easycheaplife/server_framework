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
#include "connector.h"
#include "reactor.h"
#include "msg.h"
#include "login.pb.h"
#include "client_packet_handle.h"

int Connector::handle_packet( easy_int32 __fd,const std::string& __string_packet,void* __user_data )
{
	return packet_handle_->handle_packet(__fd,__string_packet,__user_data);
}

Connector::Connector( const easy_char* __host,easy_uint32 __port ) : Client_Impl((reactor_ = new Reactor(true)),__host,__port) 
{
	packet_handle_ = new Client_Packet_Handle(this);
}

Connector::~Connector()
{

}

int Connector::event_loop( easy_ulong __millisecond )
{
	return reactor_->event_loop(__millisecond);
}