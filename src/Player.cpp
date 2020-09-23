#include "Player.hpp"


Player::Player(std::shared_ptr<SpriteSheet> sheet, int width, int height, std::shared_ptr<Background> bg)
    : Sprite(sheet, width, height, bg), KeyboardEventListener() {

        
        

        state = State::IDDLE_RIGHT;
        spriteRect->x = 50;
        spriteRect->y = 603;

        jumpSpeed = 0.2f;    
        jumpApex = 553;
        
        
    
        SDL_QueryTexture(bg->getTexture(), NULL,NULL, &textureWidth, NULL);
        
    }

Player::~Player(){
    
}


void Player::draw(SDL_Renderer *renderer){

    // reset helper ! delete, when it hit walls repeat
    // if(this->spriteRect->y <= 0 || this->spriteRect->y > 800 || this->spriteRect->x >= 1000){
    //     this->spriteRect->y = 600;
    //     this->spriteRect->x = 10;
    // }

    
    // Limits initial frame so it doesnt make overflow of vector of animations
    if(state == State::IDDLE_RIGHT || state == State::IDDLE_LEFT){
        if(initialFrame >= 16) {
            initialFrame = 0;
        }
    } else if(state == State::RIGHT || state == State::LEFT || state == State::JUMP){
        if(initialFrame >= 14) {
            initialFrame = 0;
        }
    } else if (state == State::ATTACK){
        if(initialFrame >= 15){
            initialFrame = 0;
        }
    } else if(state == State::DYING){
        if(initialFrame >= 14){
            initialFrame = 0;
        }
    } else if(state == State::DEAD){
        if(initialFrame >= 14){
            initialFrame = 0;
        }
    }

    frameCounter++;
    
    if(frameCounter%frameSkip == 0) {
        initialFrame++;
        frameCounter = 0;
    }

    
    
    

    if(state == State::IDDLE_RIGHT){
        spriteSheet->drawRect(renderer, "iddle_blinking", initialFrame, spriteRect);
    } else if (state == State::IDDLE_LEFT){
        spriteSheet->drawFlippedRect(renderer, "iddle_blinking", initialFrame, spriteRect, flip);
    } else if (state == State::RIGHT){
        spriteSheet->drawRect(renderer, "walking", initialFrame, spriteRect);
    } else if (state == State::LEFT){
        spriteSheet->drawFlippedRect(renderer, "walking", initialFrame, spriteRect, flip);
    } else if (state == State::JUMP){
         spriteSheet->drawRect(renderer, "walking", initialFrame, spriteRect);   
    } else if (state == State::ATTACK){
        spriteSheet->drawRect(renderer, "slashing", initialFrame, spriteRect);
    } else if (state == State::DYING){
        spriteSheet->drawRect(renderer, "dying", initialFrame, spriteRect);
    } else if (state == State::DEAD){
        spriteSheet->drawRect(renderer, "dead", initialFrame, spriteRect);
    }
    
    
    
    
}


    

/*
** move **
desc:
    defines method of moving the character(running has different speed than walking, jumping...)
params:
    dX - X coordinate of destination rectangle, 
    dY - Y coordinate of destination rectangle, 
return: void - 
*/
void Player::move(int dX, int dY){
    isMoving = true;

    // Restricts to move to left end of texture
    if(bg->getSrcRect()->x + dX <= 0){
        return;
    }

    // If dead restrict move
    


    
    
    // Restricts to move to the end of texture
    if(bg->getSrcRect()->x + dX > textureWidth - 1070){
        return;
    }
    
    // Allows player to move to the center and back, but when it's centered then it moves the background
    if(spriteRect->x + dX <= 300 && spriteRect->x +dX >= 50){
        spriteRect->x += dX / 3;
   }
    
    // spriteRect->x += dX;
    // spriteRect->y += dY;
    bg->setSrcRectX(bg->getSrcRect()->x + dX);
    bg->setDestRectW(bg->getDestRect()->w - dX);
    

    
}

void Player::move(){
    if(state != 0){
        // walking left
        if(state == 2){
            move(-5, 0);
        }
        // walking right
        if(state == 3){
            move(5, 0);
        }
        // jumping
        if(state == 4){
            // move(0, -30);
            jump();
        } if (state == 8){
            // std::cout << "Slash" << std::endl;
        }
        
    }
}

/*
** listenForKeyboardEvent **
desc:
    Waits for key presses and changes states accordingly 
params:
    event - structure that contains keyboard button information, 
return:  void - 
*/
void Player::listenForKeyboardEvent(SDL_KeyboardEvent &event){
    switch (event.keysym.sym)
    {
    case SDLK_d:
        state = State::RIGHT;
        isMoving = true;
        break;
    case SDLK_a:
        state = State::LEFT;
        isMoving = true;
        break;
    case SDLK_SPACE:        
        state = State::JUMP;
        break;    
    case SDLK_j:
        state = State::ATTACK;
        break;
    case SDLK_k:
        state = State::DYING;
        break;
    case SDLK_ESCAPE:
        quit = true;
    default:
        break;
    }

    
}



void Player::jump(){
    
    if(spriteRect->y > jumpApex){
        spriteRect->y -= 100 * jumpSpeed;
        jumping = true;
    }
    
    
}


bool Player::checkCollision(SDL_Rect *enemy){
    // Border Box collision
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    
    leftA = spriteRect->x;
    rightA = spriteRect->x + (spriteRect->w - 40); // we subtract 40 px of width and height because our sprites are 128x128 and they're placed in the middle so we have blank space around them
    topA = spriteRect->y;
    bottomA = spriteRect->y + (spriteRect->h - 40);

    
    leftB = enemy->x;
    rightB = enemy->x + (enemy->w - 40);
    topB = enemy->y;
    bottomB = enemy->y + (enemy->h - 40);

    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    return true;
}



bool Player::getIsMoving(){ return this->isMoving; }
void Player::setIsMoving(bool move){ this->isMoving = move; }
bool Player::getIsDead(){ return this->isDead; }
void Player::setIsDead(bool dead){ this->isDead = dead; }
bool Player::getQuit(){ return this->quit; }