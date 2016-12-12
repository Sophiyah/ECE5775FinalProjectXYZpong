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
#include "opencv_top.h"


int main (int argc, char** argv) {

    IplImage* src = cvLoadImage(INPUT_IMAGE);
std::cout<< "Size = " << cvGetSize(src).width << ", " << cvGetSize(src).height << std::endl;

    IplImage* dst0 = cvCreateImage(cvGetSize(src), src->depth, src->nChannels);
    //IplImage* dst1 = cvCreateImage(cvGetSize(src), src->depth, 1);
    IplImage* dst1 = cvCreateImage(cvGetSize(src), src->depth, src->nChannels);
    //IplImage* dst2 = cvCreateImage(cvGetSize(src), src->depth, 1);
    IplImage* dst2 = cvCreateImage(cvGetSize(src), src->depth, src->nChannels);
    IplImage* dst3 = cvCreateImage(cvGetSize(src), src->depth, src->nChannels);
    IplImage* dst4 = cvCreateImage(cvGetSize(src), src->depth, src->nChannels);
    IplImage* dst5 = cvCreateImage(cvGetSize(src), src->depth, src->nChannels);
    IplImage* dst6 = cvCreateImage(cvGetSize(src), src->depth, src->nChannels);
    IplImage* dst7 = cvCreateImage(cvGetSize(src), src->depth, src->nChannels);
    IplImage* dst8 = cvCreateImage(cvGetSize(src), src->depth, src->nChannels);
    IplImage* dst9 = cvCreateImage(cvGetSize(src), src->depth, src->nChannels);
    IplImage* dst10 = cvCreateImage(cvGetSize(src), src->depth, src->nChannels);
    
    AXI_STREAM  src_axi, dst_axi;
    IplImage2AXIvideo(src, src_axi);

    image_filter(src_axi, dst_axi, src->height, src->width);

    AXIvideo2IplImage(dst_axi, dst0);

    cvSaveImage(OUTPUT_IMAGE0, dst0);
    
    //second frame
    IplImage2AXIvideo(dst0, src_axi);
    image_filter(src_axi, dst_axi, src->height, src->width);
    AXIvideo2IplImage(dst_axi, dst1);
    cvSaveImage(OUTPUT_IMAGE1, dst1);
    
    //frame 3
    IplImage2AXIvideo(dst1, src_axi);
    image_filter(src_axi, dst_axi, src->height, src->width);
    AXIvideo2IplImage(dst_axi, dst2);
    cvSaveImage(OUTPUT_IMAGE2, dst2);
    
    //frame 4
    IplImage2AXIvideo(dst2, src_axi);
    image_filter(src_axi, dst_axi, src->height, src->width);
    AXIvideo2IplImage(dst_axi, dst3);
    cvSaveImage(OUTPUT_IMAGE3, dst3);
    
    //frame 5
    IplImage2AXIvideo(dst3, src_axi);
    image_filter(src_axi, dst_axi, src->height, src->width);
    AXIvideo2IplImage(dst_axi, dst4);
    cvSaveImage(OUTPUT_IMAGE4, dst4);
    
    //frame 6
    IplImage2AXIvideo(dst4, src_axi);
    image_filter(src_axi, dst_axi, src->height, src->width);
    AXIvideo2IplImage(dst_axi, dst5);
    cvSaveImage(OUTPUT_IMAGE5, dst5);

    //frame 7
    IplImage2AXIvideo(dst5, src_axi);
    image_filter(src_axi, dst_axi, src->height, src->width);
    AXIvideo2IplImage(dst_axi, dst6);
    cvSaveImage(OUTPUT_IMAGE6, dst6);
    
    //frame 8
    IplImage2AXIvideo(dst6, src_axi);
    image_filter(src_axi, dst_axi, src->height, src->width);
    AXIvideo2IplImage(dst_axi, dst7);
    cvSaveImage(OUTPUT_IMAGE7, dst7);

    //frame 9
    IplImage2AXIvideo(dst7, src_axi);
    image_filter(src_axi, dst_axi, src->height, src->width);
    AXIvideo2IplImage(dst_axi, dst8);
    cvSaveImage(OUTPUT_IMAGE8, dst8);
    
    //frame 10
    IplImage2AXIvideo(dst8, src_axi);
    image_filter(src_axi, dst_axi, src->height, src->width);
    AXIvideo2IplImage(dst_axi, dst9);
    cvSaveImage(OUTPUT_IMAGE9, dst9);
    
    //frame 11
    IplImage2AXIvideo(dst9, src_axi);
    image_filter(src_axi, dst_axi, src->height, src->width);
    AXIvideo2IplImage(dst_axi, dst10);
    cvSaveImage(OUTPUT_IMAGE10, dst10);
    
    cvReleaseImage(&src);
    cvReleaseImage(&dst1);
    cvReleaseImage(&dst2);
    cvReleaseImage(&dst3);
    cvReleaseImage(&dst4);
	cvReleaseImage(&dst5);
	cvReleaseImage(&dst6);
	cvReleaseImage(&dst7);
	cvReleaseImage(&dst8);
	cvReleaseImage(&dst9);
	cvReleaseImage(&dst10);
	

    char tempbuf[2000];
    sprintf(tempbuf, "diff --brief -w %s %s", OUTPUT_IMAGE0, OUTPUT_IMAGE1);
    int ret = system(tempbuf);

    /*
    if (ret != 0) {
        printf("Test Failed!\n");
	ret = 1;
    } else {
	printf("Test Passed!\n");
    }
    return ret;
    */
    return 0;
}
