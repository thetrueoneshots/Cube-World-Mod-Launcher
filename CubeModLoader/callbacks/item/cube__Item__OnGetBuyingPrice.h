#pragma once
#include "cwsdk.h"

extern "C" void cube__Item__GetBuyingPrice(float base_cost, cube::Item* item, int* price)
{
	*price = std::max<int>(base_cost * std::powf(2, item->rarity), 1);

	for (uint8_t priority = 0; priority <= 4; priority += 1) {
		for (DLL* dll : modDLLs) {
			if (dll->mod->OnGetItemBuyingPricePriority == (GenericMod::Priority)priority) {
				dll->mod->OnGetItemBuyingPrice(item, price);
			}
		}
	}
}

__attribute__((naked)) void ASM_cube__Item__GetBuyingPrice() {
		asm(".intel_syntax \n"
			
			"movaps xmm0, xmm6 \n"
			"movaps xmm6, xmmword ptr [rsp+0x20] \n"

			"push	rax \n"
			"mov	rdx, r8 \n" // Item pointer
			"lea	r8, [rsp] \n" // Price pointer

			PREPARE_STACK
			"call cube__Item__GetBuyingPrice \n"
			RESTORE_STACK
			"pop rax \n"

			// Old code and return
			"add	rsp, 0x38 \n"
			"retn \n"
		);
}

void setup_cube__Item__GetBuyingPrice() {
    WriteFarJMP(CWOffset(0x109E0E), ASM_cube__Item__GetBuyingPrice);
}