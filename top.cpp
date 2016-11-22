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

void image_filter(AXI_STREAM& input, AXI_STREAM& output, int rows, int cols) {
    //Create AXI streaming interfaces for the core
#pragma HLS RESOURCE variable=input core=AXIS metadata="-bus_bundle INPUT_STREAM"
#pragma HLS RESOURCE variable=output core=AXIS metadata="-bus_bundle OUTPUT_STREAM"

#pragma HLS RESOURCE core=AXI_SLAVE variable=rows metadata="-bus_bundle CONTROL_BUS"
#pragma HLS RESOURCE core=AXI_SLAVE variable=cols metadata="-bus_bundle CONTROL_BUS"
#pragma HLS RESOURCE core=AXI_SLAVE variable=return metadata="-bus_bundle CONTROL_BUS"

#pragma HLS INTERFACE ap_stable port=rows
#pragma HLS INTERFACE ap_stable port=cols

    RGB_IMAGE img_0(rows, cols);
    RGB_IMAGE img_1(rows, cols);
    GRAY_IMAGE img_2(rows, cols);
    GRAY_IMAGE img_3(rows, cols);
    RGB_IMAGE img_4(rows, cols);
    RGB_IMAGE img_5(rows, cols);
    GRAY_IMAGE img_r_1(rows, cols);
    GRAY_IMAGE img_g_1(rows, cols);
    GRAY_IMAGE img_b_1(rows, cols);
    GRAY_IMAGE img_r_2(rows, cols);
    GRAY_IMAGE img_g_2(rows, cols);
    GRAY_IMAGE img_b_2(rows, cols);
    RGB_PIXEL pix(50, 50, 50);
#pragma HLS dataflow

    hls::AXIvideo2Mat(input, img_0); // input (AXI4) -> img_0 (hls::Mat)


    hls::Split(img_0, img_b_1, img_g_1, img_r_1); 
    
    hls::Threshold(img_b_1, img_b_2, 60, 255, 0);
    hls::Threshold(img_g_1, img_g_2, 60, 255, 0);
    hls::Threshold(img_r_1, img_r_2, 60, 255, 0);

    hls::CvtColor<HLS_GRAY2RGB>(img_b_2, img_1);

    hls::Mat2AXIvideo(img_1, output);

    //hls::GaussianBlur<5, 5>(img_0, img_1, (double)1.0, (double)1.0);
    //hls::CvtColor<HLS_RGB2GRAY, rows, cols, >(img_0, img_1, HLS_RGB2GRAY);
    //hls::CvtColor<HLS_RGB2GRAY>(img_1, img_2);
    //hls::Threshold<>(img_2, img_3, 127, 255, 0);
    //hls::CvtColor<HLS_GRAY2RGB>(img_r_1, img_r_2);

/*
    hls::Sobel<1,0,3>(img_0, img_1); 
    hls::SubS(img_1, pix, img_2);
    hls::Scale(img_2, img_3, 2, 0);
    hls::Erode(img_3, img_4);
    hls::Dilate(img_4, img_5);
    hls::Mat2AXIvideo(img_5, output);
*/

}
