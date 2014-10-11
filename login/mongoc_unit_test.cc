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
#include "mongoc_unit_test.h"
#include "easy_mongoc_wrapper.h"


MongocUnitTest::MongocUnitTest(std::string	__collection_name)
{
	collection_name_ = __collection_name;
}

MongocUnitTest::~MongocUnitTest()
{

}

void MongocUnitTest::init()
{
	//	find a doc
	doc_ = bson_new ();
	bson_t* __query = bson_new ();
	bson_init (__query);
	mongoc_cursor_t* __cursor = easy::MongocWrapper::instance()->collection_find(collection_name_.c_str(),__query);
	char* __str = NULL;
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
}

void MongocUnitTest::save()
{
	doc_ = bson_new ();
	bson_oid_t __oid;
	bson_oid_init (&__oid, NULL);
	BSON_APPEND_OID (doc_, "_id", &__oid);
	BSON_APPEND_UTF8 (doc_, "hello", "world");
	easy::MongocWrapper::instance()->collection_insert(collection_name_.c_str(),doc_);
	bson_destroy (doc_);
}
