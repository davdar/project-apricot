#include "Sprite.h"

Sprite::Sprite(){}

Sprite::Sprite(const Sprite &sprite)
:translation(sprite.translation), animation(sprite.animation)
{}

Sprite::~Sprite(){}

void Sprite::setTranslation(const Vector2 &in_translation){ translation = in_translation; }

const Vector2 &Sprite::getTranslation(){ return translation; }


void Sprite::setAnimation(Animation *in_animation){ animation = in_animation; }
Animation *Sprite::getAnimation(){ return animation; }

void Sprite::setFrame(int in_frame){ frame = in_frame; }
int Sprite::getFrame(){ return frame; }
