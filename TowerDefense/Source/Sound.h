//
//  Sound.h
//  Game-mac
//
//  Created by apple on 1/26/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#pragma once
#include "Asset.h"


class Sound: public Asset{
     DECL_ASSET(Sound, Asset);
    
public:
    Sound();
    ~Sound();
    bool Load(const char* fileName, class AssetCache* cache) override;
    struct Mix_Chunk* GetData();

private:
    struct Mix_Chunk* mData;
};
DECL_PTR(Sound);