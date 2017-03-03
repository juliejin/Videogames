//
//  AudioComponent.cpp
//  Game-mac
//
//  Created by apple on 1/26/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#include "AudioComponent.h"
#include "Actor.h"
#include <SDL/SDL_mixer.h>
IMPL_COMPONENT(AudioComponent, Component);

AudioComponent::AudioComponent(Actor& owner):Component(owner){
    
}

SoundCue AudioComponent::PlaySound(SoundPtr sound, bool looping ){
    int para = 0;
    if(looping)
        para=-1;

    return Mix_PlayChannel(-1, sound->GetData(), para);
}

SoundCue::SoundCue(){
    mChannel = -1;
}

SoundCue::SoundCue(int a){
    mChannel = a;
}

void SoundCue::Pause(){
    Mix_Pause(mChannel);
}
void SoundCue::Resume(){
    Mix_Resume(mChannel);
}
void SoundCue::Stop(){
    Mix_HaltChannel(mChannel);
}
bool SoundCue::IsPlaying(){
    return Mix_Playing(mChannel);
}
bool SoundCue::IsPaused(){
    return Mix_Paused(mChannel);
}