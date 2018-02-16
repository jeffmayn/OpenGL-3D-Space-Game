#include "main.h"
#include "utility/shape.h"

using namespace irrklang;

ISoundEngine *SoundEngine = createIrrKlangDevice();
void createShape(Shader* shader, Model m, glm::vec3 pos, float scale, glm::vec3 angle, glm::mat4 projection, glm::mat4 view);


Camera camera(glm::vec3(-20.0f, 20.0f, 3.0f));

glm::vec3 lightPos(-10.0f, 38.5f, 11.5f);

int main() {
    /** GLFW properties */
    glfwInit();
    glfwWindowHint(GL_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    /** Creating the window*/
    GLFWwindow* window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "Battleground IMADA", nullptr, nullptr);

    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

    SCR_WIDTH   = (unsigned int) mode->width;
    SCR_HEIGHT  = (unsigned int) mode->height;
    refreshRate = (unsigned int) mode->refreshRate;

    setCamera(camera, SoundEngine);

    /** Check if creation of window succeeded */
    if (!window){
        return -1;
    }
    glfwMakeContextCurrent(window);

    glfwSetCursorPos(window, WIN_WIDTH/2, WIN_HEIGHT/2);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetKeyCallback(window, special_key_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    /** Check if we could properly load GLAD */
    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    GLuint VBO, lampVAO;
    glGenVertexArrays(1, &lampVAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(lampVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*) nullptr);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    SoundEngine->play2D("assets/sounds/space_music.wav", GL_TRUE);

    Shader cube ("data/v_cube.glsl", "data/f_cube.glsl");
    Shader lamp ("data/v_lamp.glsl", "data/f_lamp.glsl");
    Shader shipShader("data/v_ship.glsl", "data/f_ship.glsl");

    const char* modelPath = "assets/models/cube/cube_blue.obj";
    const char* modelPath1 = "assets/models/table/table01.obj";
    const char* modelPath2 = "assets/models/room/room01.obj";
    const char* modelPath3 = "assets/models/pc_screen/screen.obj";
    const char* modelPath4 = "assets/models/chair/chair_01.obj";
    const char* modelPath5 = "assets/models/battlecruiser/test_cruiser.obj";

    Model tables(modelPath1);
    Model room(modelPath2);
    Model pcScreen(modelPath3);
    Model chair(modelPath4);

    Model shipModel(modelPath5);

    Text text(SCR_WIDTH, SCR_HEIGHT, "data/text.vs", "data/text.frag");

    text.GenerateText("assets/fonts/starcraft.ttf");

    string hp;
    GLuint counter = 160000;
    GLuint fuelConsumption = 10;
    // placing the imovable battle-pinata
    glm::vec3 collide = glm::vec3(0.0f,0.0f,-30.0f);
    setImoveable(collide);

    /** Define our triangle coordinates */

    glEnable(GL_DEPTH_TEST);

    bool walkXpos = false, walkXneg = true;
    bool walkZpos = false, walkZneg = false;
    float limit = 5.0f;
    float increment = 0.1f;

    // ---------- Rendering loop -------------------

    while(!glfwWindowShouldClose(window)){

        updateDeltaTime();
        processInput(window);

        // background
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if(counter >= 0){
            counter -= fuelConsumption;
        }
        std::ostringstream os;
        os << counter;
        std::string digits = os.str();

        if(digits.size() == 6){
            hp = "Fuel: " + digits.substr(0, 3) + "." + digits.substr(3, 3);
        }
        else if (digits.size() == 5){
            hp = "Fuel: " + digits.substr(0, 2) + "." + digits.substr(2, 3);
        }
        else if (digits.size() == 4) {
            hp = "Fuel: " + digits.substr(0, 1) + "." + digits.substr(1, 3);
        }
        else if (counter == 0){
            hp = "Fuel: RESERVE, DOCK IMMEDIATELY";
        }
        else {
            hp = "Fuel: " + digits;
        }

        os.clear();

        glEnable(GL_BLEND);
        text.shader.use();
        if(counter > 0){
            text.RenderText(hp, 25.0f, 25.0f, 0.4f, glm::vec3(0.5, 0.8f, 0.2f));
            counter--;
        }
        string title = "Battleground IMADA";
        text.RenderText(title, (1920/2) - 300, 1000, 0.9f, glm::vec3(0.3f, 0.7f, 0.9f));
        text.RenderText("First objective commander:  Scout the room for enemies !", 100.0f, 570.0f, 0.5f, glm::vec3(0.3, 0.7f, 0.9f));
        glDisable(GL_BLEND);

        glm::mat4 projection;
        if(windowedMode){
            projection = glm::perspective(glm::radians(camera.Zoom), (float) WIN_WIDTH / (float) WIN_HEIGHT, 0.1f, 10000.0f);
        }
        else{
            projection = glm::perspective(glm::radians(camera.Zoom), (float) SCR_WIDTH / (float) SCR_HEIGHT, 0.1f, 10000.0f);
        }
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 model;


        // GENERATE LAMPS AND LIGHT
        for (unsigned int j = 0; j < 3; j++) {
            for (unsigned int i = 0; i < 6; i++) {
                GLfloat x = -10.0f + j * 32.6f, y = 38.5f, z;
                if(i < 3){
                    z = 11.5f - i * 30;
                }
                else {
                    z = -10.0f - i * 30;
                }
                cube.use();
                cube.setVec3("light.position", x, y, z);
                cube.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
                cube.setVec3("light.specular", 1.0f, 0.856f, 0.501f);

                cube.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
                cube.setFloat("material.shininess", 64.0f);
                model = glm::scale(model, glm::vec3(22.0f, 0.0f,6.0f));
                cube.setMat4("model", model);

                model = glm::mat4();
                lamp.use();
                lamp.setMat4("projection", projection);
                lamp.setMat4("view", view);
                model = glm::translate(model, glm::vec3(x, y, z));
                model = glm::scale(model, glm::vec3(22.0f, 1.0f,6.0f));
                lamp.setMat4("model", model);

                glBindVertexArray(lampVAO);
                glDrawArrays(GL_TRIANGLES, 0, 36);
            }
        }

        for (unsigned int j = 0; j < 4; j++){
            for (unsigned int i = 0; i < 4; i++){
                Shape chairObj(&cube, &chair, view, projection);
                chairObj.Move(10.5f + j * 21.0f, -2.2f, -23.0f - i * 40);
                chairObj.Scale(1.5f, AXIS_XYZ);
                chairObj.Rotate(90.0f, AXIS_X);
                chairObj.Rotate(90.0f, AXIS_Z);
//                chairObj.Rotate(180.0f, AXIS_Z);
                chairObj.Render();
            }
        }
        for (unsigned int j = 0; j < 4; j++){
            for (unsigned int i = 0; i < 4; i++){
                Shape chairObj(&cube, &chair, view, projection);
                chairObj.Move(-3.5f + j * 21.0f, -2.0f, 3.0f - i * 40);
                chairObj.Scale(1.5, AXIS_XYZ);
                chairObj.Rotate(90.0f, AXIS_X);
                chairObj.Rotate(270.0f, AXIS_Z);
                chairObj.Render();
            }
        }
        // START PC-SCREEN-MODELS
        for (unsigned int j = 0; j < 4; j++){
            for (unsigned int i = 0; i < 4; i++){
                Shape screen(&cube, &pcScreen, view, projection);
                screen.Move(3.7f + i * 21.0f, 3.7f, -15.0f - j * 40);
                screen.Scale(0.7f, AXIS_XYZ);
                screen.Rotate(90.0f, AXIS_X);
                screen.Rotate(180.0f, AXIS_Z);
                screen.Render();
            }
        }
        for (unsigned int j = 0; j < 4; j++){
            for (unsigned int i = 0; i < 4; i++){
                Shape screen(&cube, &pcScreen, view, projection);
                screen.Move(3.7f + j * 21.0f, 3.7f, -5.0f - i * 40);
                screen.Scale(0.7, AXIS_XYZ);
                screen.Rotate(90.0f, AXIS_X);
                screen.Render();
            }
        }
        // END PC-SCREEN-MODELS

        // START ROOM-MODEL
        Shape roomObj(&cube, &room, view, projection);
        roomObj.Move(0.0f, 0.0f, 0.0f);
        roomObj.Scale(1.0f, AXIS_XYZ);
        roomObj.Rotate(0.0, AXIS_Y);
        roomObj.Render();
        // END ROOM-MODEL

        // START TABLE-MODELS
        for (unsigned int j = 0; j < 4; j++){
            for (unsigned int i = 0; i < 4; i++){
                Shape tableObj(&cube, &tables, view, projection);
                tableObj.Move(3.0f + i * 21.0f, 5.0f, -15.0f - j * 40);
                tableObj.Scale(0.7f, AXIS_XZ);
                tableObj.Scale(1.2f, AXIS_Y);
                tableObj.Scale(1.3f, AXIS_X);
                tableObj.Rotate(180.0f, AXIS_Y);
                tableObj.Render();
            }
        }
        for (unsigned int k = 0; k < 4; k++) {
            for (unsigned int m = 0; m < 4; m++) {
                Shape tableObj(&cube, &tables, view, projection);
                tableObj.Move(3.0f + k * 21.0f, 5.0f, -5.0f - m * 40);
                tableObj.Scale(0.7f, AXIS_XZ);
                tableObj.Scale(1.2f, AXIS_Y);
                tableObj.Scale(1.3f, AXIS_X);
                tableObj.Rotate(0.0f, AXIS_Y);
                tableObj.Render();
            }
        }
        // END TABLE-MODELS
//        // moves the camera along with model
        camera.setPos(getPos() + getDir() * glm::vec3(-10.0, 10.0, -10.0)); // disable to get free cameraview
        camera.setFront(getDir() * glm::vec3(1.0f, -1.0f, 1.0f));
//        glm::mat4 view = camera.GetViewMatrix();

//        ----- calling in the fleet.. -------
        createShape(&shipShader, shipModel, getPos(), 0.1f, getRot(), projection, view);
//        ------ calling in crash-test-dummy ---
        createShape(&shipShader, shipModel, collide, 0.1f,glm::vec3(0.0f, 0.0f, 0.0f), projection, view);


        /** Check and call events, and swap buffers */
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    /** Terminate program */
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwTerminate();
    return 0;
}

void moveShape(glm::vec3 &pos, float increment, float limit, bool &walkXpos, bool &walkXneg, bool &walkZpos, bool &walkZneg) {
    if(walkXneg){
        pos.x -= increment;
    }
    if(walkZneg){
        pos.z -= increment;
    }
    if(walkXpos){
        pos.x += increment;
    }
    if(walkZpos){
        pos.z += increment;
    }

    if(pos.x < -limit){
        pos.x = -limit;
        walkXpos = false;
        walkZpos = false;
        walkXneg = false;
        walkZneg = true;
    }
    else if(pos.z < -limit){
        pos.z = -limit;
        walkXpos = true;
        walkZpos = false;
        walkXneg = false;
        walkZneg = false;
    }

    else if(pos.z > limit){
        pos.z = limit;
        walkXpos = false;
        walkZpos = false;
        walkXneg = true;
        walkZneg = false;
    }
    else if(pos.x > limit){
        pos.x = limit;
        walkXpos = false;
        walkZpos = true;
        walkXneg = false;
        walkZneg = false;
    }
}
unsigned int loadTexture(char const * path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}
void createShape(Shader* shader, Model m, glm::vec3 pos, float scale, glm::vec3 angle, glm::mat4 projection, glm::mat4 view){
    shader->use();
    glm::mat4 model;

    model = glm::translate(model, pos);
    model = glm::scale(model, glm::vec3(scale));
    model = glm::rotate(model, glm::radians(angle.x), glm::vec3(0.0,1.0,0.0)); //rotate (R/L) around Y
    model = glm::rotate(model, glm::radians(angle.z), glm::vec3(0.0,0.0,1.0)); //rotate (Roll)around Z
    model = glm::rotate(model, glm::radians(angle.y), glm::vec3(1.0,0.0,0.0)); //rotate (U/D)around X

    int modelLoc = glGetUniformLocation(shader->ID, "model");
    int viewLoc = glGetUniformLocation(shader->ID, "view");
    int projectionLoc = glGetUniformLocation(shader->ID, "projection");

    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    m.Draw(*shader);
}
