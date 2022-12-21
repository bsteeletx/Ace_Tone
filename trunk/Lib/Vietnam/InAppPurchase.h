#pragma once

#include "Text.h"
#include "Defines.h"

class InAppPurchase
{
public:
	InAppPurchase(Text Title, Text AppID, bool isConsumable);
	~InAppPurchase(void);
#if (OS != WINDOWS)
	void Activate(unsigned int ID);
	
	bool GetAvailable(int ID);
	bool GetState(void);

	void Restore(void); 

private:
	unsigned int _purchaseID;

	void _AddProductID(Text productID, bool isConsumable);

	void _SetTitle(Text Title);
	void _Setup(void);
#endif
};

