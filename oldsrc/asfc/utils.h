/*Protected under the GNU General Public License read and see copying.txt for details
 ANNEX SOLUTIONS		© 2002 Annex Solutions, Eoin Coffey, Andy Stone
     
	 * * *                          \ | / Annex Solutions
	* ASFC *---------------------- -- + -- Foundation
	 * * *                          / | \    Classes
	
	File:	utils.h
    By:		Andy Stone
    Desc:	This file includes various macros you may find helpful in your coding. Have fun!
*/

#ifndef ASFC_UTILS_H_
#define ASFC_UTILS_H_

//Include C++ libs
	#include <string>
	#include <iostream>
	#include <fstream>
	using namespace std;
//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
#define DBG(A)
//#define DBG(A) cerr << A

//... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ...
/*MEMVAR_SET: This macro creates a function that sets variable C, of type B, with a function called A
	Example: If you had an int called iValue you could do this:
				MEMVAR_SET(SetValue, int, iValue);
	
	Result:
		void A(B zSetTo) 
		{	C = zSetTo
		}
		
	Result of Example:
		void SetValue(int zSetTo)
		{	iValue = zSetTo;
		}
		
	It save typing!
*/
#define MEMVAR_SET(A, B, C) 	void A(B zSetTo) {C = zSetTo;}
//..................................................................................................................
/*MEMVAR_GET: This macro creates a function that returns variable C, of type B, with a function called A
	Example: If you had an int called iValue you could do this:
				MEMVAR_GET(GetValue, int, iValue);
	
	Result:
		B A() 
		{	return(C)
		}
		
	Result of Example:
		int GetValue()
		{	return(iValue);
		}	
*/
#define MEMVAR_GET(A, B, C) 	B A() {return(C);}
//..................................................................................................................
/*MEMVAR_GETREF: Same as MEMVAR_GET but returns the value by reference.*/
#define MEMVAR_GETREF(A, B, C) 	B& A() {return(C);}
//..................................................................................................................
/*MEMVAR_SETGET: This macro creates a function simply calls MEMVAR_SET(A, C, D); and thne
			   	 MEMVAR_GET(B, C, D);
	
	Result:
		MEMVAR_SET(A, C, D);
		MEMVAR_GET(B, C, D);
*/
#define MEMVAR_SETGET(A, B, C, D)	void A(C zSetTo) {D = zSetTo;} C B() {return(D);}
//..................................................................................................................
/*MEMVAR_LINK: This macro creates a MEMVAR_SET and MEMVAR_GET functions that overload eachother
	
	Result:
		MEMVAR_SET(A, B, C);
		MEMVAR_GET(A, B, C);
*/
#define MEMVAR_LINK(A, B, C)	void A(B zSetTo) {C = zSetTo;} B A() {return(C);}
//..................................................................................................................
/*<xyz>		CRIPTs: Constant Reference Indetifier Passing Tags

	The following macros are equivelent to typing const, a type, then the passed by reference "&" symbol.


	SYNTAX:		CRIPTS are in the following syntax:
				"C_" + Prefix

				Where prefix is a common, standard, variable prefix that the CRIPT identifies as the
				type of variable being passed.

	PROUNCE:	CRIPT is pronounced like the word crypt. A cript macro identifier, such as C_b, is
				pronounced as "C of" + Prefix. Where prefix is the macro's passing type. So C_b is
				prounounced as "C of b."

	NOTICE:		This macro was intended to be used in function prototypes. Don't use it anywhere else!

	WARNING:	Add's a new level of crypticness to programs code. Use with care!


	Pronounciating:	To pronounciate a CRIPT, such as C_b, simply say C, and then the prefix.


	C_b(A)	=	const Uint8  & A			//Byte CRIPT
	C_c(A)	=	const char   & A			//Character CRIPT
	C_d(A)	=	const double & A			//Double CRIPT
	C_f(A)	=	const bool	 & A			//Boolean / Flag / Bit CRIPT
	C_i(A)	=	const int	 & A			//Integer CRIPT
	C_s(A)	=	const string & A			//String CRIPT
	C_str(A)=	const char*  & A			//C String CRIPT
	C_z(A)	=	const void	 & A			//Void (Anytype) CRIPT
*/					
#define C_b(A)														const Uint8 &A
#define C_b2(A,B)													const Uint8 &A, const Uint8 &B
#define C_b3(A,B,C)													const Uint8 &A, const Uint8 &B, const Uint8 &C
#define C_b4(A,B,C,D)												const Uint8 &A, const Uint8 &B, const Uint8 &C, const Uint8 &D
#define C_b5(A,B,C,D,E)												const Uint8 &A, const Uint8 &B, const Uint8 &C, const Uint8 &D, const Uint8 &E
#define C_b6(A,B,C,D,E,F)											const Uint8 &A, const Uint8 &B, const Uint8 &C, const Uint8 &D, const Uint8 &E, const Uint8 &F
#define C_b7(A,B,C,D,E,F,G)											const Uint8 &A, const Uint8 &B, const Uint8 &C, const Uint8 &D, const Uint8 &E, const Uint8 &F, const Uint8 &G
#define C_b8(A,B,C,D,E,F,G,H)										const Uint8 &A, const Uint8 &B, const Uint8 &C, const Uint8 &D, const Uint8 &E, const Uint8 &F, const Uint8 &G, const Uint8 &H
#define C_b9(A,B,C,D,E,F,G,H,I)										const Uint8 &A, const Uint8 &B, const Uint8 &C, const Uint8 &D, const Uint8 &E, const Uint8 &F, const Uint8 &G, const Uint8 &H, const Uint8 &I
#define C_b10(A,B,C,D,E,F,G,H,I,J)									const Uint8 &A, const Uint8 &B, const Uint8 &C, const Uint8 &D, const Uint8 &E, const Uint8 &F, const Uint8 &G, const Uint8 &H, const Uint8 &I, const Uint8 &J
#define C_b11(A,B,C,D,E,F,G,H,I,J,K)								const Uint8 &A, const Uint8 &B, const Uint8 &C, const Uint8 &D, const Uint8 &E, const Uint8 &F, const Uint8 &G, const Uint8 &H, const Uint8 &I, const Uint8 &J, const Uint8 &K
#define C_b12(A,B,C,D,E,F,G,H,I,J,K,L)								const Uint8 &A, const Uint8 &B, const Uint8 &C, const Uint8 &D, const Uint8 &E, const Uint8 &F, const Uint8 &G, const Uint8 &H, const Uint8 &I, const Uint8 &J, const Uint8 &K, const Uint8 &L
#define C_b13(A,B,C,D,E,F,G,H,I,J,K,L,M)							const Uint8 &A, const Uint8 &B, const Uint8 &C, const Uint8 &D, const Uint8 &E, const Uint8 &F, const Uint8 &G, const Uint8 &H, const Uint8 &I, const Uint8 &J, const Uint8 &K, const Uint8 &L, const Uint8 &M
#define C_b14(A,B,C,D,E,F,G,H,I,J,K,L,M,N)							const Uint8 &A, const Uint8 &B, const Uint8 &C, const Uint8 &D, const Uint8 &E, const Uint8 &F, const Uint8 &G, const Uint8 &H, const Uint8 &I, const Uint8 &J, const Uint8 &K, const Uint8 &L, const Uint8 &M, const Uint8 &N
#define C_b15(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O)						const Uint8 &A, const Uint8 &B, const Uint8 &C, const Uint8 &D, const Uint8 &E, const Uint8 &F, const Uint8 &G, const Uint8 &H, const Uint8 &I, const Uint8 &J, const Uint8 &K, const Uint8 &L, const Uint8 &M, const Uint8 &N, const Uint8 &O
#define C_b16(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P)						const Uint8 &A, const Uint8 &B, const Uint8 &C, const Uint8 &D, const Uint8 &E, const Uint8 &F, const Uint8 &G, const Uint8 &H, const Uint8 &I, const Uint8 &J, const Uint8 &K, const Uint8 &L, const Uint8 &M, const Uint8 &N, const Uint8 &O, const Uint8 &P
#define C_b17(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q)					const Uint8 &A, const Uint8 &B, const Uint8 &C, const Uint8 &D, const Uint8 &E, const Uint8 &F, const Uint8 &G, const Uint8 &H, const Uint8 &I, const Uint8 &J, const Uint8 &K, const Uint8 &L, const Uint8 &M, const Uint8 &N, const Uint8 &O, const Uint8 &P, const Uint8 &Q
#define C_b18(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R)					const Uint8 &A, const Uint8 &B, const Uint8 &C, const Uint8 &D, const Uint8 &E, const Uint8 &F, const Uint8 &G, const Uint8 &H, const Uint8 &I, const Uint8 &J, const Uint8 &K, const Uint8 &L, const Uint8 &M, const Uint8 &N, const Uint8 &O, const Uint8 &P, const Uint8 &Q, const Uint8 &R
#define C_b19(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S)				const Uint8 &A, const Uint8 &B, const Uint8 &C, const Uint8 &D, const Uint8 &E, const Uint8 &F, const Uint8 &G, const Uint8 &H, const Uint8 &I, const Uint8 &J, const Uint8 &K, const Uint8 &L, const Uint8 &M, const Uint8 &N, const Uint8 &O, const Uint8 &P, const Uint8 &Q, const Uint8 &R, const Uint8 &S
#define C_b20(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T)				const Uint8 &A, const Uint8 &B, const Uint8 &C, const Uint8 &D, const Uint8 &E, const Uint8 &F, const Uint8 &G, const Uint8 &H, const Uint8 &I, const Uint8 &J, const Uint8 &K, const Uint8 &L, const Uint8 &M, const Uint8 &N, const Uint8 &O, const Uint8 &P, const Uint8 &Q, const Uint8 &R, const Uint8 &S, const Uint8 &T
#define C_b21(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U)			const Uint8 &A, const Uint8 &B, const Uint8 &C, const Uint8 &D, const Uint8 &E, const Uint8 &F, const Uint8 &G, const Uint8 &H, const Uint8 &I, const Uint8 &J, const Uint8 &K, const Uint8 &L, const Uint8 &M, const Uint8 &N, const Uint8 &O, const Uint8 &P, const Uint8 &Q, const Uint8 &R, const Uint8 &S, const Uint8 &T, const Uint8 &U
#define C_b22(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V)			const Uint8 &A, const Uint8 &B, const Uint8 &C, const Uint8 &D, const Uint8 &E, const Uint8 &F, const Uint8 &G, const Uint8 &H, const Uint8 &I, const Uint8 &J, const Uint8 &K, const Uint8 &L, const Uint8 &M, const Uint8 &N, const Uint8 &O, const Uint8 &P, const Uint8 &Q, const Uint8 &R, const Uint8 &S, const Uint8 &T, const Uint8 &U, const Uint8 &V
#define C_b23(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W)		const Uint8 &A, const Uint8 &B, const Uint8 &C, const Uint8 &D, const Uint8 &E, const Uint8 &F, const Uint8 &G, const Uint8 &H, const Uint8 &I, const Uint8 &J, const Uint8 &K, const Uint8 &L, const Uint8 &M, const Uint8 &N, const Uint8 &O, const Uint8 &P, const Uint8 &Q, const Uint8 &R, const Uint8 &S, const Uint8 &T, const Uint8 &U, const Uint8 &V, const Uint8 &W
#define C_b24(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X)		const Uint8 &A, const Uint8 &B, const Uint8 &C, const Uint8 &D, const Uint8 &E, const Uint8 &F, const Uint8 &G, const Uint8 &H, const Uint8 &I, const Uint8 &J, const Uint8 &K, const Uint8 &L, const Uint8 &M, const Uint8 &N, const Uint8 &O, const Uint8 &P, const Uint8 &Q, const Uint8 &R, const Uint8 &S, const Uint8 &T, const Uint8 &U, const Uint8 &V, const Uint8 &W, const Uint8 &X
#define C_b25(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y)	const Uint8 &A, const Uint8 &B, const Uint8 &C, const Uint8 &D, const Uint8 &E, const Uint8 &F, const Uint8 &G, const Uint8 &H, const Uint8 &I, const Uint8 &J, const Uint8 &K, const Uint8 &L, const Uint8 &M, const Uint8 &N, const Uint8 &O, const Uint8 &P, const Uint8 &Q, const Uint8 &R, const Uint8 &S, const Uint8 &T, const Uint8 &U, const Uint8 &V, const Uint8 &W, const Uint8 &X, const Uint8 &Y
#define C_b26(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z)	const Uint8 &A, const Uint8 &B, const Uint8 &C, const Uint8 &D, const Uint8 &E, const Uint8 &F, const Uint8 &G, const Uint8 &H, const Uint8 &I, const Uint8 &J, const Uint8 &K, const Uint8 &L, const Uint8 &M, const Uint8 &N, const Uint8 &O, const Uint8 &P, const Uint8 &Q, const Uint8 &R, const Uint8 &S, const Uint8 &T, const Uint8 &U, const Uint8 &V, const Uint8 &W, const Uint8 &X, const Uint8 &Y, const Uint8 &Z

#define C_i(A)														const int &A
#define C_i2(A,B)													const int &A, const int &B
#define C_i3(A,B,C)													const int &A, const int &B, const int &C
#define C_i4(A,B,C,D)												const int &A, const int &B, const int &C, const int &D
#define C_i5(A,B,C,D,E)												const int &A, const int &B, const int &C, const int &D, const int &E
#define C_i6(A,B,C,D,E,F)											const int &A, const int &B, const int &C, const int &D, const int &E, const int &F
#define C_i7(A,B,C,D,E,F,G)											const int &A, const int &B, const int &C, const int &D, const int &E, const int &F, const int &G
#define C_i8(A,B,C,D,E,F,G,H)										const int &A, const int &B, const int &C, const int &D, const int &E, const int &F, const int &G, const int &H
#define C_i9(A,B,C,D,E,F,G,H,I)										const int &A, const int &B, const int &C, const int &D, const int &E, const int &F, const int &G, const int &H, const int &I
#define C_i10(A,B,C,D,E,F,G,H,I,J)									const int &A, const int &B, const int &C, const int &D, const int &E, const int &F, const int &G, const int &H, const int &I, const int &J
#define C_i11(A,B,C,D,E,F,G,H,I,J,K)								const int &A, const int &B, const int &C, const int &D, const int &E, const int &F, const int &G, const int &H, const int &I, const int &J, const int &K
#define C_i12(A,B,C,D,E,F,G,H,I,J,K,L)								const int &A, const int &B, const int &C, const int &D, const int &E, const int &F, const int &G, const int &H, const int &I, const int &J, const int &K, const int &L
#define C_i13(A,B,C,D,E,F,G,H,I,J,K,L,M)							const int &A, const int &B, const int &C, const int &D, const int &E, const int &F, const int &G, const int &H, const int &I, const int &J, const int &K, const int &L, const int &M
#define C_i14(A,B,C,D,E,F,G,H,I,J,K,L,M,N)							const int &A, const int &B, const int &C, const int &D, const int &E, const int &F, const int &G, const int &H, const int &I, const int &J, const int &K, const int &L, const int &M, const int &N
#define C_i15(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O)						const int &A, const int &B, const int &C, const int &D, const int &E, const int &F, const int &G, const int &H, const int &I, const int &J, const int &K, const int &L, const int &M, const int &N, const int &O
#define C_i16(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P)						const int &A, const int &B, const int &C, const int &D, const int &E, const int &F, const int &G, const int &H, const int &I, const int &J, const int &K, const int &L, const int &M, const int &N, const int &O, const int &P
#define C_i17(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q)					const int &A, const int &B, const int &C, const int &D, const int &E, const int &F, const int &G, const int &H, const int &I, const int &J, const int &K, const int &L, const int &M, const int &N, const int &O, const int &P, const int &Q
#define C_i18(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R)					const int &A, const int &B, const int &C, const int &D, const int &E, const int &F, const int &G, const int &H, const int &I, const int &J, const int &K, const int &L, const int &M, const int &N, const int &O, const int &P, const int &Q, const int &R
#define C_i19(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S)				const int &A, const int &B, const int &C, const int &D, const int &E, const int &F, const int &G, const int &H, const int &I, const int &J, const int &K, const int &L, const int &M, const int &N, const int &O, const int &P, const int &Q, const int &R, const int &S
#define C_i20(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T)				const int &A, const int &B, const int &C, const int &D, const int &E, const int &F, const int &G, const int &H, const int &I, const int &J, const int &K, const int &L, const int &M, const int &N, const int &O, const int &P, const int &Q, const int &R, const int &S, const int &T
#define C_i21(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U)			const int &A, const int &B, const int &C, const int &D, const int &E, const int &F, const int &G, const int &H, const int &I, const int &J, const int &K, const int &L, const int &M, const int &N, const int &O, const int &P, const int &Q, const int &R, const int &S, const int &T, const int &U
#define C_i22(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V)			const int &A, const int &B, const int &C, const int &D, const int &E, const int &F, const int &G, const int &H, const int &I, const int &J, const int &K, const int &L, const int &M, const int &N, const int &O, const int &P, const int &Q, const int &R, const int &S, const int &T, const int &U, const int &V
#define C_i23(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W)		const int &A, const int &B, const int &C, const int &D, const int &E, const int &F, const int &G, const int &H, const int &I, const int &J, const int &K, const int &L, const int &M, const int &N, const int &O, const int &P, const int &Q, const int &R, const int &S, const int &T, const int &U, const int &V, const int &W
#define C_i24(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X)		const int &A, const int &B, const int &C, const int &D, const int &E, const int &F, const int &G, const int &H, const int &I, const int &J, const int &K, const int &L, const int &M, const int &N, const int &O, const int &P, const int &Q, const int &R, const int &S, const int &T, const int &U, const int &V, const int &W, const int &X
#define C_i25(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y)	const int &A, const int &B, const int &C, const int &D, const int &E, const int &F, const int &G, const int &H, const int &I, const int &J, const int &K, const int &L, const int &M, const int &N, const int &O, const int &P, const int &Q, const int &R, const int &S, const int &T, const int &U, const int &V, const int &W, const int &X, const int &Y
#define C_i26(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z)	const int &A, const int &B, const int &C, const int &D, const int &E, const int &F, const int &G, const int &H, const int &I, const int &J, const int &K, const int &L, const int &M, const int &N, const int &O, const int &P, const int &Q, const int &R, const int &S, const int &T, const int &U, const int &V, const int &W, const int &X, const int &Y, const int &Z

#define C_s(A)														const string &A
#define C_s2(A,B)													const string &A, const string &B
#define C_s3(A,B,C)													const string &A, const string &B, const string &C
#define C_s4(A,B,C,D)												const string &A, const string &B, const string &C, const string &D
#define C_s5(A,B,C,D,E)												const string &A, const string &B, const string &C, const string &D, const string &E
#define C_s6(A,B,C,D,E,F)											const string &A, const string &B, const string &C, const string &D, const string &E, const string &F
#define C_s7(A,B,C,D,E,F,G)											const string &A, const string &B, const string &C, const string &D, const string &E, const string &F, const string &G
#define C_s8(A,B,C,D,E,F,G,H)										const string &A, const string &B, const string &C, const string &D, const string &E, const string &F, const string &G, const string &H
#define C_s9(A,B,C,D,E,F,G,H,I)										const string &A, const string &B, const string &C, const string &D, const string &E, const string &F, const string &G, const string &H, const string &I
#define C_s10(A,B,C,D,E,F,G,H,I,J)									const string &A, const string &B, const string &C, const string &D, const string &E, const string &F, const string &G, const string &H, const string &I, const string &J
#define C_s11(A,B,C,D,E,F,G,H,I,J,K)								const string &A, const string &B, const string &C, const string &D, const string &E, const string &F, const string &G, const string &H, const string &I, const string &J, const string &K
#define C_s12(A,B,C,D,E,F,G,H,I,J,K,L)								const string &A, const string &B, const string &C, const string &D, const string &E, const string &F, const string &G, const string &H, const string &I, const string &J, const string &K, const string &L
#define C_s13(A,B,C,D,E,F,G,H,I,J,K,L,M)							const string &A, const string &B, const string &C, const string &D, const string &E, const string &F, const string &G, const string &H, const string &I, const string &J, const string &K, const string &L, const string &M
#define C_s14(A,B,C,D,E,F,G,H,I,J,K,L,M,N)							const string &A, const string &B, const string &C, const string &D, const string &E, const string &F, const string &G, const string &H, const string &I, const string &J, const string &K, const string &L, const string &M, const string &N
#define C_s15(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O)						const string &A, const string &B, const string &C, const string &D, const string &E, const string &F, const string &G, const string &H, const string &I, const string &J, const string &K, const string &L, const string &M, const string &N, const string &O
#define C_s16(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P)						const string &A, const string &B, const string &C, const string &D, const string &E, const string &F, const string &G, const string &H, const string &I, const string &J, const string &K, const string &L, const string &M, const string &N, const string &O, const string &P
#define C_s17(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q)					const string &A, const string &B, const string &C, const string &D, const string &E, const string &F, const string &G, const string &H, const string &I, const string &J, const string &K, const string &L, const string &M, const string &N, const string &O, const string &P, const string &Q
#define C_s18(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R)					const string &A, const string &B, const string &C, const string &D, const string &E, const string &F, const string &G, const string &H, const string &I, const string &J, const string &K, const string &L, const string &M, const string &N, const string &O, const string &P, const string &Q, const string &R
#define C_s19(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S)				const string &A, const string &B, const string &C, const string &D, const string &E, const string &F, const string &G, const string &H, const string &I, const string &J, const string &K, const string &L, const string &M, const string &N, const string &O, const string &P, const string &Q, const string &R, const string &S
#define C_s20(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T)				const string &A, const string &B, const string &C, const string &D, const string &E, const string &F, const string &G, const string &H, const string &I, const string &J, const string &K, const string &L, const string &M, const string &N, const string &O, const string &P, const string &Q, const string &R, const string &S, const string &T
#define C_s21(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U)			const string &A, const string &B, const string &C, const string &D, const string &E, const string &F, const string &G, const string &H, const string &I, const string &J, const string &K, const string &L, const string &M, const string &N, const string &O, const string &P, const string &Q, const string &R, const string &S, const string &T, const string &U
#define C_s22(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V)			const string &A, const string &B, const string &C, const string &D, const string &E, const string &F, const string &G, const string &H, const string &I, const string &J, const string &K, const string &L, const string &M, const string &N, const string &O, const string &P, const string &Q, const string &R, const string &S, const string &T, const string &U, const string &V
#define C_s23(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W)		const string &A, const string &B, const string &C, const string &D, const string &E, const string &F, const string &G, const string &H, const string &I, const string &J, const string &K, const string &L, const string &M, const string &N, const string &O, const string &P, const string &Q, const string &R, const string &S, const string &T, const string &U, const string &V, const string &W
#define C_s24(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X)		const string &A, const string &B, const string &C, const string &D, const string &E, const string &F, const string &G, const string &H, const string &I, const string &J, const string &K, const string &L, const string &M, const string &N, const string &O, const string &P, const string &Q, const string &R, const string &S, const string &T, const string &U, const string &V, const string &W, const string &X
#define C_s25(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y)	const string &A, const string &B, const string &C, const string &D, const string &E, const string &F, const string &G, const string &H, const string &I, const string &J, const string &K, const string &L, const string &M, const string &N, const string &O, const string &P, const string &Q, const string &R, const string &S, const string &T, const string &U, const string &V, const string &W, const string &X, const string &Y
#define C_s26(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z)	const string &A, const string &B, const string &C, const string &D, const string &E, const string &F, const string &G, const string &H, const string &I, const string &J, const string &K, const string &L, const string &M, const string &N, const string &O, const string &P, const string &Q, const string &R, const string &S, const string &T, const string &U, const string &V, const string &W, const string &X, const string &Y, const string &Z

#define C_c(A)														const char &A
#define C_c2(A,B)													const char &A, const char &B
#define C_c3(A,B,C)													const char &A, const char &B, const char &C
#define C_c4(A,B,C,D)												const char &A, const char &B, const char &C, const char &D
#define C_c5(A,B,C,D,E)												const char &A, const char &B, const char &C, const char &D, const char &E
#define C_c6(A,B,C,D,E,F)											const char &A, const char &B, const char &C, const char &D, const char &E, const char &F
#define C_c7(A,B,C,D,E,F,G)											const char &A, const char &B, const char &C, const char &D, const char &E, const char &F, const char &G
#define C_c8(A,B,C,D,E,F,G,H)										const char &A, const char &B, const char &C, const char &D, const char &E, const char &F, const char &G, const char &H
#define C_c9(A,B,C,D,E,F,G,H,I)										const char &A, const char &B, const char &C, const char &D, const char &E, const char &F, const char &G, const char &H, const char &I
#define C_c10(A,B,C,D,E,F,G,H,I,J)									const char &A, const char &B, const char &C, const char &D, const char &E, const char &F, const char &G, const char &H, const char &I, const char &J
#define C_c11(A,B,C,D,E,F,G,H,I,J,K)								const char &A, const char &B, const char &C, const char &D, const char &E, const char &F, const char &G, const char &H, const char &I, const char &J, const char &K
#define C_c12(A,B,C,D,E,F,G,H,I,J,K,L)								const char &A, const char &B, const char &C, const char &D, const char &E, const char &F, const char &G, const char &H, const char &I, const char &J, const char &K, const char &L
#define C_c13(A,B,C,D,E,F,G,H,I,J,K,L,M)							const char &A, const char &B, const char &C, const char &D, const char &E, const char &F, const char &G, const char &H, const char &I, const char &J, const char &K, const char &L, const char &M
#define C_c14(A,B,C,D,E,F,G,H,I,J,K,L,M,N)							const char &A, const char &B, const char &C, const char &D, const char &E, const char &F, const char &G, const char &H, const char &I, const char &J, const char &K, const char &L, const char &M, const char &N
#define C_c15(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O)						const char &A, const char &B, const char &C, const char &D, const char &E, const char &F, const char &G, const char &H, const char &I, const char &J, const char &K, const char &L, const char &M, const char &N, const char &O
#define C_c16(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P)						const char &A, const char &B, const char &C, const char &D, const char &E, const char &F, const char &G, const char &H, const char &I, const char &J, const char &K, const char &L, const char &M, const char &N, const char &O, const char &P
#define C_c17(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q)					const char &A, const char &B, const char &C, const char &D, const char &E, const char &F, const char &G, const char &H, const char &I, const char &J, const char &K, const char &L, const char &M, const char &N, const char &O, const char &P, const char &Q
#define C_c18(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R)					const char &A, const char &B, const char &C, const char &D, const char &E, const char &F, const char &G, const char &H, const char &I, const char &J, const char &K, const char &L, const char &M, const char &N, const char &O, const char &P, const char &Q, const char &R
#define C_c19(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S)				const char &A, const char &B, const char &C, const char &D, const char &E, const char &F, const char &G, const char &H, const char &I, const char &J, const char &K, const char &L, const char &M, const char &N, const char &O, const char &P, const char &Q, const char &R, const char &S
#define C_c20(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T)				const char &A, const char &B, const char &C, const char &D, const char &E, const char &F, const char &G, const char &H, const char &I, const char &J, const char &K, const char &L, const char &M, const char &N, const char &O, const char &P, const char &Q, const char &R, const char &S, const char &T
#define C_c21(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U)			const char &A, const char &B, const char &C, const char &D, const char &E, const char &F, const char &G, const char &H, const char &I, const char &J, const char &K, const char &L, const char &M, const char &N, const char &O, const char &P, const char &Q, const char &R, const char &S, const char &T, const char &U
#define C_c22(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V)			const char &A, const char &B, const char &C, const char &D, const char &E, const char &F, const char &G, const char &H, const char &I, const char &J, const char &K, const char &L, const char &M, const char &N, const char &O, const char &P, const char &Q, const char &R, const char &S, const char &T, const char &U, const char &V
#define C_c23(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W)		const char &A, const char &B, const char &C, const char &D, const char &E, const char &F, const char &G, const char &H, const char &I, const char &J, const char &K, const char &L, const char &M, const char &N, const char &O, const char &P, const char &Q, const char &R, const char &S, const char &T, const char &U, const char &V, const char &W
#define C_c24(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X)		const char &A, const char &B, const char &C, const char &D, const char &E, const char &F, const char &G, const char &H, const char &I, const char &J, const char &K, const char &L, const char &M, const char &N, const char &O, const char &P, const char &Q, const char &R, const char &S, const char &T, const char &U, const char &V, const char &W, const char &X
#define C_c25(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y)	const char &A, const char &B, const char &C, const char &D, const char &E, const char &F, const char &G, const char &H, const char &I, const char &J, const char &K, const char &L, const char &M, const char &N, const char &O, const char &P, const char &Q, const char &R, const char &S, const char &T, const char &U, const char &V, const char &W, const char &X, const char &Y
#define C_c26(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z)	const char &A, const char &B, const char &C, const char &D, const char &E, const char &F, const char &G, const char &H, const char &I, const char &J, const char &K, const char &L, const char &M, const char &N, const char &O, const char &P, const char &Q, const char &R, const char &S, const char &T, const char &U, const char &V, const char &W, const char &X, const char &Y, const char &Z

#define C_d(A)														const double &A
#define C_d2(A,B)													const double &A, const double &B
#define C_d3(A,B,C)													const double &A, const double &B, const double &C
#define C_d4(A,B,C,D)												const double &A, const double &B, const double &C, const double &D
#define C_d5(A,B,C,D,E)												const double &A, const double &B, const double &C, const double &D, const double &E
#define C_d6(A,B,C,D,E,F)											const double &A, const double &B, const double &C, const double &D, const double &E, const double &F
#define C_d7(A,B,C,D,E,F,G)											const double &A, const double &B, const double &C, const double &D, const double &E, const double &F, const double &G
#define C_d8(A,B,C,D,E,F,G,H)										const double &A, const double &B, const double &C, const double &D, const double &E, const double &F, const double &G, const double &H
#define C_d9(A,B,C,D,E,F,G,H,I)										const double &A, const double &B, const double &C, const double &D, const double &E, const double &F, const double &G, const double &H, const double &I
#define C_d10(A,B,C,D,E,F,G,H,I,J)									const double &A, const double &B, const double &C, const double &D, const double &E, const double &F, const double &G, const double &H, const double &I, const double &J
#define C_d11(A,B,C,D,E,F,G,H,I,J,K)								const double &A, const double &B, const double &C, const double &D, const double &E, const double &F, const double &G, const double &H, const double &I, const double &J, const double &K
#define C_d12(A,B,C,D,E,F,G,H,I,J,K,L)								const double &A, const double &B, const double &C, const double &D, const double &E, const double &F, const double &G, const double &H, const double &I, const double &J, const double &K, const double &L
#define C_d13(A,B,C,D,E,F,G,H,I,J,K,L,M)							const double &A, const double &B, const double &C, const double &D, const double &E, const double &F, const double &G, const double &H, const double &I, const double &J, const double &K, const double &L, const double &M
#define C_d14(A,B,C,D,E,F,G,H,I,J,K,L,M,N)							const double &A, const double &B, const double &C, const double &D, const double &E, const double &F, const double &G, const double &H, const double &I, const double &J, const double &K, const double &L, const double &M, const double &N
#define C_d15(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O)						const double &A, const double &B, const double &C, const double &D, const double &E, const double &F, const double &G, const double &H, const double &I, const double &J, const double &K, const double &L, const double &M, const double &N, const double &O
#define C_d16(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P)						const double &A, const double &B, const double &C, const double &D, const double &E, const double &F, const double &G, const double &H, const double &I, const double &J, const double &K, const double &L, const double &M, const double &N, const double &O, const double &P
#define C_d17(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q)					const double &A, const double &B, const double &C, const double &D, const double &E, const double &F, const double &G, const double &H, const double &I, const double &J, const double &K, const double &L, const double &M, const double &N, const double &O, const double &P, const double &Q
#define C_d18(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R)					const double &A, const double &B, const double &C, const double &D, const double &E, const double &F, const double &G, const double &H, const double &I, const double &J, const double &K, const double &L, const double &M, const double &N, const double &O, const double &P, const double &Q, const double &R
#define C_d19(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S)				const double &A, const double &B, const double &C, const double &D, const double &E, const double &F, const double &G, const double &H, const double &I, const double &J, const double &K, const double &L, const double &M, const double &N, const double &O, const double &P, const double &Q, const double &R, const double &S
#define C_d20(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T)				const double &A, const double &B, const double &C, const double &D, const double &E, const double &F, const double &G, const double &H, const double &I, const double &J, const double &K, const double &L, const double &M, const double &N, const double &O, const double &P, const double &Q, const double &R, const double &S, const double &T
#define C_d21(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U)			const double &A, const double &B, const double &C, const double &D, const double &E, const double &F, const double &G, const double &H, const double &I, const double &J, const double &K, const double &L, const double &M, const double &N, const double &O, const double &P, const double &Q, const double &R, const double &S, const double &T, const double &U
#define C_d22(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V)			const double &A, const double &B, const double &C, const double &D, const double &E, const double &F, const double &G, const double &H, const double &I, const double &J, const double &K, const double &L, const double &M, const double &N, const double &O, const double &P, const double &Q, const double &R, const double &S, const double &T, const double &U, const double &V
#define C_d23(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W)		const double &A, const double &B, const double &C, const double &D, const double &E, const double &F, const double &G, const double &H, const double &I, const double &J, const double &K, const double &L, const double &M, const double &N, const double &O, const double &P, const double &Q, const double &R, const double &S, const double &T, const double &U, const double &V, const double &W
#define C_d24(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X)		const double &A, const double &B, const double &C, const double &D, const double &E, const double &F, const double &G, const double &H, const double &I, const double &J, const double &K, const double &L, const double &M, const double &N, const double &O, const double &P, const double &Q, const double &R, const double &S, const double &T, const double &U, const double &V, const double &W, const double &X
#define C_d25(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y)	const double &A, const double &B, const double &C, const double &D, const double &E, const double &F, const double &G, const double &H, const double &I, const double &J, const double &K, const double &L, const double &M, const double &N, const double &O, const double &P, const double &Q, const double &R, const double &S, const double &T, const double &U, const double &V, const double &W, const double &X, const double &Y
#define C_d26(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z)	const double &A, const double &B, const double &C, const double &D, const double &E, const double &F, const double &G, const double &H, const double &I, const double &J, const double &K, const double &L, const double &M, const double &N, const double &O, const double &P, const double &Q, const double &R, const double &S, const double &T, const double &U, const double &V, const double &W, const double &X, const double &Y, const double &Z

#define C_f(A)														const bool &A
#define C_f2(A,B)													const bool &A, const bool &B
#define C_f3(A,B,C)													const bool &A, const bool &B, const bool &C
#define C_f4(A,B,C,D)												const bool &A, const bool &B, const bool &C, const bool &D
#define C_f5(A,B,C,D,E)												const bool &A, const bool &B, const bool &C, const bool &D, const bool &E
#define C_f6(A,B,C,D,E,F)											const bool &A, const bool &B, const bool &C, const bool &D, const bool &E, const bool &F
#define C_f7(A,B,C,D,E,F,G)											const bool &A, const bool &B, const bool &C, const bool &D, const bool &E, const bool &F, const bool &G
#define C_f8(A,B,C,D,E,F,G,H)										const bool &A, const bool &B, const bool &C, const bool &D, const bool &E, const bool &F, const bool &G, const bool &H
#define C_f9(A,B,C,D,E,F,G,H,I)										const bool &A, const bool &B, const bool &C, const bool &D, const bool &E, const bool &F, const bool &G, const bool &H, const bool &I
#define C_f10(A,B,C,D,E,F,G,H,I,J)									const bool &A, const bool &B, const bool &C, const bool &D, const bool &E, const bool &F, const bool &G, const bool &H, const bool &I, const bool &J
#define C_f11(A,B,C,D,E,F,G,H,I,J,K)								const bool &A, const bool &B, const bool &C, const bool &D, const bool &E, const bool &F, const bool &G, const bool &H, const bool &I, const bool &J, const bool &K
#define C_f12(A,B,C,D,E,F,G,H,I,J,K,L)								const bool &A, const bool &B, const bool &C, const bool &D, const bool &E, const bool &F, const bool &G, const bool &H, const bool &I, const bool &J, const bool &K, const bool &L
#define C_f13(A,B,C,D,E,F,G,H,I,J,K,L,M)							const bool &A, const bool &B, const bool &C, const bool &D, const bool &E, const bool &F, const bool &G, const bool &H, const bool &I, const bool &J, const bool &K, const bool &L, const bool &M
#define C_f14(A,B,C,D,E,F,G,H,I,J,K,L,M,N)							const bool &A, const bool &B, const bool &C, const bool &D, const bool &E, const bool &F, const bool &G, const bool &H, const bool &I, const bool &J, const bool &K, const bool &L, const bool &M, const bool &N
#define C_f15(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O)						const bool &A, const bool &B, const bool &C, const bool &D, const bool &E, const bool &F, const bool &G, const bool &H, const bool &I, const bool &J, const bool &K, const bool &L, const bool &M, const bool &N, const bool &O
#define C_f16(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P)						const bool &A, const bool &B, const bool &C, const bool &D, const bool &E, const bool &F, const bool &G, const bool &H, const bool &I, const bool &J, const bool &K, const bool &L, const bool &M, const bool &N, const bool &O, const bool &P
#define C_f17(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q)					const bool &A, const bool &B, const bool &C, const bool &D, const bool &E, const bool &F, const bool &G, const bool &H, const bool &I, const bool &J, const bool &K, const bool &L, const bool &M, const bool &N, const bool &O, const bool &P, const bool &Q
#define C_f18(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R)					const bool &A, const bool &B, const bool &C, const bool &D, const bool &E, const bool &F, const bool &G, const bool &H, const bool &I, const bool &J, const bool &K, const bool &L, const bool &M, const bool &N, const bool &O, const bool &P, const bool &Q, const bool &R
#define C_f19(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S)				const bool &A, const bool &B, const bool &C, const bool &D, const bool &E, const bool &F, const bool &G, const bool &H, const bool &I, const bool &J, const bool &K, const bool &L, const bool &M, const bool &N, const bool &O, const bool &P, const bool &Q, const bool &R, const bool &S
#define C_f20(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T)				const bool &A, const bool &B, const bool &C, const bool &D, const bool &E, const bool &F, const bool &G, const bool &H, const bool &I, const bool &J, const bool &K, const bool &L, const bool &M, const bool &N, const bool &O, const bool &P, const bool &Q, const bool &R, const bool &S, const bool &T
#define C_f21(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U)			const bool &A, const bool &B, const bool &C, const bool &D, const bool &E, const bool &F, const bool &G, const bool &H, const bool &I, const bool &J, const bool &K, const bool &L, const bool &M, const bool &N, const bool &O, const bool &P, const bool &Q, const bool &R, const bool &S, const bool &T, const bool &U
#define C_f22(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V)			const bool &A, const bool &B, const bool &C, const bool &D, const bool &E, const bool &F, const bool &G, const bool &H, const bool &I, const bool &J, const bool &K, const bool &L, const bool &M, const bool &N, const bool &O, const bool &P, const bool &Q, const bool &R, const bool &S, const bool &T, const bool &U, const bool &V
#define C_f23(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W)		const bool &A, const bool &B, const bool &C, const bool &D, const bool &E, const bool &F, const bool &G, const bool &H, const bool &I, const bool &J, const bool &K, const bool &L, const bool &M, const bool &N, const bool &O, const bool &P, const bool &Q, const bool &R, const bool &S, const bool &T, const bool &U, const bool &V, const bool &W
#define C_f24(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X)		const bool &A, const bool &B, const bool &C, const bool &D, const bool &E, const bool &F, const bool &G, const bool &H, const bool &I, const bool &J, const bool &K, const bool &L, const bool &M, const bool &N, const bool &O, const bool &P, const bool &Q, const bool &R, const bool &S, const bool &T, const bool &U, const bool &V, const bool &W, const bool &X
#define C_f25(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y)	const bool &A, const bool &B, const bool &C, const bool &D, const bool &E, const bool &F, const bool &G, const bool &H, const bool &I, const bool &J, const bool &K, const bool &L, const bool &M, const bool &N, const bool &O, const bool &P, const bool &Q, const bool &R, const bool &S, const bool &T, const bool &U, const bool &V, const bool &W, const bool &X, const bool &Y
#define C_f26(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z)	const bool &A, const bool &B, const bool &C, const bool &D, const bool &E, const bool &F, const bool &G, const bool &H, const bool &I, const bool &J, const bool &K, const bool &L, const bool &M, const bool &N, const bool &O, const bool &P, const bool &Q, const bool &R, const bool &S, const bool &T, const bool &U, const bool &V, const bool &W, const bool &X, const bool &Y, const bool &Z

#define C_str(A)													const char* &A
#define C_str2(A,B)													const char* &A, const char* &B
#define C_str3(A,B,C)												const char* &A, const char* &B, const char* &C
#define C_str4(A,B,C,D)												const char* &A, const char* &B, const char* &C, const char* &D
#define C_str5(A,B,C,D,E)											const char* &A, const char* &B, const char* &C, const char* &D, const char* &E
#define C_str6(A,B,C,D,E,F)											const char* &A, const char* &B, const char* &C, const char* &D, const char* &E, const char* &F
#define C_str7(A,B,C,D,E,F,G)										const char* &A, const char* &B, const char* &C, const char* &D, const char* &E, const char* &F, const char* &G
#define C_str8(A,B,C,D,E,F,G,H)										const char* &A, const char* &B, const char* &C, const char* &D, const char* &E, const char* &F, const char* &G, const char* &H
#define C_str9(A,B,C,D,E,F,G,H,I)									const char* &A, const char* &B, const char* &C, const char* &D, const char* &E, const char* &F, const char* &G, const char* &H, const char* &I
#define C_str10(A,B,C,D,E,F,G,H,I,J)								const char* &A, const char* &B, const char* &C, const char* &D, const char* &E, const char* &F, const char* &G, const char* &H, const char* &I, const char* &J
#define C_str11(A,B,C,D,E,F,G,H,I,J,K)								const char* &A, const char* &B, const char* &C, const char* &D, const char* &E, const char* &F, const char* &G, const char* &H, const char* &I, const char* &J, const char* &K
#define C_str12(A,B,C,D,E,F,G,H,I,J,K,L)							const char* &A, const char* &B, const char* &C, const char* &D, const char* &E, const char* &F, const char* &G, const char* &H, const char* &I, const char* &J, const char* &K, const char* &L
#define C_str13(A,B,C,D,E,F,G,H,I,J,K,L,M)							const char* &A, const char* &B, const char* &C, const char* &D, const char* &E, const char* &F, const char* &G, const char* &H, const char* &I, const char* &J, const char* &K, const char* &L, const char* &M
#define C_str14(A,B,C,D,E,F,G,H,I,J,K,L,M,N)						const char* &A, const char* &B, const char* &C, const char* &D, const char* &E, const char* &F, const char* &G, const char* &H, const char* &I, const char* &J, const char* &K, const char* &L, const char* &M, const char* &N
#define C_str15(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O)						const char* &A, const char* &B, const char* &C, const char* &D, const char* &E, const char* &F, const char* &G, const char* &H, const char* &I, const char* &J, const char* &K, const char* &L, const char* &M, const char* &N, const char* &O
#define C_str16(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P)					const char* &A, const char* &B, const char* &C, const char* &D, const char* &E, const char* &F, const char* &G, const char* &H, const char* &I, const char* &J, const char* &K, const char* &L, const char* &M, const char* &N, const char* &O, const char* &P
#define C_str17(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q)					const char* &A, const char* &B, const char* &C, const char* &D, const char* &E, const char* &F, const char* &G, const char* &H, const char* &I, const char* &J, const char* &K, const char* &L, const char* &M, const char* &N, const char* &O, const char* &P, const char* &Q
#define C_str18(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R)				const char* &A, const char* &B, const char* &C, const char* &D, const char* &E, const char* &F, const char* &G, const char* &H, const char* &I, const char* &J, const char* &K, const char* &L, const char* &M, const char* &N, const char* &O, const char* &P, const char* &Q, const char* &R
#define C_str19(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S)				const char* &A, const char* &B, const char* &C, const char* &D, const char* &E, const char* &F, const char* &G, const char* &H, const char* &I, const char* &J, const char* &K, const char* &L, const char* &M, const char* &N, const char* &O, const char* &P, const char* &Q, const char* &R, const char* &S
#define C_str20(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T)			const char* &A, const char* &B, const char* &C, const char* &D, const char* &E, const char* &F, const char* &G, const char* &H, const char* &I, const char* &J, const char* &K, const char* &L, const char* &M, const char* &N, const char* &O, const char* &P, const char* &Q, const char* &R, const char* &S, const char* &T
#define C_str21(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U)			const char* &A, const char* &B, const char* &C, const char* &D, const char* &E, const char* &F, const char* &G, const char* &H, const char* &I, const char* &J, const char* &K, const char* &L, const char* &M, const char* &N, const char* &O, const char* &P, const char* &Q, const char* &R, const char* &S, const char* &T, const char* &U
#define C_str22(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V)		const char* &A, const char* &B, const char* &C, const char* &D, const char* &E, const char* &F, const char* &G, const char* &H, const char* &I, const char* &J, const char* &K, const char* &L, const char* &M, const char* &N, const char* &O, const char* &P, const char* &Q, const char* &R, const char* &S, const char* &T, const char* &U, const char* &V
#define C_str23(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W)		const char* &A, const char* &B, const char* &C, const char* &D, const char* &E, const char* &F, const char* &G, const char* &H, const char* &I, const char* &J, const char* &K, const char* &L, const char* &M, const char* &N, const char* &O, const char* &P, const char* &Q, const char* &R, const char* &S, const char* &T, const char* &U, const char* &V, const char* &W
#define C_str24(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X)	const char* &A, const char* &B, const char* &C, const char* &D, const char* &E, const char* &F, const char* &G, const char* &H, const char* &I, const char* &J, const char* &K, const char* &L, const char* &M, const char* &N, const char* &O, const char* &P, const char* &Q, const char* &R, const char* &S, const char* &T, const char* &U, const char* &V, const char* &W, const char* &X
#define C_str25(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y)	const char* &A, const char* &B, const char* &C, const char* &D, const char* &E, const char* &F, const char* &G, const char* &H, const char* &I, const char* &J, const char* &K, const char* &L, const char* &M, const char* &N, const char* &O, const char* &P, const char* &Q, const char* &R, const char* &S, const char* &T, const char* &U, const char* &V, const char* &W, const char* &X, const char* &Y
#define C_str26(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z)const char* &A, const char* &B, const char* &C, const char* &D, const char* &E, const char* &F, const char* &G, const char* &H, const char* &I, const char* &J, const char* &K, const char* &L, const char* &M, const char* &N, const char* &O, const char* &P, const char* &Q, const char* &R, const char* &S, const char* &T, const char* &U, const char* &V, const char* &W, const char* &X, const char* &Y, const char* &Z

#define C_z(A)														const void &A
#define C_z2(A,B)													const void &A, const void &B
#define C_z3(A,B,C)													const void &A, const void &B, const void &C
#define C_z4(A,B,C,D)												const void &A, const void &B, const void &C, const void &D
#define C_z5(A,B,C,D,E)												const void &A, const void &B, const void &C, const void &D, const void &E
#define C_z6(A,B,C,D,E,F)											const void &A, const void &B, const void &C, const void &D, const void &E, const void &F
#define C_z7(A,B,C,D,E,F,G)											const void &A, const void &B, const void &C, const void &D, const void &E, const void &F, const void &G
#define C_z8(A,B,C,D,E,F,G,H)										const void &A, const void &B, const void &C, const void &D, const void &E, const void &F, const void &G, const void &H
#define C_z9(A,B,C,D,E,F,G,H,I)										const void &A, const void &B, const void &C, const void &D, const void &E, const void &F, const void &G, const void &H, const void &I
#define C_z10(A,B,C,D,E,F,G,H,I,J)									const void &A, const void &B, const void &C, const void &D, const void &E, const void &F, const void &G, const void &H, const void &I, const void &J
#define C_z11(A,B,C,D,E,F,G,H,I,J,K)								const void &A, const void &B, const void &C, const void &D, const void &E, const void &F, const void &G, const void &H, const void &I, const void &J, const void &K
#define C_z12(A,B,C,D,E,F,G,H,I,J,K,L)								const void &A, const void &B, const void &C, const void &D, const void &E, const void &F, const void &G, const void &H, const void &I, const void &J, const void &K, const void &L
#define C_z13(A,B,C,D,E,F,G,H,I,J,K,L,M)							const void &A, const void &B, const void &C, const void &D, const void &E, const void &F, const void &G, const void &H, const void &I, const void &J, const void &K, const void &L, const void &M
#define C_z14(A,B,C,D,E,F,G,H,I,J,K,L,M,N)							const void &A, const void &B, const void &C, const void &D, const void &E, const void &F, const void &G, const void &H, const void &I, const void &J, const void &K, const void &L, const void &M, const void &N
#define C_z15(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O)						const void &A, const void &B, const void &C, const void &D, const void &E, const void &F, const void &G, const void &H, const void &I, const void &J, const void &K, const void &L, const void &M, const void &N, const void &O
#define C_z16(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P)						const void &A, const void &B, const void &C, const void &D, const void &E, const void &F, const void &G, const void &H, const void &I, const void &J, const void &K, const void &L, const void &M, const void &N, const void &O, const void &P
#define C_z17(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q)					const void &A, const void &B, const void &C, const void &D, const void &E, const void &F, const void &G, const void &H, const void &I, const void &J, const void &K, const void &L, const void &M, const void &N, const void &O, const void &P, const void &Q
#define C_z18(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R)					const void &A, const void &B, const void &C, const void &D, const void &E, const void &F, const void &G, const void &H, const void &I, const void &J, const void &K, const void &L, const void &M, const void &N, const void &O, const void &P, const void &Q, const void &R
#define C_z19(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S)				const void &A, const void &B, const void &C, const void &D, const void &E, const void &F, const void &G, const void &H, const void &I, const void &J, const void &K, const void &L, const void &M, const void &N, const void &O, const void &P, const void &Q, const void &R, const void &S
#define C_z20(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T)				const void &A, const void &B, const void &C, const void &D, const void &E, const void &F, const void &G, const void &H, const void &I, const void &J, const void &K, const void &L, const void &M, const void &N, const void &O, const void &P, const void &Q, const void &R, const void &S, const void &T
#define C_z21(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U)			const void &A, const void &B, const void &C, const void &D, const void &E, const void &F, const void &G, const void &H, const void &I, const void &J, const void &K, const void &L, const void &M, const void &N, const void &O, const void &P, const void &Q, const void &R, const void &S, const void &T, const void &U
#define C_z22(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V)			const void &A, const void &B, const void &C, const void &D, const void &E, const void &F, const void &G, const void &H, const void &I, const void &J, const void &K, const void &L, const void &M, const void &N, const void &O, const void &P, const void &Q, const void &R, const void &S, const void &T, const void &U, const void &V
#define C_z23(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W)		const void &A, const void &B, const void &C, const void &D, const void &E, const void &F, const void &G, const void &H, const void &I, const void &J, const void &K, const void &L, const void &M, const void &N, const void &O, const void &P, const void &Q, const void &R, const void &S, const void &T, const void &U, const void &V, const void &W
#define C_z24(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X)		const void &A, const void &B, const void &C, const void &D, const void &E, const void &F, const void &G, const void &H, const void &I, const void &J, const void &K, const void &L, const void &M, const void &N, const void &O, const void &P, const void &Q, const void &R, const void &S, const void &T, const void &U, const void &V, const void &W, const void &X
#define C_z25(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y)	const void &A, const void &B, const void &C, const void &D, const void &E, const void &F, const void &G, const void &H, const void &I, const void &J, const void &K, const void &L, const void &M, const void &N, const void &O, const void &P, const void &Q, const void &R, const void &S, const void &T, const void &U, const void &V, const void &W, const void &X, const void &Y
#define C_z26(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z)	const void &A, const void &B, const void &C, const void &D, const void &E, const void &F, const void &G, const void &H, const void &I, const void &J, const void &K, const void &L, const void &M, const void &N, const void &O, const void &P, const void &Q, const void &R, const void &S, const void &T, const void &U, const void &V, const void &W, const void &X, const void &Y, const void &Z
//..................................................................................................................
/*<xyz>		IPTs: Indetifier Passing Tags

	IPTs are like cripts except they aren't constant and they don't pass by referencce, Basically an IPT
	is a somewhat shorthand way of passing regular vars.


	SYNTAX:		IPTS are in the following syntax:
				"V_" + Prefix

				Where prefix is a common, standard, variable prefix that the CRIPT identifies as the
				type of variable being passed.

	NOTICE:		This macro was intended to be used in function prototypes. Don't use it anywhere else!

	WARNING:	Add's a new level of crypticness to programs code. Use with care!	
*/					

#define V_b(A)														 Uint8 A
#define V_b2(A,B)													 Uint8 A,  Uint8 B
#define V_b3(A,B,C)													 Uint8 A,  Uint8 B,  Uint8 C
#define V_b4(A,B,C,D)												 Uint8 A,  Uint8 B,  Uint8 C,  Uint8 D
#define V_b5(A,B,C,D,E)												 Uint8 A,  Uint8 B,  Uint8 C,  Uint8 D,  Uint8 E
#define V_b6(A,B,C,D,E,F)											 Uint8 A,  Uint8 B,  Uint8 C,  Uint8 D,  Uint8 E,  Uint8 F
#define V_b7(A,B,C,D,E,F,G)											 Uint8 A,  Uint8 B,  Uint8 C,  Uint8 D,  Uint8 E,  Uint8 F,  Uint8 G
#define V_b8(A,B,C,D,E,F,G,H)										 Uint8 A,  Uint8 B,  Uint8 C,  Uint8 D,  Uint8 E,  Uint8 F,  Uint8 G,  Uint8 H
#define V_b9(A,B,C,D,E,F,G,H,I)										 Uint8 A,  Uint8 B,  Uint8 C,  Uint8 D,  Uint8 E,  Uint8 F,  Uint8 G,  Uint8 H,  Uint8 I
#define V_b10(A,B,C,D,E,F,G,H,I,J)									 Uint8 A,  Uint8 B,  Uint8 C,  Uint8 D,  Uint8 E,  Uint8 F,  Uint8 G,  Uint8 H,  Uint8 I,  Uint8 J
#define V_b11(A,B,C,D,E,F,G,H,I,J,K)								 Uint8 A,  Uint8 B,  Uint8 C,  Uint8 D,  Uint8 E,  Uint8 F,  Uint8 G,  Uint8 H,  Uint8 I,  Uint8 J,  Uint8 K
#define V_b12(A,B,C,D,E,F,G,H,I,J,K,L)								 Uint8 A,  Uint8 B,  Uint8 C,  Uint8 D,  Uint8 E,  Uint8 F,  Uint8 G,  Uint8 H,  Uint8 I,  Uint8 J,  Uint8 K,  Uint8 L
#define V_b13(A,B,C,D,E,F,G,H,I,J,K,L,M)							 Uint8 A,  Uint8 B,  Uint8 C,  Uint8 D,  Uint8 E,  Uint8 F,  Uint8 G,  Uint8 H,  Uint8 I,  Uint8 J,  Uint8 K,  Uint8 L,  Uint8 M
#define V_b14(A,B,C,D,E,F,G,H,I,J,K,L,M,N)							 Uint8 A,  Uint8 B,  Uint8 C,  Uint8 D,  Uint8 E,  Uint8 F,  Uint8 G,  Uint8 H,  Uint8 I,  Uint8 J,  Uint8 K,  Uint8 L,  Uint8 M,  Uint8 N
#define V_b15(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O)						 Uint8 A,  Uint8 B,  Uint8 C,  Uint8 D,  Uint8 E,  Uint8 F,  Uint8 G,  Uint8 H,  Uint8 I,  Uint8 J,  Uint8 K,  Uint8 L,  Uint8 M,  Uint8 N,  Uint8 O
#define V_b16(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P)						 Uint8 A,  Uint8 B,  Uint8 C,  Uint8 D,  Uint8 E,  Uint8 F,  Uint8 G,  Uint8 H,  Uint8 I,  Uint8 J,  Uint8 K,  Uint8 L,  Uint8 M,  Uint8 N,  Uint8 O,  Uint8 P
#define V_b17(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q)					 Uint8 A,  Uint8 B,  Uint8 C,  Uint8 D,  Uint8 E,  Uint8 F,  Uint8 G,  Uint8 H,  Uint8 I,  Uint8 J,  Uint8 K,  Uint8 L,  Uint8 M,  Uint8 N,  Uint8 O,  Uint8 P,  Uint8 Q
#define V_b18(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R)					 Uint8 A,  Uint8 B,  Uint8 C,  Uint8 D,  Uint8 E,  Uint8 F,  Uint8 G,  Uint8 H,  Uint8 I,  Uint8 J,  Uint8 K,  Uint8 L,  Uint8 M,  Uint8 N,  Uint8 O,  Uint8 P,  Uint8 Q,  Uint8 R
#define V_b19(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S)				 Uint8 A,  Uint8 B,  Uint8 C,  Uint8 D,  Uint8 E,  Uint8 F,  Uint8 G,  Uint8 H,  Uint8 I,  Uint8 J,  Uint8 K,  Uint8 L,  Uint8 M,  Uint8 N,  Uint8 O,  Uint8 P,  Uint8 Q,  Uint8 R,  Uint8 S
#define V_b20(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T)				 Uint8 A,  Uint8 B,  Uint8 C,  Uint8 D,  Uint8 E,  Uint8 F,  Uint8 G,  Uint8 H,  Uint8 I,  Uint8 J,  Uint8 K,  Uint8 L,  Uint8 M,  Uint8 N,  Uint8 O,  Uint8 P,  Uint8 Q,  Uint8 R,  Uint8 S,  Uint8 T
#define V_b21(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U)			 Uint8 A,  Uint8 B,  Uint8 C,  Uint8 D,  Uint8 E,  Uint8 F,  Uint8 G,  Uint8 H,  Uint8 I,  Uint8 J,  Uint8 K,  Uint8 L,  Uint8 M,  Uint8 N,  Uint8 O,  Uint8 P,  Uint8 Q,  Uint8 R,  Uint8 S,  Uint8 T,  Uint8 U
#define V_b22(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V)			 Uint8 A,  Uint8 B,  Uint8 C,  Uint8 D,  Uint8 E,  Uint8 F,  Uint8 G,  Uint8 H,  Uint8 I,  Uint8 J,  Uint8 K,  Uint8 L,  Uint8 M,  Uint8 N,  Uint8 O,  Uint8 P,  Uint8 Q,  Uint8 R,  Uint8 S,  Uint8 T,  Uint8 U,  Uint8 V
#define V_b23(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W)		 Uint8 A,  Uint8 B,  Uint8 C,  Uint8 D,  Uint8 E,  Uint8 F,  Uint8 G,  Uint8 H,  Uint8 I,  Uint8 J,  Uint8 K,  Uint8 L,  Uint8 M,  Uint8 N,  Uint8 O,  Uint8 P,  Uint8 Q,  Uint8 R,  Uint8 S,  Uint8 T,  Uint8 U,  Uint8 V,  Uint8 W
#define V_b24(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X)		 Uint8 A,  Uint8 B,  Uint8 C,  Uint8 D,  Uint8 E,  Uint8 F,  Uint8 G,  Uint8 H,  Uint8 I,  Uint8 J,  Uint8 K,  Uint8 L,  Uint8 M,  Uint8 N,  Uint8 O,  Uint8 P,  Uint8 Q,  Uint8 R,  Uint8 S,  Uint8 T,  Uint8 U,  Uint8 V,  Uint8 W,  Uint8 X
#define V_b25(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y)	 Uint8 A,  Uint8 B,  Uint8 C,  Uint8 D,  Uint8 E,  Uint8 F,  Uint8 G,  Uint8 H,  Uint8 I,  Uint8 J,  Uint8 K,  Uint8 L,  Uint8 M,  Uint8 N,  Uint8 O,  Uint8 P,  Uint8 Q,  Uint8 R,  Uint8 S,  Uint8 T,  Uint8 U,  Uint8 V,  Uint8 W,  Uint8 X,  Uint8 Y
#define V_b26(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z)	 Uint8 A,  Uint8 B,  Uint8 C,  Uint8 D,  Uint8 E,  Uint8 F,  Uint8 G,  Uint8 H,  Uint8 I,  Uint8 J,  Uint8 K,  Uint8 L,  Uint8 M,  Uint8 N,  Uint8 O,  Uint8 P,  Uint8 Q,  Uint8 R,  Uint8 S,  Uint8 T,  Uint8 U,  Uint8 V,  Uint8 W,  Uint8 X,  Uint8 Y,  Uint8 Z

#define V_i(A)														 int A
#define V_i2(A,B)													 int A,  int B
#define V_i3(A,B,C)													 int A,  int B,  int C
#define V_i4(A,B,C,D)												 int A,  int B,  int C,  int D
#define V_i5(A,B,C,D,E)												 int A,  int B,  int C,  int D,  int E
#define V_i6(A,B,C,D,E,F)											 int A,  int B,  int C,  int D,  int E,  int F
#define V_i7(A,B,C,D,E,F,G)											 int A,  int B,  int C,  int D,  int E,  int F,  int G
#define V_i8(A,B,C,D,E,F,G,H)										 int A,  int B,  int C,  int D,  int E,  int F,  int G,  int H
#define V_i9(A,B,C,D,E,F,G,H,I)										 int A,  int B,  int C,  int D,  int E,  int F,  int G,  int H,  int I
#define V_i10(A,B,C,D,E,F,G,H,I,J)									 int A,  int B,  int C,  int D,  int E,  int F,  int G,  int H,  int I,  int J
#define V_i11(A,B,C,D,E,F,G,H,I,J,K)								 int A,  int B,  int C,  int D,  int E,  int F,  int G,  int H,  int I,  int J,  int K
#define V_i12(A,B,C,D,E,F,G,H,I,J,K,L)								 int A,  int B,  int C,  int D,  int E,  int F,  int G,  int H,  int I,  int J,  int K,  int L
#define V_i13(A,B,C,D,E,F,G,H,I,J,K,L,M)							 int A,  int B,  int C,  int D,  int E,  int F,  int G,  int H,  int I,  int J,  int K,  int L,  int M
#define V_i14(A,B,C,D,E,F,G,H,I,J,K,L,M,N)							 int A,  int B,  int C,  int D,  int E,  int F,  int G,  int H,  int I,  int J,  int K,  int L,  int M,  int N
#define V_i15(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O)						 int A,  int B,  int C,  int D,  int E,  int F,  int G,  int H,  int I,  int J,  int K,  int L,  int M,  int N,  int O
#define V_i16(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P)						 int A,  int B,  int C,  int D,  int E,  int F,  int G,  int H,  int I,  int J,  int K,  int L,  int M,  int N,  int O,  int P
#define V_i17(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q)					 int A,  int B,  int C,  int D,  int E,  int F,  int G,  int H,  int I,  int J,  int K,  int L,  int M,  int N,  int O,  int P,  int Q
#define V_i18(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R)					 int A,  int B,  int C,  int D,  int E,  int F,  int G,  int H,  int I,  int J,  int K,  int L,  int M,  int N,  int O,  int P,  int Q,  int R
#define V_i19(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S)				 int A,  int B,  int C,  int D,  int E,  int F,  int G,  int H,  int I,  int J,  int K,  int L,  int M,  int N,  int O,  int P,  int Q,  int R,  int S
#define V_i20(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T)				 int A,  int B,  int C,  int D,  int E,  int F,  int G,  int H,  int I,  int J,  int K,  int L,  int M,  int N,  int O,  int P,  int Q,  int R,  int S,  int T
#define V_i21(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U)			 int A,  int B,  int C,  int D,  int E,  int F,  int G,  int H,  int I,  int J,  int K,  int L,  int M,  int N,  int O,  int P,  int Q,  int R,  int S,  int T,  int U
#define V_i22(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V)			 int A,  int B,  int C,  int D,  int E,  int F,  int G,  int H,  int I,  int J,  int K,  int L,  int M,  int N,  int O,  int P,  int Q,  int R,  int S,  int T,  int U,  int V
#define V_i23(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W)		 int A,  int B,  int C,  int D,  int E,  int F,  int G,  int H,  int I,  int J,  int K,  int L,  int M,  int N,  int O,  int P,  int Q,  int R,  int S,  int T,  int U,  int V,  int W
#define V_i24(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X)		 int A,  int B,  int C,  int D,  int E,  int F,  int G,  int H,  int I,  int J,  int K,  int L,  int M,  int N,  int O,  int P,  int Q,  int R,  int S,  int T,  int U,  int V,  int W,  int X
#define V_i25(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y)	 int A,  int B,  int C,  int D,  int E,  int F,  int G,  int H,  int I,  int J,  int K,  int L,  int M,  int N,  int O,  int P,  int Q,  int R,  int S,  int T,  int U,  int V,  int W,  int X,  int Y
#define V_i26(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z)	 int A,  int B,  int C,  int D,  int E,  int F,  int G,  int H,  int I,  int J,  int K,  int L,  int M,  int N,  int O,  int P,  int Q,  int R,  int S,  int T,  int U,  int V,  int W,  int X,  int Y,  int Z

#define V_s(A)														 string A
#define V_s2(A,B)													 string A,  string B
#define V_s3(A,B,C)													 string A,  string B,  string C
#define V_s4(A,B,C,D)												 string A,  string B,  string C,  string D
#define V_s5(A,B,C,D,E)												 string A,  string B,  string C,  string D,  string E
#define V_s6(A,B,C,D,E,F)											 string A,  string B,  string C,  string D,  string E,  string F
#define V_s7(A,B,C,D,E,F,G)											 string A,  string B,  string C,  string D,  string E,  string F,  string G
#define V_s8(A,B,C,D,E,F,G,H)										 string A,  string B,  string C,  string D,  string E,  string F,  string G,  string H
#define V_s9(A,B,C,D,E,F,G,H,I)										 string A,  string B,  string C,  string D,  string E,  string F,  string G,  string H,  string I
#define V_s10(A,B,C,D,E,F,G,H,I,J)									 string A,  string B,  string C,  string D,  string E,  string F,  string G,  string H,  string I,  string J
#define V_s11(A,B,C,D,E,F,G,H,I,J,K)								 string A,  string B,  string C,  string D,  string E,  string F,  string G,  string H,  string I,  string J,  string K
#define V_s12(A,B,C,D,E,F,G,H,I,J,K,L)								 string A,  string B,  string C,  string D,  string E,  string F,  string G,  string H,  string I,  string J,  string K,  string L
#define V_s13(A,B,C,D,E,F,G,H,I,J,K,L,M)							 string A,  string B,  string C,  string D,  string E,  string F,  string G,  string H,  string I,  string J,  string K,  string L,  string M
#define V_s14(A,B,C,D,E,F,G,H,I,J,K,L,M,N)							 string A,  string B,  string C,  string D,  string E,  string F,  string G,  string H,  string I,  string J,  string K,  string L,  string M,  string N
#define V_s15(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O)						 string A,  string B,  string C,  string D,  string E,  string F,  string G,  string H,  string I,  string J,  string K,  string L,  string M,  string N,  string O
#define V_s16(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P)						 string A,  string B,  string C,  string D,  string E,  string F,  string G,  string H,  string I,  string J,  string K,  string L,  string M,  string N,  string O,  string P
#define V_s17(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q)					 string A,  string B,  string C,  string D,  string E,  string F,  string G,  string H,  string I,  string J,  string K,  string L,  string M,  string N,  string O,  string P,  string Q
#define V_s18(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R)					 string A,  string B,  string C,  string D,  string E,  string F,  string G,  string H,  string I,  string J,  string K,  string L,  string M,  string N,  string O,  string P,  string Q,  string R
#define V_s19(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S)				 string A,  string B,  string C,  string D,  string E,  string F,  string G,  string H,  string I,  string J,  string K,  string L,  string M,  string N,  string O,  string P,  string Q,  string R,  string S
#define V_s20(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T)				 string A,  string B,  string C,  string D,  string E,  string F,  string G,  string H,  string I,  string J,  string K,  string L,  string M,  string N,  string O,  string P,  string Q,  string R,  string S,  string T
#define V_s21(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U)			 string A,  string B,  string C,  string D,  string E,  string F,  string G,  string H,  string I,  string J,  string K,  string L,  string M,  string N,  string O,  string P,  string Q,  string R,  string S,  string T,  string U
#define V_s22(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V)			 string A,  string B,  string C,  string D,  string E,  string F,  string G,  string H,  string I,  string J,  string K,  string L,  string M,  string N,  string O,  string P,  string Q,  string R,  string S,  string T,  string U,  string V
#define V_s23(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W)		 string A,  string B,  string C,  string D,  string E,  string F,  string G,  string H,  string I,  string J,  string K,  string L,  string M,  string N,  string O,  string P,  string Q,  string R,  string S,  string T,  string U,  string V,  string W
#define V_s24(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X)		 string A,  string B,  string C,  string D,  string E,  string F,  string G,  string H,  string I,  string J,  string K,  string L,  string M,  string N,  string O,  string P,  string Q,  string R,  string S,  string T,  string U,  string V,  string W,  string X
#define V_s25(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y)	 string A,  string B,  string C,  string D,  string E,  string F,  string G,  string H,  string I,  string J,  string K,  string L,  string M,  string N,  string O,  string P,  string Q,  string R,  string S,  string T,  string U,  string V,  string W,  string X,  string Y
#define V_s26(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z)	 string A,  string B,  string C,  string D,  string E,  string F,  string G,  string H,  string I,  string J,  string K,  string L,  string M,  string N,  string O,  string P,  string Q,  string R,  string S,  string T,  string U,  string V,  string W,  string X,  string Y,  string Z

#define V_c(A)														 char A
#define V_c2(A,B)													 char A,  char B
#define V_c3(A,B,C)													 char A,  char B,  char C
#define V_c4(A,B,C,D)												 char A,  char B,  char C,  char D
#define V_c5(A,B,C,D,E)												 char A,  char B,  char C,  char D,  char E
#define V_c6(A,B,C,D,E,F)											 char A,  char B,  char C,  char D,  char E,  char F
#define V_c7(A,B,C,D,E,F,G)											 char A,  char B,  char C,  char D,  char E,  char F,  char G
#define V_c8(A,B,C,D,E,F,G,H)										 char A,  char B,  char C,  char D,  char E,  char F,  char G,  char H
#define V_c9(A,B,C,D,E,F,G,H,I)										 char A,  char B,  char C,  char D,  char E,  char F,  char G,  char H,  char I
#define V_c10(A,B,C,D,E,F,G,H,I,J)									 char A,  char B,  char C,  char D,  char E,  char F,  char G,  char H,  char I,  char J
#define V_c11(A,B,C,D,E,F,G,H,I,J,K)								 char A,  char B,  char C,  char D,  char E,  char F,  char G,  char H,  char I,  char J,  char K
#define V_c12(A,B,C,D,E,F,G,H,I,J,K,L)								 char A,  char B,  char C,  char D,  char E,  char F,  char G,  char H,  char I,  char J,  char K,  char L
#define V_c13(A,B,C,D,E,F,G,H,I,J,K,L,M)							 char A,  char B,  char C,  char D,  char E,  char F,  char G,  char H,  char I,  char J,  char K,  char L,  char M
#define V_c14(A,B,C,D,E,F,G,H,I,J,K,L,M,N)							 char A,  char B,  char C,  char D,  char E,  char F,  char G,  char H,  char I,  char J,  char K,  char L,  char M,  char N
#define V_c15(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O)						 char A,  char B,  char C,  char D,  char E,  char F,  char G,  char H,  char I,  char J,  char K,  char L,  char M,  char N,  char O
#define V_c16(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P)						 char A,  char B,  char C,  char D,  char E,  char F,  char G,  char H,  char I,  char J,  char K,  char L,  char M,  char N,  char O,  char P
#define V_c17(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q)					 char A,  char B,  char C,  char D,  char E,  char F,  char G,  char H,  char I,  char J,  char K,  char L,  char M,  char N,  char O,  char P,  char Q
#define V_c18(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R)					 char A,  char B,  char C,  char D,  char E,  char F,  char G,  char H,  char I,  char J,  char K,  char L,  char M,  char N,  char O,  char P,  char Q,  char R
#define V_c19(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S)				 char A,  char B,  char C,  char D,  char E,  char F,  char G,  char H,  char I,  char J,  char K,  char L,  char M,  char N,  char O,  char P,  char Q,  char R,  char S
#define V_c20(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T)				 char A,  char B,  char C,  char D,  char E,  char F,  char G,  char H,  char I,  char J,  char K,  char L,  char M,  char N,  char O,  char P,  char Q,  char R,  char S,  char T
#define V_c21(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U)			 char A,  char B,  char C,  char D,  char E,  char F,  char G,  char H,  char I,  char J,  char K,  char L,  char M,  char N,  char O,  char P,  char Q,  char R,  char S,  char T,  char U
#define V_c22(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V)			 char A,  char B,  char C,  char D,  char E,  char F,  char G,  char H,  char I,  char J,  char K,  char L,  char M,  char N,  char O,  char P,  char Q,  char R,  char S,  char T,  char U,  char V
#define V_c23(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W)		 char A,  char B,  char C,  char D,  char E,  char F,  char G,  char H,  char I,  char J,  char K,  char L,  char M,  char N,  char O,  char P,  char Q,  char R,  char S,  char T,  char U,  char V,  char W
#define V_c24(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X)		 char A,  char B,  char C,  char D,  char E,  char F,  char G,  char H,  char I,  char J,  char K,  char L,  char M,  char N,  char O,  char P,  char Q,  char R,  char S,  char T,  char U,  char V,  char W,  char X
#define V_c25(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y)	 char A,  char B,  char C,  char D,  char E,  char F,  char G,  char H,  char I,  char J,  char K,  char L,  char M,  char N,  char O,  char P,  char Q,  char R,  char S,  char T,  char U,  char V,  char W,  char X,  char Y
#define V_c26(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z)	 char A,  char B,  char C,  char D,  char E,  char F,  char G,  char H,  char I,  char J,  char K,  char L,  char M,  char N,  char O,  char P,  char Q,  char R,  char S,  char T,  char U,  char V,  char W,  char X,  char Y,  char Z

#define V_d(A)														 double A
#define V_d2(A,B)													 double A,  double B
#define V_d3(A,B,C)													 double A,  double B,  double C
#define V_d4(A,B,C,D)												 double A,  double B,  double C,  double D
#define V_d5(A,B,C,D,E)												 double A,  double B,  double C,  double D,  double E
#define V_d6(A,B,C,D,E,F)											 double A,  double B,  double C,  double D,  double E,  double F
#define V_d7(A,B,C,D,E,F,G)											 double A,  double B,  double C,  double D,  double E,  double F,  double G
#define V_d8(A,B,C,D,E,F,G,H)										 double A,  double B,  double C,  double D,  double E,  double F,  double G,  double H
#define V_d9(A,B,C,D,E,F,G,H,I)										 double A,  double B,  double C,  double D,  double E,  double F,  double G,  double H,  double I
#define V_d10(A,B,C,D,E,F,G,H,I,J)									 double A,  double B,  double C,  double D,  double E,  double F,  double G,  double H,  double I,  double J
#define V_d11(A,B,C,D,E,F,G,H,I,J,K)								 double A,  double B,  double C,  double D,  double E,  double F,  double G,  double H,  double I,  double J,  double K
#define V_d12(A,B,C,D,E,F,G,H,I,J,K,L)								 double A,  double B,  double C,  double D,  double E,  double F,  double G,  double H,  double I,  double J,  double K,  double L
#define V_d13(A,B,C,D,E,F,G,H,I,J,K,L,M)							 double A,  double B,  double C,  double D,  double E,  double F,  double G,  double H,  double I,  double J,  double K,  double L,  double M
#define V_d14(A,B,C,D,E,F,G,H,I,J,K,L,M,N)							 double A,  double B,  double C,  double D,  double E,  double F,  double G,  double H,  double I,  double J,  double K,  double L,  double M,  double N
#define V_d15(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O)						 double A,  double B,  double C,  double D,  double E,  double F,  double G,  double H,  double I,  double J,  double K,  double L,  double M,  double N,  double O
#define V_d16(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P)						 double A,  double B,  double C,  double D,  double E,  double F,  double G,  double H,  double I,  double J,  double K,  double L,  double M,  double N,  double O,  double P
#define V_d17(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q)					 double A,  double B,  double C,  double D,  double E,  double F,  double G,  double H,  double I,  double J,  double K,  double L,  double M,  double N,  double O,  double P,  double Q
#define V_d18(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R)					 double A,  double B,  double C,  double D,  double E,  double F,  double G,  double H,  double I,  double J,  double K,  double L,  double M,  double N,  double O,  double P,  double Q,  double R
#define V_d19(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S)				 double A,  double B,  double C,  double D,  double E,  double F,  double G,  double H,  double I,  double J,  double K,  double L,  double M,  double N,  double O,  double P,  double Q,  double R,  double S
#define V_d20(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T)				 double A,  double B,  double C,  double D,  double E,  double F,  double G,  double H,  double I,  double J,  double K,  double L,  double M,  double N,  double O,  double P,  double Q,  double R,  double S,  double T
#define V_d21(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U)			 double A,  double B,  double C,  double D,  double E,  double F,  double G,  double H,  double I,  double J,  double K,  double L,  double M,  double N,  double O,  double P,  double Q,  double R,  double S,  double T,  double U
#define V_d22(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V)			 double A,  double B,  double C,  double D,  double E,  double F,  double G,  double H,  double I,  double J,  double K,  double L,  double M,  double N,  double O,  double P,  double Q,  double R,  double S,  double T,  double U,  double V
#define V_d23(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W)		 double A,  double B,  double C,  double D,  double E,  double F,  double G,  double H,  double I,  double J,  double K,  double L,  double M,  double N,  double O,  double P,  double Q,  double R,  double S,  double T,  double U,  double V,  double W
#define V_d24(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X)		 double A,  double B,  double C,  double D,  double E,  double F,  double G,  double H,  double I,  double J,  double K,  double L,  double M,  double N,  double O,  double P,  double Q,  double R,  double S,  double T,  double U,  double V,  double W,  double X
#define V_d25(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y)	 double A,  double B,  double C,  double D,  double E,  double F,  double G,  double H,  double I,  double J,  double K,  double L,  double M,  double N,  double O,  double P,  double Q,  double R,  double S,  double T,  double U,  double V,  double W,  double X,  double Y
#define V_d26(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z)	 double A,  double B,  double C,  double D,  double E,  double F,  double G,  double H,  double I,  double J,  double K,  double L,  double M,  double N,  double O,  double P,  double Q,  double R,  double S,  double T,  double U,  double V,  double W,  double X,  double Y,  double Z

#define V_f(A)														 bool A
#define V_f2(A,B)													 bool A,  bool B
#define V_f3(A,B,C)													 bool A,  bool B,  bool C
#define V_f4(A,B,C,D)												 bool A,  bool B,  bool C,  bool D
#define V_f5(A,B,C,D,E)												 bool A,  bool B,  bool C,  bool D,  bool E
#define V_f6(A,B,C,D,E,F)											 bool A,  bool B,  bool C,  bool D,  bool E,  bool F
#define V_f7(A,B,C,D,E,F,G)											 bool A,  bool B,  bool C,  bool D,  bool E,  bool F,  bool G
#define V_f8(A,B,C,D,E,F,G,H)										 bool A,  bool B,  bool C,  bool D,  bool E,  bool F,  bool G,  bool H
#define V_f9(A,B,C,D,E,F,G,H,I)										 bool A,  bool B,  bool C,  bool D,  bool E,  bool F,  bool G,  bool H,  bool I
#define V_f10(A,B,C,D,E,F,G,H,I,J)									 bool A,  bool B,  bool C,  bool D,  bool E,  bool F,  bool G,  bool H,  bool I,  bool J
#define V_f11(A,B,C,D,E,F,G,H,I,J,K)								 bool A,  bool B,  bool C,  bool D,  bool E,  bool F,  bool G,  bool H,  bool I,  bool J,  bool K
#define V_f12(A,B,C,D,E,F,G,H,I,J,K,L)								 bool A,  bool B,  bool C,  bool D,  bool E,  bool F,  bool G,  bool H,  bool I,  bool J,  bool K,  bool L
#define V_f13(A,B,C,D,E,F,G,H,I,J,K,L,M)							 bool A,  bool B,  bool C,  bool D,  bool E,  bool F,  bool G,  bool H,  bool I,  bool J,  bool K,  bool L,  bool M
#define V_f14(A,B,C,D,E,F,G,H,I,J,K,L,M,N)							 bool A,  bool B,  bool C,  bool D,  bool E,  bool F,  bool G,  bool H,  bool I,  bool J,  bool K,  bool L,  bool M,  bool N
#define V_f15(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O)						 bool A,  bool B,  bool C,  bool D,  bool E,  bool F,  bool G,  bool H,  bool I,  bool J,  bool K,  bool L,  bool M,  bool N,  bool O
#define V_f16(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P)						 bool A,  bool B,  bool C,  bool D,  bool E,  bool F,  bool G,  bool H,  bool I,  bool J,  bool K,  bool L,  bool M,  bool N,  bool O,  bool P
#define V_f17(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q)					 bool A,  bool B,  bool C,  bool D,  bool E,  bool F,  bool G,  bool H,  bool I,  bool J,  bool K,  bool L,  bool M,  bool N,  bool O,  bool P,  bool Q
#define V_f18(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R)					 bool A,  bool B,  bool C,  bool D,  bool E,  bool F,  bool G,  bool H,  bool I,  bool J,  bool K,  bool L,  bool M,  bool N,  bool O,  bool P,  bool Q,  bool R
#define V_f19(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S)				 bool A,  bool B,  bool C,  bool D,  bool E,  bool F,  bool G,  bool H,  bool I,  bool J,  bool K,  bool L,  bool M,  bool N,  bool O,  bool P,  bool Q,  bool R,  bool S
#define V_f20(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T)				 bool A,  bool B,  bool C,  bool D,  bool E,  bool F,  bool G,  bool H,  bool I,  bool J,  bool K,  bool L,  bool M,  bool N,  bool O,  bool P,  bool Q,  bool R,  bool S,  bool T
#define V_f21(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U)			 bool A,  bool B,  bool C,  bool D,  bool E,  bool F,  bool G,  bool H,  bool I,  bool J,  bool K,  bool L,  bool M,  bool N,  bool O,  bool P,  bool Q,  bool R,  bool S,  bool T,  bool U
#define V_f22(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V)			 bool A,  bool B,  bool C,  bool D,  bool E,  bool F,  bool G,  bool H,  bool I,  bool J,  bool K,  bool L,  bool M,  bool N,  bool O,  bool P,  bool Q,  bool R,  bool S,  bool T,  bool U,  bool V
#define V_f23(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W)		 bool A,  bool B,  bool C,  bool D,  bool E,  bool F,  bool G,  bool H,  bool I,  bool J,  bool K,  bool L,  bool M,  bool N,  bool O,  bool P,  bool Q,  bool R,  bool S,  bool T,  bool U,  bool V,  bool W
#define V_f24(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X)		 bool A,  bool B,  bool C,  bool D,  bool E,  bool F,  bool G,  bool H,  bool I,  bool J,  bool K,  bool L,  bool M,  bool N,  bool O,  bool P,  bool Q,  bool R,  bool S,  bool T,  bool U,  bool V,  bool W,  bool X
#define V_f25(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y)	 bool A,  bool B,  bool C,  bool D,  bool E,  bool F,  bool G,  bool H,  bool I,  bool J,  bool K,  bool L,  bool M,  bool N,  bool O,  bool P,  bool Q,  bool R,  bool S,  bool T,  bool U,  bool V,  bool W,  bool X,  bool Y
#define V_f26(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z)	 bool A,  bool B,  bool C,  bool D,  bool E,  bool F,  bool G,  bool H,  bool I,  bool J,  bool K,  bool L,  bool M,  bool N,  bool O,  bool P,  bool Q,  bool R,  bool S,  bool T,  bool U,  bool V,  bool W,  bool X,  bool Y,  bool Z

#define V_str(A)													 char* A
#define V_str2(A,B)													 char* A,  char* B
#define V_str3(A,B,C)												 char* A,  char* B,  char* C
#define V_str4(A,B,C,D)												 char* A,  char* B,  char* C,  char* D
#define V_str5(A,B,C,D,E)											 char* A,  char* B,  char* C,  char* D,  char* E
#define V_str6(A,B,C,D,E,F)											 char* A,  char* B,  char* C,  char* D,  char* E,  char* F
#define V_str7(A,B,C,D,E,F,G)										 char* A,  char* B,  char* C,  char* D,  char* E,  char* F,  char* G
#define V_str8(A,B,C,D,E,F,G,H)										 char* A,  char* B,  char* C,  char* D,  char* E,  char* F,  char* G,  char* H
#define V_str9(A,B,C,D,E,F,G,H,I)									 char* A,  char* B,  char* C,  char* D,  char* E,  char* F,  char* G,  char* H,  char* I
#define V_str10(A,B,C,D,E,F,G,H,I,J)								 char* A,  char* B,  char* C,  char* D,  char* E,  char* F,  char* G,  char* H,  char* I,  char* J
#define V_str11(A,B,C,D,E,F,G,H,I,J,K)								 char* A,  char* B,  char* C,  char* D,  char* E,  char* F,  char* G,  char* H,  char* I,  char* J,  char* K
#define V_str12(A,B,C,D,E,F,G,H,I,J,K,L)							 char* A,  char* B,  char* C,  char* D,  char* E,  char* F,  char* G,  char* H,  char* I,  char* J,  char* K,  char* L
#define V_str13(A,B,C,D,E,F,G,H,I,J,K,L,M)							 char* A,  char* B,  char* C,  char* D,  char* E,  char* F,  char* G,  char* H,  char* I,  char* J,  char* K,  char* L,  char* M
#define V_str14(A,B,C,D,E,F,G,H,I,J,K,L,M,N)						 char* A,  char* B,  char* C,  char* D,  char* E,  char* F,  char* G,  char* H,  char* I,  char* J,  char* K,  char* L,  char* M,  char* N
#define V_str15(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O)						 char* A,  char* B,  char* C,  char* D,  char* E,  char* F,  char* G,  char* H,  char* I,  char* J,  char* K,  char* L,  char* M,  char* N,  char* O
#define V_str16(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P)					 char* A,  char* B,  char* C,  char* D,  char* E,  char* F,  char* G,  char* H,  char* I,  char* J,  char* K,  char* L,  char* M,  char* N,  char* O,  char* P
#define V_str17(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q)					 char* A,  char* B,  char* C,  char* D,  char* E,  char* F,  char* G,  char* H,  char* I,  char* J,  char* K,  char* L,  char* M,  char* N,  char* O,  char* P,  char* Q
#define V_str18(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R)				 char* A,  char* B,  char* C,  char* D,  char* E,  char* F,  char* G,  char* H,  char* I,  char* J,  char* K,  char* L,  char* M,  char* N,  char* O,  char* P,  char* Q,  char* R
#define V_str19(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S)				 char* A,  char* B,  char* C,  char* D,  char* E,  char* F,  char* G,  char* H,  char* I,  char* J,  char* K,  char* L,  char* M,  char* N,  char* O,  char* P,  char* Q,  char* R,  char* S
#define V_str20(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T)			 char* A,  char* B,  char* C,  char* D,  char* E,  char* F,  char* G,  char* H,  char* I,  char* J,  char* K,  char* L,  char* M,  char* N,  char* O,  char* P,  char* Q,  char* R,  char* S,  char* T
#define V_str21(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U)			 char* A,  char* B,  char* C,  char* D,  char* E,  char* F,  char* G,  char* H,  char* I,  char* J,  char* K,  char* L,  char* M,  char* N,  char* O,  char* P,  char* Q,  char* R,  char* S,  char* T,  char* U
#define V_str22(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V)		 char* A,  char* B,  char* C,  char* D,  char* E,  char* F,  char* G,  char* H,  char* I,  char* J,  char* K,  char* L,  char* M,  char* N,  char* O,  char* P,  char* Q,  char* R,  char* S,  char* T,  char* U,  char* V
#define V_str23(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W)		 char* A,  char* B,  char* C,  char* D,  char* E,  char* F,  char* G,  char* H,  char* I,  char* J,  char* K,  char* L,  char* M,  char* N,  char* O,  char* P,  char* Q,  char* R,  char* S,  char* T,  char* U,  char* V,  char* W
#define V_str24(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X)	 char* A,  char* B,  char* C,  char* D,  char* E,  char* F,  char* G,  char* H,  char* I,  char* J,  char* K,  char* L,  char* M,  char* N,  char* O,  char* P,  char* Q,  char* R,  char* S,  char* T,  char* U,  char* V,  char* W,  char* X
#define V_str25(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y)	 char* A,  char* B,  char* C,  char* D,  char* E,  char* F,  char* G,  char* H,  char* I,  char* J,  char* K,  char* L,  char* M,  char* N,  char* O,  char* P,  char* Q,  char* R,  char* S,  char* T,  char* U,  char* V,  char* W,  char* X,  char* Y
#define V_str26(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z) char* A,  char* B,  char* C,  char* D,  char* E,  char* F,  char* G,  char* H,  char* I,  char* J,  char* K,  char* L,  char* M,  char* N,  char* O,  char* P,  char* Q,  char* R,  char* S,  char* T,  char* U,  char* V,  char* W,  char* X,  char* Y,  char* Z

#define V_z(A)														 void A
#define V_z2(A,B)													 void A,  void B
#define V_z3(A,B,C)													 void A,  void B,  void C
#define V_z4(A,B,C,D)												 void A,  void B,  void C,  void D
#define V_z5(A,B,C,D,E)												 void A,  void B,  void C,  void D,  void E
#define V_z6(A,B,C,D,E,F)											 void A,  void B,  void C,  void D,  void E,  void F
#define V_z7(A,B,C,D,E,F,G)											 void A,  void B,  void C,  void D,  void E,  void F,  void G
#define V_z8(A,B,C,D,E,F,G,H)										 void A,  void B,  void C,  void D,  void E,  void F,  void G,  void H
#define V_z9(A,B,C,D,E,F,G,H,I)										 void A,  void B,  void C,  void D,  void E,  void F,  void G,  void H,  void I
#define V_z10(A,B,C,D,E,F,G,H,I,J)									 void A,  void B,  void C,  void D,  void E,  void F,  void G,  void H,  void I,  void J
#define V_z11(A,B,C,D,E,F,G,H,I,J,K)								 void A,  void B,  void C,  void D,  void E,  void F,  void G,  void H,  void I,  void J,  void K
#define V_z12(A,B,C,D,E,F,G,H,I,J,K,L)								 void A,  void B,  void C,  void D,  void E,  void F,  void G,  void H,  void I,  void J,  void K,  void L
#define V_z13(A,B,C,D,E,F,G,H,I,J,K,L,M)							 void A,  void B,  void C,  void D,  void E,  void F,  void G,  void H,  void I,  void J,  void K,  void L,  void M
#define V_z14(A,B,C,D,E,F,G,H,I,J,K,L,M,N)							 void A,  void B,  void C,  void D,  void E,  void F,  void G,  void H,  void I,  void J,  void K,  void L,  void M,  void N
#define V_z15(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O)						 void A,  void B,  void C,  void D,  void E,  void F,  void G,  void H,  void I,  void J,  void K,  void L,  void M,  void N,  void O
#define V_z16(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P)						 void A,  void B,  void C,  void D,  void E,  void F,  void G,  void H,  void I,  void J,  void K,  void L,  void M,  void N,  void O,  void P
#define V_z17(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q)					 void A,  void B,  void C,  void D,  void E,  void F,  void G,  void H,  void I,  void J,  void K,  void L,  void M,  void N,  void O,  void P,  void Q
#define V_z18(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R)					 void A,  void B,  void C,  void D,  void E,  void F,  void G,  void H,  void I,  void J,  void K,  void L,  void M,  void N,  void O,  void P,  void Q,  void R
#define V_z19(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S)				 void A,  void B,  void C,  void D,  void E,  void F,  void G,  void H,  void I,  void J,  void K,  void L,  void M,  void N,  void O,  void P,  void Q,  void R,  void S
#define V_z20(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T)				 void A,  void B,  void C,  void D,  void E,  void F,  void G,  void H,  void I,  void J,  void K,  void L,  void M,  void N,  void O,  void P,  void Q,  void R,  void S,  void T
#define V_z21(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U)			 void A,  void B,  void C,  void D,  void E,  void F,  void G,  void H,  void I,  void J,  void K,  void L,  void M,  void N,  void O,  void P,  void Q,  void R,  void S,  void T,  void U
#define V_z22(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V)			 void A,  void B,  void C,  void D,  void E,  void F,  void G,  void H,  void I,  void J,  void K,  void L,  void M,  void N,  void O,  void P,  void Q,  void R,  void S,  void T,  void U,  void V
#define V_z23(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W)		 void A,  void B,  void C,  void D,  void E,  void F,  void G,  void H,  void I,  void J,  void K,  void L,  void M,  void N,  void O,  void P,  void Q,  void R,  void S,  void T,  void U,  void V,  void W
#define V_z24(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X)		 void A,  void B,  void C,  void D,  void E,  void F,  void G,  void H,  void I,  void J,  void K,  void L,  void M,  void N,  void O,  void P,  void Q,  void R,  void S,  void T,  void U,  void V,  void W,  void X
#define V_z25(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y)	 void A,  void B,  void C,  void D,  void E,  void F,  void G,  void H,  void I,  void J,  void K,  void L,  void M,  void N,  void O,  void P,  void Q,  void R,  void S,  void T,  void U,  void V,  void W,  void X,  void Y
#define V_z26(A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z)	 void A,  void B,  void C,  void D,  void E,  void F,  void G,  void H,  void I,  void J,  void K,  void L,  void M,  void N,  void O,  void P,  void Q,  void R,  void S,  void T,  void U,  void V,  void W,  void X,  void Y,  void Z
//..................................................................................................................
/*	Color constants


	These color constants are just a shorthand way of writing common RGB values.
*/

//Primary, Secondary, and grays (in the compu-spectrum)
#define COLOR_RED				0xff, 0x00, 0x00
#define COLOR_GREEN				0x00, 0xff, 0x00
#define COLOR_BLUE				0x00, 0x00, 0xff
#define COLOR_YELLOW			0xff, 0xff, 0x00
#define COLOR_PURPLE			0xff, 0x00, 0xff
#define COLOR_CYAN				0x00, 0xff, 0xff
#define COLOR_GRAY				0x7f, 0x7f, 0x7f

#define COLOR_LIGHT_RED			0xff, 0x7f, 0x7f
#define COLOR_LIGHT_GREEN		0x7f, 0xff, 0x7f
#define COLOR_LIGHT_BLUE		0x7f, 0x7f, 0xff
#define COLOR_LIGHT_YELLOW		0xff, 0xff, 0x7f
#define COLOR_LIGHT_PURPLE		0xff, 0x7f, 0xff
#define COLOR_LIGHT_CYAN		0x7f, 0xff, 0xff
#define COLOR_LIGHT_GRAY		0xbf, 0xbf, 0xbf

#define COLOR_DARK_RED			0x7f, 0x00, 0x00
#define COLOR_DARK_GREEN		0x00, 0x7f, 0x00
#define COLOR_DARK_BLUE			0x00, 0x00, 0x7f
#define COLOR_DARK_YELLOW		0x7f, 0x7f, 0x00
#define COLOR_DARK_PURPLE		0x7f, 0x00, 0x7f
#define COLOR_DARK_CYAN			0x00, 0x7f, 0x7f
#define COLOR_DARK_GRAY			0x3f, 0x3f, 0x3f

#define COLOR_GRAY_0			0x00, 0x00, 0x00
#define COLOR_GRAY_1			0x10, 0x10, 0x10
#define COLOR_GRAY_2			0x20, 0x20, 0x20
#define COLOR_GRAY_3			0x30, 0x30, 0x30
#define COLOR_GRAY_4			0x40, 0x40, 0x40
#define COLOR_GRAY_5			0x50, 0x50, 0x50
#define COLOR_GRAY_6			0x60, 0x60, 0x60
#define COLOR_GRAY_7			0x70, 0x70, 0x70
#define COLOR_GRAY_8			0x80, 0x80, 0x80
#define COLOR_GRAY_9			0x90, 0x90, 0x90
#define COLOR_GRAY_A			0xa0, 0xa0, 0xa0
#define COLOR_GRAY_B			0xb0, 0xb0, 0xb0
#define COLOR_GRAY_C			0xc0, 0xc0, 0xc0
#define COLOR_GRAY_D			0xd0, 0xd0, 0xd0
#define COLOR_GRAY_E			0xe0, 0xe0, 0xe0
#define COLOR_GRAY_F			0xf0, 0xf0, 0xf0

#define COLOR_BLACK				0x00, 0x00, 0x00
#define COLOR_WHITE				0xff, 0xff, 0xff

//Oranges & Browns
#define COLOR_ORANGE			0xff, 0x80, 0x00
#define COLOR_LIGHT_ORANGE		0xff, 0xbf, 0x80
#define COLOR_DARK_ORANGE		0xbf, 0x5f, 0x00

#define COLOR_BROWN				0xa5, 0x7b, 0x48
#define COLOR_LIGHT_BROWN		0xa5, 0x93, 0x7c
#define COLOR_DARK_BROWN		0x59, 0x45, 0x2c

//..................................................................................................................
/*	Direction constants

	These constants associate direction with a numerical value
*/
enum ASFC_DIRECTION
{	DIR_NORTH		=	0,
	DIR_NORTH_WEST,
	DIR_NORTH_EAST,
       
	DIR_SOUTH,
	DIR_SOUTH_WEST,
	DIR_SOUTH_EAST,
       
	DIR_WEST,
	DIR_EAST,
       
	DIR_UP,
	DIR_DOWN,
	DIR_LEFT,
	DIR_RIGHT,
       
	DIR_X_POS,
	DIR_X_NEG,
	DIR_Y_POS,
	DIR_Y_NEG,
	DIR_Z_POS,
	DIR_Z_NEG,
       
	DIR_QUAD_1,
	DIR_QUAD_2,
	DIR_QUAD_3,
	DIR_QUAD_4,
       
	DIR_CLOCKWISE,
	DIR_COUNTER_CLOCKWISE,
       
	DIR_WITH,
	DIR_AGAINST,
       
	DIR_DOWNSTREAM,
	DIR_UPSTREAM,

	DIR_IDLE
};


//..................................................................................................................
/*	True\False constants

	These constants hold bool values.
*/

#define YES			true
#define NO			false

#define AFFIRMATIVE	true
#define NEGATIVE	false

#define ON			true
#define OFF			false

#define GO			true
#define STOP		false

//..................................................................................................................
//Angular Constants
const 	double	ANGLE_0  			= 0.0;
const	double	ANGLE_PIovr6		= 0.5235987756;
const	double	ANGLE_PIover4		= 0.7853981634;
const	double	ANGLE_PIover3		= 1.047197551;
const	double	ANGLE_PIover2		= 1.570796327;
const	double	ANGLE_2PIover3		= 2.094395102;
const	double	ANGLE_3PIover4		= 2.35619449;
const	double	ANGLE_5PIover6		= 2.617993878;
const	double	ANGLE_PI			= 3.141592654;
const	double	ANGLE_7PIover6		= 5.497787144;
const	double	ANGLE_5PIover4		= 3.926990817;
const	double	ANGLE_4PIover3		= 4.188790205;
const	double	ANGLE_3PIover2		= 4.71238898;
const	double	ANGLE_5PIover3		= 5.235987756;
const	double	ANGLE_7PIover4		= 5.497787144;
const	double	ANGLE_11PIover6		= 5.759586532;
const	double	ANGLE_2PI			= 6.283185307;
//..................................................................................................................
/*	Returns

	These constants hold common return values that functions may use
*/
enum ASFC_RETURN
{	RETURN_GOOD   = 0,
	RETURN_BAD    = -1,
	RETURN_DEBUG  = 10
};
//..................................................................................................................
/*	UnTypeable Characters

	These constants hold some important characters that can't usually be typed easily. NOTICE:
	these chars are for ANSI fonts!
*/
const char CH_ENDL					= '\n';
const char CH_TAB					= '\t';
const char CH_BELL					= '\a';
const char CH_SPACE					= ' ';
const char CH_CENTS					= '¢';
const char CH_POUNDS				= '£';
const char CH_YEN					= '¥';
const char CH_COPYRIGHT				= '©';
const char CH_RIGHTSRESERVED		= '®';
const char CH_DEGREES				= '°';
const char CH_PLUSORMINUS			= '±';
const char CH_SQUARED				= '²';
const char CH_CUBED					= '³';
const char CH_PARAGRAPH				= '¶';
const char CH_DOT					= '·';
const char CH_1OVER4				= '¼';
const char CH_1OVER2				= '½';
const char CH_3OVER4				= '¾';
const char CH_INVERSEQUESTION		= '¿';
const char CH_DIVIDE				= '÷';
//..................................................................................................................
//Prototypes of various helper functions (String manipulation mostly)
string UpperString(string s);				//Returns s in all caps
string LowerString(string s);				//Returns s in all lowers
string Val(double d);			  			//Converts a value to a string
double Val(string s);		 	  			//Converts a string to a value
string Rot(int iChars, string s); 			//Rotates all the chars iChars down in a string
void SToStr(string s, char* str); 			//Converts a C++ string to an C string
void RangeCheck(int i, int iMin, int iMax, string sFunction, string sVar, int iErrCode);	//Range checks variable i (inclusive min & max)
string Qoute(string s);						//Returns string s surrounded with qoutes
string ReadString(ifstream &oFile); 		//Reads in a string surrounded by double qoutes (or any other set of characters) from a ifstream
bool FileExist(string sFile);				//Returns true if sFile is a valid file

#endif
