/**************************************************************************************************** 
area.h 艾数机器人区域头文件 
 
Purpose: 
	球场区域管理 
 
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
// 区域信息 
// 
class AreaInfo 
{ 
public: 
	/** 
		* x1,y1 - x2,y2 两个点描述出球场上的一个局部区域 
		* area 当前区域 
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
	 * x,y 点是否在当前区域内 
	 */ 
	bool isInside (double x, double y) 
	{ 
		if (x >= _x1 && x <= _x2 && y <= _y1 && y >= _y2) 
			return true; 
		else 
			return false; 
	} 
 
	/** 
	 * 获得区域的四个坐标点 
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
// 区域管理 
// 
class AreaManager 
{ 
public: 
	AreaManager (void); 
	~AreaManager (void); 
 
	/** 
	 * 添加一个区域 
	 */ 
	void addArea (double x1, double y1, double x2, double y2, BallArea area); 
	/** 
	 * 获得 x,y 所在的区域 
	 */ 
	const AreaInfo *getArea (double x, double y); 
	 
protected:	 
	vector<AreaInfo *> areas; 
}; // end class AreaManager 
 
#endif // __ROBOT_AREA_H__