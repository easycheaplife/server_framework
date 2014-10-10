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
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include "reactor.h"
#include "client_protobuf_impl.h"
#include "login.pb.h"
int main(int __arg_num,char** args)
{
	if(3 != __arg_num)
	{
		printf("param error,please input correct param! for example: nohup ./transform 192.168.22.63 9876 & \n");
		exit(1);
	}
	char* __host = args[1];
	unsigned int __port = atoi(args[2]);
	Reactor* __reactor = Reactor::instance();
	Client_Impl* __client_impl = new Client_Impl(__reactor,__host,__port);
	static const int __max_time_out = 5000*1000;
	//	test code begin
	unsigned int __head = 0;
	int __pakcet_id = 123;
	login::c2l_login __c2l_login;
	__c2l_login.set_user_name("lee");
	__c2l_login.set_user_pwd("lee");
	std::string __string_login;
	__c2l_login.SerializeToString(&__string_login);
	__head |= (__pakcet_id << 16);
	__head |= (__string_login.length());
	__client_impl->write((const char*)&__head,sizeof(unsigned int));
	__client_impl->write(__string_login);
	//	test code end
	__reactor->event_loop(__max_time_out);
	return 0;
}
