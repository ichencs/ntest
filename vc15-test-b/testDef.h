#pragma once
//#pragma execution_character_set("utf-8")

/***
 * Filename:@OutputName.h
 * Author: Chencs
 * version     @MM/@dd/@yyyy 
 * date: 
 ***/

template <class T> inline T MyMin(T a, T b) { return a < b ? a : b; }
template <class T> inline T MyMax(T a, T b) { return a > b ? a : b; }

template <class T> inline int MyCompare(T a, T b)
{
	return a == b ? 0 : (a < b ? -1 : 1);
}

inline int BoolToInt(bool v) { return (v ? 1 : 0); }
inline bool IntToBool(int v) { return (v != 0); }