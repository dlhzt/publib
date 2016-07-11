//=============================================================================
// File:          crontab.hpp
// Author:        Zhaojunwei
// CreateTime:    2005/04/19
// Descripiton:   Head file for invoking a procdure in crontab format.
//                Notice: this class is a virtual base class, which could not
//                be instanced without subclassing.
// ----------------------------------------------------------------------------
// Version:
//         2005/04/19   1.0 First work release.
//=============================================================================

#ifndef CORNTAB_HPP
#define CORNTAB_HPP

#include <string>
#include <set>
#include <utility>
#include <stdexcept>

using std::string;
using std::set;
using std::pair;
using std::runtime_error;

typedef unsigned int uint;
typedef pair<time_t,time_t> scope_t;

class Crontab
{
public:
	enum Status{RUNNING, IDLE};
public:
	Crontab(const string& strFmt, const string& strTag, const string& strCmd);
	virtual ~Crontab(){};
	
	bool Check(uint uMinute, uint uHour, uint uDay, uint uMonth, uint uWeek) const;
	const string& GetCmd(void) const
	{return m_strCmd;};
	const string& GetTag(void) const
	{return m_strTag;};
	Status GetStatus(void) const
	{return m_status;};
	scope_t GetCost(void) const
	{return m_lifecycle;};
	
	void SetStart(time_t start_t)
	{m_lifecycle.first = start_t;};
	void SetEnd(time_t end_t)
	{m_lifecycle.second = end_t;};
	
	virtual int Run(void) = 0;
	
protected:
	bool Resolv(const string& strLine);
	bool MakeTime(set<uint>& scope, const string& strSetting, uint uMin, uint uMax);
	set<uint>	m_minutes;
	set<uint>	m_hours;
	set<uint>	m_days;
	set<uint>	m_months;
	set<uint>	m_weeks;
	string		m_strTag;
	string		m_strCmd;
	Status		m_status;
	scope_t		m_lifecycle;
};

#endif // CORNTAB_HPP
