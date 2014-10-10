//	for mongo c drive 
#include "mongo_unit_test.h"
#include "login.h"
int main(int __arg_num,char** args)
{
	if(3 != __arg_num)
	{
		printf("param error,please input correct param! for example: nohup ./transform 192.168.22.63 9876 & \n");
		exit(1);
	}

	MongocUnitTest __mongoc_unit_test;
	__mongoc_unit_test.init();
	//__mongoc_unit_test.save();

	char* __host = args[1];
	unsigned int __port = atoi(args[2]);
	Login __login_srv(__host,__port);
	__login_srv.event_loop();
	return 0;
}