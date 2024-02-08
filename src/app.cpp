#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <glad.c>

#include <app.hpp>
#include <imGUI/imgui_demo.cpp>

#include <checkpoints.hpp>

namespace shb{

AppState App::state{};

//std::vector<unsigned int> textures;

void App::reloadShader(){
    shaderProgram3DObjectSkybox = createShaderProg(
    {   {"3DObjectSkybox.vert",GL_VERTEX_SHADER}, 
        {"3DObjectSkybox.frag",GL_FRAGMENT_SHADER}    
    }
    );
    skybox.shaderProgram = shaderProgram3DObjectSkybox;
}

App::App(const std::string& _name) : appName(_name)
{
    //PLEASE MAKE TEXT RENDERER A SINGLETON
    textRenderer.init();
    
    //main camera. TODO:: name cameras, camera manager class?
    cameras.push_back(mainCamera);
    mainCamera.index = cameras.size()-1;
    
    cameras.push_back(followCamera);
    followCamera.index = cameras.size()-1;

    for(int i = -5; i < 5; i++){
        Camera randomCamera{{(float)i,1,0},{0.f,0.f,0.f}};
        cameras.push_back(randomCamera);
    }

    //shaders and shader programs
    shaderProgramTex3DObject = createShaderProg(
    {   {"3DObjectTextured.vert",GL_VERTEX_SHADER}, 
        {"3DObjectTextured.frag",GL_FRAGMENT_SHADER}    
    }
    );
    shaderProgram3DObjectSkybox = createShaderProg(
    {   {"3DObjectSkybox.vert",GL_VERTEX_SHADER}, 
        {"3DObjectSkybox.frag",GL_FRAGMENT_SHADER}    
    }
    );

    shaderProgram3DObject = createShaderProg(
    {   {"3DObject.vert",GL_VERTEX_SHADER}, 
        {"3DObject.frag",GL_FRAGMENT_SHADER}    
    }
    );

  
    //buffers
    quadVertexBuffer.fillBuffer(VertexData::quad().vertices);
    quadIndexBuffer.fillBuffer(VertexData::quad().indices);
    //vao is used with index buffer to draw
    quadVAO = formatVertexBufferGetVAO(quadVertexBuffer,
        {
        {VAO_FORMAT_VER, 3},
        {VAO_FORMAT_COL, 3},
        {VAO_FORMAT_TEX, 2}
        }
    );

    cubeTexturedVertexBuffer.fillBuffer(VertexData::cubeTextured().vertices);
    cubeTexturedIndexBuffer.fillBuffer(VertexData::cubeTextured().indices);
    cubeTexturedVAO = formatVertexBufferGetVAO(cubeTexturedVertexBuffer,
        {
        {VAO_FORMAT_VER, 3},
        {VAO_FORMAT_COL, 3},
        {VAO_FORMAT_TEX, 2}
        }
    );

    cubeVertexBuffer.fillBuffer(VertexData::cube().vertices);
    cubeIndexBuffer.fillBuffer(VertexData::cube().indices);
    cubeVAO = formatVertexBufferGetVAO(cubeVertexBuffer,
        {
        {VAO_FORMAT_VER, 3},
        {VAO_FORMAT_COL, 3}
        }
    );

    
    floor.indexBuffer = &quadIndexBuffer;
    floor.vertexBuffer = &quadVertexBuffer;
    floor.vao = quadVAO;
    floor.shaderProgram = shaderProgramTex3DObject;
    floor.texture = 7;
    floor.name = "Floor";
    floor.numElements = VertexData::quad().indices.size();
    floor.type = OBJECT_TYPE_QUAD;
    floor.pos = glm::vec3{0.f,0.f,0.f} ;
    floor.scale = glm::vec3(20.f,1.f,20.f);
    float rotAngle = 90.f;
    glm::vec3 rotAxis = glm::vec3(1.f, 0.f, 0.f);
    floor.model *= glm::translate(glm::mat4(1.f),floor.pos) *  glm::scale(glm::mat4(1.f),floor.scale) * glm::rotate(glm::mat4(1.f),glm::radians(rotAngle),rotAxis) ;
    
    objects.push_back(&floor);
    floor.index = objects.size()-1;
    floorIndex = objects.size()-1;

    skybox.vertexBuffer = &cubeVertexBuffer;
    skybox.indexBuffer = &cubeIndexBuffer;
    skybox.vao = cubeVAO;
    skybox.shaderProgram = shaderProgram3DObjectSkybox;
    skybox.scale = glm::vec3{1.f};
    skybox.name = "skybox";
    skybox.pos = glm::vec3{-1.f,floor.pos.y+1.f,-3.f};
    skybox.numElements = VertexData::cube().indices.size();
    skybox.type = OBJECT_TYPE_CUBE;
    skybox.model = glm::scale(glm::mat4{1.f},skybox.scale); 
    objects.push_back(&skybox);
    
    cube3.vertexBuffer = &cubeTexturedVertexBuffer;
    cube3.indexBuffer = &cubeTexturedIndexBuffer;
    cube3.vao = cubeTexturedVAO;
    cube3.shaderProgram = shaderProgramTex3DObject;
    cube3.name = "Cube3 1";
    cube3.texture = 6;
    cube3.numElements = VertexData::cubeTextured().indices.size();
    cube3.type = OBJECT_TYPE_CUBE;
    cube3.pos = glm::vec3(-8.0f,floor.pos.y+1.f,-4.0f);
    cubeRotAngle = glm::radians(50.f);
    cubeRotAxis = glm::vec3(1.f, 0.f, 0.f);
    cube3.model = glm::mat4{1.f};
    objects.push_back(&cube3);
 
    
    cube2.pos = glm::vec3(0.f,0.f,-0.5f);
    cube2.model =glm::translate(glm::mat4{1.f},cube2.pos) * glm::rotate(glm::mat4{1.f},glm::radians(90.f),glm::vec3(0,1,0)) * glm::scale(glm::mat4{1.f},cube2.scale);
    cube2.texture = 0;
    cube2.name = "Cube 2";
    cube2.vertexBuffer = &cubeTexturedVertexBuffer;
    cube2.indexBuffer = &cubeTexturedIndexBuffer;
    cube2.vao = cubeTexturedVAO;
    cube2.numElements = VertexData::cubeTextured().indices.size();
    cube2.shaderProgram = shaderProgramTex3DObject;
    cube2.type = OBJECT_TYPE_CUBE;
    objects.push_back(&cube2);
   

   //trefoil knot - TODO:: create it's own vertex buffer
    float x = -10.f;
    float y = 1.f;
    float t = -10.f;
    for(int i = 0; i < 200; ++i){
        Object cubeEntry;
        //x +=0.1f;
        t += 0.1f;
        x = sin(t) + 2*sin(2*t);
        y = cos(t) -2*cos(2*t);
        cubeEntry.pos = glm::vec3(x*10,y*10,0) + glm::vec3(150.f,30.f,-100.f);
        cubeEntry.model =glm::translate(glm::mat4{1.f},cubeEntry.pos);
        cubeEntry.scale = glm::vec3{.05f};
        cubeEntry.texture = i%Texture::textures.size()-1;
        cubeEntry.vertexBuffer = &cubeVertexBuffer;
        cubeEntry.indexBuffer = &cubeIndexBuffer;
        cubeEntry.vao = cubeVAO;
        cubeEntry.shaderProgram = shaderProgram3DObject;
        cubeEntry.numElements = VertexData::cube().indices.size();
        cubes.push_back(cubeEntry);
    }

    textRenderer.setTextUniformProjection(
        glm::ortho(
            textDetails.textLeft,
            textDetails.textRight,
            textDetails.textBottom,
            textDetails.textTop,
            textDetails.textZNear,
            textDetails.textZFar
        )
    );
    //textRenderer.setTextUniformProjection(glm::perspective(glm::radians(90.f),(float)WIN_WIDTH/WIN_HEIGHT,0.1f,10000.f));

}


void drawObject(Object* object){

    if(!object->shaderProgram){
        reportError("No shader program on " + object->name);
    }
    glUseProgram(object->shaderProgram);
    glUniformMatrix4fv(glGetUniformLocation( object->shaderProgram, "model" ), 1, GL_FALSE, &object->model[0][0]);

    if(object->texture != -1){
        glUniform1i(glGetUniformLocation(object->shaderProgram, "tex"), 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, Texture::textures[object->texture]);
    }
    
    glBindVertexArray(object->vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object->indexBuffer->id());
    glDrawElements( GL_TRIANGLES ,object->numElements, GL_UNSIGNED_INT,0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

//very limited. Not actually bouncing.
void objectBounce(Object* object, float amount){
    object->pos.y = abs(sin((float)glfwGetTime())) * amount + 1.f;
}

void App::renderFrame()
{   
    glViewport( 0, 0, viewportWidth, viewportHeight);
    glClearColor(clearRGB[0]/255.f,clearRGB[1]/255.f,clearRGB[2]/0.f,(float)transparency);
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

    updateKeyInput();
    updateMouseInput(); 
    //get delta
    timeSinceStart = glfwGetTime();       
    state.delta = delta = timeSinceStart - oldTimeSinceStart;
    oldTimeSinceStart = timeSinceStart;             
    frameTimeMS = delta *1000;
    

    //update view and projection
    cameras[camIndex].update();
    view = cameras[camIndex].view;
    proj3d = glm::perspective(glm::radians(radians),aspectRatioX/aspectRatioY,near,far);

    //uniforms
    glUseProgram(shaderProgramTex3DObject);
    GLuint uModel = glGetUniformLocation( shaderProgramTex3DObject, "model" );
    GLuint uView = glGetUniformLocation( shaderProgramTex3DObject, "view" );
    GLuint uProj = glGetUniformLocation( shaderProgramTex3DObject, "projection" );

    //feed the shaders ʕっ•ᴥ•ʔっ (｡◕‿‿◕｡)
    glUniformMatrix4fv(uView, 1, GL_FALSE, &view[0][0]);
    glUniformMatrix4fv(uProj, 1, GL_FALSE, &proj3d[0][0]);

    glUseProgram(shaderProgram3DObject);
    glUniformMatrix4fv(glGetUniformLocation( shaderProgram3DObject, "view" ), 1, GL_FALSE, &view[0][0]);
    glUniformMatrix4fv(glGetUniformLocation( shaderProgram3DObject, "projection" ), 1, GL_FALSE, &proj3d[0][0]);

 
    //Skybox shader work
    glUseProgram(shaderProgram3DObjectSkybox);
    glUniformMatrix4fv(glGetUniformLocation( shaderProgram3DObjectSkybox, "view" ), 1, GL_FALSE, &view[0][0]);
    glUniformMatrix4fv(glGetUniformLocation( shaderProgram3DObjectSkybox, "projection" ), 1, GL_FALSE, &proj3d[0][0]);
    glUniform1f(glGetUniformLocation( shaderProgram3DObjectSkybox, "iTime" ), glfwGetTime());
    glUniform1i(glGetUniformLocation( shaderProgram3DObjectSkybox, "offset" ), offset);
    glUniform3fv(glGetUniformLocation( shaderProgram3DObjectSkybox, "colors" ), 1, &skyboxColor[0]);
    glUniform1f(glGetUniformLocation( shaderProgram3DObjectSkybox, "smoothstepStart" ), smoothstepStart);
    glUniform1f(glGetUniformLocation( shaderProgram3DObjectSkybox, "smoothstepEnd" ), smoothstepEnd);


    //UPDATE CUBE
    cube3.model = glm::mat4{1.f};
    objectBounce(&cube3, 5.f);
    cube3.model *= glm::translate(glm::mat4{1.f}, cube3.pos) * glm::scale(glm::mat4{1.f},cube3.scale);
    cube3.model *= glm::rotate(glm::mat4{1.f},(float)glfwGetTime()*cubeRotAngle,cubeRotAxis);
    

    //rotate cube 2 around cube 1
    cube2.model = glm::mat4{1.f};
    cube2.pos = cube3.pos + glm::vec3{2.f,2.f,2.f};
    cube2.model *= glm::translate(glm::mat4{1.f}, cube2.pos);
    cube2.model *= glm::translate(glm::mat4{1.f}, cube3.pos - cube2.pos);

    cube2.model *= glm::rotate(glm::mat4{1.f},(float)glfwGetTime()* (float)glm::radians(50.f),glm::vec3{1.f,1.f,0.f}) * glm::scale(glm::mat4{1.f},cube2.scale);
    cube2.model *= glm::translate(glm::mat4{1.f}, cube2.pos - cube3.pos);
    
    cameras[followCamera.index].pos = cube2.pos + glm::vec3{4.f,4.f,4.f};
    cameras[followCamera.index].target = cube3.pos; //TODO:: Fix


    skybox.model = glm::mat4{1.f};
    skybox.model *= glm::scale(glm::mat4{1.f},skybox.scale) * glm::translate(glm::mat4{1.f}, skybox.pos);
    
    floor.model = glm::mat4(1.f);
    floor.model *= glm::scale(glm::mat4{1.f},floor.scale) *glm::translate(glm::mat4(1.f),floor.pos) * glm::rotate(glm::mat4(1.f),glm::radians(90.f),glm::vec3{1.f,0.f,0.f});
    //draw all objects
    for( int i = 0; i < objects.size(); ++i){
        drawObject(objects[i]);
    }

  

    for(int i = 0; i <cubes.size()-1; ++i){
        cubes[i].model = glm::mat4{1.f};
        cubes[i].model *= glm::scale(glm::mat4{1.f},cubes[i].scale);
        cubes[i].model *= glm::translate(glm::mat4{1.f},cubes[i].pos);
        cubes[i].model *= glm::rotate(glm::mat4{1.f},(float)glfwGetTime()* (float)glm::radians(50.f),glm::vec3{1.f,1.f,0.f});
        drawObject(&cubes[i]);
    }
     
    renderText();

    //optionally keep everything in proportion
    if(maintainViewportSize){
        glfwGetFramebufferSize(window, &windowWidth, &windowHeight);
        viewportHeight = windowHeight;
        viewportWidth = windowWidth;
    }
    if(maintainAspectRatio){
        aspectRatioY = windowHeight;
        aspectRatioX = windowWidth;
    }
    
    //growing window lol
    //growingWindowTimerMS += frameTimeMS;
    //if(growingWindowTimerMS > 500){
    //    glfwSetWindowSize(window,windowWidth+=20, windowHeight += 20);
    //    growingWindowTimerMS = 0;
    //}

}


App::~App(){
    glDeleteVertexArrays(1,&cube3.vao);  //TODO:: make VAO an object
    glDeleteVertexArrays(1,&objects[floorIndex]->vao);
}



void App::renderText(){
    textRenderer.setTextUniformProjection(
    glm::ortho(
        textDetails.textLeft,
        textDetails.textRight,
        textDetails.textBottom,
        textDetails.textTop,
        textDetails.textZNear,
        textDetails.textZFar
        )
    );
    
    //updates text based on a timer
    elapsedText += delta;
    if(elapsedText>=durationText){
        fps= 1000/delta;
        elapsedText = 0.f;
    }
    textRenderer.setScale(.5f); 
    textRenderer.setFont("debrosee.ttf"); 
    textRenderer.setColor({51.f/255.f,114.f/255.f,145.f/255.f});
    textRenderer.rendertext(appName, TextPositons::getPosition(TITLE)); 
    textRenderer.setFont("MonasRegular-7BZmR.ttf"); 
    textRenderer.setColor({255.f,0.f,0.f});
    textRenderer.setScale(.5f); 
    textRenderer.rendertext(std::to_string((int)fps)+ " fps", TextPositons::getPosition(BOTTOM_LEFT));
    textRenderer.setColor({240.f,255.f,240.f});
    textRenderer.setFont("Vanilla.ttf"); 
    textRenderer.setScale(.5f); 
    textRenderer.rendertext("Lorem ipsum dolor sit amet, consectetur adipiscing elit.", TextPositons::getPosition(BOTTOM_LEFT) + glm::vec3{0.0f,100.f,0.0f});        
    textRenderer.setColor({255,255,255});
    textRenderer.setFont("Amatic-Bold.ttf");
    textRenderer.rendertext("Mouse position: " + std::to_string(mouseXPos) + " " + std::to_string(mouseYPos), TextPositons::getPosition(TITLE)- glm::vec3{0.f,50.f,0.f});
}


}//namespace shb


int initOpenGL(){
    if (!glfwInit()){
        std::cout<<"GLFW init error";
        return -1;
    }
    return 1;
}


GLFWwindow* createWindow(int width, int height, std::string name, int monitor){
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, 1);
    //glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
    
    

    GLFWwindow* window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
    if (!window){
        std::cout<<"Window creation error";
        glfwTerminate();
        return nullptr;
    }

    int numMonitors;
    GLFWmonitor** monitors = glfwGetMonitors(&numMonitors);
    const GLFWvidmode* vidmode = glfwGetVideoMode(monitors[monitor]);
    int windowHeight = vidmode->height;
    int windowWidth = vidmode->width;
    glfwSetWindowMonitor(window,NULL ,0,0,windowWidth/2,windowHeight/2,GLFW_DONT_CARE);

    glfwMakeContextCurrent(window);
    gladLoadGL();
    
    glViewport( 0, 0, width, height);
    //glEnable              ( GL_DEBUG_OUTPUT );
    //glDebugMessageCallback( MessageCallback, 0 );
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  
    glEnable(GL_DEPTH_TEST);

    //Window icon
    GLFWimage image[1];
    image[0].pixels = stbi_load("../resources/textures/icon2.png", &image[0].width, &image[0].height, 0, 4); 
    glfwSetWindowIcon(window, 1, image);
    stbi_image_free(image[0].pixels); 

    

    return window;
}


int main(){

    initOpenGL();
    checkpoint("init opengl.");
    //create opengl window
    GLFWwindow* window = createWindow(WIN_WIDTH,WIN_HEIGHT,"SHB Engine", 0);
    //GLFWwindow* window2 = createWindow(WIN_WIDTH,WIN_HEIGHT,"SHB Engine2", 0); //FIX:: breaks for some reason when trying to render to second window
    checkpoint("window created.");

    //create GUI
    shb::GUI gui{window};
    shb::GUI gui2{window};
    checkpoint("GUI created.");

    //load all textures
    shb::setTextureParams();
    shb::loadAllTextures(&shb::Texture::textures);
    checkpoint("textures created.");

    //pass app to gui
    shb::App app{"Sandbox"};
    app.attachAppToWindow(window);
    gui.attachAppToGUI(&app);
    shb::App app2{"Scuba Diving"};
    app2.attachAppToWindow(window);
    gui2.attachAppToGUI(&app2);

    checkpoint("apps created.");

    checkpoint("Running...");
    while (app.running){   
        glfwMakeContextCurrent(window);

        if(glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS){
            app2.renderFrame();
            gui2.show();
        }
        else{
            app.renderFrame();
            if(gui.open){
                gui.show();
            }
        }
        if(glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS){ //TODO:: account for debounce
            gui.open = !gui.open;
        }
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    checkpoint("Finished.");
    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        std::cout << "OpenGL error: " << err << std::endl;
    }
    if (err == GL_NO_ERROR) {
        std::cout << "No Errors (lol)"<< std::endl;
    }
    return 0;
}