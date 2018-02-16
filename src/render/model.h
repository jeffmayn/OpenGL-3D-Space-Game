//
// Created by chris on 12.12.2017.
//

#ifndef LEARN_OPENGL_MODEL_H
#define LEARN_OPENGL_MODEL_H

#include "../../include/assimp/scene.h"
#include "../../include/assimp/mesh.h"
#include "../../include/assimp/material.h"
#include "../../include/assimp/Importer.hpp"
#include "../../include/assimp/postprocess.h"
#include "../../include/stb/stb_image.h"

#include "../shader/shader.h"
#include "mesh.h"

class Model {
public:
    vector<Texture> textures_loaded;
    vector<Mesh> meshes;
    string directory;
    bool gammaCorrection;
    const aiScene* scene;

    Model(const char* path, bool gamma = false) : gammaCorrection(gamma){
        loadModel(path);
    }
    void Draw(Shader shader);

private:

    void loadModel(string const &path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);

    vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);

    unsigned int TextureFromFile(const char *path, const string &directory, bool gamma = false);

};


#endif //LEARN_OPENGL_MODEL_H
