// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

//
#define P1 ADD(A);
#define REAL P1
//#define ISP1
#define P2 ADD(C);
//
#define mm(a) a
//
#ifdef ISP1
#undef P2
#define P2 P1 ADD(B)
#undef REAL
#define REAL P2
#undef ISP1
#else
#undef P1
#define P1 P2 ;ADD(K)
#undef REAL
#define REAL P1
#define ISP1
#endif
//
//
#ifdef ISP1
#undef P2
#define P2 P1 ADD(B)
#undef REAL
#define REAL P2
#undef ISP1
#else
#undef P1
#define P1 P2 ;ADD(K)
#undef REAL
#define REAL P1
#define ISP1
#endif
//
//
#ifdef ISP1
#undef P2
#define P2 P1 ADD(B)
#undef REAL
#define REAL P2
#undef ISP1
#else
#undef P1
#define P1 P2 ;ADD(K)
#undef REAL
#define REAL P1
#define ISP1
#endif
//
#define SH(m) h(m)
#define h(m) #m
#include <iostream>
using namespace std;
int _tmain(int argc, _TCHAR* argv[])
{
	cout<<SH(REAL)<<endl;
	system("pause");
	return 0;
}

