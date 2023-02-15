#include <iostream>
#include <windows.h>
#include <wbemidl.h>
#include "GetFanInfo.h"
#include "utilites.h"

void GetFanInfo(std::vector<std::map<std::string, val>> &groupQueryResult)
{

    long hres = CoInitializeEx(0, COINIT_MULTITHREADED);

    if (hres < 0)
    {
        std::cout << "CoInitializeEx Failed\n";
        exit(-1);
    }

    hres = CoInitializeSecurity(
        NULL,
        -1,
        NULL,
        NULL,
        RPC_C_AUTHN_LEVEL_DEFAULT,
        RPC_C_IMP_LEVEL_IMPERSONATE,
        NULL,
        EOAC_NONE,
        NULL);

    if (hres < 0)
    {
        std::cout << "CoInitializeSecurity Failed\n";
        exit(-1);
    }

    IWbemLocator *pLoc = NULL;

    hres = CoCreateInstance(
        CLSID_WbemLocator, // 创建的Com对象的类标识符(CLSID)
        0,
        CLSCTX_INPROC_SERVER, // 创建在同一进程中运行的组件。为能够同一进程中运行，组件必须是在DLL中实现的。
        IID_IWbemLocator,
        reinterpret_cast<void **>(&pLoc));

    if (hres < 0)
    {
        std::cout << "CoCreateInstance Failed\n";
        exit(-1);
    }

    IWbemServices *pSvc = NULL;

    hres = pLoc->ConnectServer(
        L"root\\CIMV2",
        NULL,
        NULL,
        NULL,
        0,
        NULL,
        NULL,
        &pSvc);

    if (hres < 0)
    {
        std::cout << "Connect to Server failed\n";
        exit(-1);
    }

    IEnumWbemClassObject *pClsObject = NULL;

    hres = pSvc->ExecQuery(
        L"WQL",
        L"SELECT * FROM Win32_Fan",
        WBEM_FLAG_RETURN_WBEM_COMPLETE,
        NULL,
        &pClsObject);

    if (hres < 0)
    {
        std::cout << "ExecQuery Failed\n";
        exit(-1);
    }

    long wmiIteratorResult;

    do
    {
        IWbemClassObject *wbemClsObj[10];
        unsigned long pReturned;
        wmiIteratorResult = pClsObject->Next(
            WBEM_INFINITE,
            10,
            wbemClsObj,
            &pReturned);

        for (unsigned long i = 0; i < pReturned; i++)
        {
            auto &&wbemObj = std::move(wbemClsObj[i]);

            long wbemObjEnumResult = wbemObj->BeginEnumeration(0);

            std::vector<std::wstring> wbemObjClsNameCollection;

            do
            {
                BSTR wbemObjClsName = NULL;
                VARIANT wbemVariant;
                CIMTYPE wbemCimtype;
                long wbemPFlavor;
                wbemObjEnumResult = wbemObj->Next(
                    0,
                    &wbemObjClsName,
                    &wbemVariant,
                    &wbemCimtype,
                    &wbemPFlavor);

                if (wbemObjEnumResult >= 0)
                {
                    wbemObjClsNameCollection.emplace_back(std::wstring(wbemObjClsName, SysStringLen(wbemObjClsName)));
                }

                VariantClear(&wbemVariant);
            } while (wbemObjEnumResult == 0);

            wbemObjClsNameCollection = vectorEmptyStringFilter<std::wstring>(wbemObjClsNameCollection);

            std::map<std::string, val> wbemObjQueryKeyValueMappingCollection;

            for (auto &&wbemObjClsName : wbemObjClsNameCollection)
            {

                VARIANT wbemVariant;
                CIMTYPE wbemCimtype;
                long wbemPFlavor;
                long wbemObjQueryResult = wbemObj->Get(
                    wbemObjClsName.data(),
                    0,
                    &wbemVariant,
                    &wbemCimtype,
                    &wbemPFlavor);

                if (wbemObjQueryResult >= 0)
                {
                    std::string outString;

                    unsigned short valType = wbemVariant.vt;

                    std::string wbemObjClsNameUtf8Val;
                    SomeWSTRToString<wchar_t *>(const_cast<wchar_t *>(wbemObjClsName.data()), wbemObjClsNameUtf8Val);
                    val _v;
                    switch (wbemVariant.vt)
                    {
                    case VT_I2:
                    {
                        _v.valType = NUMBER_TYPE;
                        _v.numberVal = static_cast<double>(wbemVariant.iVal);
                        wbemObjQueryKeyValueMappingCollection.insert(std::pair<std::string, val>(wbemObjClsNameUtf8Val, _v));
                        break;
                    }
                    case VT_I4:
                    {
                        _v.valType = NUMBER_TYPE;
                        _v.numberVal = static_cast<double>(wbemVariant.lVal);
                        wbemObjQueryKeyValueMappingCollection.insert(std::pair<std::string, val>(wbemObjClsNameUtf8Val, _v));
                        break;
                    }
                    case VT_R4:
                    {
                        _v.valType = NUMBER_TYPE;
                        _v.numberVal = static_cast<double>(wbemVariant.fltVal);
                        wbemObjQueryKeyValueMappingCollection.insert(std::pair<std::string, val>(wbemObjClsNameUtf8Val, _v));
                        break;
                    }
                    case VT_R8:
                    {
                        _v.valType = NUMBER_TYPE;
                        _v.numberVal = static_cast<double>(wbemVariant.dblVal);
                        wbemObjQueryKeyValueMappingCollection.insert(std::pair<std::string, val>(wbemObjClsNameUtf8Val, _v));
                        break;
                    }
                    case VT_BSTR:
                    {
                        std::string _val;
                        SomeWSTRToString<BSTR>(wbemVariant.bstrVal, _val);
                        _v.valType = STRING_TYPE;
                        _v.stringVal = _val;
                        wbemObjQueryKeyValueMappingCollection.insert(std::pair<std::string, val>(wbemObjClsNameUtf8Val, _v));
                        break;
                    }
                    case VT_BOOL:
                    {
                        _v.valType = BOOLEAN_TYPE;
                        _v.boolVal = wbemVariant.boolVal;
                        wbemObjQueryKeyValueMappingCollection.insert(std::pair<std::string, val>(wbemObjClsNameUtf8Val, _v));
                        break;
                    }
                    default:
                    {
                        _v.valType = NULL_TYPE;
                        wbemObjQueryKeyValueMappingCollection.insert(std::pair<std::string, val>(wbemObjClsNameUtf8Val, _v));
                        break;
                    }
                    }
                }

                VariantClear(&wbemVariant);
            }

            wbemObj->EndEnumeration();
            wbemObj->Release();

            groupQueryResult.emplace_back(wbemObjQueryKeyValueMappingCollection);
        }

    } while (wmiIteratorResult == 0);

    pLoc->Release();
    pSvc->Release();
    pClsObject->Release();
    CoUninitialize();
}