/* 
 * File:   err.h
 * Author: chris
 *
 * Created on March 11, 2014, 6:54 AM
 */

#ifndef SND_OPENAL_ERR_H
#define	SND_OPENAL_ERR_H

#include <AL/al.h>
#include <AL/alc.h>
#include <string>

std::string getALErrorString(int err);
std::string getALCErrorString(int err);

#endif	/* SND_OPENAL_ERR_H */

