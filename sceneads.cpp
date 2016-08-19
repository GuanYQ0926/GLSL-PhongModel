#include "sceneads.h"
#include "glutils.h"
#include "defines.h"

#include <cstdio>
#include <cstdlib>
using glm::vec3;

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>

SceneADS::SceneADS() : angle(0.0f)
{
}

void SceneADS::initScene()
{
    glewInit();
    compileAndLinkShader();
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);

    torus = new VBOTorus(0.7f, 0.3f, 50, 50);

    model = mat4(1.0f);
    model *= glm::rotate(-35.0f, vec3(1.0f, 0.0f, 0.0f));
    model *= glm::rotate(35.0f, vec3(0.0f, 1.0f, 0.0f));
    model = glm::translate(model, vec3(0.0f, 0.0f, 0.5f));
    view = glm::lookAt(vec3(0.0f, 0.0f, 2.0f), vec3(0.0f, 0.0f, 0.0f),
                       vec3(0.0f, 1.0f, 0.0f));
    projection = mat4(1.0f);
    vec4  worldLight = vec4(5.0f, 5.0f, 2.0f, 1.0f);

    prog.setUniform("Material.Kd", 0.9f, 0.5f, 0.3f);
    prog.setUniform("Light.Ld", 1.0f, 1.0f, 1.0f);
    prog.setUniform("Light.Position", view * worldLight);
    prog.setUniform("Material.Ka", 0.9f, 0.5f, 0.3f);
    prog.setUniform("Light.La", 0.4f, 0.4f, 0.4f);
    prog.setUniform("Material.Ks", 0.8f, 0.8f, 0.8f);
    prog.setUniform("Light.Ls", 1.0f, 1.0f, 1.0f);
    prog.setUniform("Material.Shininess", 100.0f);
}

void SceneADS::update(float t){}

void SceneADS::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    model = mat4(1.0f);
    model *= glm::rotate(angle, vec3(0.0f, 1.0f, 0.0f));
    model *= glm::rotate(-35.0f, vec3(1.0f, 0.0f, 0.0f));
    model *= glm::rotate(35.0f, vec3(0.0f, 1.0f, 0.0f));
    model = glm::translate(model, vec3(0.0f, 0.0f, 0.5f));

    setMatrices();
    torus->render();
}

void SceneADS::resize(int w, int h)
{
    glViewport(0, 0, w, h);
    width = w;
    height = h;
    float fov = TO_DEGREES(70.0f);
    projection = glm::perspective(fov, (float)w/h, 0.3f, 100.0f);
}

void SceneADS::setMatrices()
{
    mat4 mv = view * model;
    prog.setUniform("ModelViewMatrix", mv);
    prog.setUniform("NormalMatrix",
                    mat3(vec3(mv[0]), vec3(mv[1]), vec3(mv[2])));
    prog.setUniform("MVP", projection * mv);
}

void SceneADS::compileAndLinkShader()
{
    if(!prog.compileShaderFromFile("/home/guanyuqing/Documents/cppcode/phongmodel/shader/phong.vert",
                                   GLSLShader::VERTEX))
    {
        printf("Vertex shader failed to compile!\n%s",
               prog.log().c_str());
        exit(1);
    }

    if(!prog.compileShaderFromFile("/home/guanyuqing/Documents/cppcode/phongmodel/shader/phong.frag",
                                   GLSLShader::FRAGMENT))
    {
        printf("Fragment shader failed to compile!\n%s",
               prog.log().c_str());
        exit(1);
    }
    if(!prog.link())
    {
        printf("Shader program failed to link!\n%s",
               prog.log().c_str());
        exit(1);
    }
    if(!prog.validate())
    {
        printf("Program failed to validate!\n%s",
               prog.log().c_str());
        exit(1);
    }
    prog.use();
}
