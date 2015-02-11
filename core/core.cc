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

#include "core.h"
#include "reactor.h"
#include "core_packet_handle.h"

#ifdef __LINUX
#include "easy_dump.h"
#endif // __LINUX

Core* Core::inst_ = easy_null;
Core::Core(const easy_char* __host /*= "0.0.0.0"*/,easy_uint32 __port /*= 9876*/ )
	: Server_Impl((reactor_ = new Reactor),__host,__port),host_(__host),port_(__port)
{
#ifdef __LINUX
	signal(SIGSEGV,dump);
	//	when calls send() function twice if peer socket is closed, the SIG_PIPE signal will be trigger. and the SIG_PIPE 's default action is exit process.
	//	just ignore it! if use gdb debug,add 'handle SIGPIPE nostop print' or 'handle SIGPIPE nostop noprint' before run.
	signal(SIGPIPE,SIG_IGN);
#endif // __LINUX
	packet_handle_ = new Core_Packet_Handle(this);
}

Core::~Core()
{
	delete reactor_;
	reactor_ = easy_null;
}

int Core::event_loop()
{
	static const easy_int32 __max_time_out = 5000*1000;
	return reactor_->event_loop(__max_time_out);
}

easy_int32 Core::handle_packet( easy_int32 __fd,const std::string& __string_packet,void* __user_data )
{
	packet_handle_->handle_packet(__fd,__string_packet,__user_data);
	return 0;
}

void Core::connected( easy_int32 __fd )
{
#ifdef __DEBUG
	printf("%d connected\n",__fd);
#endif // __DEBUG
}

void Core::dis_connected( easy_int32 __fd )
{
#ifdef __DEBUG
	printf("%d disconnected\n",__fd);
#endif // __DEBUG
}

Core* Core::instance( const easy_char* __host /*= "0.0.0.0"*/,easy_uint32 __port /*= 9876*/ )
{
	if (!inst_)
	{
		inst_ = new Core(__host,__port);
	}
	return inst_;
}

void Core::destroy()
{
	if (inst_)
	{
		delete inst_;
		inst_ = easy_null;
	}
}

