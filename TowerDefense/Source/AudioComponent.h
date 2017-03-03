//
//  AudioComponent.h
//  Game-mac
//
//  Created by apple on 1/26/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#pragma once

#include "Component.h"
#include "Sound.h"

class SoundCue{
private:
    int mChannel;
public:
    SoundCue();
    SoundCue(int a);
    void Pause();
    void Resume();
    void Stop();
    bool IsPlaying();
    bool IsPaused();
};

class AudioComponent: public Component{
    DECL_COMPONENT(AudioComponent, Component);
public:
    AudioComponent(Actor& owner);
    SoundCue PlaySound(SoundPtr sound, bool looping = false);
};
DECL_PTR(AudioComponent);