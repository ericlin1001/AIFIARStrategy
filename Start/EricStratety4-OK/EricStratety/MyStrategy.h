#ifndef __MYSTRATEGY_H__
#define __MYSTRATEGY_H__
#include "strategy.h"
#include "base.h"
class Strategy:public StrategyBasis{
public:

protected:
	virtual void PreProcess();
	virtual void DecisionMaking();
	
	virtual void PostProcess();
};
#endif
