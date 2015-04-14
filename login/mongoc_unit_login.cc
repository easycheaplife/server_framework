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
#include "mongoc_unit_login.h"
#include "easy_mongoc_wrapper.h"
#ifdef __USE_MONGOC

MongocUnitLogin::MongocUnitLogin(std::string	__collection_name)
{
	collection_name_ = __collection_name;
}

MongocUnitLogin::~MongocUnitLogin()
{

}

void MongocUnitLogin::init()
{
	if(0)
	{
		save();
	}
}

void MongocUnitLogin::save()
{

}

easy_bool MongocUnitLogin::query( std::string& __user_name, std::string& __user_pwd )
{
	//	find a doc
	doc_ = bson_new ();
	bson_t* __query = bson_new ();
	bson_init (__query);
	BSON_APPEND_UTF8 (__query, __user_name.c_str(), __user_pwd.c_str());
	mongoc_cursor_t* __cursor = easy::MongocWrapper::instance()->collection_find(collection_name_.c_str(),__query);
	easy_char* __str = NULL;
#ifdef WIN32
	while (mongoc_cursor_next (__cursor, (const bson_t**)&doc_)) {
#else
	while (mongoc_cursor_next (__cursor, &doc_)) {
#endif // WIN32
		__str = bson_as_json (doc_, NULL);
		fprintf (stdout, "%s\n", __str);
		bson_free (__str);
	}
	if (mongoc_cursor_error (__cursor, &error_)) {
		fprintf (stderr, "Cursor Failure: %s\n", error_.message);
	}
	if (__str)
	{
		return true;
	}
	return false;
}
#endif //__USE_MONGOC