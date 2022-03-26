# Image Enhancement with the Application of Local and Global Enhancement Methods for Dark Images 

###### tags: `Image Processing`, `Paper Implmentation`

## Flow chart of the proposed Algorithm

![](https://i.imgur.com/ZtZNAMo.png)

## Abstract

The disvantage of Global image contrast enhacement is it didn’t consider the local details of an image.

The key of this proposed algorithm is
1. local enhance on the image
2. global enhance the output.


## Introduction

Contrast stretching contain two types of methods.

- Global Enhancement
- Local Enhancement

Spatial domain means processing of image is done directly on the image pixel, not on the other transformed domain.

One technique may give a very good result to a specific type of image but may not give to another type.

## Background Knowledge

### Image Enhancement Techniques

1. Local Enhancement of the image.
    + [Unsharp masking](https://www.notion.so/Unsharp-masking-Local-Enhancement-95b790311bfe4852a4a668b872fa5a16)
2. Global Enhancement of the image.
    + [Global Histogram Equalization](https://www.notion.so/Global-Histogram-Equalization-GHE-fb0bc67d7d9f4df58859fba010f0ee2e)

### Introduction of the Color Space: [HSV](https://www.notion.so/HSV-6eb655cb37b24091aeb910fae3dced34)

Code for RGB to HSV:
![](https://i.imgur.com/NPGLGA2.png)

![](https://i.imgur.com/xfTCGyK.png)


```c++=
void BGR2HSV(Mat &src, Mat &dst)
{
    // BGR TO HSV.
    for (int i = 0; i < src.rows; i++)
    {
        for (int j = 0; j < src.cols; j++)
        {
            double B = src.at<Vec3b>(i, j)[0] / 255.0;
            double G = src.at<Vec3b>(i, j)[1] / 255.0;
            double R = src.at<Vec3b>(i, j)[2] / 255.0;
            double V = findMax(R, G, B);
            dst.at<Vec3b>(i, j)[2] = 255.0 * V;                          // V
            dst.at<Vec3b>(i, j)[1] = 255.0 * (V - findMin(R, G, B)) / V; // S
            dst.at<Vec3b>(i, j)[0] = calculateHue(R, G, B, V);           // Calculate
        }
    }
}


double calculateHue(double R, double G, double B,double V)
{
	double H = 0;
	if (V == R)
	{
		H = fmod((60 * (G - B)) / (V - findMin(R, G, B)),360.0);
	}
	else if (V == G)
	{
		H = fmod(120 + (60 * (B - R)) / (V - findMin(R, G, B)),360.0);
	}
	else if (V == B)
	{
		H = fmod(240 + (60 * (R - G)) / (V - findMin(R, G, B)),360.0);
	}
	else if (R == G && G == B)
	{
		H = 0;
	}
	return H;
}


```

### Why use HSV:

The reason to change color space of the image is avoid failed on the RGB image.

Lots of Image Enhancement Techniques can not applied on RGB image.

For example, Using Histogram Equalization to enhance the image.

The gray image with histogram equalization:

![](https://i.imgur.com/Bhx92Vw.png)

The RGB image with histogram equalization (`RGB_HE.cpp`):
Can see the obvious distortion on the picture.
![](https://i.imgur.com/TDpbyes.jpg)

## Proposed Algorithm (`main.cpp`)

1. First we change the color space of the pic from `RGB` to `HSV`
![](https://i.imgur.com/X8anDrB.jpg)
3. Applied Local Enhancement Techniques (Unsharp masking)
![](https://i.imgur.com/Cd29g3q.jpg)

5. Applied Global Enhancement Techniques (Global Histogram Equalization)
![](https://i.imgur.com/JXTSV6S.jpg)

6. Change the color space back from `HSV` to `RGB`

![](https://i.imgur.com/aqDk7V7.jpg)

### Comparison between RGB and HSV method

![](https://i.imgur.com/RAlyIoD.jpg)
