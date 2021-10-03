#pragma once

#define function_overwrite(offset, function)\
void ASM_##function() {\
	asm(".intel_syntax \n"\
		"call "#function" \n"\
		"retn \n"\
	);\
}\
void setup_##function() {\
	WriteFarJMP(Offset(base, offset), (void*)&ASM_##function);\
}

#define function_setup(function) setup_##function();