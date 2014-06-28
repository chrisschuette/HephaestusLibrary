/* 
 * File:   FTERRORS.h
 * Author: chris
 *
 * Created on February 13, 2014, 3:26 PM
 */

#ifndef FTERRORS_H
#define	FTERRORS_H

#undef __FTERRORS_H__
#define FT_ERRORDEF( e, v, s )  { e, s },
#define FT_ERROR_START_LIST     {
#define FT_ERROR_END_LIST       { 0, 0 } };

const struct {
    int code;
    const char* message;
} FT_Errors[] =
#include FT_ERRORS_H

#endif	/* FTERRORS_H */

