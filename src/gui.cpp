#include <gui.hpp>
#include <app.hpp>
namespace shb{
bool GUI::initialisedLib = false;

float xyzTrans[3] = {0.f,0.f,0.f} ;
float xyzPos[3] = {0.f,0.f,0.f} ;
float xyzScale[3] = {1.f,1.f,1.f} ;
float xyzRot[3] = {0.f,0.f,0.f} ;

std::vector<float> xyz = {2.f,23.f,23.f};

int GUI::attachAppToGUI(App* _app){
        if(!_app){
            std::cout << "Null pointer passed to gui\n";
        }
        if(!app){
            app = _app;
            return 1;
        }
        else{
            delete app;
            app = _app;
            return 1;
        }
        return -1;
}

void GUI::show(){
        //start frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        //begin first window
        ImGui::Begin("Debug", &open);
        ImGui::Text(std::string("App Name: " + app->appName).c_str());
        
        if(ImGui::CollapsingHeader("App Info")){
            ImGui::Checkbox("Demo Window", &demoWindow);
            ImGui::Text("Press M to toggle mouse input");
        }
    
        if(ImGui::CollapsingHeader("Objects")){
            
        for(int i = 0; i < app->objects.size(); ++i){
            if(ImGui::TreeNode(app->objects[i]->name.c_str())){
                    ImGui::SeparatorText("Model");
                        displayXYZ();
                        ImGui::DragFloat3("Rotation",xyzRot);

                        float objectScaleXYZ[3] = {app->objects[i]->scale.x,app->objects[i]->scale.y,app->objects[i]->scale.z};
                        ImGui::DragFloat3("Scale",objectScaleXYZ);
                        app->objects[i]->scale.x = objectScaleXYZ[0];
                        app->objects[i]->scale.y = objectScaleXYZ[1];
                        app->objects[i]->scale.z = objectScaleXYZ[2];
                    

                        float objectPosXYZ[3] = {app->objects[i]->pos.x,app->objects[i]->pos.y,app->objects[i]->pos.z};
                        ImGui::DragFloat3("Position", objectPosXYZ);
                        app->objects[i]->pos.x = objectPosXYZ[0];
                        app->objects[i]->pos.y = objectPosXYZ[1];
                        app->objects[i]->pos.z = objectPosXYZ[2];

                    ImGui::SeparatorText("Projection");
                  
                    ImGui::SeparatorText("Texture");
                        ImGui::Text("%d", app->objects[i]->texture);
                        if (ImGui::Button("Increment")) {
                            if(app->objects[i]->texture<Texture::textures.size()-1){
                                app->objects[i]->texture++;
                            }
                        }
                        ImGui::SameLine(); // Put the next button on the same line
                        if (ImGui::Button("Decrement")) {
                            if(app->objects[i]->texture > 0){
                                app->objects[i]->texture--;
                            }
                        }
                        if (ImGui::Button("Reload shader")) {
                            app->reloadShader();
                        }   

                    ImGui::TreePop();
                }     

            }
        }
        if(ImGui::CollapsingHeader("Text projection")){
            ImGui::DragFloat("textLeft",&app->textDetails.textLeft);
            ImGui::DragFloat("textRight",&app->textDetails.textRight);
            ImGui::DragFloat("textBottom",&app->textDetails.textBottom);
            ImGui::DragFloat("textTop",&app->textDetails.textTop);
            ImGui::DragFloat("textZNear",&app->textDetails.textZNear, 0.1f);
            ImGui::DragFloat("textZFar",&app->textDetails.textZFar);
        }


        if(ImGui::CollapsingHeader("App projection")){
            ImGui::DragFloat("FOV",&app->radians,0.4f);
            ImGui::DragFloat("aspectRatioX",&app->aspectRatioX,0.4f);
            ImGui::DragFloat("aspectRatioY",&app->aspectRatioY,0.4f);
            ImGui::DragFloat("near",&app->near,0.4f);
            ImGui::DragFloat("far",&app->far);

        }

        if(ImGui::CollapsingHeader("Window settings")){
            ImGui::DragFloat("Viewport X",&app->viewportHeight);
            ImGui::DragFloat("Viewport Y",&app->viewportWidth);
            ImGui::Checkbox("Background opaque?",&app->transparency);
            ImGui::Checkbox("Maintain aspect ratio?",&app->maintainAspectRatio);
            ImGui::Checkbox("Maintain viewport size?",&app->maintainViewportSize);
            ImGui::DragFloat3("Clear colour RGB",app->clearRGB.data()); //drag int?
            for(int i = 0; i < app->clearRGB.size(); ++i){
                if(app->clearRGB[i] > 255){
                    app->clearRGB[i] = 255;
                }
                if(app->clearRGB[i] < 0){
                    app->clearRGB[i] = 0;
                }
            }
        }

        

        if(ImGui::CollapsingHeader("Camera")){
            xyz[0] = app->cameras[app->camIndex].pos.x;
            xyz[1] = app->cameras[app->camIndex].pos.y; 
            xyz[2] = app->cameras[app->camIndex].pos.z;
            ImGui::DragFloat3("xyz",xyz.data(), app->cameras[app->camIndex].moveSpeed);
            app->cameras[app->camIndex].pos.x = xyz[0];
            app->cameras[app->camIndex].pos.y = xyz[1];
            app->cameras[app->camIndex].pos.z = xyz[2];

            xyz[0] = app->cameras[app->camIndex].front.x;
            xyz[1] = app->cameras[app->camIndex].front.y; 
            xyz[2] = app->cameras[app->camIndex].front.z;
            ImGui::DragFloat3("target",xyz.data(), app->cameras[app->camIndex].moveSpeed);
            app->cameras[app->camIndex].front.x = xyz[0];
            app->cameras[app->camIndex].front.y = xyz[1];
            app->cameras[app->camIndex].front.z = xyz[2];

            ImGui::DragFloat("yaw",&app->cameras[app->camIndex].yaw);
            ImGui::DragFloat("pitch",&app->cameras[app->camIndex].pitch);
            app->cameras[app->camIndex].update();
            

            if (ImGui::Button("Increment")) {
                    if(app->camIndex<app->cameras.size()-1){
                            app->camIndex++;
                    }
                }
            ImGui::SameLine(); // Put the next button on the same line
            if (ImGui::Button("Decrement")) {
                if(app->camIndex > 0){
                    app->camIndex--;
                }
            }
            
        }


        if(ImGui::CollapsingHeader("Shaders")){
            if(ImGui::TreeNode("shaderProgram3DObjectSkybox")){
                ImGui::DragInt("offset",&app->offset);
                ImGui::DragFloat3("color",shaderColors, 0.01f, 0.0f, 1.f);
                ImGui::DragFloat("smoothstepStart",&app->smoothstepStart, 0.001f, 0.0f, 1.f);
                ImGui::DragFloat("smoothstepEnd",&app->smoothstepEnd, 0.001f, 0.0f, 1.f);
                
                app->skyboxColor[0] = shaderColors[0];
                app->skyboxColor[1] = shaderColors[1];
                app->skyboxColor[2] = shaderColors[2];
                ImGui::TreePop();
            }
        }


        //end frame
        ImGui::End();
        if(demoWindow){
            ImGui::ShowDemoWindow();
        }
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}

// Show a row displaying XYZ like 
// [x      y       z]
void GUI::displayXYZ(){
    if (ImGui::BeginTable("table1", 3))
    {
        std::string col = "";
        for (int row = 0; row < 1; row++)
        {
            ImGui::TableNextRow();
            for (int column = 0; column < 3; column++)
            {
                ImGui::TableSetColumnIndex(column);
                
                if(column ==0){
                    col = "x";
                }
                if(column ==1){
                    col = "y";
                }
                if(column ==2){
                    col = "z";
                }
                ImGui::TextUnformatted(col.c_str());
                
            }
        }
        ImGui::EndTable();

    }
}



//Creation and destruction
GUI::GUI(GLFWwindow* _window) : window(_window) { 
    if(!GUI::initialisedLib){
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 330");
        GUI::initialisedLib = true;
    }
}

}//namespace shb