//
//  Sound.cpp
//  Game-mac
//
//  Created by apple on 1/26/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#include "Sound.h"
#include <SDL/SDL_mixer.h>
#include <SDL/SDL.h>

Sound::Sound():Asset(){
    mData = nullptr;
}

Sound::~Sound(){
    if(mData!=nullptr){
        Mix_FreeChunk(mData);
    }
}

bool Sound::Load(const char* fileName, class AssetCache* cache){
    mData = Mix_LoadWAV(fileName);
    if(mData == nullptr){
        SDL_Log("Failed to load audio file");
        return false;
    }
    return true;
}

Mix_Chunk* Sound::GetData(){
    return mData;
}