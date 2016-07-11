//=============================================================================
// File:          threadlog.hpp
// Author:        Zhaojunwei
// CreateTime:    2005/03/31
// Descripiton:   Head file for threadlog, which subclass the filelog to provide
//                mutli-thread logging. User should create a thread to loop the
//                WriteLog method, and in other thread call debug()...
// ----------------------------------------------------------------------------
// Version:
//         2005/03/31   1.0 First work release.
//
//=============================================================================

#ifndef THREAD_LOG_HPP
#define THREAD_LOG_HPP

#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>
#include <list>

#include <sys/types.h>
#include <sys/stat.h>

#ifdef WIN32
#include <windows.h>
#include <io.h>
#include <stdio.h>
#else
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#endif

#include "filelog.hpp"

using namespace std;

class ThreadLog : public FileLog
{
public:
	ThreadLog(const char* fileName, unsigned long fileNumber, unsigned long maxFileSize) : 
		FileLog(fileName, fileNumber, maxFileSize)
	{
		#ifdef WIN32
		m_sem = CreateSemaphore(NULL, 0, 2048, NULL);
		m_lock = CreateMutex(NULL, false, NULL);
		#else
        sem_init(&m_sem, 0, 0);
		pthread_mutex_init(&m_lock, NULL);
		#endif
		m_bInThreadMode = false;
	};
	
	virtual ~ThreadLog(){};
	
	void SetThreadMode(bool bMode);
	bool GetThreadMode() const {return m_bInThreadMode;};
	
	bool WriteLog(void);
	
private:
	#ifdef WIN32
    HANDLE                      m_sem;
    HANDLE                      m_lock;
    #else	
	sem_t						m_sem;
	pthread_mutex_t				m_lock;
	#endif
	
	bool						m_bInThreadMode;
	list<string>				m_dataList;
	
	virtual void InsertLog(PRIORITY pri, const char *szInstance, const char* szText);
	unsigned long GetRecCount()const{return m_dataList.size();};
};


#endif
