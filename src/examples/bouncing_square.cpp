#include <main.hpp>

namespace shb{


int square()
{


    AppState state;
    createApplication(&state);
    std::thread inputThread(input,std::ref(state));

    //shaders and shader programs
    int quadShaderProg = createShaderProg();

    //create quad
    bool ortho = true;
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    if(ortho){
        vertices =  {
         0.f,   0.f,  0.f,   0.f,1.f,0.f,
         0.f,  500.f,  0.f,   1.f,0.f,1.f,
        500.f,  0.f,  0.f,   1.f,0.f,0.f,
        500.f,   500.f,  0.f,   0.f,0.f,1.f
        };
        indices ={
        0,1,3,  //bottom left, top left, top right
        0,3,2   //bottom left, top right, borttom right
        };
    }
    else{
        vertices =  {
            0.5f,   0.5f,  0.1f,   0.f,1.f,0.f,
            0.5f,  -0.5f,  0.1f,   0.f,1.f,1.f,
            -0.5f,  -0.5f,  0.1f,   0.f,1.f,0.f,
            -0.5f,   0.5f,  0.1f,   0.f,0.f,0.f
        };
        indices ={
        0,1,3,  //bottom left, top left, top right
        1,2,3   //bottom left, top right, borttom right
        };

    }
  
  
    
    //buffers
    GLuint quadVAO;
    glGenVertexArrays(1, &quadVAO);
    glBindVertexArray(quadVAO);
    
    unsigned int quadVertexBuffer;
    glGenBuffers(1,&quadVertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER,quadVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER,vertices.size() * sizeof(float),&vertices[0],GL_STATIC_DRAW);

    unsigned int quadIndexBuffer;
    glGenBuffers(1,&quadIndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,quadIndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,indices.size() * sizeof(unsigned int),&indices[0],GL_STATIC_DRAW);
   

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,quadIndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,indices.size() * sizeof(unsigned int),&indices[0],GL_STATIC_DRAW);
   
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    glBindVertexArray(0);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    
    glm::mat4 model{1.f};
    glm::mat4 view{1.f};
    glm::mat4 proj{1.f};
    view = glm::translate(view,glm::vec3(0,0,-0.2f)); 

    if(ortho){
        view = glm::translate(view,glm::vec3(250,250,0)); 
        proj = glm::ortho(0.f,(float)WIN_WIDTH,0.f,(float)WIN_HEIGHT,0.f,100.f); 
    }
    else{
        proj = glm::perspective(glm::radians(45.f),(float)WIN_WIDTH/WIN_HEIGHT,0.1f,100.f); 
    }

    
    float velocityX = 0.5f;
    float velocityY = 0.3f;
    float resist = -.9f;
    float gravity = -0.09f;

    float squareX = 250;
    float squareY = 250;

    

    while (state.running)
    {   
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0,0,0,0);
        
        if(!ortho){
            glm::mat4 model{1.f};
            glm::mat4 view{1.f};
            glm::mat4 proj{1.f};
        }
        int topOfSquare = squareY + 500;
        int bottomOfSquare = squareY;
        int leftOfSquare = squareX;
        int rightOfSquare = squareX +500;

        velocityY += gravity;

        if(topOfSquare >= WIN_HEIGHT || bottomOfSquare <= 0){
            if(velocityY > 0 && velocityY < 0.1){
                velocityY =0;
                squareY = 0;
                velocityX = 0;
               
            }else{
                velocityY *=resist;
            }
        }
        if(rightOfSquare >= WIN_WIDTH || leftOfSquare <= 0){
            if(velocityX != 0){
                velocityX *=resist;
            }
        }

        if(velocityX != 0){
            squareX += velocityX;
        }
        if(velocityY != 0){
            squareY += velocityY;
        }
        view = glm::translate(view, glm::vec3(velocityX,velocityY,0));
        
      
        //calc MVP 
        glm::mat4 mvp = proj*view*model;
        
        //uniforms
        glUseProgram(quadShaderProg);
        //send MVP to shader
        GLuint location = glGetUniformLocation( quadShaderProg, "MVP" );
        glUniformMatrix4fv(location, 1, GL_FALSE, &mvp[0][0]);


       // draw
        glBindVertexArray(quadVAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadIndexBuffer);
        glDrawElements( GL_TRIANGLES ,6, GL_UNSIGNED_INT,0);
        glBindVertexArray(0);

       
        glfwSwapBuffers(state.window);
        glfwPollEvents();
        if(glfwWindowShouldClose(state.window)){
            state.running = false;
        }
    }



    inputThread.join();
    glDeleteBuffers(1,&quadVertexBuffer);
    glDeleteBuffers(1,&quadIndexBuffer);
    glfwTerminate();
    return 0;
}

}//namespace shb