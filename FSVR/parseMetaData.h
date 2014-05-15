/* 
 * File:   parseMetaData.h
 * Author: chris
 *
 * Created on June 10, 2013, 3:06 PM
 */

#ifndef PARSEMETADATA_H
#define	PARSEMETADATA_H

#include "ResourceMetaData.h"
#include "../BNDL/BID.h"
#include <list>

namespace FSVR {
std::list<ResourceMetaData> parseMetaData(unsigned char* pData, int nBytes, BNDL::tBID id);
}
#endif	/* PARSEMETADATA_H */

