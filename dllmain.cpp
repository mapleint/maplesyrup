#include <Windows.h>
#include <iostream>

HMODULE HMOD;

    constexpr uintptr_t GNAMES = 0x34F9798;
    constexpr uintptr_t GWORLD = 0x35E9B38;
    constexpr uintptr_t nop    = 0x02900EC;


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
public:
    inline TArray()
    {
        Data = nullptr;
    };

    inline T& operator[](int i)
    {
        return Data[i];
    };

    inline int Count()
    {
        return count;
    }

    inline const T& operator[](int i) const
    {
        return Data[i];
    };
private:
    T* Data;
    int count;
    int max;
};

bool GetGName(int id, char* outname)
{
    DWORD_PTR modBase = (DWORD_PTR)GetModuleHandle(NULL);
    DWORD_PTR GNames = *(DWORD_PTR*)(modBase + GNAMES);
    if (!GNames)
        return false;
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
        if (c == 0x0)
            break;
        str_len++;
        if (str_len > 150)
            return false;
    }
    memcpy(outname, (LPVOID)(nameptr + 0x10), str_len);
    return true;
}

struct aactor {
    char buf0[0x18]; // 0x0
    int id; //0x18
    char buf1[0xd75];//0x1c
    bool xray; // 0xd91
};


struct Ulevel {
    char buf[0xa0];
    TArray<aactor*> Entitylist;
};

struct Ugameinstance {
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
    uintptr_t playercontroller;
    char pad0[0x38];
    UGameViewportClient* ViewportClient;

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
    coninit("console");

    while (true) {
        Sleep(10); /* 90 hertz */
        
        if (GetAsyncKeyState(VK_F1) & 1) {
            infammo = !infammo;
            printf("infammo %i\n",  infammo);
            if (infammo) {
            }
        }
        if (GetAsyncKeyState(VK_F2) & 1) {
            xray = !xray;
            printf("xray %i\n", xray);
        }
        if (xray) {
            printf("running xray, gworld : %p gnames : %p\n", pgworld, pgnames);
            uintptr_t names = *pgnames;
            Uworld* world = (Uworld*)pgworld;
            if (!names || !world) {
                printf("names or gworld were null\n");
                continue;
            }
            printf("world %p, names %x\n", world, names);

            Ulevel* plevel = world->m_pULevel; // plevel 
            printf("%p", plevel);
            if (!plevel) {
                printf("plevel was null\n");
                continue;
            }
            printf("entering entityloop, count %i\n", plevel->Entitylist.Count());
            for (int i = 0; i < plevel->Entitylist.Count(); i++) {
                char name[150]{ 0 };
                auto pactor = plevel->Entitylist[i];
                if (GetGName(pactor->id, name)) {
                    printf("[%i] %s\n", i, name);
                    if (!strcmp(name, "BP_PavlovPawn_C")) {
                        printf("player!\n");
                        pactor->xray = 1;
                    }
                } else {
                    printf("[%i] failed to get name\n", i);
                    continue;
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

