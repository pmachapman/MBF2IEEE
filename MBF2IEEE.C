//
// mbf2ieee.c
// 
// uses: _dmsbintoieee, _fmsbintoieee
//       _dieeetomsbin, _fieeetomsbin
//
// This is a set of routines to emulate the old BASIC
// MKS, MKD, CVS, and CVD routines.
//

#include <windows.h> 
#include "c:\vb\cdk\vbapi.h"
#include <math.h> 

#define VB_OVERFLOW 6

float FAR PASCAL _export CVS(HLSTR hlstr)
{
    float src, dst;
    
    src = *(float *)VBDerefHlstr(hlstr);
    
    if( _fmsbintoieee(&src, &dst) )
        VBRuntimeError(VB_OVERFLOW);
    else
        return dst;
}

double FAR PASCAL _export CVD(HLSTR hlstr)
{
    double src, dst;
    
    src = *(double *)VBDerefHlstr(hlstr);
    
    if( _dmsbintoieee(&src, &dst) )
        VBRuntimeError(VB_OVERFLOW);
    else
        return dst;
}

HLSTR FAR PASCAL _export MKS(float *src)
{
    float dst;
    
    if( _fieeetomsbin(src, &dst) )
        VBRuntimeError(VB_OVERFLOW);
    else
        return VBCreateTempHlstr(&dst, 4);
}

HLSTR FAR PASCAL _export MKD(double *src)
{
    double dst;
    
    if( _dieeetomsbin(src, &dst) )
        VBRuntimeError(VB_OVERFLOW);
    else
        return VBCreateTempHlstr(&dst, 8);
}
     
