#ifndef mongo_unit_login_h__
#define mongo_unit_login_h__

#include "easy_mongoc_unit.h"
#include <bson.h>
#include <string>

class MongocUnitLogin : public easy::MongocUnit{
public:
	MongocUnitLogin(std::string	__collection_name = "test");

	~MongocUnitLogin();

	void init();

	void save();
private:
	bson_error_t	error_;

	std::string		collection_name_;

	std::string		user_name;

	std::string		user_pwd;

#ifdef WIN32
	bson_t*			doc_;
#else
	const bson_t*	doc_;
#endif //WIN32
};

#endif // mongo_unit_login_h__