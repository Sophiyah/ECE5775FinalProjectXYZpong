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



/*
 * Converts an RGB image to detect red. Outputs a single channel (grayscale) image.
 */
void red_filter (RGB_IMAGE& input, GRAY_IMAGE& output, int rows, int cols) {

    GRAY_IMAGE img_r1(rows, cols);
    GRAY_IMAGE img_g1(rows, cols);
    GRAY_IMAGE img_b1(rows, cols);
    GRAY_IMAGE img_r2(rows, cols);
    GRAY_IMAGE img_g2(rows, cols);
    GRAY_IMAGE img_b2(rows, cols);
    GRAY_IMAGE img_g3(rows, cols);
    GRAY_IMAGE img_b3(rows, cols);
    GRAY_IMAGE img_and_buf(rows, cols);

    hls::Split(input, img_b1, img_g1, img_r1);
    hls::Threshold(img_r1, img_r2, 60, 255, 0); // red image
    hls::Threshold(img_g1, img_g2, 20, 255, 0); // green image
    hls::Threshold(img_b1, img_b2, 40, 255, 0); // blue image
    hls::Not(img_g2, img_g3); // not green image
    hls::Not(img_b2, img_b3); // not blue image
    hls::And(img_r2, img_g3, img_and_buf);
    hls::And(img_b3, img_and_buf, output);

}


/*
 * Converts an RGB image to detect green. Outputs a single channel (grayscale) image.
 */
void green_filter (RGB_IMAGE& input, GRAY_IMAGE& output, int rows, int cols) {

    GRAY_IMAGE img_r1(rows, cols);
    GRAY_IMAGE img_g1(rows, cols);
    GRAY_IMAGE img_b1(rows, cols);
    GRAY_IMAGE img_r2(rows, cols);
    GRAY_IMAGE img_g2(rows, cols);
    GRAY_IMAGE img_b2(rows, cols);
    GRAY_IMAGE img_r3(rows, cols);
    GRAY_IMAGE img_b3(rows, cols);
    GRAY_IMAGE img_and_buf(rows, cols);

    hls::Split(input, img_b1, img_g1, img_r1);
    hls::Threshold(img_r1, img_r2, 40, 255, 0); // red image
    hls::Threshold(img_g1, img_g2, 60, 255, 0); // green image
    hls::Threshold(img_b1, img_b2, 80, 255, 0); // blue image
    hls::Not(img_r2, img_r3); // not red image
    hls::Not(img_b2, img_b3); // not blue image
    hls::And(img_g2, img_r3, img_and_buf);
    hls::And(img_b3, img_and_buf, output);

}


/*
 * Converts an RGB image to detect blue. Outputs a single channel (grayscale) image.
 */
void blue_filter (RGB_IMAGE& input, GRAY_IMAGE& output, int rows, int cols) {

    GRAY_IMAGE img_r1(rows, cols);
    GRAY_IMAGE img_g1(rows, cols);
    GRAY_IMAGE img_b1(rows, cols);
    GRAY_IMAGE img_r2(rows, cols);
    GRAY_IMAGE img_g2(rows, cols);
    GRAY_IMAGE img_b2(rows, cols);
    GRAY_IMAGE img_r3(rows, cols);
    GRAY_IMAGE img_g3(rows, cols);
    GRAY_IMAGE img_and_buf(rows, cols);

    hls::Split(input, img_b1, img_g1, img_r1);
    hls::Threshold(img_r1, img_r2, 30, 255, 0); // red image
    hls::Threshold(img_g1, img_g2, 30, 255, 0); // green image
    hls::Threshold(img_b1, img_b2, 50, 255, 0); // blue image
    hls::Not(img_r2, img_r3); // not red image
    hls::Not(img_g2, img_g3); // not green image
    hls::And(img_b2, img_r3, img_and_buf);
    hls::And(img_g3, img_and_buf, output);

}


/*
void median_filter(RGB_IMAGE& src, RGB_IMAGE& dst)
{
  HLS_SIZE_T rows = src.rows;
  HLS_SIZE_T cols = src.cols;

  hls::LineBuffer<8, 1920, unsigned char> lineBuffer;
 
  // 5x5 window buffer/kernal which traverse horizontally through line buffer
  hls::Window<9,9, unsigned char> window;

  #pragma PIPELINE II=1
  RGB_PIXEL pixel_in;
  RGB_PIXEL pixel_out;

  unsigned char pixel_in_val;
  unsigned char pixel_out_val;
  unsigned char lineBuff0;
  unsigned char lineBuff1;
  unsigned char lineBuff2;
  unsigned char lineBuff3;
  unsigned char lineBuff4;
  unsigned char lineBuff5;
  unsigned char lineBuff6;
  unsigned char lineBuff7;
  
  for (HLS_SIZE_T i=0; i< rows+1; i++) {
//#pragma HLS LOOP_TRIPCOUNT min=601 max=1081 avg=721 
    for (HLS_SIZE_T j=0; j < cols+1; j++) {
//#pragma HLS LOOP_TRIPCOUNT min=801 max=1921 avg=1281
#pragma HLS LOOP_FLATTEN OFF
//#pragma HLS DEPENDENCE array inter false
#pragma HLS PIPELINE
      if(i < rows && j < cols) {
        src >> pixel_in;
        // 1st element is having thresholded value
        pixel_in_val = pixel_in.val[0];    
      }

      // move the column values of linebuffer up. 
      // To make space for the new pixel in the right bottom of line buffer
      if ( j < cols ) {
        lineBuff0 = lineBuffer.getval(0,j);
        lineBuff1 = lineBuffer.getval(1,j);
        lineBuff2 = lineBuffer.getval(2,j);
        lineBuff3 = lineBuffer.getval(3,j);
        lineBuff4 = lineBuffer.getval(4,j);
        lineBuff5 = lineBuffer.getval(5,j);
        lineBuff6 = lineBuffer.getval(6,j);
        lineBuff7 = lineBuffer.getval(7,j);

        lineBuffer.val[7][j] = lineBuff6;
        lineBuffer.val[6][j] = lineBuff5;
        lineBuffer.val[5][j] = lineBuff4;
        lineBuffer.val[4][j] = lineBuff3;
        lineBuffer.val[3][j] = lineBuff2;
        lineBuffer.val[2][j] = lineBuff1;
        lineBuffer.val[1][j] = lineBuff0;
      }

      // insert new pixel to the bottom right of the linebuffer.
      // right bottom element is at the 0th location
      if ( j < cols && i < rows ) {
        lineBuffer.insert_bottom(pixel_in_val, j);
      }
     
      // shift the window to right on every pixel input
      window.shift_right();

      // after shifting window to right, we have freed up a space at 0th column
      // of all the rows of window. So move linebuffer and new pixel values to 
      // the window's 0th column  
      if(j < cols ) {
        window.insert( lineBuff0, 8, 0);
        window.insert( lineBuff1, 7, 0);
        window.insert( lineBuff2, 6, 0);
        window.insert( lineBuff3, 5, 0);
        window.insert( lineBuff4, 4, 0);
        window.insert( lineBuff5, 3, 0);
        window.insert( lineBuff6, 2, 0);
        window.insert( lineBuff7, 1, 0);
        window.insert( pixel_in_val, 0, 0);
      }

      unsigned int countOnes = 0;

      // 1st 4 rows and column will have garbage values
      // because window is not filled initially, so for them
      // assign 1st four rows and columns as black
      if (i< 8 || j < 8 || i>rows-1 || j> cols - 1) {
        pixel_out_val = 0; 
      }
      else {
        for(unsigned int l = 0; l<9;l++) {
          for (unsigned int m =0; m<9;m++) {
            countOnes = (window.getval(l,m) == 0) ? countOnes : countOnes + 1;
          }
        }

        // check if majority of the pixels are red
        // if so, then assign it as white value, otherwise black value
        // note: white = 255 pixel value, black = 0 pixel value
        // threshold point is 19. That means, out of 5x5 = 25 pixel,
        //  atleast 19 pixels have to red for median value to be white
        pixel_out_val = (countOnes > 41 ) ? 255 : 0;
      }
  
      // if pixel is within the bound then assign the value to the out going pixel
      if ( j>0 && i>0 ) {
        pixel_out.val[0] = pixel_out_val;
        //pixel_out.val[1] = 0;
        //pixel_out.val[2] = 0;
        dst << pixel_out;
      }
    } // end of inner for loop
  } // end of outer for loop
} // end of function
*/


/*
 * Takes a grayscale image and computes XY coordinates of the center of the largest blob.
 */
void compute_coordinates(GRAY_IMAGE& input, GRAY_IMAGE& output) {

  GRAY_PIXEL pixel_in;
  GRAY_PIXEL pixel_out;

  HLS_SIZE_T rows = input.rows;
  HLS_SIZE_T cols = input.cols;

  ap_uint<12> min_row = 4095;
  ap_uint<12> max_row = 0;
  ap_uint<12> min_col = 4095;
  ap_uint<12> max_col = 0;
  ap_uint<12> row_center;
  ap_uint<12> col_center;

  for (HLS_SIZE_T i=0; i<rows; i++) {
    for (HLS_SIZE_T j=0; j<cols; j++) {
#pragma HLS LOOP_FLATTEN_OFF
#pragma HLS PIPELINE
      input >> pixel_in;
      pixel_out.val[0] = pixel_in.val[0];
      output << pixel_out;

      if (pixel_in.val[0] == 255) { // process the white pixels
        if (i < min_row)
          min_row = i;
        if (i > max_row)
          max_row = i;
        if (j < min_col)
          min_col = j;
        if (j > max_col)
          max_col = j;
      }

    } // end of inner for loop
  } // end of outer for loop

  row_center = (min_row + max_row)/2;
  col_center = (min_col + max_col)/2;

} // end of function


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


  RGB_IMAGE  rgb_buf1(rows, cols);
  RGB_IMAGE  rgb_buf2(rows, cols);
  GRAY_IMAGE gs_buf3(rows, cols);
  GRAY_IMAGE gs_buf4(rows, cols);
  RGB_IMAGE  rgb_buf5(rows, cols);

  hls::AXIvideo2Mat(input, rgb_buf1);

  hls::GaussianBlur<5, 5>(rgb_buf1, rgb_buf2, (double)1.0, (double)1.0);
  //median_filter(rgb_buf1, rgb_buf2);
  red_filter(rgb_buf2, gs_buf3, rows, cols);
  compute_coordinates(gs_buf3, gs_buf4);
  hls::CvtColor<HLS_GRAY2RGB>(gs_buf4, rgb_buf5);

  hls::Mat2AXIvideo(rgb_buf5, output);






/*
    RGB_IMAGE img_inbuf_1(rows, cols);
    RGB_IMAGE img_inbuf_2(rows, cols);
    RGB_IMAGE img_inbuf_3(rows, cols);
    RGB_IMAGE img_inbuf_4(rows, cols);
   
    GRAY_IMAGE img_r_1(rows, cols);
    GRAY_IMAGE img_g_1(rows, cols);
    GRAY_IMAGE img_b_1(rows, cols);
    GRAY_IMAGE img_r_2(rows, cols);
    GRAY_IMAGE img_g_2(rows, cols);
    GRAY_IMAGE img_b_2(rows, cols);
    GRAY_IMAGE img_r_3(rows, cols);
    GRAY_IMAGE img_g_3(rows, cols);
    GRAY_IMAGE img_b_3(rows, cols);

    GRAY_IMAGE img_and_buf(rows, cols);

    GRAY_IMAGE img_pure_blue_gray(rows, cols);
    GRAY_IMAGE img_pure_green_gray(rows, cols);
    GRAY_IMAGE img_pure_red_gray(rows, cols);
    RGB_IMAGE img_pure_blue_rgb(rows, cols);
    RGB_IMAGE img_pure_green_rgb(rows, cols);
    RGB_IMAGE img_pure_red_rgb(rows, cols);

    RGB_IMAGE img_1(rows, cols);

    RGB_PIXEL pix(50, 50, 50);
#pragma HLS dataflow

    hls::AXIvideo2Mat(input, img_inbuf_1); // input (AXI4) -> img_0 (hls::Mat)
    hls::Duplicate(img_inbuf_1, img_inbuf_3, img_inbuf_4);
    hls::Duplicate(img_inbuf_4, img_inbuf_1, img_inbuf_2);

    // Process red image
    hls::Split(img_inbuf_3, img_b_1, img_g_1, img_r_1);
    hls::Threshold(img_r_1, img_r_2, 60, 255, 0); // red image
    hls::Threshold(img_g_1, img_g_2, 20, 255, 0); // green image
    hls::Threshold(img_b_1, img_b_2, 40, 255, 0); // blue image
    hls::Not(img_b_2, img_b_3); // not blue image
    hls::Not(img_g_2, img_g_3); // not green image
    hls::And(img_r_2, img_b_3, img_and_buf);
    hls::And(img_g_3, img_and_buf, img_pure_red_gray);
    //hls::CvtColor<HLS_GRAY2RGB>(img_pure_red_gray, img_pure_red_rgb);

    // Process green image
    hls::Split(img_inbuf_2, img_b_1, img_g_1, img_r_1);
    hls::Threshold(img_r_1, img_r_2, 40, 255, 0); // red image
    hls::Threshold(img_g_1, img_g_2, 60, 255, 0); // green image
    hls::Threshold(img_b_1, img_b_2, 80, 255, 0); // blue image
    hls::Not(img_b_2, img_b_3); // not blue image
    hls::Not(img_r_2, img_r_3); // not red image
    hls::And(img_g_2, img_b_3, img_and_buf);
    hls::And(img_r_3, img_and_buf, img_pure_green_gray);
    //hls::CvtColor<HLS_GRAY2RGB>(img_pure_green_gray, img_pure_green_rgb);

    // Process blue image
    hls::Split(img_inbuf_1, img_b_1, img_g_1, img_r_1);
    hls::Threshold(img_r_1, img_r_2, 30, 255, 0); // red image
    hls::Threshold(img_g_1, img_g_2, 30, 255, 0); // green image
    hls::Threshold(img_b_1, img_b_2, 60, 255, 0); // blue image
    hls::Not(img_g_2, img_g_3); // not green image
    hls::Not(img_r_2, img_r_3); // not red image
    hls::And(img_b_2, img_g_3, img_and_buf);
    hls::And(img_r_3, img_and_buf, img_pure_blue_gray);
    //hls::CvtColor<HLS_GRAY2RGB>(img_pure_blue_gray, img_pure_blue_rgb);

    hls::Merge(img_pure_blue_gray, img_pure_green_gray, img_pure_red_gray, img_1);

    hls::Mat2AXIvideo(img_1, output);

    //hls::GaussianBlur<5, 5>(img_0, img_1, (double)1.0, (double)1.0);
    //hls::CvtColor<HLS_RGB2GRAY, rows, cols, >(img_0, img_1, HLS_RGB2GRAY);
    //hls::CvtColor<HLS_RGB2GRAY>(img_1, img_2);
    //hls::Threshold<>(img_2, img_3, 127, 255, 0);
    //hls::CvtColor<HLS_GRAY2RGB>(img_r_1, img_r_2);
*/
}


/*
    hls::Sobel<1,0,3>(img_0, img_1); 
    hls::SubS(img_1, pix, img_2);
    hls::Scale(img_2, img_3, 2, 0);
    hls::Erode(img_3, img_4);
    hls::Dilate(img_4, img_5);
    hls::Mat2AXIvideo(img_5, output);
}
*/
