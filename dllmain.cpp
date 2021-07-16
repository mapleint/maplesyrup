#include <Windows.h>
#include <iostream>
#include <vector>


#ifdef DEBUG
#define log(x, ...) \
printf(x, ...)
#else
#define log(x, ...) \

#endif 


HMODULE HMOD;

constexpr uintptr_t GNAMES = 0x34F9798;
constexpr uintptr_t GWORLD = 0x35E9B38;

constexpr uintptr_t nop    = 0x027E850;
constexpr uintptr_t decax =  0x02900EC;

void coninit(const char* title) 
{
#ifdef DEBUG
        AllocConsole();

        freopen_s(reinterpret_cast<_iobuf**>(__acrt_iob_func(0)), "conin$", "r", static_cast<_iobuf*>(__acrt_iob_func(0)));
        freopen_s(reinterpret_cast<_iobuf**>(__acrt_iob_func(1)), "conout$", "w", static_cast<_iobuf*>(__acrt_iob_func(1)));
        freopen_s(reinterpret_cast<_iobuf**>(__acrt_iob_func(2)), "conout$", "w", static_cast<_iobuf*>(__acrt_iob_func(2)));

        SetConsoleTitleA(title);
    }
#endif // DBG
}

void freeconsole() 
{
#ifdef DEBUG


    fclose(static_cast<_iobuf*>(__acrt_iob_func(0)));
    fclose(static_cast<_iobuf*>(__acrt_iob_func(1)));
    fclose(static_cast<_iobuf*>(__acrt_iob_func(2)));

    FreeConsole();

#endif // DBG
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
    char buf0[0x5F4];
    float recoil;
    char buf1[0xB4];
    float firerate;
    byte firemode;
    char buf2[0x67];
    float recoils[3];
    // 0x09B0
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
    int pump;
    int m9;
    int m1911;
    int glock;
    int fiveseven;
    int de;
    int revolver;
    int sawedoff;
    int autoshotgun;
    int drumshotgun;
    int lmga;
    int uzi;
    int mp5;
    int smg;
    int famas;
    int p90;
    int kar98;
    int ak47;
    int ak12;
    int ak;
    int m4;
    int aug;
    int autosniper;
    int awp;
    int ar9;
    int scar;
    int pepe;
    int vss;
    int kriss;

    int ppsh;
    int mp40;
    int g43;
    int garand;
    int svt40;
    int luger;
    int tokarev;
    int webley;
    int bren;
    int bar;
    int sten;
    int stg44;
    int mosin;
    int springfield;
    int thompson;
    int mg42;
    int enfield;
    int dp27;

    int flaregun;
}

bool havematch(int a, std::vector<int*> v, void(*func)(void*), void* ptr)
{
    for (int i = 0; i < v.size(); i++)
        if (*v[i] == a) {
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
    g->recoil = 0.f;
    g->recoils[0] = 0.f;
    g->recoils[1] = 0.f;
    g->recoils[2] = 0.f;
}


#define assign(x, y) \
if (!strcmp(buf, x)) { \
y = i; \
log("%s, %i\n", buf, i); \
continue;\
}

void update_ids(uintptr_t* gnames) {
    for (int i = 0; i < 140'000; i++) {
        char buf[150]{ 0 };
        GetGName(i, buf, *gnames);

        assign("BP_PavlovPawn_C", id::pawn)
        assign("Gun_Galil_C", id::galil)
        assign("Gun_AntiTank_C", id::at)
        assign("Gun_Cet9_C", id::tec9)
        assign("Gun_Shotgun_C", id::pump)
        assign("Gun_M9_C", id::m9)
        assign("Gun_1911_C", id::m1911)
        assign("Gun_Glock_C", id::glock)
        assign("Gun_57_C", id::fiveseven)
        assign("Gun_DE_C", id::de)
        assign("Gun_Revolver_C", id::revolver)
        assign("Gun_Sawedoff_C", id::sawedoff)
        assign("Gun_AutoShotgun_C", id::autoshotgun)
        assign("Gun_DrumShotgun_C", id::drumshotgun)
        assign("Gun_LMGA_C", id::lmga)
        assign("Gun_Uzi_C", id::uzi)
        assign("Gun_MP5_C", id::mp5)
        assign("Gun_SMG_C", id::smg)
        assign("Gun_Vanas_C", id::famas)
        assign("Gun_P90_C", id::p90)
        assign("Gun_Kar98_C", id::kar98)
        assign("Gun_AK47_C", id::ak47)
        assign("Gun_AK12_C", id::ak12)
        assign("Gun_AK_C", id::ak)
        assign("Gun_M4_C", id::m4)
        assign("Gun_AUG_C", id::aug)
        assign("Gun_AutoSniper_C", id::autosniper)
        assign("Gun_AWP_C", id::awp)
        assign("Gun_SCAR20_C", id::scar)
        assign("Gun_AR9_C", id::ar9)
        assign("Gun_Pepe_C", id::pepe)
        assign("Gun_VSS_C", id::vss)
        assign("Gun_Kriss_C", id::kriss)
        assign("Gun_DP27_C", id::dp27)
        assign("Gun_PPSH41_C", id::ppsh)
        assign("Gun_MP40_C", id::mp40)
        assign("Gun_G43_C", id::g43)
        assign("Gun_M1Garand_C", id::garand)
        assign("Gun_SVT40_C", id::svt40)
        assign("Gun_Luger_C", id::luger)
        assign("Gun_Tokarev_C", id::tokarev)
        assign("Gun_Webley_C", id::webley)
        assign("Gun_Bren_C", id::bren)
        assign("Gun_BAR_C", id::bar)
        assign("Gun_STG44_C", id::stg44)
        assign("Gun_Mosin_C", id::mosin)
        assign("Gun_Springfield_C", id::springfield)
        assign("Gun_Thompson_C", id::thompson)
        assign("Gun_MG42_C", id::mg42)
        assign("Gun_LeeEnfield_C", id::enfield)
        assign("Gun_FlarePistol_C", id::flaregun)
    }
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

    update_ids(pgnames);

    while (true) {
        Sleep(10); /* 90 hertz */
        
        if (GetAsyncKeyState(VK_F1) & 1) {
            infammo = !infammo;
            log("infammo %i\n",  infammo);
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
            log("xray %i\n", xray);
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
                if (havematch(pactor->id, {&id::galil, &id::at, &id::tec9, &id::pump}, &rapid_fire, pactor))
                    continue;
            }

        }
    }   
}

BOOL APIENTRY DllMain(HMODULE hmodule, DWORD  reason, LPVOID lpReserved)
{
    HMOD = hmodule;
    if (reason == DLL_PROCESS_ATTACH) {
        HANDLE status = CreateThread(nullptr, NULL,
            (LPTHREAD_START_ROUTINE)mainthread, hmodule, NULL, nullptr);

        if (status)
            CloseHandle(status);
    } else {
        shouldrun = false;
    }
    return TRUE;
}

