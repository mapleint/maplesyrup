
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

enum class firemode : uint8_t
{
	Semi = 0,
	Automatic = 1,
	Manual = 2,
	Burst = 3,
};
bool shouldrun = true;

struct gun 
{
public:
	char off[0x04D0];
	bool                                               bInvertRollRecoil;                                        // 0x04D0(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x3];                                       // 0x04D1(0x0003) MISSED OFFSET
	float                                              RecoilRatio;                                              // 0x04D4(0x0004) (ZeroConstructor, IsPlainOldData)
	float                                              ReloadCooldown;                                           // 0x04D8(0x0004) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x34];                                      // 0x04DC(0x0034) MISSED OFFSET
	float                                              BasisBlendAlpha;                                          // 0x0510(0x0004) (ZeroConstructor, IsPlainOldData)
	char bufn1[0x18];
	float                                              CounterRecoilTimer;                                       // 0x052C(0x0004) (ZeroConstructor, IsPlainOldData)
	float                                              DynamicPivotRecoil;                                       // 0x0530(0x0004) (ZeroConstructor, Transient, IsPlainOldData)
	float                                              DynamicPivotRecoilSaved;                                  // 0x0534(0x0004) (ZeroConstructor, Transient, IsPlainOldData)
	float                                              CounterPivotRecoilTimer;                                  // 0x0538(0x0004) (ZeroConstructor, Transient, IsPlainOldData)
	float                                              BoltReleaseTimer;                                         // 0x053C(0x0004) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData02[0x28];                                      // 0x0540(0x0028) MISSED OFFSET
	int                                                BurstCount;                                               // 0x0568(0x0004) (ZeroConstructor, IsPlainOldData)
	float                                              BurstDelayTimer;                                          // 0x056C(0x0004) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData03[0x8];                                       // 0x0570(0x0008) MISSED OFFSET
	unsigned char                                      UnknownData04[0x48];                                      // 0x0588(0x0048) MISSED OFFSET
	void* MuzzleFlashComp;                                          // 0x05C0(0x0008) (ExportObject, ZeroConstructor, Transient, InstancedReference, IsPlainOldData)
	unsigned char                                      UnknownData05[0x10];                                      // 0x05C8(0x0010) MISSED OFFSET
	void* State;                                                    // 0x05D8(0x0008) (BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, InstancedReference, IsPlainOldData)
	void* PreviousOwner;                                            // 0x05E0(0x0008) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	void* ChargingHandle;                                           // 0x05E8(0x0008) (BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, InstancedReference, IsPlainOldData)
	float                                              FireRateTimer;                                            // 0x05F0(0x0004) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	float                                              Recoil;                                                   // 0x05F4(0x0004) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	float                                              SlideTimer;                                               // 0x05F8(0x0004) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	bool                                               bBoltLocked;                                              // 0x05FC(0x0001) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	bool                                               bTriggered;                                               // 0x05FD(0x0001) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	bool                                               bTriggerSnapped;                                          // 0x05FE(0x0001) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData06[0x1];                                       // 0x05FF(0x0001) MISSED OFFSET
	float                                              SnapTrigger;                                              // 0x0600(0x0004) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	float                                              SnapTriggerSmooth;                                        // 0x0604(0x0004) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	class AVRMagazine* Magazine;                                                 // 0x0608(0x0008) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	float                                              MagGrabRateMax;                                           // 0x0610(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               bBulletInChamber;                                         // 0x0614(0x0001) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	bool                                               bHammerReady;                                             // 0x0615(0x0001) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData07[0x2];                                       // 0x0616(0x0002) MISSED OFFSET
	float                                              HammerRatio;                                              // 0x0618(0x0004) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	int                                                SkinId;                                                   // 0x061C(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, Net, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	char bufn0[0x18];
	float                                              GenericScalar1;                                           // 0x0638(0x0004) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              GenericScalar2;                                           // 0x063C(0x0004) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	bool                                               bGenericFlag1;                                            // 0x0640(0x0001) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	bool                                               bGenericFlag2;                                            // 0x0641(0x0001) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	bool                                               bGenericFlag3;                                            // 0x0642(0x0001) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData08[0x1];                                       // 0x0643(0x0001) MISSED OFFSET
	bool                                               bDisableCocking;                                          // 0x0644(0x0001) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	bool                                               bBoltLockedTillAmmo;                                      // 0x0645(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               bChamberOnMagazine;                                       // 0x0646(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData09[0x1];                                       // 0x0647(0x0001) MISSED OFFSET
	void* StateClass;                                               // 0x0648(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	void* MuzzleSocket;                                             // 0x0650(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              MuzzleZeroBias;                                           // 0x0658(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData10[0x4];                                       // 0x065C(0x0004) MISSED OFFSET
	class UCurveVector* NormalizedRecoilCurve;                                    // 0x0660(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              RecoilCurveScale;                                         // 0x0668(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              RecoilAngleMul;                                           // 0x066C(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              RecoilAngleLateralMul;                                    // 0x0670(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              RecoilTraslationMul;                                      // 0x0674(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               bUsePivotedRecoil;                                        // 0x0678(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData11[0x3];                                       // 0x0679(0x0003) MISSED OFFSET
	char                                     RecoilPivotOffset[0xc];                                        // 0x067C(0x000C) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              PivotRecoilMul;                                           // 0x0688(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              PivotRecoilLateralMul;                                    // 0x068C(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              CounterPivotRecoilDuration;                               // 0x0690(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData12[0x4];                                       // 0x0694(0x0004) MISSED OFFSET
	class UCurveFloat* CounterPivotRecoilCurve;                                  // 0x0698(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              CokingThreashold;                                         // 0x06A0(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              ReChamberThreashold;                                      // 0x06A4(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              FireThreashold;                                           // 0x06A8(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              FireRate;                                                 // 0x06AC(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	firemode                                     FireMode;                                                 // 0x06B0(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly, Net, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData13[0x7];                                       // 0x06B1(0x0007) MISSED OFFSET
	class USoundCue* HandlingSound;                                            // 0x06B8(0x0008) (Edit, BlueprintVisible, BlueprintReadOnly, Net, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               bOpenBolt;                                                // 0x06C0(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData14[0x3];                                       // 0x06C1(0x0003) MISSED OFFSET
	float                                              FireDelay;                                                // 0x06C4(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	TArray<firemode>                             AdditionalFireModes;                                      // 0x06C8(0x0010) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance)
	float                                              BurstDelay;                                               // 0x06D8(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               bLockBolt;                                                // 0x06DC(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData15[0x3];                                       // 0x06DD(0x0003) MISSED OFFSET
	float                                              BoltReleaseCooldown;                                      // 0x06E0(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               bStaticSlider;                                            // 0x06E4(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData16[0x3];                                       // 0x06E5(0x0003) MISSED OFFSET
	void* ChargingHandleAttachName;                                 // 0x06E8(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	void* BulletClass;                                              // 0x06F0(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	int                                                BulletSpray;                                              // 0x06F8(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              BulletSpraySpread;                                        // 0x06FC(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               bUseEvenSpread;                                           // 0x0700(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData17[0x3];                                       // 0x0701(0x0003) MISSED OFFSET
	float                                              EvenSpread;                                               // 0x0704(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              LimitedBulletSpraySpreadMul;                              // 0x0708(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              RecoilLimitThreadshold;                                   // 0x070C(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	void* BulletSprayRecoilCurve;                                   // 0x0710(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              RecoilPerBullet;                                          // 0x0718(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              RecoilNormalizationRate;                                  // 0x071C(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              RecoilMul;                                                // 0x0720(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData18[0x4];                                       // 0x0724(0x0004) MISSED OFFSET
	void* RecoilCurve;                                              // 0x0728(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	void* RecoilPatternCurve;                                       // 0x0730(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	void* MagazineClass;                                            // 0x0738(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               bManualMagazineRelease;                                   // 0x0740(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData19[0x3];                                       // 0x0741(0x0003) MISSED OFFSET
	float                                              ManualReloadCooldown;                                     // 0x0744(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               bNoMagazine;                                              // 0x0748(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               bReloadChamberByMagazine;                                 // 0x0749(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               bComplexTrigger;                                          // 0x074A(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData20[0x1];                                       // 0x074B(0x0001) MISSED OFFSET
	float                                              ComplexTriggerDuration;                                   // 0x074C(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	void* ComplexTriggerCurve;                                      // 0x0750(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               bAutoUnchamber;                                           // 0x0758(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               bTakeBulletOnQuickReload;                                 // 0x0759(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData21[0x2];                                       // 0x075A(0x0002) MISSED OFFSET
	float                                              BasisLerpRate;                                            // 0x075C(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               bDynamicRecoil;                                           // 0x0760(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData22[0x3];                                       // 0x0761(0x0003) MISSED OFFSET
	float                                              CounterRecoilDuration;                                    // 0x0764(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               bApplyRecoilPullback;                                     // 0x0768(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData23[0x3];                                       // 0x0769(0x0003) MISSED OFFSET
	float                                              PullbackLerpExp;                                          // 0x076C(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              CounterRecoilPullback;                                    // 0x0770(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData24[0x4];                                       // 0x0774(0x0004) MISSED OFFSET
	void* CounterRecoilCurve;                                       // 0x0778(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              CounterRecoilThreashold;                                  // 0x0780(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	char                                     CounterRecoilLimits[0xc];                                      // 0x0784(0x000C) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              SmoothCounterRecoilLimitsExp;                             // 0x0790(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData25[0x4];                                       // 0x0794(0x0004) MISSED OFFSET
	void* ShotSound;                                                // 0x0798(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	void* ShotTailSound;                                            // 0x07A0(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	void* SuppressedShotSound;                                      // 0x07A8(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	void* SuppressedShotTailSound;                                  // 0x07B0(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	void* ShotSoundLQ;                                              // 0x07B8(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	void* ShotSoundLQ2D;                                            // 0x07C0(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	void* SuppressedShotSoundLQ;                                    // 0x07C8(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	void* SupressedShotSoundLQ2D;                                   // 0x07D0(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	void* ShotSourceBus;                                            // 0x07D8(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	void* SuppressedShotSourceBus;                                  // 0x07E0(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	int                                                LowAmmoThreashold;                                        // 0x07E8(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData26[0x4];                                       // 0x07EC(0x0004) MISSED OFFSET
	void* LowAmmoSound;                                             // 0x07F0(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	void* TriggerSound;                                             // 0x07F8(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	void* ReleaseTriggerSound;                                      // 0x0800(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	void* BoltReleaseSound;                                         // 0x0808(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	void* BoltLockSound;                                            // 0x0810(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	void* CockSound;                                                // 0x0818(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	void* ReloadSound;                                              // 0x0820(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	void* EjectMagazineSound;                                       // 0x0828(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	void* CycleFireModeSound;                                       // 0x0830(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              MuzzleFlashDuration;                                      // 0x0838(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              MuzzleFlashScale;                                         // 0x083C(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              MuzzleFlashOffset;                                        // 0x0840(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData27[0x4];                                       // 0x0844(0x0004) MISSED OFFSET
	void* MuzzleFlash;                                              // 0x0848(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	void* MuzzleFlashLQ;                                            // 0x0850(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	void* MuzzleFlashSuppressed;                                    // 0x0858(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	void* MuzzleFlashSuppressedLQ;                                  // 0x0860(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	void* ShotHapticEffect;                                         // 0x0868(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	unsigned char                                      UnknownData001[0x1C];                                      // 0x0870(0x001C) MISSED OFFSET
	char                                     GripRefLocation[0xc];                                          // 0x088C(0x000C) (ZeroConstructor, IsPlainOldData)
	bool                                               bHasLegacyGrip;                                           // 0x0898(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData011[0x5F];                                      // 0x0899(0x005F) MISSED OFFSET
	void* SourceBusComp;                                            // 0x08F8(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	void* AudioVolume;                                              // 0x0900(0x0008) (ZeroConstructor, Transient, IsPlainOldData)
	void* ReverbSubmix;                                             // 0x0908(0x0008) (ZeroConstructor, Transient, IsPlainOldData)
	unsigned char                                      UnknownData021[0x20];                                      // 0x0910(0x0020) MISSED OFFSET
	char                                     LastTwoHandDirection[0xc];                                     // 0x0930(0x000C) (Net, ZeroConstructor, IsPlainOldData)
	char                                     TwoHandPickOffset[0xc];                                        // 0x093C(0x000C) (Net, ZeroConstructor, IsPlainOldData)
	unsigned char                                      aUnknownData03[0x2];                                       // 0x0948(0x0002) MISSED OFFSET
	bool                                               bKeepTwoHand;                                             // 0x094A(0x0001) (Net, ZeroConstructor, IsPlainOldData)
	unsigned char                                      aUnknownData04[0x1];                                       // 0x094B(0x0001) MISSED OFFSET
	char                                     AdditionalHandOffset[0xc];                                     // 0x094C(0x000C) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	bool                                               bSideGun;                                                 // 0x0958(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               bGenerateMagBoltReleaseEvents;                            // 0x0959(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               bCustomCocking;                                           // 0x095A(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               bDeltaCocking;                                            // 0x095B(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               bNeedsTwoHands;                                           // 0x095C(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      aUnknownData05[0x3];                                       // 0x095D(0x0003) MISSED OFFSET
	float                                              StockDuration;                                            // 0x0960(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               bTwoHandSupportOnly;                                      // 0x0964(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               bTwoHandReload;                                           // 0x0965(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      aUnknownData06[0x2];                                       // 0x0966(0x0002) MISSED OFFSET
	void* TwoHandGripSound;                                         // 0x0968(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               bDropByRecoil;                                            // 0x0970(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               bSupportsAutoUngrip;                                      // 0x0971(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               bSupportsMagRelease;                                      // 0x0972(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               bSingleShotDrop;                                          // 0x0973(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              MaxTwoHandGripDistance;                                   // 0x0974(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	char                                     GripOffset[0xc];                                               // 0x0978(0x000C) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              MagneticGripDistance;                                     // 0x0984(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	void* MagneticGripSequence;                                     // 0x0988(0x0008) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	void* NoMagazineMagneticGripSequence;                           // 0x0990(0x0008) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	void* AccessoryGripSequence;                                    // 0x0998(0x0008) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              TriggerAngle;                                             // 0x09A0(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              UnsteadyRecoilAngleMul;                                   // 0x09A4(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              UnsteadyRecoilTraslationMul;                              // 0x09A8(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              UnsteadySpraySpreadMul;                                   // 0x09AC(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              MaxUngrippedRecoil;                                       // 0x09B0(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              MaxUngrippedDuration;                                     // 0x09B4(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	char                                     GrippedCounterRecoilLimitMul[0xc];                             // 0x09B8(0x000C) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      aUnknownData07[0x4];                                       // 0x09C4(0x0004) MISSED OFFSET
	void* ExploitSound;                                             // 0x09C8(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	char                     ShotConcurrencyQuality[0x28];                                   // 0x09D0(0x0028) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	void* HitSurfaceFX;                                             // 0x09F8(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               bUseChamberEjectFX;                                       // 0x0A00(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      aUnknownData08[0x7];                                       // 0x0A01(0x0007) MISSED OFFSET
	void* ChamberEjectSurfaceFX;                                    // 0x0A08(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	int                                                RattlePoints;                                             // 0x0A10(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              SpeedModifier;                                            // 0x0A14(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              CrouchAcuracy;                                            // 0x0A18(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              StandingAcuracy;                                          // 0x0A1C(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              MovingAcuracy;                                            // 0x0A20(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      aUnknownData09[0x4];                                       // 0x0A24(0x0004) MISSED OFFSET
	void* BobCurve;                                                 // 0x0A28(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              BobSpeed;                                                 // 0x0A30(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              BobMultiplier;                                            // 0x0A34(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              BobBlendSpeed;                                            // 0x0A38(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              ADSSpeedMultiplier;                                       // 0x0A3C(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              StrafingMultiplier;                                       // 0x0A40(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              CrouchSideRecoilMul;                                      // 0x0A44(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	void* bHapticsRecoil;                                           // 0x0A48(0x0008) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               bScopeIsLongerThanGun;                                    // 0x0A50(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      aUnknownData10[0x3];                                       // 0x0A51(0x0003) MISSED OFFSET
	float                                              LastHapticTime;                                           // 0x0A54(0x0004) (ZeroConstructor, IsPlainOldData)
	void* Suppresor;                                                // 0x0A58(0x0008) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	void* Sight;                                                    // 0x0A60(0x0008) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	void* Grip;                                                     // 0x0A68(0x0008) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	void* Accessory;                                                // 0x0A70(0x0008) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	void*                                       PicatinnySocket;                                          // 0x0A78(0x0008) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              PicatinnyLength;                                          // 0x0A80(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      SightCompatibility;                                       // 0x0A84(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      aUnknownData11[0x3];                                       // 0x0A85(0x0003) MISSED OFFSET
	void*                                       GripSocket;                                               // 0x0A88(0x0008) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      GripCompatibility;                                        // 0x0A90(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      aUnknownData12[0x7];                                       // 0x0A91(0x0007) MISSED OFFSET
	void*                                       SuppressorSocket;                                         // 0x0A98(0x0008) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      SuppressorCompatibility;                                  // 0x0AA0(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      aUnknownData13[0x7];                                       // 0x0AA1(0x0007) MISSED OFFSET
	void*                                       AccessorySocket;                                          // 0x0AA8(0x0008) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      AccessoryCompatibility;                                   // 0x0AB0(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      aUnknownData14[0x7];                                       // 0x0AB1(0x0007) MISSED OFFSET
	char                         DefaultAttachments[0x28];                                       // 0x0AB8(0x0028) (Edit, BlueprintVisible, BlueprintReadOnly, DisableEditOnInstance)
	void*                                   AttachmentModeRange;                                      // 0x0AE0(0x0008) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	void* LowEndSightReplacement;                                   // 0x0AE8(0x0008) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              AttachmentModeHoldTime;                                   // 0x0AF0(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              AttachModeTime;                                           // 0x0AF4(0x0004) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	bool                                               bHideIronOverride;                                        // 0x0AF8(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      aUnknownData15[0x7];                                       // 0x0AF9(0x0007) MISSED OFFSET
	char                    OnMagBoltRelease[0x10];                                         // 0x0B00(0x0010) (ZeroConstructor, InstancedReference, BlueprintAssignable)


};