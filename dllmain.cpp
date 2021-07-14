#include <Windows.h>
#include <iostream>

HMODULE HMOD;

    constexpr uintptr_t GNAMES = 0x34F9798;
    constexpr uintptr_t GWORLD = 0x35E9B38;
    constexpr uintptr_t nop    = 0x027E850;


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


bool shouldrun = true;

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

    while (true) {
        Sleep(10); /* 90 hertz */
        
        if (GetAsyncKeyState(VK_F1) & 1) {
            infammo = !infammo;
            printf("infammo %i\n",  infammo);
            if (infammo) {
                byte buffer[] = { 0x90, 0x90 , 0xC6, 0x04, 0x10, 0x01 };
                WriteProcessMemory(GetCurrentProcess(), (LPVOID)(nop + base), buffer, sizeof(buffer), 0);
            } else {
                byte buffer[] = { 0x74, 0x23 , 0xC6, 0x04, 0x10, 0x02 };
                WriteProcessMemory(GetCurrentProcess(), (LPVOID)(nop + base), buffer, sizeof(buffer), 0);
            }
        }
        if (GetAsyncKeyState(VK_F2) & 1) {
            xray = !xray;
            printf("xray %i\n", xray);
        }
        if (xray) {
            Uworld* world = (Uworld*)*pgworld;
            if (!world)
                continue;
            Ugameinstance* gameinstance = world->gameinstance;
            if (!gameinstance)
                continue;
            auto plevel = world->m_pULevel;
            ULocalPlayer* localplayer = world->gameinstance->LocalPlayers[0];


            for (int i = 0; i < plevel->Entitylist.count; i++) {
                auto pactor = plevel->Entitylist[i];
                if (IsBadReadPtr(pactor, 0x328)) {
                    continue;
                }
                switch (pactor->id) {
                case 79867: // bp_PavlovPawn_c
                    printf("player: %p", pactor);
                    if (pactor != localplayer->playercontroller->pawn) {
                        pactor->xray_enabled = 1;
                    } else {
                            printf("localplayer");
                    }
                    break;
                case 49174:
                case 80159: /* galil */
                case 109288:
                    printf("galil: %p", pactor);
                    gun* galil = (gun*)pactor;
                    galil->firerate = 0.0184000000f;
                    printf("%f : %i\n", galil->firerate, galil->firemode);
                    break;

                }
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

