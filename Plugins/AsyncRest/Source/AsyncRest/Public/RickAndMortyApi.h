#pragma once

#include "CoreMinimal.h"

class RickAndMortyApi
{
public:
    static FString GetURLBase();
    static FString GetURLCharacters(int page);
    static FString GetURLCharacter(int id);
    static FString GetURLocations(int page);
    static FString GetUREpisodes(int page);
};

