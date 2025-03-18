#pragma once

#include <locale>
#include <codecvt>
#include <string>

inline bool bDebugLog = false;

enum LogLevel {
    Log,
    Debug,
    Warning,
    Error
};

namespace ELogVerbosity
{
    enum Type : uint8
    {
        /** Not used */
        NoLogging = 0,

        /** Always prints a fatal error to console (and log file) and crashes (even if logging is disabled) */
        Fatal,

        /**
         * Prints an error to console (and log file).
         * Commandlets and the editor collect and report errors. Error messages result in commandlet failure.
         */
        Error,

        /**
         * Prints a warning to console (and log file).
         * Commandlets and the editor collect and report warnings. Warnings can be treated as an error.
         */
        Warning,

        /** Prints a message to console (and log file) */
        Display,

        /** Prints a message to a log file (does not print to console) */
        Log,

        /**
         * Prints a verbose message to a log file (if Verbose logging is enabled for the given category,
         * usually used for detailed logging)
         */
        Verbose,

        /**
         * Prints a verbose message to a log file (if VeryVerbose logging is enabled,
         * usually used for detailed logging that would otherwise spam output)
         */
        VeryVerbose,

        // Log masks and special Enum values

        All = VeryVerbose,
        NumVerbosity,
        VerbosityMask = 0xf,
        SetColor = 0x40, // not actually a verbosity, used to set the color of an output device 
        BreakOnLog = 0x80
    };
}

std::string TCHARToANSI(const TCHAR* tcharStr)
{
    int size_needed = WideCharToMultiByte(CP_UTF8, 0, tcharStr, -1, NULL, 0, NULL, NULL);
    std::string result(size_needed, 0);
    WideCharToMultiByte(CP_UTF8, 0, tcharStr, -1, &result[0], size_needed, NULL, NULL);

    return result;
}

void WriteLog(const char* category, LogLevel level, const TCHAR* format, ...)
{
    const TCHAR* levelStr;

    if (!bDebugLog && level == LogLevel::Debug)
        return;

    switch (level) 
    {
        case LogLevel::Log: levelStr = TEXT("Info"); break;
        case LogLevel::Debug: levelStr = TEXT("Debug"); break;
        case LogLevel::Warning: levelStr = TEXT("Warning"); break;
        case LogLevel::Error: levelStr = TEXT("Error"); break;
        default: levelStr = TEXT("Unknown"); break;
    }

    printf("Ares-5.41-Log: %s: %s: ", category, TCHARToANSI(levelStr));

    va_list args;
    va_start(args, format);
    vprintf(TCHARToANSI(format).c_str(), args);
    va_end(args);

    printf("\n");
}

/*void WriteLog(const char* File, int32 Line, const char* Caca, LogLevel level, const TCHAR* Fmt, ...)
{
    FName Category = UKismetStringLibrary::Conv_StringToName(TEXT("LogFort"));

    va_list Args;
    va_start(Args, Fmt);

    void (*Logf_InternalImpl)(const char* File, int32 Line, const FName & Category, ELogVerbosity::Type Verbosity, const TCHAR* Fmt, ...) = decltype(Logf_InternalImpl)(0x15ff740 + uintptr_t(GetModuleHandle(0)));
    Logf_InternalImpl(File, Line, Category, ELogVerbosity::Type::Log, Fmt, Args);

    va_end(Args);
}

#define FN_LOG(CategoryName, Verbosity, Format, ...) \
    WriteLog(__FILE__, __LINE__, #CategoryName, Verbosity, Format , ##__VA_ARGS__)*/


#define FN_LOG(Category, Level, ...) WriteLog(#Category, Level, __VA_ARGS__)


static auto StaticLoadObjectInternal = reinterpret_cast<UObject * (*)(UClass * InClass, UObject * InOuter, const TCHAR * Name, const TCHAR * FileName, uint32_t LoadFlags, UPackageMap * Sandbox, bool bAllowObjectReconciliation)>(uintptr_t(GetModuleHandle(NULL)) + 0x1856210);

template <typename T>
static T* StaticLoadObject(const TCHAR* InPath)
{
    return (T*)StaticLoadObjectInternal(T::StaticClass(), nullptr, InPath, nullptr, 0, nullptr, false);
}

template <typename T>
static T* FindObjectFast(std::string ObjectName, UClass* ObjectClass = UObject::StaticClass())
{
    auto OrigInName = std::wstring(ObjectName.begin(), ObjectName.end()).c_str();

    auto StaticFindObject = (T * (*)(UClass*, UObject * Package, const wchar_t* OrigInName, bool ExactClass))((uintptr_t)GetModuleHandleA(0) + 0x1854780);
    return StaticFindObject(ObjectClass, nullptr, OrigInName, false);
}


struct FCommandLine
{
    /**
     * Returns an edited version of the executable's command line with the game name and certain other parameters removed.
     */
    static const TCHAR* Get()
    {
        // 7FF66FC70AF0
        const TCHAR* (*Get)() = decltype(Get)(0x1620AF0 + uintptr_t(GetModuleHandle(0)));
        return Get();
    }
};

struct FParse
{
    /** Checks if a command-line parameter exists in the stream. */
    static bool Param(const TCHAR* Stream, const TCHAR* Params)
    {
        // 7FF66FCA24F0
        bool (*Param)(const TCHAR * Stream, const TCHAR * Params) = decltype(Param)(0x16524F0 + uintptr_t(GetModuleHandle(0)));
        return Param(Stream, Params);
    }
};


#define RESULT_PARAM Z_Param__Result
#define RESULT_DECL void*const RESULT_PARAM

#pragma pack(push, 0x1)
class alignas(0x08) FOutputDevice
{
public:
    uint8 Pad_01[0x10];
};
#pragma pack(pop)

struct FFrame : public FOutputDevice
{
public:
    UFunction* Node; // 0x10
    UObject* Object; // 0x18
    uint8* Code; // 0x20
    uint8* Locals; // 0x28

    UProperty* MostRecentProperty; // 0x30
    uint8* MostRecentPropertyAddress; // 0x38

    uint8 Pad_01[0x58];

public:
    void Step(UObject* Context, RESULT_DECL)
    {
        // 7FF66FE7FCE0
        void (*Step)(FFrame* Frame, UObject* Context, RESULT_DECL) = decltype(Step)(0x182FCE0 + uintptr_t(GetModuleHandle(0)));
        Step(this, Context, RESULT_PARAM);
    }

    void StepExplicitProperty(void* const Result, UProperty* Property)
    {
        // 7FF66FE7FD10
        void (*StepExplicitProperty)(FFrame* Frame, void* const Result, UProperty* Property) = decltype(StepExplicitProperty)(0x182FD10 + uintptr_t(GetModuleHandle(0)));
        StepExplicitProperty(this, Result, Property);
    }

    void StepCompiledIn(void* const Result)
    {
        // https://imgur.com/q5efUyh

        if (Code)
        {
            Step(Object, Result);
        }
        else
        {
            // https://imgur.com/a/CvmkuCy
            UProperty* Property = (UProperty*)(*(UField**)(__int64(this) + 0x80));
            *(UField**)(__int64(this) + 0x80) = Property->Next;

            StepExplicitProperty(Result, Property);
        }
    }

    template<typename TNativeType>
    TNativeType& StepCompiledInRef(void* const TemporaryBuffer)
    {
        MostRecentPropertyAddress = NULL;

        if (Code)
        {
            Step(Object, TemporaryBuffer);
        }
        else
        {
            // https://imgur.com/a/CvmkuCy
            UProperty* Property = (UProperty*)(*(UField**)(__int64(this) + 0x80));
            *(UField**)(__int64(this) + 0x80) = Property->Next;

            StepExplicitProperty(TemporaryBuffer, Property);
        }

        return (MostRecentPropertyAddress != NULL) ? *(TNativeType*)(MostRecentPropertyAddress) : *(TNativeType*)TemporaryBuffer;
    }
};

struct FActorSpawnParameters
{
    /* A name to assign as the Name of the Actor being spawned. If no value is specified, the name of the spawned Actor will be automatically generated using the form [Class]_[Number]. */
    FName Name = FName(0);

    /* An Actor to use as a template when spawning the new Actor. The spawned Actor will be initialized using the property values of the template Actor. If left NULL the class default object (CDO) will be used to initialize the spawned Actor. */
    AActor* Template = nullptr;

    /* The Actor that spawned this Actor. (Can be left as NULL). */
    AActor* Owner = nullptr;

    /* The APawn that is responsible for damage done by the spawned Actor. (Can be left as NULL). */
    APawn* Instigator = nullptr;

    /* The ULevel to spawn the Actor in, i.e. the Outer of the Actor. If left as NULL the Outer of the Owner is used. If the Owner is NULL the persistent level is used. */
    class	ULevel* OverrideLevel = nullptr;

    /** Method for resolving collisions at the spawn point. Undefined means no override, use the actor's setting. */
    ESpawnActorCollisionHandlingMethod SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::Undefined;

private:

    friend class UPackageMapClient;

    /* Is the actor remotely owned. This should only be set true by the package map when it is creating an actor on a client that was replicated from the server. */
    uint16	bRemoteOwned : 1;

public:

    bool IsRemoteOwned() const { return bRemoteOwned; }

    /* Determines whether spawning will not fail if certain conditions are not met. If true, spawning will not fail because the class being spawned is `bStatic=true` or because the class of the template Actor is not the same as the class of the Actor being spawned. */
    uint16	bNoFail : 1;

    /* Determines whether the construction script will be run. If true, the construction script will not be run on the spawned Actor. Only applicable if the Actor is being spawned from a Blueprint. */
    uint16	bDeferConstruction : 1;

    /* Determines whether or not the actor may be spawned when running a construction script. If true spawning will fail if a construction script is being run. */
    uint16	bAllowDuringConstructionScript : 1;

#if WITH_EDITOR
    /** Determines whether the begin play cycle will run on the spawned actor when in the editor. */
    uint16 bTemporaryEditorActor : 1;
#endif

    /* Flags used to describe the spawned actor/object instance. */
    EObjectFlags ObjectFlags;
};

class Util
{
public:
    template <typename ActorType>
    static ActorType* SpawnActor(UClass* Class, FVector Location = FVector(), FRotator Rotation = FRotator())
    {
        // 7FF670C24D40
        AActor* (*RealSpawnActor)(UWorld* World, UClass* Class, FVector const* Location, FRotator const* Rotation, const FActorSpawnParameters& SpawnParameters) = decltype(RealSpawnActor)(0x25D4D40 + uintptr_t(GetModuleHandle(0)));

        auto SpawnParameters = (FActorSpawnParameters*)VirtualAlloc(0, sizeof(FActorSpawnParameters), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
        SpawnParameters->SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
        SpawnParameters->bDeferConstruction = false;

        AActor* Actor = RealSpawnActor(Globals::GetWorld(), Class, &Location, &Rotation, *SpawnParameters);

        VirtualFree(SpawnParameters, 0, MEM_RELEASE);

        return (ActorType*)Actor;
    }

    template <typename ActorType>
    static ActorType* SpawnActorTransfrom(UClass* Class, FTransform Transform)
    {
        // 7FF670C23D60
        AActor* (*RealSpawnActor)(UWorld* World, UClass* Class, FTransform Transform, const FActorSpawnParameters& SpawnParameters) = decltype(RealSpawnActor)(0x25D3D60 + uintptr_t(GetModuleHandle(0)));

        auto SpawnParameters = (FActorSpawnParameters*)VirtualAlloc(0, sizeof(FActorSpawnParameters), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
        SpawnParameters->SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
        SpawnParameters->bDeferConstruction = false;

        AActor* Actor = RealSpawnActor(Globals::GetWorld(), Class, Transform, *SpawnParameters);

        VirtualFree(SpawnParameters, 0, MEM_RELEASE);

        return (ActorType*)Actor;
    }

    static AFortPlayerPawn* SpawnPlayer(AFortPlayerController* PlayerController, const FVector& Location, const FRotator& Rotation, bool NewPlayer = true)
    {
        APlayerPawn_Athena_C* PlayerPawn = SpawnActor<APlayerPawn_Athena_C>(APlayerPawn_Athena_C::StaticClass(), Location, Rotation);

        if (!PlayerPawn)
        {
            FN_LOG(LogPlayer, Error, L"Failed to spawn PlayerPawn!");
            return nullptr;
        }

        UWorld* World = Globals::GetWorld();

        if (!World)
        {
            FN_LOG(LogPlayer, Error, L"Failed to get World!");
            return nullptr;
        }

        PlayerPawn->bCanBeDamaged = (NewPlayer == true && !World->GetName().contains("Athena_Faceoff")) ? false : true;
        PlayerPawn->Owner = PlayerController;
        PlayerPawn->OnRep_Owner();

        PlayerController->Pawn = PlayerPawn;
        PlayerController->OnRep_Pawn();
        PlayerController->Possess(PlayerPawn);

        if (NewPlayer)
        {
            AFortPlayerState* PlayerState = Cast<AFortPlayerState>(PlayerController->PlayerState);
            PlayerState->bHasFinishedLoading = true;
            PlayerState->bHasStartedPlaying = true;
            PlayerState->OnRep_bHasStartedPlaying();

            PlayerPawn->SetMaxHealth(100);
            PlayerPawn->SetHealth(100);
            PlayerPawn->SetMaxShield(100);

            // 7FF66F7BC760 (Je suis sévèrement autiste)
            void (*SetShield)(AFortPawn* Pawn, float NewShieldValue) = decltype(SetShield)(0x116C760 + uintptr_t(GetModuleHandle(0)));
            SetShield(PlayerPawn, 0);

            PlayerController->bIsDisconnecting = false;
            PlayerController->bHasClientFinishedLoading = true;
            PlayerController->bHasServerFinishedLoading = true;
            PlayerController->bHasInitiallySpawned = true;
        }

        return PlayerPawn;
    }
};