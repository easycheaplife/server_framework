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
#include "common.pb.h"
#include "mongocxx_unit_login.h"
#include "msg.h"
#include "event_handle.h"
#include "json_login.h"

int Login_Packet_Handle::handle_packet(easy_int32 __fd,const std::string& __packet,void* __user_data )
{
	common::common_head __packet_head;
	__packet_head.ParseFromString(__packet);
	easy_int32 __msg_id =__packet_head.msg_id();
	switch (__msg_id)
	{
	case MSG_C2L_LOGIN: 
		{
			login::c2l_login __packet_c2l;
			__packet_c2l.ParseFromString(__packet);
			std::string __user_name = __packet_c2l.user_name();
			std::string __user_pwd = __packet_c2l.user_pwd();
			MongocxxUnitLogin __mongocxx_unit_login;
			easy_bool __success = __mongocxx_unit_login.query(__user_name,__user_pwd);
			if(__success){
				login::l2c_login __packet_l2c_login;
				__packet_l2c_login.set_msg_id(MSG_L2C_LOGIN);
				__packet_l2c_login.set_status(LOGIN_STATUS_OK);
				Proxy_Info* __proxy_info = JsonLogin::instance()->get_proxy_info();
				if (__proxy_info)
				{
					__packet_l2c_login.set_proxy_ip(__proxy_info->ip_);
					__packet_l2c_login.set_proxy_port(__proxy_info->port_);
				}
				std::string __string_login;
				__packet_l2c_login.SerializeToString(&__string_login);
				easy_uint32 __length = 0;
				__length = __string_login.length();
				event_handle_->write(__fd,(const easy_char*)&__length,sizeof(easy_uint32));
				event_handle_->write(__fd,__string_login.c_str(),__string_login.length());
			}
		}
		break;
	default:
		break;
	}

	return 0;
}
