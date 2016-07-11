//=============================================================================
// File:          readcfg.cpp
// Author:        Zhaojunwei
// CreateTime:    2004/11/22
// Descripiton:   Implementation file for configuration file reading. 
// ----------------------------------------------------------------------------
// Version:
//         2004/11/22   1.0 First work release.
//         2005/03/31   1.1 Change the type of finding string to string::size_type
//                          according to its defination.
//=============================================================================

#include "readcfg.hpp"

ReadCfg::ReadCfg():
m_bOpen(false), m_strFileName("")
{
}

ReadCfg::ReadCfg(const string& strFileName):
m_bOpen(false), m_strFileName(strFileName)
{
    OpenCfg(strFileName);
}

ReadCfg::ReadCfg(const char* pFileName):
m_bOpen(false), m_strFileName(pFileName)
{
    OpenCfg(pFileName);
}

ReadCfg::~ReadCfg()
{
}

bool ReadCfg::OpenCfg(const string& strFileName)
{
    return OpenCfg(strFileName.c_str());
}

bool ReadCfg::OpenCfg(const char* pFileName)
{
    m_strFileName = pFileName;
    
    ifstream fin(pFileName);
    if(!fin)
    {
        return false;
    }
    
    char str[1024];
    string strLine;
    string::size_type nPos1, nPos2;
    string strSection("Global"); 
    string strKey, strValue;
    while(fin.getline(str, sizeof(str)))
    {
        strLine = str;
        if(strLine[0] == '#' || strLine.length() == 0)
            continue;
        
        // Find a Section tag
        if(strLine[0] == '[')
        {
            if((nPos1 = strLine.find(']')) != string::npos)
            {
                strSection = strLine.substr(1, nPos1 - 1);
            }
            continue;
        }
        
        // Get rid of rear comment
        if((nPos1 = strLine.find('#')) != string::npos)
        {
            strLine = strLine.substr(0, nPos1);
        }
        
        // Get a pair of key and value
        if((nPos1 = strLine.find('=')) != string::npos)
        {
            nPos2 = strLine.find_first_not_of(" \t");
            strKey = strLine.substr(nPos2, nPos1 - nPos2);
            if((nPos2 = strKey.find_last_not_of(" \t")) != string::npos)
            {
                strKey = strKey.substr(0, nPos2 + 1);
            }
            
            nPos2 = strLine.find_first_not_of(" \t", nPos1 + 1);
            strValue = strLine.substr(nPos2);
            if((nPos2 = strValue.find_last_not_of(" \t")) != string::npos)
            {
                strValue = strValue.substr(0, nPos2 + 1);
            }

            m_triGroup[strSection][strKey] = strValue;
        }
    }
    
    //#define _DEBUG_DATA
    #ifdef _DEBUG_DATA
    map<string, KeyValue>::iterator itSection;
    KeyValue::iterator itKey;
    for(itSection = m_triGroup.begin(); itSection != m_triGroup.end(); itSection++)
    {
        cout << "Section: [" << itSection->first << "]" << endl;
        for(itKey = itSection->second.begin(); itKey != itSection->second.end(); itKey++)
            cout << "\tKey: [" << itKey->first << "], Val: [" << itKey->second << "]" << endl;
    }
    #endif
    
    m_bOpen = true;
    return m_bOpen;
}

const string& ReadCfg::GetValue(const string& strSection, const string& strKey)
{
    if(!m_bOpen)
    {
        return m_strNULL;
    }
    
    return m_triGroup[strSection][strKey];
}

const string& ReadCfg::GetValue(const char* pSection, const char*pKey)
{
    if(!m_bOpen)
    {
        return m_strNULL;
    }
    return m_triGroup[string(pSection)][string(pKey)];
}


