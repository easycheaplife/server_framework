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
#include "client_packet_handle.h"
#include "login.pb.h"
#include "msg.h"
#include "event_handle.h"

int Client_Packet_Handle::handle_packet(int __fd, int __packet_id,const std::string& __packet )
{
	switch (__packet_id)
	{
	case MSG_L2C_LOGIN:
		{
			login::l2c_login __packet_l2c_login;
			__packet_l2c_login.ParseFromString(__packet);
			int __status = __packet_l2c_login.status();
			if (LOGIN_STATUS_OK == __status)
			{
				printf("login ok\n");
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
