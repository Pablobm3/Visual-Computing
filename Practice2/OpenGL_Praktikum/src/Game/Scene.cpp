#include "Scene.h"
#include <AssetManager.h>
#include <cmath>

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

        //Head
        T2 = new Transform;
        T2->scale(glm::vec3(0.1f, 0.2f, 0.1f));
        T2->translate(glm::vec3(0.0f, 0.57f, 0));

        //Body
        T3 = new Transform;
        T3->scale(glm::vec3(0.25f, 0.5f, 0.1f));
        T3->translate(glm::vec3(0.0f, 0.2f, 0));

        //Right Leg
        T4 = new Transform;
        T4->scale(glm::vec3(0.08f, 0.6f, 0.1f));
        T4->translate(glm::vec3(-0.085f, -0.37f, 0));


        //Left Leg
        T5 = new Transform;
        T5->scale(glm::vec3(0.08f, 0.6f, 0.1f));
        T5->translate(glm::vec3(0.085f, -0.37f, 0));

        //Upper Left arm
        T6 = new Transform;
        T6->scale(glm::vec3(0.03f, 0.25f, 0.1f));
        T6->translate(glm::vec3(0.18f, 0.325f, 0));

        //Down Left arm
        T7 = new Transform;
        T7->scale(glm::vec3(0.03f, 0.25f, 0.1f));
        T7->translate(glm::vec3(0.18f, 0.07f, 0));

        //Upper Right arm
        T8 = new Transform;
        T8->scale(glm::vec3(0.03f, 0.25f, 0.1f));
        T8->translate(glm::vec3(-0.18f, 0.325f, 0));

        //Down Right arm
        T9 = new Transform;
        T9->scale(glm::vec3(0.03f, 0.25f, 0.1f));
        T9->translate(glm::vec3(-0.18f, 0.07f, 0));

        // OpenGL States
        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CCW);
        glCullFace(GL_BACK);

        // Set Background clear color
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_GREATER);
        glClearDepth(0.0);

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

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // bind correct VAO
    glBindVertexArray(vaoID);

    T1->rotate(glm::vec3(0, 0.2 * dt, 0));

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

    //Down Left Arm
    m_shader->setUniform("mm",
                         T1->getTransformMatrix() * T9->getTransformMatrix(),
                         false);



    //Generar el color
    float animationTime;

    for (int (i) = 0; (i) < 1.0; ++(i)) {
        animationTime+=0.1;
        glm::vec3 color = glm::vec3(sin(animationTime), 0.5, cos(animationTime)); // Ejemplo de cambio de color utilizando seno y coseno
        m_shader->setUniform("colorAdjustment", color);

    }



    glDrawElements(GL_TRIANGLES, cubeIndSize, GL_UNSIGNED_INT, 0);

    // unbind VAO
    glBindVertexArray(0);

}

void Scene::update(float dt) {
    cont++;

    if (cont == 30) {
        if (changeMove) {
            changeMove = false;
        } else {
            changeMove = true;
        }
        cont = 0;
    }

    if (first_move == true) {
        angle_leg = 0.02f;
    }
    if (changeMove == false) {
        //legs
        T5->rotateAroundPoint(glm::vec3(-0.0425f, 0, 0.05f), glm::vec3(angle_leg, 0.0f, 0.0f));
        T4->rotateAroundPoint(glm::vec3(0.0425f, 0, 0.05f), glm::vec3(-angle_leg, 0.0f, 0.0f));
        //Left Arm
        T6->rotateAroundPoint(glm::vec3(0.09f, 0.325f, 0), glm::vec3(-angle_leg, 0.0f, 0.0f));
        T7->rotateAroundPoint(glm::vec3(0.09f, 0.325f, 0), glm::vec3(-angle_leg, 0.0f, 0.0f));
        //Right Arm
        T8->rotateAroundPoint(glm::vec3(-0.09f, 0.325f, 0), glm::vec3(angle_leg, 0.0f, 0.0f));
        T9->rotateAroundPoint(glm::vec3(-0.09f, 0.325f, 0), glm::vec3(angle_leg, 0.0f, 0.0f));


    } else {
        if (first_move) {
            first_move = false;
            angle_leg = 0.04f;
        }
        //Legs
        T5->rotateAroundPoint(glm::vec3(-0.0425f, 0, 0.05f), glm::vec3(-angle_leg, 0.0f, 0.0f));
        T4->rotateAroundPoint(glm::vec3(0.0425f, 0, 0.05f), glm::vec3(angle_leg, 0.0f, 0.0f));
        //Left Arm
        T6->rotateAroundPoint(glm::vec3(0.09f, 0.325f, 0), glm::vec3(angle_leg, 0.0f, 0.0f));
        T7->rotateAroundPoint(glm::vec3(0.09f, 0.325f, 0), glm::vec3(angle_leg, 0.0f, 0.0f));
        //Right Arm
        T8->rotateAroundPoint(glm::vec3(-0.09f, 0.325f, 0), glm::vec3(-angle_leg, 0.0f, 0.0f));
        T9->rotateAroundPoint(glm::vec3(-0.09f, 0.325f, 0), glm::vec3(-angle_leg, 0.0f, 0.0f));
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
