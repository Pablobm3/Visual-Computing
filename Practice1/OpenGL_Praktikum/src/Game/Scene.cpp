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
        /*Ejercicio 2
        float vertices[] = {-0.5, -0.5, 0.0, 0.0, 1.0,
                            0.5, -0.5, 0.0, 0.0, 1.0,
                            0.5, 0.5, 0.0, 1.0, 0.0,
                            0.0, 1.0, 1.0, 0.0, 0.0,
                            -0.5, 0.5, 0.0, 1.0, 0.0};

        int indices[] = {0, 1, 2,
                         0, 2, 4,
                         4, 2, 3};
                         */
        //Ejercicio 3
        /*
        float vertices[] = {
                -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,   // Posición y color del primer vértice
                -0.4f, 0.5f, 0.0f, 0.0f, 1.0f,   // Posición y color del segundo vértice
                -0.4f, -0.5f, 0.0f, 0.0f, 1.0f,  // Posición y color del tercer vértice
                -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,  // Posición y color del cuarto vértice

                // Rectángulo 2 (Parte superior)
                -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,  // Posición y color del primer vértice
                0.0f, 0.5f, 0.0f, 0.0f, 1.0f,  // Posición y color del segundo vértice
                0.0f, 0.4f, 0.0f, 0.0f, 1.0f,  // Posición y color del tercer vértice
                -0.5f, 0.4f, 0.0f, 0.0f, 1.0f,  // Posición y color del cuarto vértice

                // Rectángulo 3 (Parte central)
                -0.05f, 0.4f, 0.0f, 0.0f, 1.0f,  // Posición y color del primer vértice
                0.0f, 0.0f, 0.0f, 0.0f, 1.0f,   // Posición y color del segundo vértice
                -0.05f, 0.0f, 0.0f, 0.0f, 1.0f,   // Posición y color del tercer vértice
                0.0f, 0.4f, 0.0f, 0.0f, 1.0f,  // Posición y color del cuarto vértice

                // Rectángulo 4 (Parte inferior)
                0.0f, 0.0f, 0.0f, 0.0f, 1.0f, // Posición y color del primer vértice
                -0.4f, 0.0f, 0.0f, 0.0f, 1.0f, // Posición y color del segundo vértice
                -0.4f, -0.1f, 0.0f, 0.0f, 1.0f, // Posición y color del tercer vértice

        };

        unsigned int indices[] = {
                0, 1, 2,   // primer rectángulo
                0, 2, 3,
                4, 5, 6,   // segundo rectángulo
                4, 6, 7,
                8, 11, 10,  // tercer rectángulo
                9, 10, 11,
                12, 13, 14 //cuarto
        };*/
        //Ejercicio 4
        float vertices[] = {
                -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,   // Posición y color del primer vértice
                -0.4f, 0.5f, 0.0f, 0.0f, 1.0f,   // Posición y color del segundo vértice
                -0.4f, -0.5f, 0.0f, 0.0f, 1.0f,  // Posición y color del tercer vértice
                -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,  // Posición y color del cuarto vértice

                // Rectángulo 2 (Parte superior)
                -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,  // Posición y color del primer vértice
                0.0f, 0.5f, 0.0f, 0.0f, 1.0f,  // Posición y color del segundo vértice
                0.0f, 0.4f, 0.0f, 0.0f, 1.0f,  // Posición y color del tercer vértice
                -0.5f, 0.4f, 0.0f, 0.0f, 1.0f,  // Posición y color del cuarto vértice

                // Rectángulo 3 (Parte central)
                -0.05f, 0.4f, 0.0f, 0.0f, 1.0f,  // Posición y color del primer vértice
                0.0f, 0.0f, 0.0f, 0.0f, 1.0f,   // Posición y color del segundo vértice
                -0.05f, 0.0f, 0.0f, 0.0f, 1.0f,   // Posición y color del tercer vértice
                0.0f, 0.4f, 0.0f, 0.0f, 1.0f,  // Posición y color del cuarto vértice

                // Rectángulo 4 (Parte inferior)
                0.0f, 0.0f, 0.0f, 0.0f, 1.0f, // Posición y color del primer vértice
                -0.4f, 0.0f, 0.0f, 0.0f, 1.0f, // Posición y color del segundo vértice
                -0.4f, -0.1f, 0.0f, 0.0f, 1.0f, // Posición y color del tercer vértice

        };

        unsigned int indices[] = {
                0, 2, 1,   // primer rectángulo
                3, 2, 0,
                6, 5, 4,   // segundo rectángulo
                6, 4, 7,
                11, 8, 10,  // tercer rectángulo
                9, 11, 10,
                12, 13, 14 //cuarto
        };



        //Configurar VBO
        glGenBuffers(1,&vboID);
        glBindBuffer(GL_ARRAY_BUFFER, vboID);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

        //Configurar VAO
        glGenVertexArrays(1, &vaoID);
        glBindVertexArray(vaoID);

        // describir VBO en VAO //
        glVertexAttribPointer(0, 3, GL_FLOAT, false, 5* sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, false, 5* sizeof(float), (void*)(3* sizeof(float)));
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
    glDrawElements(GL_TRIANGLES, 21, GL_UNSIGNED_INT, 0);
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
