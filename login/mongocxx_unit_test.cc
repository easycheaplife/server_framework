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
#include "mongocxx_unit_test.h"
#include "easy_mongocxx_wrapper.h"
#include "json_login.h"

#ifndef verify
#  define verify(x) MONGO_verify(x)
#endif


MongocxxUnitTest::MongocxxUnitTest(std::string	__collection)
	:MongocxxUnit(__collection)
{
	
}

MongocxxUnitTest::~MongocxxUnitTest()
{

}

void MongocxxUnitTest::test()
{
	std::string __mongodb_url = JsonLogin::instance()->mongodb_url();
	//	test mongo code begin
	easy::MongocxxWrapper::instance(__mongodb_url.c_str())->db_client_connection().dropCollection(collection_);
	// clean up old data from any previous tests
	easy::MongocxxWrapper::instance()->db_client_connection().remove( collection_, mongo::BSONObj() );
	verify( easy::MongocxxWrapper::instance()->db_client_connection().findOne( collection_ , mongo::BSONObj() ).isEmpty() );
	// test insert
	easy::MongocxxWrapper::instance()->db_client_connection().insert( collection_ ,BSON( "name" << "eliot" << "num" << 1 ) );
	// test remove
	easy::MongocxxWrapper::instance()->db_client_connection().remove( collection_, mongo::BSONObj() );
	verify( easy::MongocxxWrapper::instance()->db_client_connection().findOne( collection_ , mongo::BSONObj() ).isEmpty() );
	// insert, findOne testing
	easy::MongocxxWrapper::instance()->db_client_connection().insert( collection_ , BSON( "name" << "eliot" << "num" << 1 ) );
	{
		mongo::BSONObj __res = easy::MongocxxWrapper::instance()->db_client_connection().findOne( collection_ , mongo::BSONObj() );
		const easy_char* __name = __res.getStringField( "name" );
		verify( strstr(__name , "eliot") );
		const easy_char* __name2 = __res.getStringField( "name2" );
		verify( !strstr(__name2 , "eliot") );
		verify( 1 == __res.getIntField( "num" ) );
	}
	// cursor
	easy::MongocxxWrapper::instance()->db_client_connection().insert( collection_ ,BSON( "name" << "sara" << "num" << 2 ) );
	{
		std::auto_ptr<mongo::DBClientCursor> __cursor = easy::MongocxxWrapper::instance()->db_client_connection().query( collection_ , mongo::BSONObj() );
		easy_int32 __count = 0;
		while ( __cursor->more() ) {
			__count++;
			mongo::BSONObj __obj = __cursor->next();
		}
		verify( __count == 2 );
	}
	//	test mongo code end
	easy::MongocxxWrapper::instance()->db_client_connection().insert( collection_ ,BSON( "lee" << "lee" ) );
	printf("mongo cxx test\n");
}
