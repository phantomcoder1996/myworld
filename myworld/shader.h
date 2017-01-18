//
//  shader.hpp
//  myworld
//
//  Created by MacBook Pro on 1/18/17.
//  Copyright © 2017 the Goodies___. All rights reserved.
//

#ifndef shader_h
#define shader_h
#include<GL/glew.h>
#include<string>
#include<sstream>
#include<fstream>
#include<iostream>
#include <stdio.h>
using namespace std;
//This is the program shader object
//now it includes the fragment shader and the vertex shader
class shader
{
    
    GLuint vertexcode;//id of the vertex shader
    GLuint fragmentcode; //id of the fragment shader
    
    public:
    GLuint programID; //The id of the program object containing  the vertex and fragment shaders
  
    shader(const char* vertexshaderpath,const char* fragmentshaderpath);
    void use(); //just a simple function to use the program object
    
    
    
    
    
};

#endif /* shader_hpp */
