// ora7API.cpp
//
//////////////////////////////////////////////////////////////////////

#include <SQLAPI.h>
#include <ora7API.h>

#include <assert.h>
#include <string.h>

#include "samisc.h"
#include "errmsg.h"

#include <dlfcn.h>

long g_nORA7DLLVersionLoaded = 0;

// API definitions
ora7API g_ora7API;

ora7API::ora7API()
{
	obindps	= NULL;
	obreak	= NULL;
	ocan	= NULL;
	oclose	= NULL;
	ocof	= NULL;
	ocom	= NULL;
	ocon	= NULL;
	odefinps	= NULL;
	odessp	= NULL;
	odescr	= NULL;
	oerhms	= NULL;
	oermsg	= NULL;
	oexec	= NULL;
	oexfet	= NULL;
	oexn	= NULL;
	ofen	= NULL;
	ofetch	= NULL;
	oflng	= NULL;
	ogetpi	= NULL;
	oopt	= NULL;
	opinit	= NULL;
	olog	= NULL;
	ologof	= NULL;
	oopen	= NULL;
	oparse	= NULL;
	orol	= NULL;
	osetpi	= NULL;
	sqlld2	= NULL;
	sqllda	= NULL;
	onbset	= NULL;
	onbtst	= NULL;
	onbclr	= NULL;
	ognfd	= NULL;
	obndra	= NULL;
	obndrn	= NULL;
	obndrv	= NULL;
	odefin	= NULL;
	oname	= NULL;
	orlon	= NULL;
	olon	= NULL;
	osql3	= NULL;
	odsc	= NULL;
}

ora7ConnectionHandles::ora7ConnectionHandles()
{
	memset(m_hda, 0, sizeof(m_hda));
	memset(&m_lda, 0, sizeof(m_lda));
}

ora7CommandHandles::ora7CommandHandles()
{
	memset(&m_cda, 0, sizeof(m_cda));
}

void AddORA7Support()
{
	assert(false);
}

void ReleaseORA7Support()
{
	assert(false);
}

