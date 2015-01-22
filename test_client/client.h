#ifndef client_h__
#define client_h__
#include <string>
#include "easy_base_type.h"

class Connector;

class Client
{
public:
	Client();

	~Client();

	static Client* instance();

	static void destroy();

	easy_bool connect_login(const easy_char* __host, easy_uint32 __port);

	easy_bool connect_proxy(const easy_char* __host, easy_uint32 __port);

	void	send_login_msg();

	void	send_test_msg();

private:
	static Client*		inst_;

	//	connector for login
	Connector*			connector_login_;

	//	connector for proxy
	Connector*			connector_proxy_;

	std::string			login_host_;

	easy_uint32			login_port_;

	std::string			proxy_host_;

	easy_uint32			proxy_port_;
				
};
#endif // client_h__
