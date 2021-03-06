#include "ball.h"


void initVector(struct vector_t *v, int32_t x, int32_t y) {
    v->x = x << FIX14_SHIFT;
    v->y = y << FIX14_SHIFT;
}

void initBall(struct ball_t *b, int32_t x, int32_t y, int32_t vx, int32_t vy, uint8_t aliveOrDead){
    initVector(&(b->pos), x, y);
    initVector(&(b->vel), vx, vy);
    (b->state) = aliveOrDead;
}




void updatePosition(struct ball_t *b, int32_t x1, int32_t y1, int32_t x2, int32_t y2, uint8_t playingField[128][32], uint8_t *bricks, uint8_t *lives, uint8_t *score, struct powerUp_t *p, uint8_t *balls, uint8_t *menuSettings){
    int32_t cx, cy, len;
    int8_t i, j, strikerLeft, strikerRight, powerUpLeftOrRight;
    uint8_t leftOrRight, q;

    // Find striker left
    for(q=1; q<32; q++){
        if (playingField[0][q] == 179){
            strikerLeft = q;
            break;
        }
    }
    // Find striker right
    for(q=1; q<32; q++){
        if (playingField[100][q] == 179){
            strikerRight = q;
            break;
        }
    }
    cx = (b->pos).x + (b->vel).x;
    cy = (b->pos).y + (b->vel).y;
    leftOrRight = ((cx <= ((x1+1) << FIX14_SHIFT))?1:0); // Is the ball left or right? Left = 1
    len = 2;

    if(b->state == 0){ // If ball dead at left striker
        initBall(b, x1+1, 5+strikerLeft, 0, 0, 0);
        if(readJoystick() & (0x001 << 3)){
            initBall(b, x2-1, 5+strikerRight, 0, 0, 1);
        }
        else if(readJoystick() & (0x001 << 0)){
            initBall(b, x1+1, 5+strikerLeft, 1, 1, 2);
            rotate(&(b->vel), -64);
        }
    }
    if(b->state == 1){ // If ball dead at right striker
        initBall(b, x2-1, 5+strikerRight, 0, 0, 1);
        if(readJoystick() & (0x001 << 2)){
            initBall(b, x1+1, 5+strikerLeft, 0, 0, 0);
        }
        else if(readJoystick() & (0x001 << 0)){
            initBall(b, x2-1, 5+strikerRight, -1, 1, 2);
            rotate(&(b->vel), 64);
        }
    }
    else if((b->state) == 2){
        if (cy <= ((y1+1) << FIX14_SHIFT) || cy >= ((y2-1) << FIX14_SHIFT)){ // If it hits top/bottom (regular bounce)
            (b->vel).y = -((b->vel).y);
            cx = (b->pos).x + (b->vel).x;
            cy = (b->pos).y + (b->vel).y;
        }

        if (cx <= ((x1) << FIX14_SHIFT) || cx >= ((x2) << FIX14_SHIFT)){ // When the ball hits a striker
            // Top of the striker?
            if((leftOrRight)?(cy > ((strikerLeft) << FIX14_SHIFT) && cy <= ((len+strikerLeft) << FIX14_SHIFT)):(cy > (strikerRight << FIX14_SHIFT) && cy <= ((len+strikerRight) << FIX14_SHIFT))){
                (b->vel).x = -((b->vel).x);
                if(leftOrRight){ // Striker left or right?
                    rotate(&(b->vel), -43);
                }else{
                    rotate(&(b->vel), 43);
                    }
                if(leftOrRight){ // If the angle is too small, prevents it being stuck
                    if((b->vel).x<MINVELX){
                        (b->vel).x = MINVELX;
                        (b->vel).y = MINVELY;
                    }
                }else{
                    if((b->vel).x>-MINVELX){
                        (b->vel).x = -MINVELX;
                        (b->vel).y = -MINVELY;
                    }
                }
            }
            // Almost the top of the striker?
            else if((leftOrRight)?(cy > ((len+strikerLeft) << FIX14_SHIFT) && cy <= (((len*2)+strikerLeft) << FIX14_SHIFT)):(cy > ((len+strikerRight) << FIX14_SHIFT) && cy <= (((len*2)+strikerRight) << FIX14_SHIFT))){
                (b->vel).x = -((b->vel).x);
                if(leftOrRight){ // Striker left or right?
                    rotate(&(b->vel), -21);
                }else{
                    rotate(&(b->vel), 21);
                }
                if(leftOrRight){ // If the angle is too small, prevents it being stuck
                    if((b->vel).x<MINVELX){
                        (b->vel).x = MINVELX;
                    }
                }else{
                    if((b->vel).x>-MINVELX){
                        (b->vel).x = -MINVELX;
                    }
                }
            }
            // Hit mid?
            else if((leftOrRight)?(cy > (((len*2)+strikerLeft) << FIX14_SHIFT) && cy <= (((len*3)+strikerLeft) << FIX14_SHIFT)):(cy > (((len*2)+strikerRight) << FIX14_SHIFT) && cy <= (((len*3)+strikerRight) << FIX14_SHIFT))){  //nest�verste, tjekker
                (b->vel).x = -((b->vel).x);
            }
            // Hit mid bottom?
            else if((leftOrRight)?(cy > (((len*3)+strikerLeft) << FIX14_SHIFT) && cy <= (((len*4)+strikerLeft) << FIX14_SHIFT)):(cy > (((len*3)+strikerRight) << FIX14_SHIFT) && cy <= (((len*4)+strikerRight) << FIX14_SHIFT))){  //nest�verste, tjekker
                 (b->vel).x = -((b->vel).x);
                 if(leftOrRight){ // Striker left or right?
                    rotate(&(b->vel), 21);
                }else{
                    rotate(&(b->vel), -21);
                }
                if(leftOrRight){ // If the angle is too small, prevents it being stuck
                    if((b->vel).x<MINVELX){
                        (b->vel).x = MINVELX;
                    }
                }else{
                    if((b->vel).x>-MINVELX){
                        (b->vel).x = -MINVELX;
                    }
                }
            }
            // Hit bottom ?
            else if((leftOrRight)?(cy > (((len*4)+strikerLeft) << FIX14_SHIFT) && cy < ((len*5)+strikerLeft) << FIX14_SHIFT):(cy > (((len*4)+strikerRight) << FIX14_SHIFT) && cy <= (((len*5)+strikerRight) << FIX14_SHIFT))){  //nest�verste, tjekker
                (b->vel).x = -((b->vel).x);
                if(leftOrRight){ // Striker left or right?
                    rotate(&(b->vel), 43);
                }else{
                    rotate(&(b->vel), -43);
                }
                if(leftOrRight){ // If the angle is too small, prevents it being stuck
                    if((b->vel).x<MINVELX){
                        (b->vel).x = MINVELX;
                    }
                }else{
                    if((b->vel).x>-MINVELX){
                        (b->vel).x = -MINVELX;
                    }
                }
            }
            cx = (b->pos).x + (b->vel).x; // Update position for more checks
            cy = (b->pos).y + (b->vel).y;

            if(cx < ((x1) << FIX14_SHIFT)){ // Based on new position, if outside left striker
                if ((*balls) > 1){ // More than one ball, just remove the ball
                    initBall(b, x1+1, 5+strikerLeft, 0, 0, 3);
                    (*balls)--;
                }else{
                    if ((*lives) > 0 ) {
                        initBall(b, x1+1, 5+strikerLeft, 0, 0, 1);
                        (*lives)--;
                    } else {
                        (*menuSettings) |= (0x01 << 6);
                        youLoseScreen(playingField, (*score));
                    }
                }
            }
            else if(cx > ((x2) << FIX14_SHIFT)){ // Based on new position, if outside right striker
                if ((*balls) > 1){ // More than one ball, just remove the ball
                    initBall(b, x1+1, 5+strikerRight, 0, 0, 3);
                    (*balls)--;
                }else{
                    if ((*lives) > 0 ) {
                        initBall(b, x2-1, 5+strikerRight, 0, 0, 1);
                        (*lives)--;
                    } else {
                        (*menuSettings) |= (0x01 << 6);
                        youLoseScreen(playingField, (*score));
                    }
                }
            }
        }

        i = cx >> FIX14_SHIFT; // Rounded version of ball position for brick check
        j = cy >> FIX14_SHIFT;

        // If the ball hits a brick it will then try and figure out where the upmost
        // left corner is, so it can send it to remove brick.
        if (playingField[i][j] != 0 && cy >= ((y1+2) << FIX14_SHIFT) && cy <= ((y2-2) << FIX14_SHIFT) && cx >= ((x1+2) << FIX14_SHIFT) && cx <= ((x2-2) << FIX14_SHIFT)){
            // Figure out what side of the brick it is hit
            // for when a powerup might spawn
            if ((b->vel).x > 0){
                powerUpLeftOrRight = -1;
            } else {
                powerUpLeftOrRight = 1;
            }
            if (playingField[i][j]==196){ // If the ball hits a horizontal line on the brick
                while (playingField[i][j] != 192 && playingField[i][j] != 218){
                    i--;
                }
                if (playingField[i][j] == 192){
                    while(playingField[i][j] != 218){
                        j--;
                    }
                    removeBrick(i, j, playingField, bricks, p, powerUpLeftOrRight, score);
                } else if(playingField[i][j] == 218){
                    removeBrick(i, j, playingField, bricks, p, powerUpLeftOrRight, score);
                }
                // Corner found and brick removed, change ball velocity
                (b->vel).y = -((b->vel).y);
                cx = (b->pos).x + (b->vel).x;
                cy = (b->pos).y + (b->vel).y;
            } else if (playingField[i][j] == 179){ // If the ball hits a vertical brick line
                while (playingField[i][j] != 218 && playingField[i][j] != 191){
                    j--;
                } if (playingField[i][j] == 191){
                    while (playingField[i][j] != 218){
                        i--;
                    }
                    removeBrick(i, j, playingField, bricks, p, powerUpLeftOrRight, score);
                }else if (playingField[i][j] == 218){
                    removeBrick(i, j, playingField, bricks, p, powerUpLeftOrRight, score);
                }
                (b->vel).x = -((b->vel).x);
                cx = (b->pos).x + (b->vel).x;
                cy = (b->pos).y + (b->vel).y;
            } else if (playingField[i][j] == 192){ // Ball hit the down-left most corner
                if(playingField[i-1][j] == 217){ // How are the nearby bricks oriented
                    (b->vel).y = -((b->vel).y);
                }
                if (playingField[i][j+1] == 218){
                    (b->vel).x = -((b->vel).x);
                }
                else{
                    if ((b->vel).x<0 && (b->vel).y>0){ //if the ball hits the brick in an upward-left velocity
                        (b->vel).y = -((b->vel).y);
                    }
                    if ((b->vel).x>0 && (b->vel).y<0){ //if the ball hits the brick in an downward-right velocity
                        (b->vel).x = -((b->vel).x);
                    } else {
                        (b->vel).x = -((b->vel).x);
                        (b->vel).y = -((b->vel).y);
                    }
                }
                cx = (b->pos).x + (b->vel).x;
                cy = (b->pos).y + (b->vel).y;
                while (playingField[i][j] != 218){
                    j--;
                }
                removeBrick(i, j, playingField, bricks, p, powerUpLeftOrRight, score);
            } else if (playingField[i][j] == 218){ // Upmost left corner is hit
                if (playingField[i-1][j] == 191){ // Where are the nearby bricks located
                    (b->vel).y = -((b->vel).y);
                }
                if (playingField[i][j-1] == 192){
                    (b->vel).x = -((b->vel).x);
                } else {
                    if ((b->vel).x<0 && (b->vel).y<0){ // If the ball hits the brick in an downward-left velocity
                        (b->vel).y = -((b->vel).y);
                    }if ((b->vel).x>0 && (b->vel).y>0){ // If the ball hits the brick in an upward-right velocity
                        (b->vel).x = -((b->vel).x);
                    } else {
                        (b->vel).x = -((b->vel).x);
                        (b->vel).y = -((b->vel).y);
                    }
                }
                removeBrick(i, j, playingField, bricks, p, powerUpLeftOrRight, score);
                cx = (b->pos).x + (b->vel).x;
                cy = (b->pos).y + (b->vel).y;
            } else if (playingField[i][j] == 191){ // top-right corner is hit
                if (playingField[i+1][j] == 218){ // How are the surrounding bricks located?
                    (b->vel).y = -((b->vel).y);
                }
                if (playingField[i][j-1] == 217){
                    (b->vel).x = -((b->vel).x);
                } else {
                    if ((b->vel).x<0 && (b->vel).y>0){ // If the ball hits the brick in an upward-left velocity
                        (b->vel).x = -((b->vel).x);
                    } if ((b->vel).x>0 && (b->vel).y<0){ // If the ball hits the brick in an downward-right velocity
                        (b->vel).y = -((b->vel).y);
                    } else {
                        (b->vel).x = -((b->vel).x);
                        (b->vel).y = -((b->vel).y);
                    }
                }
                cx = (b->pos).x + (b->vel).x;
                cy = (b->pos).y + (b->vel).y;
                while (playingField[i][j] != 218){
                    i--;
                }
                removeBrick(i, j, playingField, bricks, p, powerUpLeftOrRight, score);
            } else if (playingField[i][j] == 217){ //Down-right corner is hit
                if(playingField[i+1][j] == 192){ // How are the surrounding bricks located?
                    (b->vel).y = -((b->vel).y);
                }
                if(playingField[i][j+1] == 191){
                    (b->vel).x = -((b->vel).x);
                }
                else{
                    if((b->vel).x<0 && (b->vel).y<0){ // If the ball hits the brick in an downward-left velocity
                        (b->vel).x = -((b->vel).x);
                    }if((b->vel).x>0 && (b->vel).y>0){ // If the ball hits the brick in an upward-right velocity
                        (b->vel).y = -((b->vel).y);
                    }else{
                        (b->vel).x = -((b->vel).x);
                        (b->vel).y = -((b->vel).y);
                    }
                }
                cx = (b->pos).x + (b->vel).x;
                cy = (b->pos).y + (b->vel).y;
                // Find upmost left corner
                while(playingField[i][j] != 192){
                    i--;
                }
                while(playingField[i][j] != 218){
                    j--;
                }
                removeBrick(i, j, playingField, bricks, p, powerUpLeftOrRight, score);
            }
        }
        (b->pos).x = cx; // Final update to ball position
        (b->pos).y = cy;
    }
}




void ballToArray(struct ball_t *b, uint8_t playingField[128][32]){
    if(b->state != 3){ //If the ball isnt perma-dead
        if(playingField[(b->pos).x >> FIX14_SHIFT][(b->pos).y >> FIX14_SHIFT] == 0){
            playingField[(b->pos).x >> FIX14_SHIFT][(b->pos).y >> FIX14_SHIFT] = 111;
        }
    }
}



void removeBallFromArray(struct ball_t *b, uint8_t playingField[128][32]) {
    // Remove ball, but make sure you dont remove it if something else is there
    // since it will remove that "something"
    if(playingField[(b->pos).x >> FIX14_SHIFT][(b->pos).y >> FIX14_SHIFT] == 111){
        playingField[(b->pos).x >> FIX14_SHIFT][(b->pos).y >> FIX14_SHIFT] = 0;
    }
}

/*
void removePowerUpFromArray(struct powerUp_t *p, uint8_t playingField[128][32]) {
    // Remove if it is alive
    if((p->vel)>0){
        if(playingField[p->x-1][p->y-1] == 92){
            playingField[p->x-1][p->y-1] = 0;
        }
        if(playingField[p->x][p->y] == 62){
            playingField[p->x][p->y] = 0;
        }
        if(playingField[p->x-1][p->y+1] == 47){
            playingField[p->x-1][p->y+1] = 0;
        }
    } else {
        if(playingField[p->x+1][p->y-1] == 47){
            playingField[p->x+1][p->y-1] = 0;
        }
        if(playingField[p->x][p->y] == 60){
            playingField[p->x][p->y] = 0;
        }
        if(playingField[p->x+1][p->y+1] == 92){
            playingField[p->x+1][p->y+1] = 0;
        }
    }
}
*/
void updatePlayer(uint8_t a[128][32],uint16_t adc1,uint16_t adc2){

    uint8_t i;



    // Remove everything in the player line.
    for (i = 1; i < 31; i++) {
        a[0][i] = 0;
        a[100][i] = 0;
    }

    //player 1 replace
    for (i = (adc1+1); i < (adc1+11); i++) {
        a[0][i]=179;
    }

    //player 2 replace
    for (i = (adc2+1); i < (adc2+11); i++) {
        a[100][i]=179;
    }
}
