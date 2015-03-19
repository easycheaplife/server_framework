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
#include "core_packet_handle.h"
#include "event_handle.h"
#include "common.pb.h"
#ifdef __DEBUG
#include "transfer.pb.h"
#endif // __DEBUG
#include "msg.h"
#include "core.h"

int Core_Packet_Handle::handle_packet(easy_int32 __fd,const std::string& __packet,void* __user_data )
{
	common::common_head __packet_head;
	__packet_head.ParseFromString(__packet);
	easy_int32 __msg_id =__packet_head.msg_id();
	easy_uint32 __packet_length = __packet.length();
	easy_uint16* __real_fd = (easy_uint16*)(__user_data);
	__packet_length |= (*__real_fd << 16);
	switch (__msg_id)
	{
	case MSG_C2S2C_TEST:
		{
#ifdef __DEBUG
			transfer::Packet __packet_protobuf;
			__packet_protobuf.ParseFromString(__packet);
			printf("%s\n",__packet_protobuf.content().c_str());
#endif // __DEBUG
#if 0
			static const easy_int32 max_buffer_size_ = 8*1024;
			easy_char __buffer[max_buffer_size_] = {};
			size_t __head_size = sizeof(__packet_length);
			size_t __packet_size = __packet.length();
			memcpy(__buffer,&__packet_length,__head_size);
			memcpy(__buffer + __head_size,__packet.c_str(),__packet_size);
			Core::instance()->send_packet(__fd,__buffer,__head_size +__packet_size);
#else
			Core::instance()->send_packet(__fd,(easy_char*)&__packet_length,sizeof(easy_uint32));
			Core::instance()->send_packet(__fd,__packet.c_str(),__packet.length());
#endif
		}
		break;
	default:
		break;
	}
	return 0;
}
