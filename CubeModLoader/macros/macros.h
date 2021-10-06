#pragma once

#define overwrite_function(offset, function)\
void ASM_##function() {\
	asm(".intel_syntax \n"\
		"call "#function" \n"\
		"retn \n"\
	);\
}\
void setup_##function() {\
	WriteFarJMP(Offset(base, offset), (void*)&ASM_##function);\
}

#define setup_function(function) setup_##function();