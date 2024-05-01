// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "bot.h"
#include "board.h"

/*
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}*/

extern "C" __declspec(dllexport) void* NewBoard()
{
    return (void*) new Board();
}

extern "C" __declspec(dllexport) void BoardSetPiece(Board b, int r, int f, int p)
{
    b.setPiece(r, f, (BoardPiece)p);
}

extern "C" __declspec(dllexport) char* BoardGetPlacement(Board b)
{

    return b.getPlacement();
}

extern "C" __declspec(dllexport) void* NewBot()
{
    return (void*) new Bot();
}

extern "C" __declspec(dllexport) int SuggestColumn(Bot bot)
{
    return bot.suggestColumn();
}