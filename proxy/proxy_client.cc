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

#include "proxy_client.h"
#include "proxy.h"

Proxy_client::Proxy_client( Reactor* __reactor,const easy_char* __host,easy_uint32 __port /*= 9876*/ )
	: Client_Impl(__reactor,__host,__port)
{

}

easy_int32 Proxy_client::handle_packet( easy_int32 __fd,const std::string& __string_packet ,void* __user_data)
{
	easy_uint32 __packet_length = __string_packet.length();
#if 0
	static const easy_int32 max_buffer_size_ = 8*1024;
	easy_char __buffer[max_buffer_size_] = {};
	size_t __head_size = sizeof(__packet_length);
	memcpy(__buffer,&__packet_length,__head_size);
	memcpy(__buffer + __head_size,__string_packet.c_str(),__packet_length);
	Proxy::instance()->send_packet(__fd,__buffer,__head_size + __packet_length);
#else
	Proxy::instance()->send_packet(__fd,(easy_char*)&__packet_length,sizeof(__packet_length));
	Proxy::instance()->send_packet(__fd,__string_packet.c_str(),__packet_length);
#endif
#ifdef __DEBUG_
	printf("send_packet %d\n",__packet_length);
#endif // __DEBUG
	return -1;
}

Proxy_client::~Proxy_client()
{

}
