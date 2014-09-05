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
#include "server_impl.h"
#include "reactor.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include "mongo/client/dbclient.h"	//	fpr mango
#ifdef __LINUX
#include "easy_dump.h"
#endif // __LINUX

const char* __mongo_host = "127.0.0.1:";
const char* __mongo_port = "27017";

#ifndef verify
#  define verify(x) MONGO_verify(x)
#endif

int main(int __arg_num,char** args)
{
	if(3 != __arg_num)
	{
		printf("param error,please input correct param! for example: nohup ./transform 192.168.22.63 9876 & \n");
		exit(1);
	}
#ifdef __LINUX
	signal(SIGSEGV,dump);
	//	when calls send() function twice if peer socket is closed, the SIG_PIPE signal will be trigger. and the SIG_PIPE 's default action is exit process.
	//	just ignore it! if use gdb debug,add 'handle SIGPIPE nostop print' or 'handle SIGPIPE nostop noprint' before run.
	signal(SIGPIPE,SIG_IGN);
#endif // __LINUX
	//	init mongo
	mongo::Status __status = mongo::client::initialize();
	if ( !__status.isOK() ) 
	{
        printf ("failed to initialize the client driver: %s\n",__status.toString().c_str());
        return EXIT_FAILURE;
    }
	mongo::DBClientConnection __conn;
	std::string __err_msg;
    if ( ! __conn.connect( std::string( __mongo_host ) + __mongo_port , __err_msg ) ) {
        printf("couldn't connect : %s\n",__err_msg.c_str());
        return EXIT_FAILURE;
    }
	printf("connect mongo server %s %s ok\n",__mongo_host,__mongo_port);
	//	test mongo code begin
	const char * __ns = "test.test1";
	__conn.dropCollection(__ns);
	// clean up old data from any previous tests
    __conn.remove( __ns, mongo::BSONObj() );
    verify( __conn.findOne( __ns , mongo::BSONObj() ).isEmpty() );
    // test insert
    __conn.insert( __ns ,BSON( "name" << "eliot" << "num" << 1 ) );
    verify( ! __conn.findOne( __ns , mongo::BSONObj() ).isEmpty() );
	//	test mongo code end
	
	char* __host = args[1];
	unsigned int __port = atoi(args[2]);
	Reactor* __reactor = Reactor::instance();
	Server_Impl __event_handle_srv(__reactor,__host,__port);
	static const int __max_time_out = 5000*1000;
	__reactor->event_loop(__max_time_out);
	return 0;
}
