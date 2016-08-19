#include "gllib.h"
#include <GL/freeglut.h>

#include <stdio.h>
#include "scene.h"
#include "glutils.h"
#include "sceneads.h"

Scene* scene;

void initializeGL()
{
    scene = new SceneADS();

    GLUtils::dumpGLInfo();

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

    glewExperimental = GL_TRUE;
    scene->initScene();
}

void paintGL()
{
    GLUtils::checkForOpenGLError(__FILE__, __LINE__);
    scene->render();
    glutSwapBuffers();
}

void resizeGL(int w, int h)
{
    scene->resize(w, h);
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH |
                        GLUT_STENCIL);
    glutInitContextVersion(3, 3);
    glutInitContextProfile(GLUT_CORE_PROFILE);

    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("phong model");


    initializeGL();
    printf("guanyq!.\n");

    glutDisplayFunc(paintGL);

    glutReshapeFunc(resizeGL);

    glutMainLoop();
    return 0;
}
