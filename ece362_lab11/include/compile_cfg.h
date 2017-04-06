
// Compile configururation for ARMCC, inline is replaced with __inline since inline is NOT available in C90.
#ifndef COMPILE_CFG_H_
#define COMPILE_CFG_H_

#define ARMCC

#ifdef ARMCC
#define inline __inline
#endif

#endif

