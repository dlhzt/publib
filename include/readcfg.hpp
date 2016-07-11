//=============================================================================
// File:          readcfg.hpp
// Author:        Zhaojunwei
// CreateTime:    2004/11/22
// Descripiton:   Head file for configuration file reading. 
// ----------------------------------------------------------------------------
// Version:
//         2004/11/22   1.0 First work release.
//
//=============================================================================

#ifndef READ_CFG_HPP
#define READ_CFG_HPP

#include <fstream>
#include <string>
#include <map>

#include <iostream> 

using namespace std;
typedef map<string, string> KeyValue;

class ReadCfg{
public:
    ReadCfg(const string& strFileName);
    ReadCfg(const char* pFileName);
    ReadCfg();
    ~ReadCfg();
    
    bool OpenCfg(const string& strFileName);
    bool OpenCfg(const char* pFileName);
    const string& GetValue(const string& strSection, const string& strKey);
    const string& GetValue(const char* pSection, const char*pKey);
private:
    bool m_bOpen;
    string m_strFileName;
    string m_strNULL;
    map<string, KeyValue> m_triGroup;
};

#endif

