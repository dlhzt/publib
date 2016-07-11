//=============================================================================
// File:          filelock.hpp
// Author:        Zhaojunwei
// CreateTime:    2004/11/22
// Descripiton:   Head file for file locking, this class amis at the sole 
//                instance running.
// ----------------------------------------------------------------------------
// Version:
//         2004/11/22   1.0 First work release.
//         2005/04/20   1.1 Add WritePid() to write pid in ascii format in lock
//                          file.
//
//=============================================================================


#ifndef WIN32

#ifndef FILE_LOCK_HPP
#define FILE_LOCK_HPP

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

enum lockStat{LOCK_SUCCESS, LOCK_FAILED, FILE_ERROR};

class FileLock
{
public:

        FileLock(const char * strFileName):m_strFileName(strFileName), m_bLock(false){
                m_lock.l_type = F_WRLCK;
                m_lock.l_start = 0;
                m_lock.l_whence = SEEK_SET;
                m_lock.l_len = 0;
        };

        FileLock(const std::string& strFileName):m_strFileName(strFileName), m_bLock(false){
                m_lock.l_type = F_WRLCK;
                m_lock.l_start = 0;
                m_lock.l_whence = SEEK_SET;
                m_lock.l_len = 0;
        };

        ~FileLock(){Unlock(); close(m_fd);};

        lockStat Lock(void);
        bool Unlock(void);
        void Write(const void *buf, size_t nbyte);
        void WritePid(void);
        void Seek(off_t offset, int whence);
        void Rewind(void);
        void Truncate(off_t len);

private:
        std::string m_strFileName;
        bool m_bLock;
        int m_fd;
        struct flock m_lock;
};

#endif // WIN32

#endif // FILE_LOCK_HPP
