#include "Scene.h"
#include <AssetManager.h>

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
        static const float vertices[] =  {0.5, -0.5, -0.5, 1, 0, 0,
                                  0.5, -0.5, 0.5, 0, 1, 0,
                                  -0.5, -0.5, 0.5, 0, 0, 1,
                                  -0.5, -0.5, -0.5, 1, 1, 0,
                                  0.5, 0.5, -0.5, 1, 0, 1,
                                  0.5, 0.5, 0.5, 0, 1, 1,
                                  -0.5, 0.5, 0.5, 1, 1, 1,
                                  -0.5, 0.5, -0.5, 0.5, 1, 0.5};

        static const int indices[] = {1, 2, 3,
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



        //Configurar VBO
        glGenBuffers(1,&vboID);
        glBindBuffer(GL_ARRAY_BUFFER, vboID);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

        //Configurar VAO
        glGenVertexArrays(1, &vaoID);
        glBindVertexArray(vaoID);

        // describir VBO en VAO //
        glVertexAttribPointer(0, 3, GL_FLOAT, false, 6* sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, false, 6* sizeof(float), (void*)(3* sizeof(float)));
        glEnableVertexAttribArray(1);


        //Crear y vincular IBO
        GLuint iboID;
        glGenBuffers(1, &iboID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        std::cout << "Scene initialization done\n";
        //Ejercicio 4
        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CCW);
        glCullFace(GL_BACK);

        return true;
	}
	catch (std::exception& ex)
	{
	    throw std::logic_error("Scene initialization failed:\n" + std::string(ex.what()) + "\n");
	}
}

void Scene::render(float dt)
{
    m_shader->use();
    glBindVertexArray(vaoID);
    //Es un nueve en el ejercicio 1
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
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
