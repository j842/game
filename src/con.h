#ifndef __CON
#define __CON

#include <string>

class Con
{
public:
    Con();
    ~Con();

    void errormsg(std::string s);
    void title();

    void endCon();

private:
    bool HasEnded;
};

Con * con();

#endif