#include "login_packet_handle.h"
#include "login.pb.h"
#include "mongo_unit_login.h"

int Login_Packet_Handle::handle_packet( int __packet_id,const std::string& __packet )
{
	login::c2l_login __packet_protobuf;
	__packet_protobuf.ParseFromString(__packet);
	std::string __user_name = __packet_protobuf.user_name();
	std::string __user_pwd = __packet_protobuf.user_pwd();
	MongocUnitLogin __mongoc_unit_login;
	__mongoc_unit_login.init();
	return 0;
}
