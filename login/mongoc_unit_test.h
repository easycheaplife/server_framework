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
#ifdef __USE_MONGOC
#ifndef mongoc_unit_test_h__
#define mongoc_unit_test_h__
#include "easy_mongoc_unit.h"
#include "easy_base_type.h"
#include <bson.h>
#include <string>
class MongocUnitTest : public easy::MongocUnit{
public:
	MongocUnitTest(std::string	__collection_name = "test");

	~MongocUnitTest();

	void init();

	void save();
private:
	bson_error_t	error_;

	std::string		collection_name_;

#ifdef WIN32
	bson_t*			doc_;
#else
	const bson_t*	doc_;
#endif //WIN32
};

#endif // mongoc_unit_test_h__
#endif //__USE_MONGOC