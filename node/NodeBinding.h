#ifndef __NODE_BINDING_H__
#define __NODE_BINDING_H__

#include <napi.h>

Napi::Value NodeGetFanInfo(const Napi::CallbackInfo&);
Napi::Object Initialize(Napi::Env, Napi::Object);


#endif
