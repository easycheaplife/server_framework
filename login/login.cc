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
//	for mongo c drive 
#include <bson.h>
#include <mongoc.h>
#ifdef __LINUX
#include "easy_dump.h"
#endif // __LINUX

const char* __uri_string = "mongodb://192.168.22.61/";
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

	//	init mongoc
	mongoc_init();
	mongoc_client_t* __client = mongoc_client_new (__uri_string);
	if (!__client) {
      fprintf (stderr, "Failed to parse URI.\n");
      return EXIT_FAILURE;
    }
    bson_t __query;
    bson_init (&__query);
    mongoc_collection_t* __collection = mongoc_client_get_collection (__client, "test", "test");
	//	add a doc
    const bson_t* __doc = bson_new ();
	bson_oid_t __oid;
	bson_oid_init (&__oid, NULL);
	BSON_APPEND_OID (__doc, "_id", &__oid);
    BSON_APPEND_UTF8 (__doc, "hello", "world");
	bson_error_t __error;
    if (!mongoc_collection_insert (__collection, MONGOC_INSERT_NONE, __doc, NULL, &__error)) {
        printf ("%s\n", __error.message);
    }
	bson_destroy (__doc);
	//	find a doc
	mongoc_cursor_t* __cursor = mongoc_collection_find (__collection,
                                    MONGOC_QUERY_NONE,
                                    0,
                                    0,
                                    0,
                                    &__query,
                                    NULL,  /* Fields, NULL for all. */
                                    NULL); /* Read Prefs, NULL for default */
	char* __str = NULL;;
	while (mongoc_cursor_next (__cursor, &__doc)) {
      __str = bson_as_json (__doc, NULL);
      fprintf (stdout, "%s\n", __str);
      bson_free (__str);
	}
    if (mongoc_cursor_error (__cursor, &__error)) {
      fprintf (stderr, "Cursor Failure: %s\n", __error.message);
      return EXIT_FAILURE;
    }
   
	char* __host = args[1];
	unsigned int __port = atoi(args[2]);
	Reactor* __reactor = Reactor::instance();
	Server_Impl __event_handle_srv(__reactor,__host,__port);
	static const int __max_time_out = 5000*1000;
	__reactor->event_loop(__max_time_out);
	return 0;
}
