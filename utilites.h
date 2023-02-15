#ifndef __UTILITES_H__
#define __UTILITES_H__
#include <windows.h>
#include <algorithm>
#include <string>
#include <vector>
#include <map>

template <typename T>
static inline std::vector<T> vectorEmptyStringFilter(std::vector<T> &inVec)
{
    std::vector<T> outVec;

    std::copy_if(inVec.begin(), inVec.end(), std::inserter(outVec, outVec.end()), [](T str) -> bool
                 { return str.length() > 0; });

    return outVec;
}

template <typename T>
static inline bool SomeWSTRToString(T inBSTR, std::string &outString)
{
    DWORD size = WideCharToMultiByte(CP_UTF8,
                                     0,
                                     inBSTR,
                                     -1,
                                     nullptr,
                                     0,
                                     nullptr,
                                     nullptr);

    if (size == 0)
    {
        return false;
    }

    std::unique_ptr<char[]> res = std::make_unique<char[]>(size);
    DWORD result = WideCharToMultiByte(CP_UTF8,
                                       0,
                                       inBSTR,
                                       -1,
                                       res.get(),
                                       size,
                                       nullptr,
                                       nullptr);

    if (result == 0)
    {
        return false;
    }

    outString = std::string(res.get());

    return true;
}

template <typename T>
static inline bool vectorZip(std::vector<T> &vec1, std::vector<T> &vec2, std::map<T, T> &out)
{
    if (vec1.size() != vec2.size())
    {
        return false;
    }

    std::transform(vec1.begin(), vec1.end(), vec2.begin(), std::back_inserter(out.begin(), out.end()), [](T str1, T str2) -> T
                   { out.insert(std::pair<T, T>(str1, str2)); });

    return true;
}

#endif