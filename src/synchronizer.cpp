//=============================================================================
// File:          synchronizer.cpp
// Author:        Zhaojunwei
// CreateTime:    2005/04/04
// Descripiton:   Implementation file for synchornization in mutil-thread process.
// ----------------------------------------------------------------------------
// Version:
//         2005/04/04   1.0 First work release.
//
//=============================================================================

#include "synchronizer.hpp"

Synchronizer::Synchronizer()
{
	  #ifdef WIN32
		InitializeCriticalSection(&m_mutex);
	  #else
		pthread_mutex_init(&m_mutex, 0);
	  #endif
}

Synchronizer::~Synchronizer()
{
	  #ifdef WIN32
		DeleteCriticalSection(&m_mutex);
	  #endif
}

void Synchronizer::lock()
{
	  #ifdef WIN32
		EnterCriticalSection(&m_mutex);
	  #else
		pthread_mutex_lock(&m_mutex);
	  #endif
}

void Synchronizer::unlock()
{
	  #ifdef WIN32	
		LeaveCriticalSection(&m_mutex);
	  #else
		pthread_mutex_unlock(&m_mutex);
	  #endif
}
