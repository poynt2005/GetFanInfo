#ifndef __GET_FAN_INFO_H__
#define __GET_FAN_INFO_H__
#include <vector>
#include <string>
#include <map>

#define STRING_TYPE 0xe0
#define NUMBER_TYPE 0xe2
#define BOOLEAN_TYPE 0xe3
#define NULL_TYPE 0xe4

using val = struct _val
{
    int valType;
    std::string stringVal;
    double numberVal;
    bool boolVal;
};

#ifdef BUILDFANINFOAPI
#define EXPORTFANINFOAPI __declspec(dllexport)
#else
#define EXPORTFANINFOAPI __declspec(dllimport)
#endif

EXPORTFANINFOAPI void __cdecl GetFanInfo(std::vector<std::map<std::string, val>> &);

#endif