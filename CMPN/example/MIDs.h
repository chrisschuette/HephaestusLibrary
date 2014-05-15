/* 
 * File:   MIDs.h
 * Author: chris
 *
 * Created on August 31, 2013, 5:47 PM
 */

#ifndef MIDS_H
#define	MIDS_H

enum MIDs {
    MID_UPDATE = 0,
    MID_RENDER
};

#define subscribe(x) (1 << x)

#endif	/* MIDS_H */

