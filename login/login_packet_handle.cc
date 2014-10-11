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
#include "login_packet_handle.h"
#include "login.pb.h"
#include "mongo_unit_login.h"
#include "msg.h"
#include "event_handle.h"

int Login_Packet_Handle::handle_packet(int __fd, int __packet_id,const std::string& __packet )
{
	switch (__packet_id)
	{
	case MSG_C2L_LOGIN: 
		{
			login::c2l_login __packet_c2l_login;
			__packet_c2l_login.ParseFromString(__packet);
			std::string __user_name = __packet_c2l_login.user_name();
			std::string __user_pwd = __packet_c2l_login.user_pwd();
			MongocUnitLogin __mongoc_unit_login;
			bool __success = __mongoc_unit_login.query(__user_name,__user_pwd);
			if(__success){
				login::l2c_login __packet_l2c_login;
				__packet_l2c_login.set_status(LOGIN_STATUS_OK);
				std::string __string_login;
				__packet_l2c_login.SerializeToString(&__string_login);
				unsigned int __head = 0;
				__head |= (MSG_L2C_LOGIN << 16);
				__head |= (__string_login.length());
				event_handle_->write(__fd,(const char*)&__head,sizeof(unsigned int));
				event_handle_->write(__fd,__string_login.c_str(),__string_login.length());
			}
		}
		break;
	default:
		break;
	}

	return 0;
}
