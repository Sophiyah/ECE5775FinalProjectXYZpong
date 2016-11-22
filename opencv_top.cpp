/***************************************************************************

*   © Copyright 2013 Xilinx, Inc. All rights reserved. 

*   This file contains confidential and proprietary information of Xilinx,
*   Inc. and is protected under U.S. and international copyright and other
*   intellectual property laws. 

*   DISCLAIMER
*   This disclaimer is not a license and does not grant any rights to the
*   materials distributed herewith. Except as otherwise provided in a valid
*   license issued to you by Xilinx, and to the maximum extent permitted by
*   applicable law: (1) THESE MATERIALS ARE MADE AVAILABLE "AS IS" AND WITH
*   ALL FAULTS, AND XILINX HEREBY DISCLAIMS ALL WARRANTIES AND CONDITIONS, 
*   EXPRESS, IMPLIED, OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES
*   OF MERCHANTABILITY, NON-INFRINGEMENT, OR FITNESS FOR ANY PARTICULAR 
*   PURPOSE; and (2) Xilinx shall not be liable (whether in contract or 
*   tort, including negligence, or under any other theory of liability)
*   for any loss or damage of any kind or nature related to, arising under
*   or in connection with these materials, including for any direct, or any
*   indirect, special, incidental, or consequential loss or damage (including
*   loss of data, profits, goodwill, or any type of loss or damage suffered 
*   as a result of any action brought by a third party) even if such damage
*   or loss was reasonably foreseeable or Xilinx had been advised of the 
*   possibility of the same. 

*   CRITICAL APPLICATIONS 
*   Xilinx products are not designed or intended to be fail-safe, or for use
*   in any application requiring fail-safe performance, such as life-support
*   or safety devices or systems, Class III medical devices, nuclear facilities,
*   applications related to the deployment of airbags, or any other applications
*   that could lead to death, personal injury, or severe property or environmental
*   damage (individually and collectively, "Critical Applications"). Customer
*   assumes the sole risk and liability of any use of Xilinx products in Critical
*   Applications, subject only to applicable laws and regulations governing 
*   limitations on product liability. 

*   THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS PART OF THIS FILE AT 
*   ALL TIMES.

***************************************************************************/

#include "opencv_top.h"
#include "top.h"
//#include <allegro.h>
#include <cstdlib>
//#include <time.h>
void opencv_image_filter(IplImage* src, IplImage* dst) {
    IplImage* tmp = cvCreateImage(cvGetSize(src), src->depth, src->nChannels);
    cvCopy(src, tmp);
    cvSobel(tmp, dst, 1, 0);
    cvSubS(dst, cvScalar(50,50,50), tmp);
    cvScale(tmp, dst, 2, 0);
    cvErode(dst, tmp);
    cvDilate(tmp, dst);
    cvReleaseImage(&tmp);
}

void sw_image_filter(IplImage* src, IplImage* dst) {
    AXI_STREAM src_axi, dst_axi;
    IplImage2AXIvideo(src, src_axi);
    image_filter(src_axi, dst_axi, src->height, src->width);
    AXIvideo2IplImage(dst_axi, dst);
}
/******************************game implementation********************************/

int ball_x = 320;
int ball_y = 240;

int ball_tempX = 320;
int ball_tempY = 240;

int p1_x = 20;
int p1_y = 210;

int p1_tempX = 20;
int p1_tempY = 210;

int p2_x = 620;
int p2_y = 210;

int p2_tempX = 620;
int p2_tempY = 210;
int n = 0;

//time_t secs;    //The seconds on the system clock will be stored here
                //this will be used as the seed for srand()

int dir;     //This will keep track of the circles direction
            //1= up and left, 2 = down and left, 3 = up and right, 4 = down and right

//BITMAP *buffer; //This will be our temporary bitmap for double buffering

void moveBall(){

    ball_tempX = ball_x;
    ball_tempY = ball_y;

    if (dir == 1 && ball_x > 5 && ball_y > 5){
     
         if( ball_x == p1_x + 15 && ball_y >= p1_y && ball_y <= p1_y + 60){
                  dir = rand()% 2 + 3;
         }else{    
                 --ball_x;
                 --ball_y;
         }    
              
    } else if (dir == 2 && ball_x > 5 && ball_y < 475){

         if( ball_x == p1_x + 15 && ball_y >= p1_y && ball_y <= p1_y + 60){
                  dir = rand()% 2 + 3;
         }else{    
                 --ball_x;
                 ++ball_y;
         }

    } else if (dir == 3 && ball_x < 635 && ball_y > 5){

         if( ball_x + 5 == p2_x && ball_y >= p2_y && ball_y <= p2_y + 60){
                  dir = rand()% 2 + 1;
         }else{    
                 ++ball_x;
                 --ball_y;
         }

    } else if (dir == 4 && ball_x < 635 && ball_y < 475){

         if( ball_x + 5 == p2_x && ball_y >= p2_y && ball_y <= p2_y + 60){
                  dir = rand()% 2 + 1;
         }else{    
                 ++ball_x;
                 ++ball_y;
         }

    } else { 

        if (dir == 1 || dir == 3)    ++dir;
        else if (dir == 2 || dir == 4)    --dir;

    }    
        

	printf("ball_y, %d, ball_x, %d, direction, %d, p1_x,%d, p1_y, %d, p2_x, %d, p2_y, %d \n", ball_y, ball_x, dir, p1_x, p1_y, p2_x, p2_y);
//	printf("dir %d \n", dir);
//    acquire_screen();
//    circlefill ( buffer, ball_tempX, ball_tempY, 5, makecol( 0, 0, 0));
//    circlefill ( buffer, ball_x, ball_y, 5, makecol( 128, 255, 0));
//    draw_sprite( screen, buffer, 0, 0);
//    release_screen();
    
//    rest(5);

}    

//void p1Move(){
 
//    p1_tempY = p1_y;
 
//    if( key[KEY_W] && p1_y > 0){
     
//        --p1_y;
              
//    } else if( key[KEY_S] && p1_y < 420){
     
//        ++p1_y;
              
//    }     
    
//    acquire_screen();
//    rectfill( buffer, p1_tempX, p1_tempY, p1_tempX + 10, p1_tempY + 60, makecol ( 0, 0, 0));
//    rectfill( buffer, p1_x, p1_y, p1_x + 10, p1_y + 60, makecol ( 0, 0, 255));
//    release_screen();
          
//}  

//void p2Move(){
 
//    p2_tempY = p2_y;
 
//    if( key[KEY_UP] && p2_y > 0){
     
//        --p2_y;
              
//    } else if( key[KEY_DOWN] && p2_y < 420){
     
//        ++p2_y;
              
//    }     
    
//    acquire_screen();
//    rectfill( buffer, p2_tempX, p2_tempY, p2_tempX + 10, p2_tempY + 60, makecol ( 0, 0, 0));
//    rectfill( buffer, p2_x, p2_y, p2_x + 10, p2_y + 60, makecol ( 0, 0, 255));
//    release_screen();
          
//}    

void startNew(){

//    clear_keybuf();
//   readkey();
//    clear_to_color( buffer, makecol( 0, 0, 0));
    ball_x = 320;
    ball_y = 240;

    p1_x = 20;
    p1_y = 210;

    p2_x = 620;
    p2_y = 210;
    
    dir = rand() % 4 + 1;   // from setup game
    n++;
    printf("n %d \n", n);
}    

//void checkWin(){

//    if ( ball_x < p1_x){
//        textout_ex( screen, font, "Player 2 Wins!", 320, 240, makecol( 255, 0, 0), makecol( 0, 0, 0)); 
//        startNew();
//    } else if ( ball_x > p2_x){
//        textout_ex( screen, font, "Player 1 Wins!", 320, 240, makecol( 255, 0, 0), makecol( 0, 0, 0)); 
//        startNew();
//    }    
   
//}    

//void setupGame(){
 
//    acquire_screen();
//    rectfill( buffer, p1_x, p1_y, p1_x + 10, p1_y + 60, makecol ( 0, 0, 255));
//    rectfill( buffer, p2_x, p2_y, p2_x + 10, p2_y + 60, makecol ( 0, 0, 255));  
//    circlefill ( buffer, ball_x, ball_y, 5, makecol( 128, 255, 0));
//    draw_sprite( screen, buffer, 0, 0);
//    release_screen();
    
//    time(&secs);
//    srand( (unsigned int)secs);
//    dir = rand() % 4 + 1;
            
//}    

//int main(){

//    allegro_init();
//    set_color_depth(16);
//    set_gfx_mode( GFX_AUTODETECT, 640, 480, 0, 0);
    
//    buffer = create_bitmap( 640, 480); 
    
//    setupGame();
    
//    while( !key[KEY_ESC]){
//      while( 1 ){
//        p1Move();
//        p2Move();
//        moveBall();
//        checkWin();
//      }
//    }    
    
 //   return 0;

//}

