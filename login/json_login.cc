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

#include "json_login.h"
#include "easy_util.h"


JsonLogin* JsonLogin::inst_ = easy_null;
JsonLogin* JsonLogin::instance( const easy_char* __file_name )
{
	if(!inst_)
	{
		inst_ = new JsonLogin(__file_name); 
	}
	return inst_;
}

JsonLogin::JsonLogin(const easy_char* __file_name):JsonBase(__file_name),wight_total_(0)
{
	//	get the value of ip,host,wight,and so on
	json_t* __json_core_array = json_object_get(json_load_, "proxy");
	if (__json_core_array)
	{
		size_t __json_core_array_size = json_array_size(__json_core_array);
		for (easy_int32 __i = 0; __i < __json_core_array_size; ++__i)		
		{
			json_t* __json_core_element = json_array_get(__json_core_array,__i);
			if(__json_core_element)
			{
				Proxy_Info* __proxy_info = new Proxy_Info();
				json_t* __json_core_ip = json_object_get(__json_core_element,"ip");
				const easy_char* __ip = json_string_value(__json_core_ip);
				__proxy_info->ip_ = __ip;
				json_t* __json_core_port = json_object_get(__json_core_element,"port");
				easy_int64 __port = json_integer_value(__json_core_port);
				__proxy_info->port_ = __port;
				json_t* __json_core_wight = json_object_get(__json_core_element,"wight");
				easy_int64 __wight = json_integer_value(__json_core_wight);
				__proxy_info->wight_ = __wight;
				__proxy_info->wight_begin_ = wight_total_;
				wight_total_ += __wight;
				__proxy_info->wight_end_ = wight_total_;
				proxy_list_[__port] = __proxy_info;
			}
		}
	}
	//	log path
	json_t* __json_log_path = json_object_get(json_load_, "login_log_path");
	log_path_ = json_string_value(__json_log_path);
	json_t* __json_mongodb_url = json_object_get(json_load_, "mongodb_url");
	mongodb_url_ = json_string_value(__json_mongodb_url);
}

void JsonLogin::destroy()
{
	if(inst_)
	{
		delete inst_;
		inst_ = easy_null;
	}
}

void JsonLogin::_clear()
{
	for (proxy_list::iterator __it = proxy_list_.begin(); __it != proxy_list_.end(); ++__it)
	{
		if(__it->second)
		{
			delete __it->second;
			__it->second = easy_null;
		}
	}
	proxy_list_.clear();
}

JsonLogin::~JsonLogin()
{
	_clear();
}

Proxy_Info* JsonLogin::get_proxy_info()
{
	easy_int64 __wight_total = JsonLogin::instance()->wight_total();
	if (0 == __wight_total)
	{
		return easy_null;
	}
	easy_int64 __random_val = easy::Util::random(__wight_total);
	for (proxy_list::iterator __it = proxy_list_.begin(); __it != proxy_list_.end(); ++__it)
	{
		if (__it->second)
		{
			if(__random_val >= __it->second->wight_begin_ && __random_val < __it->second->wight_end_)
			{
				return __it->second;
			}
		}
	}
	return easy_null;
}



