//=============================================================================
// File:          threadlog.cpp
// Author:        Zhaojunwei
// CreateTime:    2005/03/31
// Descripiton:   Implementation file for threadlog, which subclass the filelog 
//                to provide mutli-thread logging. User should create a thread
//                to loop the WriteLog method, and in other thread call debug()
// ----------------------------------------------------------------------------
// Version:
//         2005/03/31   1.0 First work release.
//
//=============================================================================

#include <iostream>
#include <time.h>
#include "threadlog.hpp"

void ThreadLog::InsertLog(PRIORITY pri, const char* szInstance, const char* szText)
{
	if(!m_bInThreadMode)
	{
		FileLog::InsertLog(pri, szInstance, szText);
		return;
	}

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
	#ifdef WIN32
	WaitForSingleObject(m_lock, INFINITE);
	#else
	pthread_mutex_lock(&m_lock);		
	#endif
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
	
    m_dataList.push_back(m_strbuf.str());
    #ifdef WIN32
    ReleaseSemaphore(m_sem, 1, NULL);
    ReleaseMutex(m_lock);
    #else
    sem_post(&m_sem);
    pthread_mutex_unlock(&m_lock);
    #endif
};

bool ThreadLog::WriteLog(void)
{
	if(!m_bOpen)
		return false;

    unsigned long recSize;

    #ifdef WIN32
    WaitForSingleObject(m_sem, INFINITE);
    WaitForSingleObject(m_lock, INFINITE);
    #else
    sem_wait(&m_sem);
    pthread_mutex_lock(&m_lock);
    #endif
    recSize = m_dataList.front().length();
    
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
    m_logStream << m_dataList.front() << endl;
//    cout << m_dataList.size() << "::" << m_dataList.front() << endl;
    m_dataList.pop_front();
    m_currentSize += recSize;
    #ifdef WIN32
    ReleaseMutex(m_lock);
    #else
    pthread_mutex_unlock(&m_lock);
    #endif
    
    return true;
};

void ThreadLog::SetThreadMode(bool bMode)
{
	while(GetRecCount())
		WriteLog();
	m_bInThreadMode = bMode;
}
