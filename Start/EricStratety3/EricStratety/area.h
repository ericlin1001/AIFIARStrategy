/**************************************************************************************************** 
area.h ��������������ͷ�ļ� 
 
Purpose: 
	��������� 
 
author: 
	yy_cn 
 
Created Time: 
	2006-5-11 
****************************************************************************************************/ 
 
#ifndef __ROBOT_AREA_H__ 
#define __ROBOT_AREA_H__ 
 
#include "base.h" 
#include <vector>
using namespace std;
//////////////////////////////////////////////////////////////////////////////////////////////////// 
// 
// ������Ϣ 
// 
class AreaInfo 
{ 
public: 
	/** 
		* x1,y1 - x2,y2 ���������������ϵ�һ���ֲ����� 
		* area ��ǰ���� 
		*/ 
	AreaInfo (double x1, double y1, double x2, double y2, BallArea area) 
		: _x1 (x1) 
		, _y1 (y1) 
		, _x2 (x2) 
		, _y2 (y2) 
		, _area (area) 
	{ 
	} 
	~AreaInfo (void) 
	{ 
	} 
	 
	/** 
	 * x,y ���Ƿ��ڵ�ǰ������ 
	 */ 
	bool isInside (double x, double y) 
	{ 
		if (x >= _x1 && x <= _x2 && y <= _y1 && y >= _y2) 
			return true; 
		else 
			return false; 
	} 
 
	/** 
	 * ���������ĸ������ 
	 */ 
	void getPos (double &x1, double &y1, double &x2, double &y2) 
	{ 
		x1 = _x1; 
		y1 = _y1; 
		x2 = _x2; 
		y2 = _y2; 
	} 
	 
	BallArea getArea (void) const 
	{ 
		return _area; 
	} 
 
protected: 
	double  _x1, 
			_y1, 
			_x2, 
			_y2; 
	BallArea _area; 
}; // end class AreaInfo 
 
//////////////////////////////////////////////////////////////////////////////////////////////////// 
// 
// ������� 
// 
class AreaManager 
{ 
public: 
	AreaManager (void); 
	~AreaManager (void); 
 
	/** 
	 * ���һ������ 
	 */ 
	void addArea (double x1, double y1, double x2, double y2, BallArea area); 
	/** 
	 * ��� x,y ���ڵ����� 
	 */ 
	const AreaInfo *getArea (double x, double y); 
	 
protected:	 
	vector<AreaInfo *> areas; 
}; // end class AreaManager 
 
#endif // __ROBOT_AREA_H__