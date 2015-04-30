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
#include "mongocxx_unit_login.h"
#include "easy_mongocxx_wrapper.h"

MongocxxUnitLogin::MongocxxUnitLogin(std::string	__collection)
	:MongocxxUnit(__collection)
{
	
}

MongocxxUnitLogin::~MongocxxUnitLogin()
{

}

bool MongocxxUnitLogin::query( std::string& __user_name, std::string& __user_pwd, easy_int32& __unique_id )
{
	std::auto_ptr<mongo::DBClientCursor> __cursor = easy::MongocxxWrapper::instance()->db_client_connection().query( collection_ , mongo::BSONObj() );
	while (__cursor->more())
	{
		mongo::BSONObj __res = __cursor->next();
		const easy_char* __pwd = __res.getStringField( __user_name ); 
		if (__user_pwd == __pwd)
		{
			__unique_id = __res.getIntField("id");
			return true;
		}
	}
	return false;
}
