/***************************************************************************
* ECE 5775 (Fall 2016) - Final Project
* Project Name - Game of Pong with Augumented Realiy
* Authors - Albert Xu (awx2), Sophia Yan (sjy33), Man Zhang (mz338)
*
* This project references 2 other sources.
* (1) Tutorial from Xilinx - Accelerating OpenCV Applications with Zynq-7000 
*     All Programmable SoC using Vivado HLS Video Libraries
* (2) Corner Detection Algorithm of ECE 5775 (Fall 2014) by Aashish Agarwal, 
*     Asha Ganesan, and Mohit Yogesh Modi
***************************************************************************/


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

#include "top.h"
#include <stdlib.h>


/*
 * Outputs the green and blue filtered image in grayscale.
 */
void color_filter(RGB_IMAGE& input, GRAY_IMAGE& output) {

  RGB_PIXEL pixel_in;
  GRAY_PIXEL pixel_out;

  HLS_SIZE_T rows = input.rows;
  HLS_SIZE_T cols = input.cols;

  for (HLS_SIZE_T i=0; i<rows; i++) {
    for (HLS_SIZE_T j=0; j<cols; j++) {
#pragma HLS PIPELINE

      input >> pixel_in;

      // val[0] is blue, val[1] is green, val[2] is red
      // find green pixels
      if (pixel_in.val[0] < 80 &&
          pixel_in.val[1] > 60 &&
          pixel_in.val[2] < 40)
        pixel_out.val[0] = 1;

      // find blue pixels
      else if (pixel_in.val[0] > 50 &&
               pixel_in.val[1] < 30 &&
               pixel_in.val[2] < 30)
        pixel_out.val[0] = 2;

      else
        pixel_out.val[0] = 0;

      output << pixel_out;

    } // end inner for loop
  } // end outer for loop
} // end function

/*
 * This function handles the ball movement, including paddle collisions and 
 * out of bounds (game over) conditions.
 */
ap_uint<22> compute_ball(ap_uint<11> pCenters_left, ap_uint<11> pCenters_right, ap_uint<22> prevBallCenter, int rows, int cols) { 

  //new ball center initialization
  ap_uint<11> newBallCentX=prevBallCenter(10,0);
  ap_uint<11> newBallCentY=prevBallCenter(21,11); 
  
  //initialize ball logic variables   
  ap_uint<11> ball_x = prevBallCenter(10,0);
  ap_uint<11> ball_y = prevBallCenter(21,11);
  ap_uint<22> BallCenter;

  //compute left paddle location
  ap_uint<11> p1_x = PADDLE_X_OFFSET + HALF_PADDLE_WIDTH;
  ap_uint<11> p1_y_top = pCenters_left - HALF_PADDLE_HEIGHT;
  ap_uint<11> p1_y_bot = pCenters_left + HALF_PADDLE_HEIGHT; 

  //compute right paddle location
  ap_uint<11> p2_x = cols - PADDLE_X_OFFSET - HALF_PADDLE_WIDTH;
  ap_uint<11> p2_y_top = pCenters_right - HALF_PADDLE_HEIGHT;
  ap_uint<11> p2_y_bot = pCenters_right + HALF_PADDLE_HEIGHT;


    static ap_uint<3> dir = 2; //This will keep track of the circles direction
            //1= up and left, 2 = down and left, 3 = up and right, 4 = down and right

    if (dir == 1 && ball_x > BALL_RADIUS && ball_y > BALL_RADIUS){
     
         if( ball_x <= (p1_x + BALL_RADIUS) && ball_y >= p1_y_top && ball_y <= p1_y_bot){
                  dir = 3;
         }else{    
                 newBallCentX = ball_x - vel;
                 newBallCentY = ball_y - vel;
         }    
              
    } else if (dir == 2 && ball_x > BALL_RADIUS && ball_y < (rows-BALL_RADIUS)  ){

         if( ball_x <= (p1_x + BALL_RADIUS) && ball_y >= p1_y_top && ball_y <= p1_y_bot){
                  dir = 4;
         }else{    
                 newBallCentX = ball_x - vel;
                 newBallCentY = ball_y + vel;
         }

    } else if (dir == 3 &&  ball_x < (cols-BALL_RADIUS) && ball_y > BALL_RADIUS    ){

         if( (ball_x + BALL_RADIUS) >= p2_x && ball_y >= p2_y_top && ball_y <= p2_y_bot){
                  dir = 1;
         }else{    
                 newBallCentX = ball_x + vel;
                 newBallCentY = ball_y - vel;
         }

    } else if (dir == 4 &&  ball_x < (cols - BALL_RADIUS) && ball_y < (rows - BALL_RADIUS)  ){

         if( (ball_x + BALL_RADIUS) >= p2_x && ball_y >= p2_y_top && ball_y <= p2_y_bot){
                  dir = 2;
         }else{    
                 newBallCentX = ball_x + vel;
                 newBallCentY = ball_y + vel;
         }

    } else { 
		//if ball hits the left or right edge start the ball from the center
		if (ball_x <= (BALL_RADIUS) || ball_x >= ( cols - BALL_RADIUS) ) { //ball hits left edge, start from center
			newBallCentX = 700;
			newBallCentY = 500;
			dir = 3;
		}
		//~ else if ( ball_x >= ( cols - BALL_RADIUS) ) { //ball hits right edge and moves past the paddle, start from center
			//~ newBallCentX = 700;
			//~ newBallCentY = 500;
			//~ dir = 1;
		//~ }
		
		else if ( ball_y <= BALL_RADIUS ) {//ball hits the top edge
			
			if(dir == 1) {// ball is moving up and left, move ball center to be within bounds, change direction to move down and left
				newBallCentX = ball_x - vel;
                newBallCentY = BALL_RADIUS + vel;
				dir = 2;
			}
			else { //ball is moving up and right, change direction to move down and right
				newBallCentX = ball_x + vel;
                newBallCentY = BALL_RADIUS + vel;
				dir = 4;
			}
		}
		else { //ball hits the bottom edge
			if(dir == 2) { //ball is moving down and left, change direction to move up and left
				newBallCentX = ball_x - vel;
                newBallCentY = rows - BALL_RADIUS - vel;
                dir = 1; 
            }
            else { //ball is moving down and right, change direction to move up and right
				newBallCentX = ball_x + vel;
                newBallCentY = rows - BALL_RADIUS - vel;
                dir = 3; 
			}
		}
		
    } 
    
    //pack the ball center information into one variable
    BallCenter(10,0) = newBallCentX;
    BallCenter(21,11) = newBallCentY;
    
    return BallCenter;
       
}

/*
 * Takes a grayscale image and computes XY coordinates of the center of both blobs.
 */
void compute_center(GRAY_IMAGE& input, GRAY_IMAGE& output, hls::stream< ap_uint<44> >&paddle_stream) {

  GRAY_PIXEL pixel_in;
  GRAY_PIXEL pixel_out;

  HLS_SIZE_T rows = input.rows;
  HLS_SIZE_T cols = input.cols;

  ap_uint<11> left_min_row = cols;
  ap_uint<11> left_max_row = 0;
  ap_uint<11> right_min_row = cols;
  ap_uint<11> right_max_row = 0;

  ap_uint<11> left_center;
  ap_uint<11> right_center;
  ap_uint<22> ballCenter;
  ap_uint<44> temp;
  
  //static variables that hold value from iteration to iteration
  static ap_uint<11> prev_left_center;
  static ap_uint<11> prev_right_center;
  static ap_uint<22> prevBallCenter= 1331580; //start the ball somewhere in the middle

  for (HLS_SIZE_T i=0; i<rows; i++) {
    for (HLS_SIZE_T j=0; j<cols; j++) {
#pragma HLS PIPELINE

      temp(10,0) = prev_left_center;
      temp(21,11) = prev_right_center;
      temp(43,22) = prevBallCenter;  
      paddle_stream.write(temp);

      input >> pixel_in;
      // detect green on the left side
      if (pixel_in.val[0] == 1 && j > 50 && j < 250) {
        if (i < left_min_row)
          left_min_row = i;
        if (i > left_max_row)
          left_max_row = i;
      }

      // detect blue on the right side
      if (pixel_in.val[0] == 2 && j > (cols-250) && j < (cols-50)) {
        if (i < right_min_row)
          right_min_row = i;
        if (i > right_max_row)
          right_max_row = i;

      }

      //pixel_out.val[0] = pixel_in.val[0];
      pixel_out.val[0] = 0;
      output << pixel_out;

    } // end inner for loop
  } // end outer for loop

  left_center = (left_min_row + left_max_row) >> 1;
  right_center = (right_min_row + right_max_row) >> 1;
  //calculate new ball position
  ballCenter = compute_ball(left_center, right_center, prevBallCenter, rows, cols);
   
  ap_uint<11> left_RAW_buffer;
  ap_uint<11> right_RAW_buffer;
  ap_uint<22> ball_RAW_buffer;

  left_RAW_buffer = left_center;
  right_RAW_buffer = right_center;
  ball_RAW_buffer = ballCenter;
 
  prev_left_center = left_RAW_buffer;
  prev_right_center = right_RAW_buffer;
  prevBallCenter = ball_RAW_buffer;
  
} // end function


/*
 * This is the main draw function.
 */
void draw_output(GRAY_IMAGE& input, hls::stream< ap_uint<44> >&paddle_stream, GRAY_IMAGE& output, int rows, int cols) {
  
  GRAY_PIXEL pixel_in;
  GRAY_PIXEL pixel_out;

  // hardcoded X-axis bounds, the paddle only moves vertically
  ap_uint<11> left_lft_bound = PADDLE_X_OFFSET - HALF_PADDLE_WIDTH;
  ap_uint<11> left_rgt_bound = PADDLE_X_OFFSET + HALF_PADDLE_WIDTH;
  ap_uint<11> right_lft_bound = cols - PADDLE_X_OFFSET - HALF_PADDLE_WIDTH;
  ap_uint<11> right_rgt_bound = cols - PADDLE_X_OFFSET + HALF_PADDLE_WIDTH;

  //streamed data initialization
  ap_uint<44> paddle_centers;
  ap_uint<11> left_center;
  ap_uint<11> right_center;
  ap_uint<11> ballCenterX;
  ap_uint<11> ballCenterY; 

  for (HLS_SIZE_T i=0; i<rows; i++) {
    for (HLS_SIZE_T j=0; j<cols; j++) {
#pragma HLS PIPELINE

      input >> pixel_in;

      paddle_centers = paddle_stream.read();
      //unpack the data from the stream
      left_center = paddle_centers(10,0);
      right_center = paddle_centers(21,11);
      ballCenterX = paddle_centers(32,22);
      ballCenterY = paddle_centers(43,33);  
 
      // if centers are at the bounds, assign new values to prevent overflow
      if (left_center < HALF_PADDLE_HEIGHT)
        left_center = HALF_PADDLE_HEIGHT;
      if (left_center > rows - HALF_PADDLE_HEIGHT) 
        left_center = rows - HALF_PADDLE_HEIGHT;
      if (right_center < HALF_PADDLE_HEIGHT)
        right_center = HALF_PADDLE_HEIGHT;
      if (right_center > rows - HALF_PADDLE_HEIGHT)
        right_center = rows - HALF_PADDLE_HEIGHT;
        
      //~ // if ball centers are at the bounds, assign new values to prevent overflow
      //~ if (ballCenterX < BALL_RADIUS)
        //~ ballCenterX = BALL_RADIUS;
      //~ if (ballCenterX > cols - BALL_RADIUS) 
        //~ ballCenterX = cols - BALL_RADIUS;
      //~ if (ballCenterY < BALL_RADIUS)
        //~ ballCenterY = BALL_RADIUS;
      //~ if (ballCenterY > rows - BALL_RADIUS)
        //~ ballCenterY = rows - BALL_RADIUS;
 
      // compute paddle dimensions based on the centers
      ap_uint<11> left_top_bound = left_center - HALF_PADDLE_HEIGHT;
      ap_uint<11> left_bot_bound = left_center + HALF_PADDLE_HEIGHT;
      ap_uint<11> right_top_bound = right_center - HALF_PADDLE_HEIGHT;
      ap_uint<11> right_bot_bound = right_center + HALF_PADDLE_HEIGHT;
      
	  // compute ball boundary 
	  ap_uint<11> ball_left_bound = ballCenterX - BALL_RADIUS;
	  ap_uint<11> ball_right_bound = ballCenterX + BALL_RADIUS; 
	  ap_uint<11> ball_top_bound = ballCenterY - BALL_RADIUS;
	  ap_uint<11> ball_bot_bound = ballCenterY + BALL_RADIUS;
	  
      // draw left paddle
      if (i > left_top_bound &&
          i < left_bot_bound &&
          j > left_lft_bound &&
          j < left_rgt_bound)
        pixel_out.val[0] = 255;


      // draw right paddle
      else if (i > right_top_bound &&
               i < right_bot_bound &&
               j > right_lft_bound &&
               j < right_rgt_bound)
        pixel_out.val[0] = 255;

      // draw ball
      else if (i > ball_top_bound &&
               i < ball_bot_bound &&
               j > ball_left_bound &&
               j < ball_right_bound ) {
        pixel_out.val[0] = 255;
	  }

       // if no game element, draw black pixel
       else
         pixel_out.val[0] = 0;

     output << pixel_out;

     } // end inner for loop
   } // end outer for loop
} // end function


/*
 * This is the main image processing function called in test.cp.
 */
void image_filter(AXI_STREAM& input, AXI_STREAM& output, int rows, int cols) {
  //Create AXI streaming interfaces for the core
  #pragma HLS RESOURCE variable=input core=AXIS metadata="-bus_bundle INPUT_STREAM"
  #pragma HLS RESOURCE variable=output core=AXIS metadata="-bus_bundle OUTPUT_STREAM"

  #pragma HLS RESOURCE core=AXI_SLAVE variable=rows metadata="-bus_bundle CONTROL_BUS"
  #pragma HLS RESOURCE core=AXI_SLAVE variable=cols metadata="-bus_bundle CONTROL_BUS"
  #pragma HLS RESOURCE core=AXI_SLAVE variable=return metadata="-bus_bundle CONTROL_BUS"

  #pragma HLS INTERFACE ap_stable port=rows
  #pragma HLS INTERFACE ap_stable port=cols

  RGB_IMAGE rgb_buf1(rows, cols);
  RGB_IMAGE rgb_buf2(rows, cols);
  GRAY_IMAGE gs_buf3(rows, cols);
  GRAY_IMAGE gs_buf4(rows, cols);
  GRAY_IMAGE gs_buf5(rows, cols);
  RGB_IMAGE rgb_buf6(rows, cols);

  hls::stream< ap_uint<44> > paddle_stream;

#pragma HLS dataflow
  hls::AXIvideo2Mat(input, rgb_buf1);
  hls::GaussianBlur<5, 5>(rgb_buf1, rgb_buf2, (double)1.0, (double)1.0);
  color_filter(rgb_buf2, gs_buf3);
  compute_center(gs_buf3, gs_buf4, paddle_stream);
  draw_output(gs_buf4, paddle_stream, gs_buf5, rows, cols);
  hls::CvtColor<HLS_GRAY2RGB>(gs_buf5, rgb_buf6);
  hls::Mat2AXIvideo(rgb_buf6, output);

}
