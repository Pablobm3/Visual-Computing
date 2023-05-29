#pragma once

#include "OpenGLWindow.h"
#include <ShaderProgram.h>
#include <memory>
#include <AssetManager.h>
#include "../SceneElements/Transform.h"

class Scene
{
public:
    Scene(OpenGLWindow* window);
    ~Scene();

    bool init();
    void shutdown();
    void render(float dt);
    void update(float dt);
    OpenGLWindow* getWindow();

    void onKey(Key key, Action action, Modifier modifier);
    void onMouseMove(MousePosition mouseposition);
    void onMouseButton(MouseButton button, Action action, Modifier modifier);
    void onMouseScroll(double xscroll, double yscroll);
    void onFrameBufferResize(int width, int height);

private:
    OpenGLWindow* m_window;
    AssetManager m_assets;
    ShaderProgram* m_shader;
    GLuint vaoID, vboID;
    int cubeIndSize;

    Transform* T1, *T2, *T3, *T4,*T5,*T6,*T7,*T8,*T9,*T10,*T11,*T12,*T13,*T14,*T15;
    float angle_leg = 0;
    int cont = 0;
    bool changeMove = false;
    bool first_move = true;
    glm::mat4 viewMatrix;
    glm::mat4 viewProjectionMatrix;





};
