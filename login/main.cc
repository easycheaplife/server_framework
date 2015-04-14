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
//	for mongo c drive 
#include "mongoc_unit_test.h"
#include "mongocxx_unit_test.h"
#include "login.h"

easy_int32 main(easy_int32 __arg_num,easy_char** args)
{
	if(3 != __arg_num)
	{
		printf("param error,please input correct param! for example: nohup ./transform 192.168.22.63 9876 & \n");
		exit(1);
	}

	easy_char* __host = args[1];
	easy_uint32 __port = atoi(args[2]);
	Login __login_srv(__host,__port);

	MongocxxUnitTest __mongocxx_unit_test;
	__mongocxx_unit_test.test();

	__login_srv.event_loop();
	return 0;
}