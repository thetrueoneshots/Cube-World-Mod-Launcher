#pragma once
#include "../../CWSDK/cwsdk.h"

extern "C" int cube__Item__OnGetSellingPrice(cube::Item* item)
{
	int buyingPrice = item->GetBuyingPrice();
	int sellingPrice = std::max<float>(0.5f * std::sqrt(buyingPrice), 1);

	for (uint8_t priority = 0; priority <= 4; priority += 1) {
		for (DLL* dll : modDLLs) {
			if (dll->mod->OnGetItemSellingPricePriority == (GenericMod::Priority)priority) {
				dll->mod->OnGetItemSellingPrice(item, &sellingPrice);
			}
		}
	}

	return sellingPrice;
}

overwrite_function(0x10A390, cube__Item__OnGetSellingPrice)