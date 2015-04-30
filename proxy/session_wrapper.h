#ifndef session_wrapper_h__
#define session_wrapper_h__
#include <map>
#include "easy_base_type.h"

class Session;

class Session_Wrapper
{
public:
	Session_Wrapper();

	void add_session(easy_int32 __unique_id,Session* __session);

	void del_session(easy_int32 __unique_id);

	Session* get_session(easy_int32 __unique_id);

	static Session_Wrapper* instance();

	static void		destrory();

	~Session_Wrapper();
	
private:
	typedef std::map<easy_int32,Session*>	session;
	session								sessions_;

	static	Session_Wrapper*		inst_;
};
#endif // session_wrapper_h__
