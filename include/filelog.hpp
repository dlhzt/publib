//=============================================================================
// File:          filelog.hpp
// Author:        Zhaojunwei
// CreateTime:    2005/03/31
// Descripiton:   Head file for logfile, which providing the time,
//                instance and log level records. The log files will be a group 
//                that cycles file of fixed length.
//                With setting log level, user can change the log contents 
//                according to the importance of record.
// ----------------------------------------------------------------------------
// Version:
//         2005/03/31   1.0 First work release.
//
//=============================================================================
#ifndef FILE_LOG_HPP
#define FILE_LOG_HPP

#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <list>

#include <sys/types.h>
#include <sys/stat.h>

#ifdef WIN32
#include <io.h>
#include <stdio.h>
#else
#include <unistd.h>
#endif //Win32

using namespace std;

class FileLog{
public:
	enum PRIORITY{P_NOTSET,P_DEBUG,P_INFO,P_NOTIFY,P_WARNING,P_ERR,P_FATAL};

public:
	FileLog(const char* fileName, unsigned long fileNumber, unsigned long maxFileSize):
		m_fileName(fileName), m_maxFileSize(maxFileSize), m_fileNumber(fileNumber),
		m_fileSeq(0),m_bOpen(false),m_priority(P_NOTSET){};
	
	virtual ~FileLog(){if(m_bOpen) m_logStream.close();};
	
	bool OpenLog(void);

	void debug(const char* szInstance, const char* szText){InsertLog(P_DEBUG, szInstance, szText);};
	void info(const char* szInstance, const char* szText){InsertLog(P_INFO, szInstance, szText);};
	void notify(const char* szInstance, const char* szText){InsertLog(P_NOTIFY, szInstance, szText);};
	void warning(const char* szInstance, const char* szText){InsertLog(P_WARNING, szInstance, szText);};
	void error(const char* szInstance, const char* szText){InsertLog(P_ERR, szInstance, szText);};
	void fatal(const char* szInstance, const char* szText){InsertLog(P_FATAL, szInstance, szText);};
	
	void setPriority(const string& strPri);
	PRIORITY getPriority()const{return m_priority;};
	
protected:
	string						m_fileName;
	const unsigned long			m_maxFileSize;
	const unsigned long			m_fileNumber;
	unsigned int				m_fileSeq;	
	unsigned long				m_currentSize;
		
	ostringstream				m_strbuf;
	ofstream					m_logStream;	
	bool						m_bOpen;
	PRIORITY					m_priority;
	
	void setPriority(PRIORITY pri){m_priority=pri;};
	virtual void InsertLog(PRIORITY pri, const char* szInstance, const char* szText);
};


#endif
