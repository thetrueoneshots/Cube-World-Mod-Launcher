#pragma once
#include "cwsdk.h"

extern "C" void cube__Item__GetBuyingPrice(cube::Item* item, int* price)
{
	for (uint8_t priority = 0; priority <= 4; priority += 1) {
		for (DLL* dll : modDLLs) {
			if (dll->mod->OnGetItemBuyingPricePriority == (GenericMod::Priority)priority) {
				dll->mod->OnGetItemBuyingPrice(item, price);
			}
		}
	}
}

extern "C" float powf(float a1, float a2)
{
	return std::powf(a1, a2);
}

__attribute__((naked)) void ASM_cube__Item__GetBuyingPrice() {
		asm(".intel_syntax \n"
			
			// Save r8 before calling powf
			"push	r8 \n"
			"call	powf \n"
			"pop	r8 \n"
			"mulss  xmm0, xmm6 \n"
			"mov    eax, 1 \n"
			"movaps xmm6, xmmword ptr [rsp+0x20] \n"

			// Old code
			"cvttss2si ecx, xmm0 \n"
			"cmp     ecx, eax \n"
			"cmovg   eax, ecx \n"

			// Get price pointer
			"push	rax \n"
			"lea	rdx, [rsp] \n"
			"mov	rcx, r8 \n"
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