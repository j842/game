#ifndef __GETEXEPATH
#define __GETEXEPATH

#include <string>
#include <sstream>


std::string getExePath(); // ends in slash.



// class to inline ostringstream, which allows embedded end of line.
class S
{
private:
    std::ostringstream os_stream;

public:
    S() {}
    S(const char *s) : os_stream(s) {}
    S(const std::string &s) : os_stream(s) {}
    template <class T>
    S &operator<<(const T &t)
    {
        os_stream << t;
        return *this;
    }
    S &operator<<(std::ostream &(*f)(std::ostream &))
    {
        os_stream << f;
        return *this;
    }
    operator std::string() const
    {
        return os_stream.str();
    }
};


#endif
