#pragma once

#include "protocol.h"
#include <framework/trackball.h>

#include "camera.h"
#include "Textures/cubeMapTexture.h"
#include "Textures/hdrTexture.h"
#include "Textures/ssaoBufferTexture.h"

#define MAX_LIGHT_CNT 10

class Application {
private:

    bool multiLightShadingEnabled = false;
    bool usePbrShading = false;

    int curDiffuseIndex = 0;
    int curSpecularIndex = 0;

    Window m_window;
    Trackball trackball;

    GLuint lightUBO = 0;

    Shader m_debugShader;
    Shader m_defaultShader;
    Shader m_multiLightShader;
    Shader m_pbrShader;
    Shader* m_selShader;

    Shader m_shadowShader;
    Shader m_lightShader;

    // Definition for SkyBox 
    bool envMapEnabled = false;
    
    #pragma region Skybox def
    // faces should follow this format
    std::vector<std::filesystem::path> faces = {
        std::filesystem::path(RESOURCE_ROOT SKYBOX_PATH "right.jpg"),
        std::filesystem::path(RESOURCE_ROOT SKYBOX_PATH "left.jpg"),
        std::filesystem::path(RESOURCE_ROOT SKYBOX_PATH "top.jpg"),
        std::filesystem::path(RESOURCE_ROOT SKYBOX_PATH "bottom.jpg"),
        std::filesystem::path(RESOURCE_ROOT SKYBOX_PATH "front.jpg"),
        std::filesystem::path(RESOURCE_ROOT SKYBOX_PATH "back.jpg")
    };

    cubeMapTex skyboxTexture;
    GLuint skyboxVAO,skyboxVBO;

    Shader m_skyBoxShader;

    void generateSkyBox();

    #pragma endregion

    #pragma region HDR_map_def
    // Definition HDR cubemap settings
    bool hdrMapEnabled = false;

    GLuint captureFBO, captureRBO; // framebuffers

    std::filesystem::path hdrSamplePath{ RESOURCE_ROOT HDR_PATH "warm_restaurant_night_4k.hdr" };
    hdrTexture hdrTextureMap;

    cubeMapTex hdrCubeMap;

    Shader m_hdrToCubeShader;
    Shader m_hdrSkyBoxShader;

    cubeMapTex hdrIrradianceMap;
    Shader m_hdrToIrradianceShader;

    cubeMapTex hdrPrefilteredMap;
    Shader m_hdrPrefilterShader;

    Texture BRDFTexture;
    Shader m_brdfShader;

    void generateHdrMap();
    #pragma endregion

    // extra vao to use
    GLuint cubeVAO = 0, cubeVBO = 0;
    GLuint quadVAO = 0, quadVBO = 0;

    /// SSAO Defintions ///

    Texture m_diffuseTex,m_specularTex;

    bool ssaoEnabled = true;
    bool defRenderBufferGenerated = true;
    // SSAO Processing Shader
    Shader m_shaderGeometryPass;
    Shader m_shaderLightingPass;

    Shader m_deferredLightShader;
    Shader m_deferredDebugShader;

    GLuint gBuffer = 0;
    ssaoBufferTex gPos, gNor, gCol;

    GLuint renderDepth;
    
    // unused
    GLuint ssaoFBO = 0, ssaoBlurFBO = 0;
    ssaoBufferTex ssaoColorBuff, ssaoColorBlurBuff;
    ssaoBufferTex ssaoNoiseTex;

    Shader m_shaderSSAO;
    Shader m_shaderSSAOBlur;

    void genSSAOFrameBuffer();

    // Definition for model Obejcts includeing texture and Material
    std::vector<GPUMesh> m_meshes;
    Texture m_texture;

    char file_path_buffer[256];
    std::string texturePath;

    std::vector<Texture> m_pbrTextures;

    bool textureEnabled = false;

    Material m_Material;
    PBRMaterial m_PbrMaterial;
    bool m_useMaterial = true;
    bool m_materialChangedByUser = false;

    int curMaterialIndex = 0;

    // mvp matrices

    glm::mat4 m_projectionMatrix;
    glm::mat4 m_viewMatrix;
    glm::mat4 m_modelMatrix;


    // Definition for Cameras
    std::vector<Camera> cameras;
    Camera* selectedCamera;

    // Definition for Lights
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