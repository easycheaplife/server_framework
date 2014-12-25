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
#include <string>
#include "client.h"
#include "login.pb.h"
#include "msg.h"
easy_int32 main(easy_int32 __arg_num,easy_char** args)
{
	if(3 != __arg_num)
	{
		printf("param error,please input correct param! for example: nohup ./transform 192.168.22.63 9876 & \n");
		exit(1);
	}
	easy_char* __host = args[1];
	easy_uint32 __port = atoi(args[2]);
	Client* __client_impl = new Client(__host,__port);
	static const easy_int32 __max_time_out = 5000*1000;
	//	test code begin
	easy_uint16 __length = 0;
	easy_int32 __pakcet_id = MSG_C2L_LOGIN;
	login::c2l_login __c2l_login;
	__c2l_login.set_msg_id(__pakcet_id);
	__c2l_login.set_user_name("lee");
	__c2l_login.set_user_pwd("lee");
	std::string __string_login;
	__c2l_login.SerializeToString(&__string_login);
	__length = __string_login.length();
	__client_impl->write((const easy_char*)&__length,sizeof(easy_uint16));
	__client_impl->write(__string_login);
	//	test code end
	__client_impl->event_loop(__max_time_out);
	return 0;
}
