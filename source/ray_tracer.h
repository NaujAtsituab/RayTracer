//  +--------------------------------------+
//  | CSCI420 - Computer Graphics          |
//  | Assignment 3 - Ray Tracer            |
//  | Author: Rodrigo Castiel              |
//  +--------------------------------------+
// ray_tracer.h

#pragma once

#include <string>
#include <iostream>
#include "gl_header.h"

#include "scene.h"
#include "camera.h"
#include "math_functions.h"

const unsigned kDefaultWidth  = 640;
const unsigned kDefaultHeight = 480;
const unsigned kFormatSize = 3;

const unsigned kMaxWidth  = 4096;
const unsigned kMaxHeight = 2160;


// ============================================================================================= //

template <const unsigned W, const unsigned H>
struct ImgBuffer
{
  // The actual buffer (static).
  unsigned char data[ W * H * kFormatSize ];

  // Dimensions of output images.
  int width   { kDefaultWidth  };
  int height  { kDefaultHeight };

  // Does not check boundaries - returns pixel regarding sub buffer defined by width and height.
  inline unsigned char * GetPixel(int x, int y) { return &data[kFormatSize*(width * y + x)]; }

  // Outputs image as JPEG to 'filePath'.
  void Save(const std::string & filePath)
  {
    ImageIO img(width, height, kFormatSize, data);

    if (img.save(filePath.c_str(), ImageIO::FORMAT_JPEG) != ImageIO::OK)
    {
      std::cerr << "ERROR Saving image buffer (JPEG) at " << filePath << ".\n";
    }
    else
    { 
      std::cout << "Image buffer (JPEG) saved at " << filePath << ".\n";
    }
  }

  // Draws its data on screen.
  void Draw()
  {
    glPointSize(2.0);  
    glBegin(GL_POINTS);

    for(unsigned int y = 0; y < height; y++)
    {
      for(unsigned int x = 0; x < width; x++)
      {
        unsigned char * pixel = GetPixel(x, y);
        glColor3f((static_cast<float>(pixel[0])) / 255.0f, 
                  (static_cast<float>(pixel[1])) / 255.0f, 
                  (static_cast<float>(pixel[2])) / 255.0f);
        glVertex2i(x, height - y);
      }
    }

    glEnd();
  }
};

// ============================================================================================= //

class Scene;
class Camera;

class RayTracer
{
public:
  RayTracer() {  }

  // Performs Ray Tracing algorithm and outputs to internal ImgBuffer.
  void RenderFrame(const Scene & scene, const Camera & camera);

  // Outputs current frame to filePath as JPEFG file.
  void SaveFrame(const std::string & filePath);

  // Displays internal buffer on the screen.
  void DrawFrame();

  // Returns the internal ImgBuffer.
  ImgBuffer<kMaxWidth, kMaxHeight> & GetFrame() { return mBuffer; }

private:
  ImgBuffer<kMaxWidth, kMaxHeight> mBuffer;
};

// ============================================================================================= //














