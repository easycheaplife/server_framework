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

#include "proxy.h"
#include "reactor.h"
#include "proxy_packet_handle.h"
#include "json_proxy.h"
#include "easy_log.h"
#include "proxy_client.h"

#ifdef __LINUX
#include "easy_dump.h"
#endif // __LINUX

Proxy* Proxy::inst_ = easy_null;
Proxy::Proxy(const easy_char* __host /*= "0.0.0.0"*/,easy_uint32 __port /*= 9876*/ )
	: Server_Impl((reactor_ = new Reactor),__host,__port),host_(__host),port_(__port)
{
#ifdef __LINUX
	signal(SIGSEGV,dump);
	//	when calls send() function twice if peer socket is closed, the SIG_PIPE signal will be trigger. and the SIG_PIPE 's default action is exit process.
	//	just ignore it! if use gdb debug,add 'handle SIGPIPE nostop print' or 'handle SIGPIPE nostop noprint' before run.
	signal(SIGPIPE,SIG_IGN);
#endif // __LINUX
	packet_handle_ = new Proxy_Packet_Handle(this);
	_load_json();
	_connect_core();
}

Proxy::~Proxy()
{
	delete reactor_;
	reactor_ = easy_null;
}

int Proxy::event_loop()
{
	static const easy_int32 __max_time_out = 5000*1000;
	return reactor_->event_loop(__max_time_out);
}

easy_int32 Proxy::handle_packet( easy_int32 __fd,const std::string& __string_packet,void* __user_data )
{
	//	dispatch and transform packet to special core server
	packet_handle_->handle_packet(__fd,__string_packet,__user_data);
	return 0;
}

easy_int32 Proxy::handle_packet(easy_int32 __fd,const easy_char* __packet,easy_int32 __length)
{
	//	dispatch and transform packet to special core server
	return 0;
}

void Proxy::connected( easy_int32 __fd )
{

	//	some schedule algorithm for allocation one level.algorithm may be polling,wight,ip hash,response time and so on.
	Core_Info* __core_info = JsonProxy::instance()->get_core_info();
	if (__core_info)
	{
		fd_core_info_[__fd] = __core_info;
	}
	else
	{
		easy::EasyLog::SaveLog(JsonProxy::instance()->log_path().c_str(),\
			easy::kErrors,"proxy config error, can not find suitable core!");
	}
#ifdef __DEBUG
	printf("%d connected\n",__fd);
#endif // __DEBUG
}

void Proxy::dis_connected( easy_int32 __fd )
{
	fd_core_info::iterator __find = fd_core_info_.find(__fd);
	if (__find != fd_core_info_.end())
	{
		fd_core_info_.erase(__find);
	}
#ifdef __DEBUG
	printf("%d disconnected\n",__fd);
#endif // __DEBUG
}

void Proxy::_load_json()
{
	JsonProxy::instance();
}

void Proxy::_connect_core()
{
	core_list& __core_list = JsonProxy::instance()->get_core_list();
	for (core_list::iterator __it = __core_list.begin(); __it != __core_list.end(); ++__it)
	{
		if(__it->second)
		{
			__it->second->client_ = new Proxy_client(new Reactor(),__it->second->ip_.c_str(),__it->second->port_);
		}
	}
}

Proxy* Proxy::instance( const easy_char* __host /*= "0.0.0.0"*/,easy_uint32 __port /*= 9876*/ )
{
	if (!inst_)
	{
		inst_ = new Proxy(__host,__port);
	}
	return inst_;
}

void Proxy::destroy()
{
	if (inst_)
	{
		delete inst_;
		inst_ = easy_null;
	}
}

Core_Info* Proxy::get_core_info( easy_int32 __fd )
{
	return fd_core_info_[__fd];
}

