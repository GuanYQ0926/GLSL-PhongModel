#ifndef SCENE_H
#define SCENE_H

class Scene
{
public:
    virtual void initScene() = 0;
    virtual void update(float t) = 0;
    virtual void render() = 0;
    virtual void resize(int,int) = 0;
};

#endif // SCENE_H

