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
 * Converts an RGB image to detect green. Outputs a single channel (grayscale) image.
 */
void green_filter (RGB_Image& input, GRAY_IMAGE& output, int rows, int cols) {

    GRAY_IMAGE img_r_1(rows, cols);
    GRAY_IMAGE img_g_1(rows, cols);
    GRAY_IMAGE img_b_1(rows, cols);
    GRAY_IMAGE img_r_2(rows, cols);
    GRAY_IMAGE img_g_2(rows, cols);
    GRAY_IMAGE img_b_2(rows, cols);
    GRAY_IMAGE img_r_3(rows, cols);
    GRAY_IMAGE img_b_3(rows, cols);
    GRAY_IMAGE img_and_buf(rows, cols);
    GRAY_IMAGE img_green_gs(rows, cols);

    hls::Split(input, img_b_1, img_g_1, img_r_1);
    hls::Threshold(img_b_1, img_b_2, 60, 255, 0); // blue image
    hls::Threshold(img_g_1, img_g_2, 60, 255, 0); // green image
    hls::Threshold(img_r_1, img_r_2, 60, 255, 0); // red image
    hls::Not(img_b_2, img_b_3); // not blue image
    hls::Not(img_r_2, img_r_3); // not red image
    hls::And(img_g_2, img_b_3, img_and_buf);
    hls::And(img_r_3, img_and_buf, img_green_gs);

}


/*
 * Converts an RGB image to detect blue. Outputs a single channel (grayscale) image.
 */
void blue_filter (RGB_Image& input, GRAY_IMAGE& output, int rows, int cols) {

    GRAY_IMAGE img_r_1(rows, cols);
    GRAY_IMAGE img_g_1(rows, cols);
    GRAY_IMAGE img_b_1(rows, cols);
    GRAY_IMAGE img_r_2(rows, cols);
    GRAY_IMAGE img_g_2(rows, cols);
    GRAY_IMAGE img_b_2(rows, cols);
    GRAY_IMAGE img_r_3(rows, cols);
    GRAY_IMAGE img_g_3(rows, cols);
    GRAY_IMAGE img_and_buf(rows, cols);
    GRAY_IMAGE img_green_gs(rows, cols);

    hls::Split(input, img_b_1, img_g_1, img_r_1);
    hls::Threshold(img_b_1, img_b_2, 60, 255, 0); // blue image
    hls::Threshold(img_g_1, img_g_2, 60, 255, 0); // green image
    hls::Threshold(img_r_1, img_r_2, 60, 255, 0); // red image
    hls::Not(img_r_2, img_r_3); // not red image
    hls::Not(img_g_2, img_g_3); // not green image
    hls::And(img_b_2, img_r_3, img_and_buf);
    hls::And(img_g_3, img_and_buf, img_blue_gs);

}







/*
void image_filter(AXI_STREAM& input, AXI_STREAM& output, int rows, int cols) {
    //Create AXI streaming interfaces for the core
#pragma HLS RESOURCE variable=input core=AXIS metadata="-bus_bundle INPUT_STREAM"
#pragma HLS RESOURCE variable=output core=AXIS metadata="-bus_bundle OUTPUT_STREAM"

#pragma HLS RESOURCE core=AXI_SLAVE variable=rows metadata="-bus_bundle CONTROL_BUS"
#pragma HLS RESOURCE core=AXI_SLAVE variable=cols metadata="-bus_bundle CONTROL_BUS"
#pragma HLS RESOURCE core=AXI_SLAVE variable=return metadata="-bus_bundle CONTROL_BUS"

#pragma HLS INTERFACE ap_stable port=rows
#pragma HLS INTERFACE ap_stable port=cols

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

    // Process blue image
    hls::Split(img_inbuf_1, img_b_1, img_g_1, img_r_1);
    hls::Threshold(img_b_1, img_b_2, 60, 255, 0); // blue image
    hls::Threshold(img_g_1, img_g_2, 60, 255, 0); // green image
    hls::Threshold(img_r_1, img_r_2, 60, 255, 0); // red image
    hls::Not(img_g_2, img_g_3); // not green image
    hls::Not(img_r_2, img_r_3); // not red image
    hls::And(img_b_2, img_g_3, img_and_buf);
    hls::And(img_r_3, img_and_buf, img_pure_blue_gray);
    //hls::CvtColor<HLS_GRAY2RGB>(img_pure_blue_gray, img_pure_blue_rgb);

    // Process green image
    hls::Split(img_inbuf_2, img_b_1, img_g_1, img_r_1);
    hls::Threshold(img_b_1, img_b_2, 60, 255, 0); // blue image
    hls::Threshold(img_g_1, img_g_2, 60, 255, 0); // green image
    hls::Threshold(img_r_1, img_r_2, 60, 255, 0); // red image
    hls::Not(img_b_2, img_b_3); // not blue image
    hls::Not(img_r_2, img_r_3); // not red image
    hls::And(img_g_2, img_b_3, img_and_buf);
    hls::And(img_r_3, img_and_buf, img_pure_green_gray);
    //hls::CvtColor<HLS_GRAY2RGB>(img_pure_green_gray, img_pure_green_rgb);

    // Process green image
    hls::Split(img_inbuf_3, img_b_1, img_g_1, img_r_1);
    hls::Threshold(img_b_1, img_b_2, 60, 255, 0); // blue image
    hls::Threshold(img_g_1, img_g_2, 60, 255, 0); // green image
    hls::Threshold(img_r_1, img_r_2, 60, 255, 0); // red image
    hls::Not(img_b_2, img_b_3); // not blue image
    hls::Not(img_g_2, img_g_3); // not green image
    hls::And(img_r_2, img_b_3, img_and_buf);
    hls::And(img_g_3, img_and_buf, img_pure_red_gray);
    //hls::CvtColor<HLS_GRAY2RGB>(img_pure_red_gray, img_pure_red_rgb);

    hls::Merge(img_pure_blue_gray, img_pure_green_gray, img_pure_red_gray, img_1);

    hls::Mat2AXIvideo(img_1, output);

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
*/

}
