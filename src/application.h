#pragma once

#include "protocol.h"
#define MAX_LIGHT_CNT 10

class Application {
private:

    bool multiLightShadingEnabled = false;
    bool usePbrShading = false;

    int curDiffuseIndex = 0;
    int curSpecularIndex = 0;

    Window m_window;

    GLuint lightUBO;

    Shader m_debugShader;
    Shader m_defaultShader;
    Shader m_multiLightShader;
    Shader m_pbrShader;
    Shader* m_selShader;

    Shader m_shadowShader;
    Shader m_lightShader;

    std::vector<GPUMesh> m_meshes;
    Texture m_texture;

    Material m_Material;
    PBRMaterial m_PbrMaterial;
    bool m_useMaterial{ true };

    int curMaterialIndex = 0;

    glm::mat4 m_projectionMatrix;
    glm::mat4 m_viewMatrix;
    glm::mat4 m_modelMatrix;

    std::vector<Camera> cameras;
    Camera* selectedCamera;

    std::vector<Light> lights{};
    Light* selectedLight;

    //Shadow
    shadowSetting shadowSettings;
    ShadowTexture m_shadowTex;

    const int SHADOWTEX_WIDTH = 1024;
    const int SHADOWTEX_HEIGHT = 1024;
    
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