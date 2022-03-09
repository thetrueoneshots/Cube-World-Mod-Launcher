#pragma once
#include "../../CWSDK/cwsdk.h"

int GoldBagValue(cube::Item* item)
{
	int retval;

	/*_asm
	{
		"mov     ecx, [rcx + cube::Item.modifier]\n"
		"xorps   xmm1, xmm1						 \n"
		"add     ecx, 0CC72Fh					 \n"
		"mov     eax, ecx						 \n"
		"shl     eax, 0Dh						 \n"
		"xor ecx, eax							 \n"
		"mov     eax, ecx						 \n"
		"shr     eax, 11h						 \n"
		"xor ecx, eax							 \n"
		"mov     eax, ecx						 \n"
		"shl     eax, 5							 \n"
		"xor ecx, eax							 \n"
		"mov     eax, 4F8B588Fh					 \n"
		"mul     ecx							 \n"
		"mov     eax, ecx						 \n"
		"sub     eax, edx						 \n"
		"shr     eax, 1							 \n"
		"add     eax, edx						 \n"
		"shr     eax, 10h						 \n"
		"imul    eax, 186A0h					 \n"
		"sub     ecx, eax						 \n"
		"mov     eax, ecx						 \n"
		"cvtsi2ss xmm1, rax						 \n"
		"movzx   eax, [r8 + cube::Item.rarity]	 \n"
		"inc     eax							 \n"
		"movd    xmm0, eax						 \n"
		"divss   xmm1, cs:dword_43800C			 \n"
		"cvtdq2ps xmm0, xmm0					 \n"
		"addss   xmm1, xmm0						 \n"
		"mulss   xmm1, cs:dword_42E598			 \n"
		"cvttss2si eax, xmm1					 \n"
		"retn									 \n"
	}*/

	return retval;
}

extern "C" int cube__Item__OnGetGoldBagValue(cube::Item * item)
{
	if (item->category != 31)
	{
		return 0;
	}

	int value = 100;

	for (uint8_t priority = 0; priority <= 4; priority += 1) {
		for (DLL* dll : modDLLs) {
			if (dll->mod->OnItemGetGoldBagValuePriority == (GenericMod::Priority)priority) {
				dll->mod->OnItemGetGoldBagValue(item, &value);
			}
		}
	}

	return value;
}

overwrite_function(0x109070, cube__Item__OnGetGoldBagValue)