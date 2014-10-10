#include "mongo_unit_login.h"
#include "easy_mongoc_wrapper.h"


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
	//	find a doc
	doc_ = bson_new ();
	bson_t* __query = bson_new ();
	bson_init (__query);
	BSON_APPEND_UTF8 (__query, "lee", "lee");
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

void MongocUnitLogin::save()
{
	doc_ = bson_new ();
	bson_oid_t __oid;
	bson_oid_init (&__oid, NULL);
	BSON_APPEND_OID (doc_, "_id", &__oid);
	BSON_APPEND_UTF8 (doc_, "lee", "lee");
	easy::MongocWrapper::instance()->collection_insert(collection_name_.c_str(),doc_);
}
