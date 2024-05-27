/*
*  Este fichero se ha obtenido con la ayuda de ChatGPT
*  y pertenece a la libreria STB de Sean Barrett.
* 
*  Se ha modificado para que acepte otro atributo que es 
*  la posicion en la que se renderiza el archivo STL
*  que es cosecha propia.
* 
*  Se deja una copia de la licencia a continuacion: 

This software is available under 2 licenses -- choose whichever you prefer.
------------------------------------------------------------------------------
ALTERNATIVE A - MIT License
Copyright (c) 2017 Sean Barrett
Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
------------------------------------------------------------------------------
ALTERNATIVE B - Public Domain (www.unlicense.org)
This is free and unencumbered software released into the public domain.
Anyone is free to copy, modify, publish, use, compile, sell, or distribute this
software, either in source code form or as a compiled binary, for any purpose,
commercial or non-commercial, and by any means.
In jurisdictions that recognize copyright laws, the author or authors of this
software dedicate any and all copyright interest in the software to the public
domain. We make this dedication for the benefit of the public at large and to
the detriment of our heirs and successors. We intend this dedication to be an
overt act of relinquishment in perpetuity of all present and future rights to
this software under copyright law.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#pragma once

#ifndef STB_STL_LOADER_H
#define STB_STL_LOADER_H

#include <vector>
#include <fstream>
#include <iostream>

#include "VectoresUtiles.h"

bool loadSTL(const char* filename, std::vector<Vector3Dfloat>& vertices, std::vector<Vector3Dfloat>& normals) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return false;
    }

    char header[80];
    file.read(header, 80);

    uint32_t numTriangles;
    file.read(reinterpret_cast<char*>(&numTriangles), sizeof(uint32_t));

    vertices.reserve(numTriangles * 3);
    normals.reserve(numTriangles * 3);

    for (uint32_t i = 0; i < numTriangles; ++i) {
        Vector3Dfloat normal, v1, v2, v3;
        file.read(reinterpret_cast<char*>(&normal), sizeof(Vector3Dfloat));
        file.read(reinterpret_cast<char*>(&v1), sizeof(Vector3Dfloat));
        file.read(reinterpret_cast<char*>(&v2), sizeof(Vector3Dfloat));
        file.read(reinterpret_cast<char*>(&v3), sizeof(Vector3Dfloat));

        v1.x = v1.x - 75;
        v1.y = v1.y - 43.3013;
        v2.x = v2.x - 75;
        v2.y = v2.y - 43.3013;
        v3.x = v3.x - 75;
        v3.y = v3.y - 43.3013;

        vertices.push_back(v1);
        vertices.push_back(v2);
        vertices.push_back(v3);
        normals.push_back(normal);
        normals.push_back(normal);
        normals.push_back(normal);

        uint16_t attributeByteCount;
        file.read(reinterpret_cast<char*>(&attributeByteCount), sizeof(uint16_t));
    }

    file.close();
    return true;
}

#endif // STB_STL_LOADER_H
