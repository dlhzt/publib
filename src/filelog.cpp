//=============================================================================
// File:          filelog.cpp
// Author:        Zhaojunwei
// CreateTime:    2005/03/31
// Descripiton:   Implementation file for logfile, which providing the time,
//                instance and log level records. The log files will be a group 
//                that cycles file of fixed length.
//                With setting log level, user can change the log contents 
//                according to the importance of record.
// ----------------------------------------------------------------------------
// Version:
//         2005/03/31   1.0 First work release.
//         2005/04/14   1.1 Modify Openlog() for its non-const value array size
//                          is not accepted by sun workshop CC though by gcc.
//
//=============================================================================

#ifdef WIN32
#include <windows.h>
#endif

#include <iostream>
#include <time.h>
#include "filelog.hpp"

bool FileLog::OpenLog(void)
{
	if(m_bOpen)
		return true;
	
	#ifdef WIN32
	#define stat _stat
	#endif
	struct stat fileStat;

	vector<string> FileName;
	vector<time_t> FileTime;
	vector<unsigned long> FileSize;
	unsigned int i;
	
	for(i = 0; i < m_fileNumber; i++)
	{
		m_strbuf.str("");
		m_strbuf << m_fileName <<"." << setfill('0') << setw(3) << i;
		FileName.push_back(m_strbuf.str());
		
		if(!stat(FileName[i].c_str(), &fileStat))
		{	
			FileTime.push_back(fileStat.st_mtime);
			FileSize.push_back(fileStat.st_size);
		}
		else
		{
			FileTime.push_back(0);
			FileSize.push_back(0);
		}
	}
	
	m_fileSeq = 0;
	time_t latestTime = 0;
	for(i = 0; i < m_fileNumber; i++)
	{
		if(FileTime[i] > latestTime)
		{
			latestTime = FileTime[i];
			m_fileSeq = i;
		}
	}
	
	m_currentSize = FileSize[m_fileSeq];
	m_logStream.open(FileName[m_fileSeq].c_str(), ios_base::out | ios_base::app);
	if(m_logStream.is_open())
		m_bOpen = true;

	return m_bOpen;
}

void FileLog::setPriority(const string& strPri)
{
	PRIORITY pri;
	if(strPri == string("DEBUG"))
		pri = P_DEBUG;
	else
	if(strPri == string("INFO"))
		pri = P_INFO;
	else
	if(strPri == string("NOTIFY"))
		pri = P_NOTIFY;
	else
	if(strPri == string("WARNING"))
		pri = P_WARNING;
	else
	if(strPri == string("ERROR"))
		pri = P_ERR;
	else
	if(strPri == string("FATAL"))
		pri = P_FATAL;
	else
		pri = P_NOTSET;
	
	setPriority(pri);
}

void FileLog::InsertLog(PRIORITY pri, const char* szInstance, const char* szText)
{
	if(pri < m_priority || m_bOpen == false)
		return;
	
	time_t current_t;
	struct tm current_tm;
	string strPri;
		
	switch(pri)
	{
		case P_NOTSET:
			strPri = "NOTSET";
			break;
		case P_DEBUG:
			strPri = "DEBUG";
			break;
		case P_INFO:
			strPri = "INFO";
			break;
		case P_NOTIFY:
			strPri = "NOTIFY";
			break;
		case P_WARNING:
			strPri = "WARNING";
			break;
		case P_ERR:
			strPri = "ERROR";
			break;
		case P_FATAL:
			strPri = "FATAL";
			break;
		default:
			strPri = "NOTSET";
	}
		
	time(&current_t);
	current_tm = *localtime(&current_t);
	m_strbuf.str("");
	m_strbuf << current_tm.tm_year + 1900
			 << "-" << setfill('0') << setw(2) << current_tm.tm_mon + 1
			 << "-" << setw(2) << current_tm.tm_mday
			 << " " << setw(2) << current_tm.tm_hour
			 << ":" << setw(2) << current_tm.tm_min
			 << ":" << setw(2) << current_tm.tm_sec
			 << ":[" << szInstance
			 << "]:[" << strPri
			 << "]=>" << szText;

	string strRec = m_strbuf.str();
	unsigned long recSize = strRec.length();
    if((m_currentSize + recSize) > m_maxFileSize)
    {
    	string strFileName;
    	m_logStream.close();
    	// add one second delay to make sure that the modifytime of next file will be later at least one second.
    	#ifdef WIN32
    	Sleep(1000);
    	#else
        sleep(1);
        #endif
    	
    	m_fileSeq++;
    	m_fileSeq %= m_fileNumber;
		m_strbuf.str("");
		m_strbuf << m_fileName << "." << setfill('0') << setw(3) << m_fileSeq;
		strFileName = m_strbuf.str();
   		#ifdef WIN32
   		#define unlink _unlink
   		#endif
        unlink(strFileName.c_str());
    	m_logStream.open(strFileName.c_str(), ios_base::out | ios_base::app);
    	if(!m_logStream)
    	{
    		m_bOpen = false;
    	}
    	m_currentSize = 0;
    }
    
    m_logStream << strRec << endl;
    m_currentSize += recSize;
    
    return;    	
};


