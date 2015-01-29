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
#ifndef json_proxy_h__
#define json_proxy_h__
#include "json_base.h"
#include "easy_base_type.h"
#include <string>
#include <map>
class Proxy_client;

struct Core_Info
{
	std::string ip_;
	easy_int64 port_;
	easy_int64 wight_;
	easy_int64 wight_begin_;
	easy_int64 wight_end_;
	Proxy_client* client_;
	Core_Info():wight_(0),wight_begin_(0),wight_end_(0),client_(easy_null){}
};

typedef std::map<easy_int64,Core_Info*>			core_list;

class JsonProxy : public JsonBase
{
public:
	

	JsonProxy(const easy_char* __file_name);

	~JsonProxy();

	static JsonProxy* instance(const easy_char* __file_name = "./config/servers.json");

	static void destroy();

public:
	//	get the wight total
	easy_int64	wight_total() const {return wight_total_;}

	std::string& log_path() { return log_path_;}

	//	get proxy information by wight
	Core_Info* get_core_info();

	core_list& get_core_list() { return core_list_;}
private:
	void _clear();

private:
	static JsonProxy* inst_;

	core_list	core_list_;

	//	wight total
	easy_int64	wight_total_;

	//	log	path
	std::string log_path_;
};

#endif // json_proxy_h__