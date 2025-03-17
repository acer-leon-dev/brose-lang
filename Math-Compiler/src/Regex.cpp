#include "Regex.hpp"

namespace regex
{

std::string match_start(
    const std::string& regex,
    const std::string& src,
    std::size_t pos,
    std::size_t n)
{
    std::string::const_iterator sit = src.cbegin() + pos;
    std::string::const_iterator eit = (pos + n >= src.size()) ? src.cend() : sit + n;
    boost::regex r { regex };
    boost::smatch m;
    if (boost::regex_search(sit, eit, m, r, boost::match_default | boost::match_continuous))
    {
        return m[0];
    }

    return "";
}

};