//
//  shader.cpp
//  myworld
//
//  Created by MacBook Pro on 1/18/17.
//  Copyright © 2017 the Goodies___. All rights reserved.
//

#include "shader.h"


shader::shader(const char* vertexshaderpath,const char* fragmentshaderpath)
{
    GLchar infolog[512];
    GLint success;
    //first:read the shader files
    ifstream vshader;
    ifstream fshader;
    
    //strings to store the shader code
    string vshadcode;
    string fragshadcode;
    
    //string streams used to store the read date
    stringstream vshaders;
    stringstream fshaders;
    
    //cstrings to be used by gl functions
    const GLchar*  vcode;
    const GLchar*  fcode;
    
    //setting error state flags for which a failure exception is thrown
    vshader.exceptions(ifstream::failbit|ifstream::badbit);
    fshader.exceptions(ifstream::failbit|ifstream::badbit);
    try{
    vshader.open(vertexshaderpath);
    fshader.open(fragmentshaderpath);
    
        
        vshaders<<vshader.rdbuf();
        fshaders<<fshader.rdbuf();
        
        vshader.close();
        fshader.close();
        
        vshadcode=vshaders.str();
        fragshadcode=fshaders.str();
        
        
        //now convert the code to c string to be able to pass it to the glsourceshader function
        vcode=vshadcode.c_str();
        fcode=fragshadcode.c_str();
        
        //now create the shaders and compile them
        vertexcode=glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexcode,1,&vcode,NULL);
        glCompileShader(vertexcode);
        
        //check for any compilation errors
        glGetShaderiv(vertexcode,GL_COMPILE_STATUS,&success);
        if (!(success)) {
            glGetShaderInfoLog(vertexcode,512,NULL,infolog);
            cout<<"Error in compilation of vertex shader ."<<infolog<<endl;
            
        }
        
        
        fragmentcode=glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentcode,1,&fcode,NULL);
        glCompileShader(fragmentcode);
        
        glGetShaderiv(fragmentcode,GL_COMPILE_STATUS,&success);
        
        if (!(success)) {
            glGetShaderInfoLog(fragmentcode,512,NULL,infolog);
            cout<<"Error in compilation of fragment shader ."<<infolog<<endl;
            
        }
        
        //create the program object and link the shaders to it
        programID=glCreateProgram();
        glAttachShader(this->programID,vertexcode);
        glAttachShader(this->programID,fragmentcode);
        glLinkProgram(this->programID);
        
        //check for link status
        
        glGetProgramiv(this->programID,GL_LINK_STATUS,&success);
        if(!success)
        {
            glGetProgramInfoLog(this->programID,512,NULL,infolog);
            cout<<"Failure to link the program. "<<infolog<<endl;
        }
        
        //after attaching the shaders to the program object you no longer need these shaders so delete them
        glDeleteShader(vertexcode);
        glDeleteShader(fragmentcode);
        
        
        
    }
    catch(ifstream::failure e)
    {
        cerr<<"Error: Shader file not successfully read ."<<endl;
    }
    
    
    
}

void shader::use()
{
    glUseProgram(this->programID);
}

