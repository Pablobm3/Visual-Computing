#include "Scene.h"
#include <AssetManager.h>
#include <cmath>
#include <thread>

Scene::Scene(OpenGLWindow * window) :
        m_window(window)
{
    assert(window != nullptr);
}

Scene::~Scene()
{}

bool Scene::init()
{
    try
    {
        //Load shader
        m_assets.addShaderProgram("shader", AssetManager::createShaderProgram("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl"));
        m_shader = m_assets.getShaderProgram("shader");
        m_shader->use();

        float cubeVert[] =  {0.5, -0.5, -0.5, 1, 0, 0,
                             0.5, -0.5, 0.5, 0, 1, 0,
                             -0.5, -0.5, 0.5, 0, 0, 1,
                             -0.5, -0.5, -0.5, 1, 1, 0,
                             0.5, 0.5, -0.5, 1, 0, 1,
                             0.5, 0.5, 0.5, 0, 1, 1,
                             -0.5, 0.5, 0.5, 1, 1, 1,
                             -0.5, 0.5, -0.5, 0.5, 1, 0.5};

        int cubeInd[] = {1, 2, 3,
                         7, 6, 5,
                         4, 5, 1,
                         5, 6, 2,
                         2, 6, 7,
                         0, 3, 7,
                         0, 1, 3,
                         4, 7, 5,
                         0, 4, 1,
                         1, 5, 2,
                         3, 2, 7,
                         4, 0, 7};
        cubeIndSize = sizeof(cubeInd);

        // setup VAO //
        glGenVertexArrays(1, &vaoID);
        glBindVertexArray(vaoID);

        // setup VBO //
        glGenBuffers(1, &vboID);
        glBindBuffer(GL_ARRAY_BUFFER, vboID);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVert), &cubeVert, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, false, 24, 0);    // 2D position
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, false, 24, (void*)12); // 3D color
        glEnableVertexAttribArray(1);

        // setup IBO //
        GLuint iboID;
        glGenBuffers(1, &iboID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID); // only works with active VAO
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeInd), cubeInd, GL_STATIC_DRAW);

        // unbind everything (not really needed here, but good practice)
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        T1 = new Transform;
        T1->rotate(glm::vec3(0.0, 0.3, 0.0));

        // Cabeza
        T2 = new Transform;
        T2->scale(glm::vec3(0.25f, 0.25f, 0.15f));
        T2->translate(glm::vec3(0.0f, 0.5f, 0.0f));

        // Cuerpo
        T3 = new Transform;
        T3->scale(glm::vec3(0.4f, 0.4f, 0.2f));
        T3->translate(glm::vec3(0.0f, 0.0f, 0.0f));

        // Pierna derecha
        T4 = new Transform;
        T4->scale(glm::vec3(0.1f, 0.3f, 0.1f));
        T4->translate(glm::vec3(-0.15f, -0.3f, 0.0f));

        // Pierna izquierda
        T5 = new Transform;
        T5->scale(glm::vec3(0.1f, 0.3f, 0.1f));
        T5->translate(glm::vec3(0.15f, -0.3f, 0.0f));

        // Oreja derecha
        T6 = new Transform;
        T6->scale(glm::vec3(0.15f, 0.20f, 0.15f));
        T6->translate(glm::vec3(-0.2f, 0.65f, 0.0f));

        // Oreja izquierda
        T7 = new Transform;
        T7->scale(glm::vec3(0.15f, 0.20f, 0.15f));
        T7->translate(glm::vec3(0.2f, 0.65f, 0.0f));

        // Cola
        T8 = new Transform;
        T8->scale(glm::vec3(0.05f, 0.15f, 0.05f));
        T8->translate(glm::vec3(0.0f, -0.14f, 0.12f));

        // Cuello
        T9 = new Transform;
        T9->scale(glm::vec3(0.1f, 0.20f, 0.05f));
        T9->translate(glm::vec3(0.0f, 0.26f, 0.00f));

        //Nariz
        T10 = new Transform;
        T10->scale(glm::vec3(0.05f, 0.05f, 0.2f));
        T10->translate(glm::vec3(0.0f, 0.45f, -0.16f));

        // Brazo izquierda
        T11 = new Transform;
        T11->scale(glm::vec3(0.05f, 0.25f, 0.05f));
        T11->translate(glm::vec3(0.23f, 0.05f, 0.0f));

        // Brazo Derecho
        T12 = new Transform;
        T12->scale(glm::vec3(0.05f, 0.25f, 0.05f));
        T12->translate(glm::vec3(-0.23f, 0.05f, 0.0f));



        // Definir los parámetros para la función lookAt()
        glm::vec3 cameraPosition(0.0f, 0.0f, 7.0f);
        glm::vec3 cameraTarget(0.0f, 0.0f, 0.0f);
        glm::vec3 cameraUp(0.0f, 1.0f, 0.0f);

        // Calcular la matriz de vista utilizando glm::lookAt()
        viewMatrix = glm::lookAt(cameraPosition, cameraTarget, cameraUp);
        // Definir los parámetros para la función glm::perspective()
        float fov = 45.0f; // Ángulo de apertura en grados
        float aspectRatio = static_cast<float>(m_window->getWindowWidth()) / m_window->getFrameBufferHeight();
        float nearClip = 0.1f;
        float farClip = 100.0f;
        // Calcular la matriz de proyección utilizando glm::perspective()
        glm::mat4 projectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip);
        // Aplicar la matriz de proyección a la matriz de vista
        viewProjectionMatrix = projectionMatrix * viewMatrix;



        // OpenGL States
        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CCW);
        glCullFace(GL_BACK);

        // Set Background clear color
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        glClearDepth(1.0);

        std::cout << "Scene initialization done\n";
        return true;
    }
    catch (std::exception& ex)
    {
        throw std::logic_error("Scene initialization failed:\n" + std::string(ex.what()) + "\n");
    }
}

void Scene::render(float dt)
{




    // Pasar la matriz de vista a tu shader
    m_shader->setUniform("vista",viewProjectionMatrix,false);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // bind correct VAO
    glBindVertexArray(vaoID);

    

    //Body
    m_shader->setUniform("mm",
                         T1->getTransformMatrix() * T3->getTransformMatrix(),
                         false);
    glDrawElements(GL_TRIANGLES, cubeIndSize, GL_UNSIGNED_INT, 0);

    //Head
    m_shader->setUniform("mm",
                         T1->getTransformMatrix() * T2->getTransformMatrix(),
                         false);
    glDrawElements(GL_TRIANGLES, cubeIndSize, GL_UNSIGNED_INT, 0);

    //Right Leg
    m_shader->setUniform("mm",
                         T1->getTransformMatrix() * T4->getTransformMatrix(),
                         false);
    glDrawElements(GL_TRIANGLES, cubeIndSize, GL_UNSIGNED_INT, 0);

    //Left Leg
    m_shader->setUniform("mm",
                         T1->getTransformMatrix() * T5->getTransformMatrix(),
                         false);
    glDrawElements(GL_TRIANGLES, cubeIndSize, GL_UNSIGNED_INT, 0);


    //Upper Right Arm
    m_shader->setUniform("mm",
                         T1->getTransformMatrix() * T6->getTransformMatrix(),
                         false);
    glDrawElements(GL_TRIANGLES, cubeIndSize, GL_UNSIGNED_INT, 0);

    //Down Right Arm
    m_shader->setUniform("mm",
                         T1->getTransformMatrix() * T7->getTransformMatrix(),
                         false);
    glDrawElements(GL_TRIANGLES, cubeIndSize, GL_UNSIGNED_INT, 0);

    //Upper Left Arm
    m_shader->setUniform("mm",
                         T1->getTransformMatrix() * T8->getTransformMatrix(),
                         false);
    glDrawElements(GL_TRIANGLES, cubeIndSize, GL_UNSIGNED_INT, 0);

    //Cuello
    m_shader->setUniform("mm",
                         T1->getTransformMatrix() * T9->getTransformMatrix(),
                         false);
    glDrawElements(GL_TRIANGLES, cubeIndSize, GL_UNSIGNED_INT, 0);

    //Nariz
    m_shader->setUniform("mm",
                         T1->getTransformMatrix() * T10->getTransformMatrix(),
                         false);
    glDrawElements(GL_TRIANGLES, cubeIndSize, GL_UNSIGNED_INT, 0);

    //Brazo Izquierdo
    m_shader->setUniform("mm",
                         T1->getTransformMatrix() * T11->getTransformMatrix(),
                         false);
    glDrawElements(GL_TRIANGLES, cubeIndSize, GL_UNSIGNED_INT, 0);

    //Brazo Derecho
    m_shader->setUniform("mm",
                         T1->getTransformMatrix() * T12->getTransformMatrix(),
                         false);
    glDrawElements(GL_TRIANGLES, cubeIndSize, GL_UNSIGNED_INT, 0);



    //Generar el color
    float animationTime;

    /*for (int (i) = 0; (i) < 1.0; ++(i)) {
        animationTime+=0.1;
        glm::vec3 color = glm::vec3(sin(animationTime), 0.5, cos(animationTime)); // Ejemplo de cambio de color utilizando seno y coseno
        m_shader->setUniform("colorAdjustment", color);

    }*/




    glDrawElements(GL_TRIANGLES, cubeIndSize, GL_UNSIGNED_INT, 0);

    // unbind VAO
    glBindVertexArray(0);

}

void Scene::update(float dt) {

    if (m_window->getInput().getKeyState(Key::W) == KeyState::Pressed) {

        T1->translate(glm::vec3(0.0f, 0.01f, 0.0f));
    }

    if (m_window->getInput().getKeyState(Key::S) == KeyState::Pressed) {

        T1->translate(glm::vec3(0.0f, -0.01f, 0.0f));
    }

    if (m_window->getInput().getKeyState(Key::D) == KeyState::Pressed) {

        T1->translate(glm::vec3(0.01f, 0.00f, 0.0f));
    }

    if (m_window->getInput().getKeyState(Key::A) == KeyState::Pressed) {

        T1->translate(glm::vec3(-0.01f, 0.00f, 0.0f));
    }




}


OpenGLWindow * Scene::getWindow()
{
    return m_window;
}

void Scene::onKey(Key key, Action action, Modifier modifier)
{

}

void Scene::onMouseMove(MousePosition mouseposition)
{



    // Obtén la nueva y antigua posición del ratón
    auto newPosition = glm::vec2(mouseposition.X, mouseposition.Y);
    auto oldPosition = glm::vec2(mouseposition.oldX, mouseposition.oldY);

    // Calcula la dirección de movimiento del ratón
    auto direction = newPosition - oldPosition;

    T1->rotate(glm::vec3(direction.x,direction.y, 0.0));
}

void Scene::onMouseButton(MouseButton button, Action action, Modifier modifier)
{

}

void Scene::onMouseScroll(double xscroll, double yscroll)
{

}

void Scene::onFrameBufferResize(int width, int height)
{

}
void Scene::shutdown()
{

}