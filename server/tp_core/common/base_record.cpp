#include <memory> 

#include <sys/types.h> 
#include <sys/stat.h> 

#include "base_record.h"

TppRecBase::TppRecBase()
{
	m_cache.reserve(MAX_SIZE_PER_FILE);
	m_start_time = 0;
	m_last_time = 0;
}

TppRecBase::~TppRecBase()
{
}

void TppRecBase::begin(const wchar_t* base_path, const wchar_t* base_fname, int record_id, const TPP_SESSION_INFO* info)
{
	m_start_time = ex_get_tick_count();

	m_base_fname = base_fname;
	m_base_path = base_path;

	wchar_t _str_rec_id[24] = { 0 };
	ex_wcsformat(_str_rec_id, 24, L"%06d", record_id);
	ex_path_join(m_base_path, false, _str_rec_id, NULL);
	ex_mkdirs(m_base_path);

	_on_begin(info);
}

void TppRecBase::end()
{
	_on_end();

#ifdef EX_DEBUG
	if (m_cache.size() > 0)
	{
		EXLOGE("[ssh] not all record data saved.\n");
	}
#endif
}
