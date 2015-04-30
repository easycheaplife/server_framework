#include "session_wrapper.h"
#include "session.h"

Session_Wrapper* Session_Wrapper::inst_ = easy_null;

Session_Wrapper::Session_Wrapper()
{

}

Session_Wrapper::~Session_Wrapper()
{

}

void Session_Wrapper::add_session(easy_int32 __unique_id,Session* __session)
{
	sessions_[__unique_id] = __session;
}

void Session_Wrapper::del_session(easy_int32 __unique_id)
{
	std::map<easy_int32,Session*>::iterator __find = sessions_.find(__unique_id);
	if (__find != sessions_.end())
	{
		sessions_.erase(__find);
	}
}

Session_Wrapper* Session_Wrapper::instance()
{
	if (!inst_)
	{
		inst_ = new Session_Wrapper();
	}
	return inst_;
}

void Session_Wrapper::destrory()
{
	if (inst_)
	{
		delete inst_;
		inst_ = easy_null;
	}
}

Session* Session_Wrapper::get_session( easy_int32 __unique_id )
{
	std::map<easy_int32,Session*>::iterator __find = sessions_.find(__unique_id);
	if (__find != sessions_.end())
	{
		return __find->second;
	}
	return easy_null;
}
