#ifndef session_h__
#define session_h__

#include "easy_base_type.h"

class Session
{
public:
	Session();

	~Session();

	//	set real fd
	void set_real_fd(easy_int32 __real_fd);

	//	get real fd
	easy_int32 real_fd() const { return real_fd_; }

private:
	easy_int32	real_fd_;
};
#endif // session_h__
