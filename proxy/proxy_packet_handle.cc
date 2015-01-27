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
#include "proxy_packet_handle.h"
#include "event_handle.h"
#include "json_proxy.h"
#include "proxy_client.h"

int Proxy_Packet_Handle::handle_packet(easy_int32 __fd,const std::string& __packet,void* __user_data )
{
	//	add current fd to head,high 16 bits, then send to core
	easy_uint32 __packet_length = __packet.length();
	__packet_length |= (__fd << 16);
	Core_Info* __core_info = JsonProxy::instance()->get_core_info();
	if (__core_info)
	{
		__core_info->client_->write((easy_char*)&__packet_length,sizeof(__packet_length));
		__core_info->client_->write(__packet.c_str(),__packet.length());
	}
	return 0;
}
