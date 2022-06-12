#include <string>
#include <vector>
#include <filesystem> // canonical
#include <unistd.h> // readlink

#include "utils.h"


std::string getExePath()
{
    std::vector<char> buf(400);
    size_t len;

    do
    {
        buf.resize(buf.size() + 100);
        len = ::readlink("/proc/self/exe", &(buf[0]), buf.size());
    } while (buf.size() == len);

    if (len > 0)
    {
        buf[len] = '\0';
        std::string exepath(&(buf[0]));
        exepath = std::filesystem::canonical(exepath);
        if (exepath.length() == 0)
            return "";

        unsigned int i = exepath.length() - 1;
        while (i > 0 && exepath[i] != '/')
            --i;
        if (i > 0 && i < exepath.length() - 1)
            exepath.erase(exepath.begin() + i + 1, exepath.end()); // keep ye slash.
        return exepath;
    }
    /* handle error */
    return "";
}
