/********************************************************************
	created:	2014/09/29
	created:	29:9:2014   15:14
	filename: 	E:\open_source\server_framework\login\mongo_unit_test.h
	file path:	E:\open_source\server_framework\login
	file base:	mongo_unit_test
	file ext:	h
	author:		King Lee
	
	purpose:	
*********************************************************************/
#ifndef mongo_unit_test_h__
#define mongo_unit_test_h__
#include "easy_mongoc_unit.h"
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

#endif // mongo_unit_test_h__