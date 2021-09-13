#include <Windows.h>
#include <iostream>
#include <vector>
#include "includes/xorstr.hpp"
#include "structs.h"

constexpr int DBG = 1;
#define log(x, ...) \
printf(xorstr(x), ##__VA_ARGS__)

//constexpr int DBG = 0;
//#define log(x, ...) \

/* GLOBALS*/

HMODULE HMOD;

constexpr uintptr_t GNAMES  = 0x34F9798;
constexpr uintptr_t GWORLD  = 0x35E9B38;
constexpr uintptr_t GOBJECT = 0x34FDD10;

constexpr uintptr_t nop    = 0x027E850;
constexpr uintptr_t decax =  0x02900EC;



void coninit(const char* title) 
{
if constexpr(DBG) {
        AllocConsole();

        freopen_s(reinterpret_cast<_iobuf**>(__acrt_iob_func(0)), xorstr("conin$" ), xorstr("r"), static_cast<_iobuf*>(__acrt_iob_func(0)));
        freopen_s(reinterpret_cast<_iobuf**>(__acrt_iob_func(1)), xorstr("conout$"), xorstr("w"), static_cast<_iobuf*>(__acrt_iob_func(1)));
        freopen_s(reinterpret_cast<_iobuf**>(__acrt_iob_func(2)), xorstr("conout$"), xorstr("w"), static_cast<_iobuf*>(__acrt_iob_func(2)));

        SetConsoleTitleA(title);
    }
}

void freeconsole() 
{
    if constexpr (DBG) {
        fclose(static_cast<_iobuf*>(__acrt_iob_func(0)));
        fclose(static_cast<_iobuf*>(__acrt_iob_func(1)));
        fclose(static_cast<_iobuf*>(__acrt_iob_func(2)));

        FreeConsole();
    }
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
    int m16;

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

    int rpg;
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

float speed = 2.f;

bool norecoil = 0;

bool rapidfire = 0;

bool muteguns = 0;



void rapid_fire(void* ptr)
{
    gun* g = (gun*)ptr;

    g->ADSSpeedMultiplier = speed;
    g->RecoilTraslationMul = norecoil ? 0 : g->RecoilTraslationMul;
    g->RecoilMul = norecoil ? 0 : g->RecoilMul;
    g->RecoilAngleMul = norecoil ? 0 : g->RecoilAngleMul;

    g->FireMode = rapidfire ? firemode::Automatic : g->FireMode;

    if (id::webley != ((aactor*)g)->id && id::revolver != ((aactor*)g)->id)
        g->ShotSound = g->TriggerSound;

    g->FireRate = rapidfire ? 0.01f : 0.07f;
    g->PicatinnyLength = 10000.f;
    g->SightCompatibility = 0xf;
    

}

void bull(void *ptr)
{
}

#define assign(x, y) if (!strcmp(buf, x)) { y = i; log("%s, %i\n", buf, i); continue;}

std::vector<int*> guns;

std::vector<int*> handguns;
std::vector<int*> sr;
std::vector<int*> ar;
std::vector<int*> shotguns;
std::vector<int*> mgs;
std::vector<int*> smgs;

void initvectors()
{
    using namespace id;
    sr = {&mosin, &springfield, &enfield, &at, &awp, &kar98, &autosniper, &scar, &g43, &garand, &svt40 };
    guns.insert(guns.end(), sr.begin(), sr.end());
    handguns = {&tec9, &m9, &glock, &m1911, &fiveseven, &de, &revolver, &luger, &tokarev, &webley};
    guns.insert(guns.end(), handguns.begin(), handguns.end());
    shotguns = { &pump, &sawedoff, &autoshotgun, &drumshotgun };
    guns.insert(guns.end(), shotguns.begin(), shotguns.end());
    mgs = {&kriss, &uzi, &mp5, &smg, &p90, &ar9, &ppsh, &pepe, &mp40, &thompson};
    guns.insert(guns.end(), mgs.begin(), mgs.end());
    smgs = {&lmga, &mg42, &dp27, &bren};
    guns.insert(guns.end(), smgs.begin(), smgs.end());
    ar = { &galil, &famas, &ak47, &ak, &ak12, &m4, &aug, &vss, &bar, &stg44, &m16};
    guns.insert(guns.end(), ar.begin(), ar.end());

    guns.push_back(&flaregun);
}

void update_ids(uintptr_t* gnames) {
    for (int i = 0; i < 140'000; i++) {
        char buf[150]{ 0 };
        GetGName(i, buf, *gnames);

        assign(xorstr("BP_PavlovPawn_C"), id::pawn)
        /*sniper rifles*/
        assign(xorstr("Gun_Mosin_C"), id::mosin)
        assign(xorstr("Gun_Springfield_C"), id::springfield)
        assign(xorstr("Gun_LeeEnfield_C"), id::enfield)
        assign(xorstr("Gun_AntiTank_C"), id::at)
        assign(xorstr("Gun_AWP_C"), id::awp)
        assign(xorstr("Gun_Kar98_C"), id::kar98)
        assign(xorstr("Gun_AutoSniper_C"), id::autosniper)
        assign(xorstr("Gun_SCAR20_C"), id::scar)
        assign(xorstr("Gun_G43_C"), id::g43)
        assign(xorstr("Gun_M1Garand_C"), id::garand)
        assign(xorstr("Gun_SVT40_C"), id::svt40)
        /*handguns*/
        assign(xorstr("Gun_Cet9_C"), id::tec9)
        assign(xorstr("Gun_M9_C"), id::m9)
        assign(xorstr("Gun_Glock_C"), id::glock)
        assign(xorstr("Gun_1911_C"), id::m1911)
        assign(xorstr("Gun_57_C"), id::fiveseven)
        assign(xorstr("Gun_DE_C"), id::de)
        assign(xorstr("Gun_Revolver_C"), id::revolver)
        assign(xorstr("Gun_Luger_C"), id::luger)
        assign(xorstr("Gun_Tokarev_C"), id::tokarev)
        assign(xorstr("Gun_Webley_C"), id::webley)
        /*shotguns*/
        assign(xorstr("Gun_Shotgun_C"), id::pump)
        assign(xorstr("Gun_Sawedoff_C"), id::sawedoff)
        assign(xorstr("Gun_AutoShotgun_C"), id::autoshotgun)
        assign(xorstr("Gun_DrumShotgun_C"), id::drumshotgun)
        /*automatic rifles*/
        assign(xorstr("Gun_Galil_C"), id::galil)
        assign(xorstr("Gun_Vanas_C"), id::famas)
        assign(xorstr("Gun_AK47_C"), id::ak47)
        assign(xorstr("Gun_AK12_C"), id::ak12)
        assign(xorstr("Gun_AK_C"), id::ak)
        assign(xorstr("Gun_M4_C"), id::m4)
        assign(xorstr("Gun_AUG_C"), id::aug)
        assign(xorstr("Gun_VSS_C"), id::vss)
        assign(xorstr("Gun_BAR_C"), id::bar)
        assign(xorstr("Gun_STG44_C"), id::stg44)
        assign(xorstr("Gun_M16_C"), id::m16)
        /*smgs*/
        assign(xorstr("Gun_Kriss_C"), id::kriss)
        assign(xorstr("Gun_Uzi_C"), id::uzi)
        assign(xorstr("Gun_MP5_C"), id::mp5)
        assign(xorstr("Gun_SMG_C"), id::smg)
        assign(xorstr("Gun_P90_C"), id::p90)
        assign(xorstr("Gun_AR9_C"), id::ar9)
        assign(xorstr("Gun_Pepe_C"), id::pepe)
        assign(xorstr("Gun_PPSH41_C"), id::ppsh)
        assign(xorstr("Gun_MP40_C"), id::mp40)
        assign(xorstr("Gun_Thompson_C"), id::thompson)
        assign(xorstr("Gun_Sten_C"), id::sten)
        /*mgs*/
        assign(xorstr("Gun_LMGA_C"), id::lmga)
        assign(xorstr("Gun_MG42_C"), id::mg42)
        assign(xorstr("Gun_DP27_C"), id::dp27)
        assign(xorstr("Gun_Bren_C"), id::bren)
        /*misc*/
        assign(xorstr("Gun_FlarePistol_C"), id::flaregun)
        assign(xorstr("RL_RPG7_C"), id::rpg)
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
    coninit(xorstr("console"));

    initvectors();
    update_ids(pgnames);

    while (shouldrun) {

            
        Sleep(10); /* 90 hertz */
        
        if (GetAsyncKeyState(VK_F1) & 1) {
            infammo = !infammo;
            log("infammo %i\n",  infammo);
            if (infammo) {
                byte buffer[] = { 0x90, 0x90 , 0xC6, 0x04, 0x10, 0x01 };
                WriteProcessMemory(GetCurrentProcess(), (LPVOID)(nop + base), buffer, sizeof(buffer), 0);
                byte buffer0[] = {0x90, 0x90, 0x90};
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
        if (GetAsyncKeyState(VK_F3) & 1) {
            rapidfire = !rapidfire;
            log("rapidfire %i\n", rapidfire);
        }

        if (GetAsyncKeyState(VK_F4) & 1) {
            norecoil = !norecoil;
            log("norecoil %i\n", norecoil);
        }

        if (GetAsyncKeyState(VK_F9) & 1) {
            break;
        }

        if(GetAsyncKeyState(VK_UP) & 1) {
            speed += .1f;
            log("speed : %f\n", speed);
        }

        if (GetAsyncKeyState(VK_DOWN) & 1) {
            speed -= .1f;
            log("speed : %f\n", speed);
        }
        if (GetAsyncKeyState(VK_LEFT) & 1) {
            speed -= 10.f;
            log("speed : %f\n", speed);
        }

        if (GetAsyncKeyState(VK_RIGHT) & 1) {
            speed += 10.f;
            log("speed : %f\n", speed);
        }

        if (GetAsyncKeyState(VK_PRIOR) & 1) {
            speed *= 0.1f;
            log("speed : %f\n", speed);
        }

        if (GetAsyncKeyState(VK_NEXT) & 1) {
            speed *= 10.f;
            log("speed : %f\n", speed);
        }

        Uworld* world = (Uworld*)*pgworld;
        if (!world)
            continue;
        Ugameinstance* gameinstance = world->gameinstance;

        if (!gameinstance)
            continue;
        auto plevel = world->m_pULevel;

        
        for (int i = 0; i < plevel->Entitylist.count; i++) {

            auto pactor = plevel->Entitylist[i];



            if (IsBadReadPtr(pactor, 0x328))
                continue;

            if (pactor->id == id::pawn) {
                if(xray)
                    pactor->xray_enabled = 1;
                continue;
            }

            if (havematch(pactor->id, guns, &rapid_fire, pactor))
                continue;


        }
    }
    freeconsole();
    FreeLibraryAndExitThread(HMOD, 0);
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

    }
    return TRUE;
}

