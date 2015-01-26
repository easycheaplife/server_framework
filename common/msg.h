#ifndef msg_h__
#define msg_h__

enum 
{
	MSG_C2L_LOGIN = 1,
	MSG_L2C_LOGIN
};

enum
{
	LOGIN_STATUS_OK = 1000,
	LOGIN_STATUS_PWD_ERROR
};

enum 
{
	MSG_C2S2C_TEST = 65536,
};

#endif // msg_h__
