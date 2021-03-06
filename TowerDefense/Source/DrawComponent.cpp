#include "DrawComponent.h"
#include "Actor.h"
#include "Game.h"

IMPL_COMPONENT(DrawComponent, Component);

DrawComponent::DrawComponent(Actor& owner)
	:Component(owner)
	,mIsVisible(true)
{

}

void DrawComponent::Register()
{
	Super::Register();
	// Register myself with the Renderer
	mOwner.GetGame().GetRenderer().AddComponent(ThisPtr());
}

void DrawComponent::Unregister()
{
	Super::Unregister();
	// Unregister myself
	mOwner.GetGame().GetRenderer().RemoveComponent(ThisPtr());
}

void DrawComponent::Draw(class Renderer& render)
{

}
