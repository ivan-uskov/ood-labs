#pragma once
#include <string>
#include <boost/lexical_cast.hpp>

namespace TextUtils
{
    template <typename DstType>
    bool convertString(std::string const& str, DstType & value)
    {
        try
        {
            value = boost::lexical_cast<DstType>(str);
            return true;
        }
        catch (boost::bad_lexical_cast const&)
        {
            return false;
        }
    }
};

