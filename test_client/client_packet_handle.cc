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
#include <stdio.h>
#include "client_packet_handle.h"
#include "login.pb.h"
#include "msg.h"
#include "event_handle.h"
#include "client.h"

int Client_Packet_Handle::handle_packet(easy_int32 __fd,const std::string& __packet )
{
	login::l2c_login __packet_l2c_login;
	__packet_l2c_login.ParseFromString(__packet);
	easy_int32 __msg_id = __packet_l2c_login.msg_id();
	switch (__msg_id)
	{
	case MSG_L2C_LOGIN:
		{
			easy_int32 __status = __packet_l2c_login.status();
			if (LOGIN_STATUS_OK == __status)
			{
				printf("login ok,ready for connect proxy ip:%s,port:%d\n",__packet_l2c_login.proxy_ip().c_str(),__packet_l2c_login.proxy_port());
				Client::instance()->connect_proxy(__packet_l2c_login.proxy_ip().c_str(),__packet_l2c_login.proxy_port());
				//	for test 
				Client::instance()->send_test_msg();
			}
			else
			{
				printf("login error\n");
			}
		}
		break;
	default:
		{

		}
		break;
	}
	return 0;
}
