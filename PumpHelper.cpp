#include "PumpHelper.h"


PumpHelper* PumpHelper::m_pInstance = NULL;
PumpHelper* PumpHelper::Instance()
{
	if (!m_pInstance)
		m_pInstance = new PumpHelper;

	return m_pInstance;
}
