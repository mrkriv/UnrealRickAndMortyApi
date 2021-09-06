#include "RickAndMortyApi.h"

FString RickAndMortyApi::GetURLBase()
{
    return TEXT("https://rickandmortyapi.com/api");
}

FString RickAndMortyApi::GetURLCharacters(int page)
{
    return FString::Printf(TEXT("%s/character/?page=%d"), *GetURLBase(), page);
}

FString RickAndMortyApi::GetURLCharacter(int id)
{
    return FString::Printf(TEXT("%s/character/%d"), *GetURLBase(), id);
}

FString RickAndMortyApi::GetURLocations(int page)
{
    return FString::Printf(TEXT("%s/locations/?page=%d"), *GetURLBase(), page);
}

FString RickAndMortyApi::GetUREpisodes(int page)
{
    return FString::Printf(TEXT("%s/episodes/?page=%d"), *GetURLBase(), page);
}