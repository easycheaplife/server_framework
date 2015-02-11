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
#include "json_login.h"
#include "easy_log.h"
#include "login_client.h"

#ifdef __LINUX
#include "easy_dump.h"
#endif // __LINUX

Login::Login(const easy_char* __host /*= "0.0.0.0"*/,easy_uint32 __port /*= 9876*/ )
	: Server_Impl((reactor_ = new Reactor),__host,__port),host_(__host),port_(__port)
{
#ifdef __LINUX
	signal(SIGSEGV,dump);
	//	when calls send() function twice if peer socket is closed, the SIG_PIPE signal will be trigger. and the SIG_PIPE 's default action is exit process.
	//	just ignore it! if use gdb debug,add 'handle SIGPIPE nostop print' or 'handle SIGPIPE nostop noprint' before run.
	signal(SIGPIPE,SIG_IGN);
#endif // __LINUX
	packet_handle_ = new Login_Packet_Handle(this);
	_load_json();
	_connect_proxy();
}

Login::~Login()
{
	delete reactor_;
	reactor_ = easy_null;
}

int Login::event_loop()
{
	static const easy_int32 __max_time_out = 5000*1000;
	return reactor_->event_loop(__max_time_out);
}

easy_int32 Login::handle_packet( easy_int32 __fd,const std::string& __string_packet,void* __user_data )
{
	packet_handle_->handle_packet(__fd,__string_packet,__user_data);
	return 0;
}

void Login::connected( easy_int32 __fd )
{
	//	some schedule algorithm for allocation one level.algorithm may be polling,wight,ip hash,response time and so on.
	Proxy_Info* __proxy_info = JsonLogin::instance()->get_proxy_info();
	if (__proxy_info)
	{
		fd_proxy_info_[__fd] = __proxy_info;
	}
	else
	{
		easy::EasyLog::SaveLog(JsonLogin::instance()->log_path().c_str(),\
			easy::kErrors,"login config error, can not find suitable proxy!");
	}
#ifdef __DEBUG
	printf("%d connected\n",__fd);
#endif // __DEBUG
}

void Login::dis_connected( easy_int32 __fd )
{
	fd_proxy_info::iterator __find = fd_proxy_info_.find(__fd);
	if (__find != fd_proxy_info_.end())
	{
		fd_proxy_info_.erase(__find);
	}
#ifdef __DEBUG
	printf("%d disconnected\n",__fd);
#endif // __DEBUG
}

void Login::_load_json()
{
	JsonLogin::instance();
}

void Login::_connect_proxy()
{
	proxy_list& __proxy_list = JsonLogin::instance()->get_proxy_list();
	for (proxy_list::iterator __it = __proxy_list.begin(); __it != __proxy_list.end(); ++__it)
	{
		if(__it->second)
		{
			__it->second->client_ = new Login_client(new Reactor(),__it->second->ip_.c_str(),__it->second->port_);
		}
	}
}

