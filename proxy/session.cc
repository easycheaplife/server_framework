#include "session.h"

Session::Session()
{
	real_fd_ = 0;
}

Session::~Session()
{

}

void Session::set_real_fd( easy_int32 __real_fd )
{
	real_fd_ = __real_fd;
}
