#include "Enemy.hpp"


Enemy::Enemy(std::shared_ptr<SpriteSheet> sheet, int width, int height, std::shared_ptr<Background> bg, int position)
    : Sprite(sheet, width, height, bg) {

        state = State::LEFT;
        spriteRect->x = bg->getDestRectX() + position;
        

        // bg->setSrcRectX(bg->getSrcRect()->x + dX);
        
        
    }

Enemy::~Enemy(){

}

void Enemy::draw(SDL_Renderer *renderer){
    
    

    if(state == State::LEFT){
        if(initialFrame >= 20){
            initialFrame = 0;
        }
    } else if(state == State::DYING){
        if(initialFrame >= 19){
            initialFrame = 0;
        }
    }
    frameCounter++;
    if(frameCounter%frameSkip == 0){
        initialFrame++;
        frameCounter = 0;
    }


    if(state == State::LEFT){
        spriteSheet->drawFlippedRect(renderer, "walking", initialFrame, spriteRect, flip);
    } else if (state == State::DYING){
        spriteSheet->drawFlippedRect(renderer, "dying", initialFrame, spriteRect, flip);
    }
}

void Enemy::move(int dX, int dY){
    spriteRect->x += dX;
    spriteRect->y += dY;    
}

void Enemy::move(){
    move(-3, 0);
}


/*
** listenForPlayerMove **
desc:
    When player is moving, it moves the background, so we need to update enemies positions
return: void - 
*/
void Enemy::listenForPlayerMove(std::shared_ptr<Player> player){
    if(!moving){
        return;
    }
    if(player->getIsMoving()){
        move(-10, 0);
    } 
     else {
        move(-5, 0);
        
    } 
    // If player moves left we update the position of enemy to right
    if(player->getState() == 2){
        move(10, 0);
    }
}


void Enemy::setMoving(bool move){ this->moving = move; }
bool Enemy::getMoving(){ return this->moving; }