#include "NodeBinding.h"
#include "../GetFanInfo.h"
#include <iostream>
#include <vector>
#include <string>
#include <map>

Napi::Value NodeGetFanInfo(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    std::vector<std::map<std::string, val>> groupInfo;
    GetFanInfo(groupInfo);

    Napi::Object jsInfoArr = Napi::Array::New(env);

    auto getNapiObj = [&env](const std::string &k, const val &v) -> Napi::Object &
    {
        Napi::Object jsObj = Napi::Object::New(env);
        switch (v.valType)
        {
        case STRING_TYPE:
            jsObj.Set(k, v.stringVal);
            break;
        case NUMBER_TYPE:
            jsObj.Set(k, v.numberVal);
            break;
        case BOOLEAN_TYPE:
            jsObj.Set(k, v.boolVal);
            break;
        case NULL_TYPE:
            jsObj.Set(k, env.Null());
            break;
        }
        return jsObj;
    };

    for (int i = 0; i < groupInfo.size(); i++)
    {
        auto info = std::move(groupInfo[i]);
        Napi::Object jsInfoObj = Napi::Object::New(env);
        std::map<std::string, val>::iterator it;

        Napi::Object jsProtoKey = Napi::Array::New(env);

        int jsProtoKeyIdx = 0;
        for (it = info.begin(); it != info.end(); it++)
        {
            std::string keyName = std::move(it->first);
            val value = std::move(it->second);

            Napi::Object jsTempObj = getNapiObj(keyName, value);

            if (!keyName.rfind("__", 0))
            {
                jsInfoObj.Set("__proto__", jsTempObj);
                jsProtoKey.Set(jsProtoKeyIdx++, keyName);
            }
            else
            {
                Napi::Object ObjectConstructor = jsInfoObj.Get("constructor").As<Napi::Object>();
                Napi::Function ObjectAssignFn = ObjectConstructor.Get("assign").As<Napi::Function>();

                jsInfoObj = ObjectAssignFn.Call(env.Null(), {jsInfoObj, jsTempObj}).As<Napi::Object>();
            }
        }
        jsInfoObj.Set("WMIQueryIndicators", jsProtoKey);
        jsInfoArr.Set(i, jsInfoObj);
    }

    return jsInfoArr;
}

Napi::Object Initialize(Napi::Env env, Napi::Object exports)
{
    exports.Set(
        Napi::String::New(env, "GetFanInfo"),
        Napi::Function::New(env, NodeGetFanInfo));
    return exports;
}

NODE_API_MODULE(GetFanInfo, Initialize)