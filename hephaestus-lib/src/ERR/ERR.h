/* 
 * File:   ERR.h
 * Author: chris
 *
 * Created on June 12, 2013, 8:37 PM
 */

#ifndef ERR_H
#define	ERR_H

#include "Exception.h"

#define THROWS(msg) throw ERR::Exception(msg, __FUNCTION__,__FILE__,__LINE__)
#define THROW(errCode,msg) throw ERR::Exception(errCode,msg, __FUNCTION__,__FILE__,__LINE__)

#endif	/* ERR_H */

