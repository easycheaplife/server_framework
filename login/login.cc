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

#include "login.h"
#include "reactor.h"
#include "login_packet_handle.h"

#ifdef __LINUX
#include "easy_dump.h"
#endif // __LINUX

Login::Login(const char* __host /*= "0.0.0.0"*/,unsigned int __port /*= 9876*/ )
	: Server_Impl(Reactor::instance(),__host,__port),host_(__host),port_(__port)
{
#ifdef __LINUX
	signal(SIGSEGV,dump);
	//	when calls send() function twice if peer socket is closed, the SIG_PIPE signal will be trigger. and the SIG_PIPE 's default action is exit process.
	//	just ignore it! if use gdb debug,add 'handle SIGPIPE nostop print' or 'handle SIGPIPE nostop noprint' before run.
	signal(SIGPIPE,SIG_IGN);
#endif // __LINUX
	packet_handle_ = new Login_Packet_Handle();
}

Login::~Login()
{
	Reactor::destory();
}

int Login::event_loop()
{
	static const int __max_time_out = 5000*1000;
	return Reactor::instance()->event_loop(__max_time_out);
}

int Login::handle_packet( unsigned int __packet_id,const std::string& __string_packet )
{
	packet_handle_->handle_packet(__packet_id,__string_packet);
	return 0;
}

