#pragma once

#define overwrite_function(offset, function)\
__attribute__((naked)) void ASM_##function() {\
	asm(".intel_syntax \n" \
		"push rbp \n" \
		"mov rbp, rsp \n" \
		"call "#function" \n"\
		"mov rsp, rbp \n" \
		"pop rbp \n" \
		"retn \n"\
	);\
}\
void setup_##function() {\
	WriteFarJMP(Offset(base, offset), (void*)&ASM_##function);\
}

#define overwrite_function_w_jmp(offset, function, ret)\
GETTER_VAR(void*, ASM_##function_jmpback); \
__attribute__((naked)) void ASM_##function() {\
	asm(".intel_syntax \n" \
		PUSH_ALL \
		"push rbp \n" \
		"mov rbp, rsp \n" \
		PREPARE_STACK \
		"call "#function" \n"\
		RESTORE_STACK \
		"mov rsp, rbp \n" \
		"pop rbp \n" \
		POP_ALL \
		DEREF_JMP(ASM_##function_jmpback) \
	);\
}\
void setup_##function() {\
	WriteFarJMP(Offset(base, offset), (void*)&ASM_##function);\
	ASM_##function_jmpback = Offset(base, ret); \
}

#define setup_function(function) setup_##function()