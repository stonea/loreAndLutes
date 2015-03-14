#ifndef LOOP_MACROS_H_
#define LOOP_MACROS_H_

//..................................................................................................................
/*AMLPORT: This macro creates a LOOP callback function and a static port to this function.
A = Name of static port
B = Class of the callback
C = Member Callback
*/

#define LOOPPORT(A, B, C) static void A(LOOP_Info oInfo, void* poCall) {B* mypCall = (B*)poCall; mypCall->C(oInfo);} void C(LOOP_Info)

#endif
