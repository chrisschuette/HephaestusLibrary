/* 
 * File:   DEFAULT_MIDS.h
 * Author: chris
 *
 * Created on June 13, 2014, 10:09 AM
 */

#ifndef DEFAULT_MIDS_H
#define	DEFAULT_MIDS_H

enum DEFAULT_MIDs {
    MID_UPDATE = 0,
    MID_RENDER,
    MID_ADD_ENTITY,
    MID_REMOVE_ENTITY,
};

#define subscribe(x) (1 << x)


#endif	/* DEFAULT_MIDS_H */

