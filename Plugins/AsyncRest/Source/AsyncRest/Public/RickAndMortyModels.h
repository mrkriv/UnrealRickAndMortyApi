#pragma once

#include "RickAndMortyModels.generated.h"

USTRUCT(Blueprintable)
struct FRaMPageInfoResponse
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Next;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Prev;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Count;    

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Pages;    
};

USTRUCT(Blueprintable)
struct FRaMLocation
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Name;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Url;
};

USTRUCT(Blueprintable)
struct FRaMCharacter
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int Id;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Name;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Status;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Species;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Type;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Gender;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FRaMLocation Origin;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FRaMLocation Location;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Image;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> Episode;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Url;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FDateTime Created;
};

USTRUCT(Blueprintable)
struct FRaMCharacterPageResponse
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FRaMPageInfoResponse Info;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FRaMCharacter> Results;
};
