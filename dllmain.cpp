#include <Windows.h>
#include <iostream>
#include <vector>

HMODULE HMOD;

    constexpr uintptr_t GNAMES = 0x34F9798;
    constexpr uintptr_t GWORLD = 0x35E9B38;
    constexpr uintptr_t nop    = 0x027E850;
    constexpr uintptr_t decax =  0x02900EC;

void coninit(const char* title) 
{
    AllocConsole();

    freopen_s(reinterpret_cast<_iobuf**>(__acrt_iob_func(0)), "conin$", "r", static_cast<_iobuf*>(__acrt_iob_func(0)));
    freopen_s(reinterpret_cast<_iobuf**>(__acrt_iob_func(1)), "conout$", "w", static_cast<_iobuf*>(__acrt_iob_func(1)));
    freopen_s(reinterpret_cast<_iobuf**>(__acrt_iob_func(2)), "conout$", "w", static_cast<_iobuf*>(__acrt_iob_func(2)));

    SetConsoleTitleA(title);
}

void freeconsole() 
{
    fclose(static_cast<_iobuf*>(__acrt_iob_func(0)));
    fclose(static_cast<_iobuf*>(__acrt_iob_func(1)));
    fclose(static_cast<_iobuf*>(__acrt_iob_func(2)));

    FreeConsole();
}

bool GetGName(int id, char* outname, uintptr_t GNames)
{
    DWORD_PTR chunk = *(DWORD_PTR*)(GNames + (id / 0x4000) * 8);
    if (!chunk)
        return false;
    DWORD_PTR nameptr = *(DWORD_PTR*)(chunk + (8 * (id % 0x4000)));
    if (!nameptr)
        return false;

    int str_len = 0;
    while (true)
    {
        char c = *(char*)(nameptr + 0x10 + str_len);
        if (c == 0x0 || str_len > 32)
            break;
        str_len++;
    }
    memcpy(outname, (LPVOID)(nameptr + 0x10), str_len);
    return true;
}

template <class T>
struct TArray
{
    inline T& operator[](int i)
    {
        return Data[i];
    };

    inline const T& operator[](int i) const
    {
        return Data[i];
    };

    T* Data;
    int count;
    int max;
};

struct aactor {
    char buf0[0x18]; // 0x0
    int id; //0x18
    char buf1[0xCC4]; //0x1c
    bool binvulnerable; // 0xCE0
    char buf2[0x178]; // 0xCE1
    bool xray_enabled; // 0xE59
};


struct Ulevel {
    char buf[0xa0];
    TArray<aactor*> Entitylist; // 0xa0
};

struct ULocalPlayer;

struct playercontroller {
    char buf[0x3b0]; // 358 or 3a8 or 3b0
    aactor* pawn;
};

struct Ugameinstance {
    byte pad[0x10];
    TArray<ULocalPlayer*> LocalPlayers;
};

struct Uworld {
    char __pad0x30[0x30];
    Ulevel* m_pULevel;
    char __pad0x108[0x158];
    Ugameinstance* gameinstance;
};

struct UGameViewportClient {
    char pad[0x78];
    Uworld* world;
};

struct ULocalPlayer
{
    char pad[0x30];
    playercontroller* playercontroller;
    char pad0[0x38];
    UGameViewportClient* ViewportClient;

};

struct gun {
    char buf[0x6AC];
    float firerate;
    byte firemode;
};

enum firemode : uint8_t 
{
    Semi = 0,
    Automatic = 1,
    Manual = 2,
    Burst = 3,
};
bool shouldrun = true;

namespace id {
    int pawn;
    int galil;
    int at;
    int tec9;
}

bool havematch(int a, std::vector<int> v, void(*func)(void*), void* ptr){
    for (int i = 0; i < v.size(); i++)
        if (v[i] == a) {
            (*func)(ptr);
            return true;
        }
    return false;
}

void xray(void* ptr) 
{
    aactor* pawn = (aactor*)ptr;
    pawn->xray_enabled = 1;
}

void rapid_fire(void* ptr)
{
    gun* g = (gun*)ptr;
    g->firemode = 1;
    g->firerate = 0.01f;
}

void mainthread() 
{

    uintptr_t base = 0;
    while (!base)
        base = (uintptr_t)GetModuleHandleA(0);
    auto pgnames = reinterpret_cast<uintptr_t*>(GNAMES + base);
    auto pgworld = reinterpret_cast<uintptr_t*>(GWORLD + base);
    bool infammo = 0;
    bool xray = 0;
    bool godmode = 0;
    coninit("console");

    for (int i = 0; i < 140'000; i++) {
        char buf[150]{ 0 };
        GetGName(i, buf, *pgnames);
        if (!strcmp(buf, "BP_PavlovPawn_C")) {
            id::pawn = i;
            printf("%s, %i\n", buf, i);
        }
        else if (!strcmp(buf, "Gun_Galil_C")) {
            id::galil = i;
            printf("%s, %i\n", buf, i);
        }
        else if (!strcmp(buf, "Gun_AntiTank_C")) {
            id::at = i;
            printf("%s, %i\n", buf, i);
        }
        else if (!strcmp(buf, "Gun_Cet9_C")) {
            id::tec9 = i;
            printf("%s, %i\n", buf, i);
        }
    }

    while (true) {
        Sleep(10); /* 90 hertz */
        
        if (GetAsyncKeyState(VK_F1) & 1) {
            infammo = !infammo;
            printf("infammo %i\n",  infammo);
            if (infammo) {
                byte buffer[] = { 0x90, 0x90 , 0xC6, 0x04, 0x10, 0x01 };
                WriteProcessMemory(GetCurrentProcess(), (LPVOID)(nop + base), buffer, sizeof(buffer), 0);
                byte buffer0[] = { 0x90, 0x90 , 0x90};
                WriteProcessMemory(GetCurrentProcess(), (LPVOID)(decax + base), buffer0, sizeof(buffer0), 0);
            } else {
                byte buffer[] = { 0x74, 0x23 , 0xC6, 0x04, 0x10, 0x02 };
                WriteProcessMemory(GetCurrentProcess(), (LPVOID)(nop + base), buffer, sizeof(buffer), 0);
                byte buffer0[] = { 0x66, 0xFF, 0xC8 };
                WriteProcessMemory(GetCurrentProcess(), (LPVOID)(decax + base), buffer0, sizeof(buffer0), 0);
            }
        }
        if (GetAsyncKeyState(VK_F2) & 1) {
            xray = !xray;
            printf("xray %i\n", xray);
        }
        if (GetAsyncKeyState(VK_F12) & 1) {
            freeconsole();
            FreeLibraryAndExitThread(HMOD, 0);
        }
        if (xray) {
            Uworld* world = (Uworld*)*pgworld;
            if (!world)
                continue;
            Ugameinstance* gameinstance = world->gameinstance;
            if (!gameinstance)
                continue;
            auto plevel = world->m_pULevel;
            //ULocalPlayer * localplayer = world->gameinstance->LocalPlayers[0];

            for (int i = 0; i < plevel->Entitylist.count; i++) {
                auto pactor = plevel->Entitylist[i];
                if (IsBadReadPtr(pactor, 0x328)) {
                    continue;
                }
                if (pactor->id == id::pawn) {
                    pactor->xray_enabled = 1;
                    continue;
                }
                if (havematch(pactor->id, { id::galil, id::at, id::tec9 }, &rapid_fire, pactor))
                    continue;
            }

        }
    }   
}

BOOL APIENTRY DllMain(HMODULE hmodule, DWORD  reason, LPVOID lpReserved)
{
    HMOD = hmodule;
    if (reason == DLL_PROCESS_ATTACH) {
        HANDLE status = CreateThread(nullptr, NULL, (LPTHREAD_START_ROUTINE)mainthread, hmodule, NULL, nullptr);
        if (status)
            CloseHandle(status);
    }
    return TRUE;
}

