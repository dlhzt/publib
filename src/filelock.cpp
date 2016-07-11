//=============================================================================
// File:          filelock.cpp
// Author:        Zhaojunwei
// CreateTime:    2004/11/22
// Descripiton:   Implementation file for file locking, this class amis at the 
//                sole instance running.
// ----------------------------------------------------------------------------
// Version:
//         2004/11/22   1.0 First work release.
//         2005/04/20   1.1 Add WritePid() to write pid in ascii format in lock
//                          file.
//
//=============================================================================

#ifndef WIN32

#include "filelock.hpp"

lockStat FileLock::Lock(void)
{
	if((m_fd = open(m_strFileName.c_str(), O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR)) < 0)
		return FILE_ERROR;
	if((fcntl(m_fd, F_SETLK, &m_lock)) < 0)
		return LOCK_FAILED;
	m_bLock = true;
	return LOCK_SUCCESS;
}

bool FileLock::Unlock(void)
{
	if(m_bLock == false)
		return true;
	m_lock.l_type = F_UNLCK;
	if((fcntl(m_fd, F_SETLK, &m_lock)) < 0)
		return false;
	else
		return true;
}

void FileLock::Write(const void *buf, size_t nbyte)
{
	write(m_fd, buf, nbyte);
}

void FileLock::WritePid(void)
{
	pid_t pid = getpid();
	char buff[16];
	snprintf(buff, 16, "%u", pid);
	Write(buff, strlen(buff));
}

void FileLock::Seek(off_t offset, int whence)
{
	lseek(m_fd, offset, whence);
}

void FileLock::Rewind(void)
{
	lseek(m_fd, 0, SEEK_SET);
}

void FileLock::Truncate(off_t len)
{
	ftruncate(m_fd, len);
}

#endif // WIN32
