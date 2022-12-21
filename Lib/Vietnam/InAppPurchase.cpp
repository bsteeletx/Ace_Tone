#include "InAppPurchase.h"
#include "agk.h"

InAppPurchase::InAppPurchase(Text Title, Text AppID, bool isConsumable)
{
#if (OS == IOS)
	_SetTitle(Title);
	_AddProductID(AppID, isConsumable);
	_Setup();
	_purchaseID = 0;
#endif
}


InAppPurchase::~InAppPurchase(void)
{
}

#if (OS == IOS)
void InAppPurchase::Activate(unsigned int ID)
{
	agk::InAppPurchaseActivate(ID);
}

bool InAppPurchase::GetAvailable(int ID)
{
	return (bool) agk::GetInAppPurchaseAvailable(ID);
}

bool InAppPurchase::GetState(void)
{
	return (bool) agk::GetInAppPurchaseState();
}

#if OS == IOS
////////////////////////////////////////////
// Restores any managed purchases made on this platform. 
// For example if a user purchased at item then reinstalled the app the app would return 0 for GetInAppPurchaseAvailable unless it was purchased again. 
// Even though this wouldn't charge the user again for managed items, 
// Apple require you to have a button that calls this function instead of making the user go through the purchase process again. 
// After calling this command you can call GetInAppPurchaseAvailable 
// Currently this command is only supported on iOS. 
// This command is unneccesary on Android as it automatically restores in InAppPurchaseSetup
//////////////////////////////////////
void InAppPurchase::Restore(void)
{
	agk::InAppPurchaseRestore();
}
#endif 

//////////////////////////////
// Use this command to add any product IDs into the list e.g. com.yourcompany.yourproduct.iap. 
// The first product ID you add becomes 0, 
// the second is 1 etc. You must also specify the type of product this is, consumable (1) or non-consumable(0). 
// Consumable products are like coins that can be bought again and again, 
// they are called Unmanaged items by Google Play. 
// Non-consumable products are one off purchases like unlocking the full version of an app, 
// they are called managed items by Google Play. 
// Currently this command is only supported on iOS and Android.
///////////////////////////////////
void InAppPurchase::_AddProductID(Text ProductID, bool isConsumable)
{
	char normalized[64] = {""};

	strcpy(normalized, ProductID.GetCString());

	agk::InAppPurchaseAddProductID(normalized, (int)isConsumable);
}

void InAppPurchase::_SetTitle(Text Title)
{
	char normalized[64] = {""};

	strcpy(normalized, Title.GetCString());

	agk::InAppPurchaseSetTitle(normalized);
}
	
void InAppPurchase::_Setup(void)
{
	agk::InAppPurchaseSetup();
}

#endif