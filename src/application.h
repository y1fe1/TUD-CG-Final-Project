#pragma once

#include "protocol.h"
#include "camera.h"
#include "protocol.h"

class Application {
private:

    int curDiffuseIndex = 0;
    int curSpecularIndex = 0;

    Window m_window;

    GLuint lightUBO;

    Shader m_defaultShader;
    Shader m_shadowShader;
    Shader m_lightShader;

    std::vector<GPUMesh> m_meshes;
    Material m_Material;
    Texture m_texture;
    bool m_useMaterial{ true };

    glm::mat4 m_projectionMatrix;
    glm::mat4 m_viewMatrix;
    glm::mat4 m_modelMatrix;

    std::vector<Camera> cameras;
    Camera* selectedCamera;

    std::vector<Light> lights;
    Light* selectedLight;

    //Shadow
    shadowSetting shadowSettings;
    GLuint texShadow;
    const int SHADOWTEX_WIDTH = 1024;
    const int SHADOWTEX_HEIGHT = 1024;
    GLuint framebuffer;
    
    void imgui();

public:
    Application();
    void update();
    void onKeyPressed(int key, int mods);
    void onKeyReleased(int key, int mods);
    void onMouseMove(const glm::dvec2& cursorPos);
    void onMouseClicked(int button, int mods);
    void onMouseReleased(int button, int mods);
};