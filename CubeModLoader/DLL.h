#ifndef DLL_H
#define DLL_H
#include <iostream>
#include <windows.h>
#define MODLOADER 1
#include "CWSDK/cwsdk.h"
//#include "GenericMod.h"

class DLL
{
    public:
        std::string fileName;
        HMODULE handle;

        FARPROC ModPreInitialize;
        FARPROC ModMajorVersion;
        FARPROC ModMinorVersion;
		FARPROC MakeMod;

		GenericMod* mod;
        bool enabled;

        DLL(std::string fileName);
        HMODULE Load();
        virtual ~DLL();

    protected:

    private:
};

#endif // DLL_H
