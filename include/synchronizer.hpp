//=============================================================================
// File:          synchronizer.hpp
// Author:        Zhaojunwei
// CreateTime:    2005/04/04
// Descripiton:   Head file for synchornization in mutil-thread process.
// ----------------------------------------------------------------------------
// Version:
//         2005/04/04   1.0 First work release.
//
//=============================================================================

#ifndef SYNCHRONIZER_HPP
#define SYNCHRONIZER_HPP

#ifdef WIN32
#include <windows.h>
#include <process.h>
#else
#include <pthread.h>
#endif   // WIN32


class Synchronizer
{

public:
	Synchronizer();
	~Synchronizer();

	void lock();
	void unlock();

private:
	  #ifdef WIN32
		CRITICAL_SECTION	m_mutex;
	  #else
		pthread_mutex_t		m_mutex;
	  #endif
}; // Synchronizer

#endif //SYNCHRONIZER_HPP
