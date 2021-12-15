#ifndef __XTPTOXML_H_
#define __XTPTOXML_H_

#include "XTPPackage.h"

void _XTP_PACKAGE_DEBUG(CXTPPackage *pPackage, FILE *fpOutput);

void Flow2XML(char *pszPath, FILE *fpXML);
void XML2Flow(FILE *fpXML, char *pszPath);

#endif
