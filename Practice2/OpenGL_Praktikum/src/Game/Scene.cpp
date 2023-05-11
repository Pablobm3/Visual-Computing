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
        T1->rotate(glm::vec3(0.3, 0.3, 0.0));

        //Head
        T2 = new Transform;
        T2->scale(glm::vec3(0.2f, 0.2f, 0.2f));
        T2->translate(glm::vec3(0.0f, 0.4f, 0));

        //Body
        T3 = new Transform;
        T3->scale(glm::vec3(0.3f, 0.5f, 0.3f));
        T3->translate(glm::vec3(0.0f, 0.0f, 0));

        // OpenGL States
        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CCW);
        glCullFace(GL_BACK);

        // Set Background clear color
        glClearColor(0.3f, 0.0f, 0.0f, 1.0f);


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



    //Body
    m_shader->setUniform("mm",
                         T1->getTransformMatrix() * T3->getTransformMatrix(),
                         false);


    glm::vec3 colorAdjustment = glm::vec3(1.0f, 1.0f, 1.0f);
    m_shader->setUniform("colorAdjustment", colorAdjustment);

    // Render die Sonne-Geometrie
    glDrawElements(GL_TRIANGLES, cubeIndSize, GL_UNSIGNED_INT, 0);

    //Head
    m_shader->setUniform("mm",
                         T1->getTransformMatrix() * T2->getTransformMatrix(),
                         false);
     colorAdjustment = glm::vec3(0.5f, 0.5f, 0.0f);
    m_shader->setUniform("colorAdjustment", colorAdjustment);

    glDrawElements(GL_TRIANGLES, cubeIndSize, GL_UNSIGNED_INT, 0);

    // unbind VAO
    glBindVertexArray(0);

}

void Scene::update(float dt)
{

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
