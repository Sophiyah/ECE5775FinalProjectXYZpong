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
 * Converts an RGB image to detect red. Outputs a single channel (grayscale) image.
 */
/*
void red_filter(RGB_IMAGE& input, GRAY_IMAGE& output) {

  HLS_SIZE_T rows = input.rows;
  HLS_SIZE_T cols = input.cols;

  GRAY_IMAGE img_r1(rows, cols);
  GRAY_IMAGE img_g1(rows, cols);
  GRAY_IMAGE img_b1(rows, cols);
  GRAY_IMAGE img_r2(rows, cols);
  GRAY_IMAGE img_g2(rows, cols);
  GRAY_IMAGE img_b2(rows, cols);
  GRAY_IMAGE img_g3(rows, cols);
  GRAY_IMAGE img_b3(rows, cols);
  GRAY_IMAGE img_and_buf(rows, cols);
  GRAY_IMAGE img_thres_buf(rows, cols);

  hls::Split(input, img_b1, img_g1, img_r1);
  hls::Threshold(img_r1, img_r2, 60, 255, 0); // red image
  hls::Threshold(img_g1, img_g2, 20, 255, 0); // green image
  hls::Threshold(img_b1, img_b2, 40, 255, 0); // blue image
  hls::Not(img_g2, img_g3); // not green image
  hls::Not(img_b2, img_b3); // not blue image
  hls::And(img_r2, img_g3, img_and_buf);
  hls::And(img_b3, img_and_buf, img_thres_buf);
  hls::Threshold(img_thres_buf, output, 127, 1, 0); // red image

}*/


/*
 * Converts an RGB image to detect green. Outputs a single channel (grayscale) image.
 */
void green_filter(RGB_IMAGE& input, GRAY_IMAGE& output) {

  HLS_SIZE_T rows = input.rows;
  HLS_SIZE_T cols = input.cols;

  GRAY_IMAGE img_r1(rows, cols);
  GRAY_IMAGE img_g1(rows, cols);
  GRAY_IMAGE img_b1(rows, cols);
  GRAY_IMAGE img_r2(rows, cols);
  GRAY_IMAGE img_g2(rows, cols);
  GRAY_IMAGE img_b2(rows, cols);
  GRAY_IMAGE img_r3(rows, cols);
  GRAY_IMAGE img_b3(rows, cols);
  GRAY_IMAGE img_and_buf(rows, cols);
  GRAY_IMAGE img_thres_buf(rows, cols);

  hls::Split(input, img_b1, img_g1, img_r1);
  hls::Threshold(img_r1, img_r2, 40, 255, 0); // red image
  hls::Threshold(img_g1, img_g2, 60, 255, 0); // green image
  hls::Threshold(img_b1, img_b2, 80, 255, 0); // blue image
  hls::Not(img_r2, img_r3); // not red image
  hls::Not(img_b2, img_b3); // not blue image
  hls::And(img_g2, img_r3, img_and_buf);
  hls::And(img_b3, img_and_buf, img_thres_buf);
  hls::Threshold(img_thres_buf, output, 127, 1, 0); // green image

}


/*
 * Converts an RGB image to detect blue. Outputs a single channel (grayscale) image.
 */
void blue_filter(RGB_IMAGE& input, GRAY_IMAGE& output) {

  HLS_SIZE_T rows = input.rows;
  HLS_SIZE_T cols = input.cols;

  GRAY_IMAGE img_r1(rows, cols);
  GRAY_IMAGE img_g1(rows, cols);
  GRAY_IMAGE img_b1(rows, cols);
  GRAY_IMAGE img_r2(rows, cols);
  GRAY_IMAGE img_g2(rows, cols);
  GRAY_IMAGE img_b2(rows, cols);
  GRAY_IMAGE img_r3(rows, cols);
  GRAY_IMAGE img_g3(rows, cols);
  GRAY_IMAGE img_and_buf(rows, cols);
  GRAY_IMAGE img_thres_buf(rows, cols);

  hls::Split(input, img_b1, img_g1, img_r1);
  hls::Threshold(img_r1, img_r2, 30, 255, 0); // red image
  hls::Threshold(img_g1, img_g2, 30, 255, 0); // green image
  hls::Threshold(img_b1, img_b2, 50, 255, 0); // blue image
  hls::Not(img_r2, img_r3); // not red image
  hls::Not(img_g2, img_g3); // not green image
  hls::And(img_b2, img_r3, img_and_buf);
  hls::And(img_g3, img_and_buf, img_thres_buf);
  hls::Threshold(img_thres_buf, output, 127, 2, 0); // blue image

}


/*
 * Takes a grayscale image and computes XY coordinates of the center of both blobs.
 */
TUPLE compute_center(GRAY_IMAGE& input) {

  GRAY_PIXEL pixel_in;
  TUPLE centers;

  HLS_SIZE_T rows = input.rows;
  HLS_SIZE_T cols = input.cols;

  ap_uint<11> left_min_row = cols;
  ap_uint<11> left_max_row = 0;
  ap_uint<11> left_center;
  ap_uint<11> right_min_row = cols;
  ap_uint<11> right_max_row = 0;
  ap_uint<11> right_center;

  for (HLS_SIZE_T i=0; i<rows; i++) {
    for (HLS_SIZE_T j=0; j<cols; j++) {
#pragma HLS LOOP_FLATTEN_OFF
#pragma HLS PIPELINE
      input >> pixel_in;
      // detect green on the left side
      if (pixel_in.val[0] == 1 && j > 50 && j < 250) {
        if (i < left_min_row)
          left_min_row = i;
        if (i > left_max_row)
          left_max_row = i;
      }

      // detect blue on the right side
      //if (pixel_in.val[0] == 255 && j > (cols-250) && j < (cols-50)) {
      if (pixel_in.val[0] == 2 && j > (cols-250) && j < (cols-50)) {
        if (i < right_min_row)
          right_min_row = i;
        if (i > right_max_row)
          right_max_row = i;
      }
    } // end inner for loop
  } // end outer for loop

  centers.first = (left_min_row + left_max_row) >> 1;
  centers.second = (right_min_row + right_max_row) >> 1;
  return centers;
} // end function

/*
 * This function handles the ball movement, including paddle collisions and 
 * out of bounds (game over) conditions.
 */

/*
void compute_ball(GRAY_IMAGE& output, int rows, int cols) {
  ap_uint<11> ball_x = 320;
  ap_uint<11> ball_y = 240;

  ap_uint<11> ball_tempX = 320;
  ap_uint<11> ball_tempY = 240;

  ap_uint<11> p1_x = PADDLE_X_OFFSET;
  ap_uint<11> p1_y = 210;

  ap_uint<11> p1_tempX = PADDLE_X_OFFSET;
  ap_uint<11> p1_tempY = 210;

  ap_uint<11> p2_x = 620;
  ap_uint<11> p2_y = 210;

  ap_uint<11> p2_tempX = cols - PADDLE_X_OFFSET;
  ap_uint<11> p2_tempY = 210;
  ap_uint<11> n = 0;
    
    
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
  
}
*/


/*
 * This is the main draw function.
 */
void draw_output(TUPLE centers, TUPLE balCenter, GRAY_IMAGE& output, int rows, int cols) {
  GRAY_PIXEL pixel_out;
  
  //ap_uint<8> PADDLE_X_OFFSET = 50; TODELETE<moved to header file
  //~ ap_uint<8> HALF_PADDLE_WIDTH = 5;
  //~ ap_uint<8> HALF_PADDLE_HEIGHT = 25;
  //~ ap_uint<8> BALL_RADIUS = 20; 
  //~ TUPLE ballCenter;
  //~ ballCenter.first = 200;
  //~ ballCenter.second = 600; 

  // if centers are at the bounds, assign new values to prevent overflow
  if (centers.first < HALF_PADDLE_HEIGHT)
    centers.first = HALF_PADDLE_HEIGHT;
  if (centers.first > rows - HALF_PADDLE_HEIGHT)
    centers.first = rows - HALF_PADDLE_HEIGHT;
  if (centers.second < HALF_PADDLE_HEIGHT)
    centers.second = HALF_PADDLE_HEIGHT;
  if (centers.second > rows - HALF_PADDLE_HEIGHT)
    centers.second = rows - HALF_PADDLE_HEIGHT;

  // compute paddle dimensions based on the centers
  ap_uint<11> left_top_bound = centers.first - HALF_PADDLE_HEIGHT;
  ap_uint<11> left_bot_bound = centers.first + HALF_PADDLE_HEIGHT;
  ap_uint<11> right_top_bound = centers.second - HALF_PADDLE_HEIGHT;
  ap_uint<11> right_bot_bound = centers.second + HALF_PADDLE_HEIGHT;

  // hardcoded X-axis bounds, the paddle only moves vertically
  ap_uint<11> left_lft_bound = PADDLE_X_OFFSET - HALF_PADDLE_WIDTH;
  ap_uint<11> left_rgt_bound = PADDLE_X_OFFSET + HALF_PADDLE_WIDTH;
  ap_uint<11> right_lft_bound = cols - PADDLE_X_OFFSET - HALF_PADDLE_WIDTH;
  ap_uint<11> right_rgt_bound = cols - PADDLE_X_OFFSET + HALF_PADDLE_WIDTH;

  // compute ball boundary 
  //ap_uint<16> ballRadiusSq = BALL_RADIUS* BALL_RADIUS;

  ap_uint<11> ball_left_bound = ballCenter.first - BALL_RADIUS;
  ap_uint<11> ball_right_bound = ballCenter.first + BALL_RADIUS; 
  ap_uint<11> ball_top_bound = ballCenter.second - BALL_RADIUS;
  ap_uint<11> ball_bot_bound = ballCenter.second + BALL_RADIUS;
  
  for (HLS_SIZE_T i=0; i<rows; i++) {
    for (HLS_SIZE_T j=0; j<cols; j++) {
#pragma HLS LOOP_FLATTEN_OFF
#pragma HLS PIPELINE

	  //compute distance current pixel is from ball
	  //ap_uint<64> distFromBall = ((i- ballX)*(i-ballX)) + (j - ballY)*(j-ballY);
      
      // draw left paddle
      if (i > left_top_bound &&
          i < left_bot_bound &&
          j > left_lft_bound &&
          j < left_rgt_bound) {
        pixel_out.val[0] = 255;
      }

      // draw right paddle
      else if (i > right_top_bound &&
               i < right_bot_bound &&
               j > right_lft_bound &&
               j < right_rgt_bound) {
        pixel_out.val[0] = 255;
      }
	
/*  
	  // draw ball
	  else if (i > ball_top_bound &&
             i < ball_bot_bound &&
             j > ball_left_bound &&
             j < ball_right_bound ) {
		  pixel_out.val[0] = 255;
	  }
*/

      // if no game element, draw black pixel
      else{
        pixel_out.val[0] = 0;
	  }
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
  RGB_IMAGE rgb_buf3(rows, cols);
  RGB_IMAGE rgb_buf4(rows, cols);
  GRAY_IMAGE gs_buf5(rows, cols);
  GRAY_IMAGE gs_buf6(rows, cols);
  GRAY_IMAGE gs_buf7(rows, cols);
  GRAY_IMAGE gs_buf8(rows, cols);
  GRAY_IMAGE gs_buf9(rows, cols);
  GRAY_IMAGE gs_buf10(rows, cols);
  GRAY_IMAGE gs_buf11(rows, cols);
  RGB_IMAGE rgb_buf12(rows, cols);

  TUPLE centers;

#pragma HLS dataflow
  hls::AXIvideo2Mat(input, rgb_buf1);
  hls::GaussianBlur<5, 5>(rgb_buf1, rgb_buf2, (double)1.0, (double)1.0);
  hls::Duplicate(rgb_buf2, rgb_buf3, rgb_buf4);
  green_filter(rgb_buf3, gs_buf5);
  blue_filter(rgb_buf4, gs_buf6);
  hls::Not(gs_buf5, gs_buf7);
  hls::Not(gs_buf6, gs_buf8);
  hls::And(gs_buf7, gs_buf8, gs_buf9);
  hls::Not(gs_buf9, gs_buf10);
  centers = compute_center(gs_buf10);
  draw_output(centers, gs_buf11, rows, cols);
  hls::CvtColor<HLS_GRAY2RGB>(gs_buf11, rgb_buf12);
  hls::Mat2AXIvideo(rgb_buf12, output);

}



/*
    //hls::GaussianBlur<5, 5>(img_0, img_1, (double)1.0, (double)1.0);
    //hls::CvtColor<HLS_RGB2GRAY, rows, cols, >(img_0, img_1, HLS_RGB2GRAY);
    //hls::CvtColor<HLS_RGB2GRAY>(img_1, img_2);
    //hls::Threshold<>(img_2, img_3, 127, 255, 0);
    //hls::CvtColor<HLS_GRAY2RGB>(img_r_1, img_r_2);
*/

/*
    hls::Sobel<1,0,3>(img_0, img_1); 
    hls::SubS(img_1, pix, img_2);
    hls::Scale(img_2, img_3, 2, 0);
    hls::Erode(img_3, img_4);
    hls::Dilate(img_4, img_5);
    hls::Mat2AXIvideo(img_5, output);
}
*/
