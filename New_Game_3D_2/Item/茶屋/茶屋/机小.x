xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 72;
 -0.31664;0.24211;0.48040;,
 -0.31664;0.20436;0.48040;,
 0.31664;0.20436;0.48040;,
 0.31664;0.24211;0.48040;,
 -0.31664;0.20436;-0.47972;,
 -0.31664;0.24211;-0.48040;,
 0.31664;0.24211;-0.48040;,
 0.31664;0.20436;-0.47972;,
 -0.29576;-0.00112;-0.44291;,
 -0.21238;-0.00112;-0.44291;,
 -0.21238;-0.00112;-0.39019;,
 -0.29576;-0.00112;-0.39019;,
 -0.29576;0.20677;-0.44291;,
 -0.29576;0.20677;-0.39019;,
 -0.21238;0.20677;-0.44291;,
 -0.21238;-0.00112;-0.44291;,
 -0.21238;-0.00112;-0.39019;,
 -0.21238;0.20677;-0.39019;,
 -0.21238;0.20677;-0.44291;,
 -0.21238;0.20677;-0.39019;,
 -0.21238;-0.00112;-0.39019;,
 -0.21238;-0.00112;-0.44291;,
 0.29312;-0.00112;-0.44291;,
 0.29312;-0.00112;-0.39019;,
 0.20974;-0.00112;-0.39019;,
 0.20974;-0.00112;-0.44291;,
 0.29312;0.20677;-0.44291;,
 0.29312;0.20677;-0.39019;,
 0.20974;-0.00112;-0.44291;,
 0.20974;0.20677;-0.44291;,
 0.20974;0.20677;-0.39019;,
 0.20974;-0.00112;-0.39019;,
 0.20974;0.20677;-0.44291;,
 0.20974;-0.00112;-0.44291;,
 0.20974;-0.00112;-0.39019;,
 0.20974;0.20677;-0.39019;,
 -0.31664;0.20436;-0.47972;,
 -0.31664;0.20436;0.48040;,
 0.31664;0.20436;-0.47972;,
 0.31664;0.20436;0.48040;,
 -0.31664;0.20436;-0.47972;,
 0.31664;0.20436;-0.47972;,
 0.31664;0.20436;0.48040;,
 -0.31664;0.20436;0.48040;,
 -0.29576;-0.00112;0.36854;,
 -0.21238;-0.00112;0.36854;,
 -0.21238;-0.00112;0.42126;,
 -0.29576;-0.00112;0.42126;,
 -0.29576;0.20677;0.36854;,
 -0.29576;0.20677;0.42126;,
 -0.21238;0.20677;0.36854;,
 -0.21238;-0.00112;0.36854;,
 -0.21238;-0.00112;0.42126;,
 -0.21238;0.20677;0.42126;,
 -0.21238;0.20677;0.36854;,
 -0.21238;0.20677;0.42126;,
 -0.21238;-0.00112;0.42126;,
 -0.21238;-0.00112;0.36854;,
 0.29312;-0.00112;0.36854;,
 0.29312;-0.00112;0.42126;,
 0.20974;-0.00112;0.42126;,
 0.20974;-0.00112;0.36854;,
 0.29312;0.20677;0.36854;,
 0.29312;0.20677;0.42126;,
 0.20974;-0.00112;0.36854;,
 0.20974;0.20677;0.36854;,
 0.20974;0.20677;0.42126;,
 0.20974;-0.00112;0.42126;,
 0.20974;0.20677;0.36854;,
 0.20974;-0.00112;0.36854;,
 0.20974;-0.00112;0.42126;,
 0.20974;0.20677;0.42126;;
 
 26;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,8,11,13;,
 4;12,14,15,8;,
 4;13,11,16,17;,
 4;18,19,20,21;,
 4;22,23,24,25;,
 4;26,27,23,22;,
 4;26,22,28,29;,
 4;27,30,31,23;,
 4;32,33,34,35;,
 4;6,5,0,3;,
 4;5,36,37,0;,
 4;38,6,3,39;,
 4;40,41,42,43;,
 4;44,45,46,47;,
 4;48,44,47,49;,
 4;48,50,51,44;,
 4;49,47,52,53;,
 4;54,55,56,57;,
 4;58,59,60,61;,
 4;62,63,59,58;,
 4;62,58,64,65;,
 4;63,66,67,59;,
 4;68,69,70,71;;
 
 MeshMaterialList {
  22;
  26;
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11;;
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   5.000000;
   0.070000;0.070000;0.070000;;
   0.630000;0.630000;0.630000;;
   TextureFilename {
    "uv®.png";
   }
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   5.000000;
   0.070000;0.070000;0.070000;;
   0.630000;0.630000;0.630000;;
   TextureFilename {
    "uv®.png";
   }
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   5.000000;
   0.070000;0.070000;0.070000;;
   0.630000;0.630000;0.630000;;
   TextureFilename {
    "uv®.png";
   }
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   5.000000;
   0.070000;0.070000;0.070000;;
   0.630000;0.630000;0.630000;;
   TextureFilename {
    "uv®.png";
   }
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   5.000000;
   0.070000;0.070000;0.070000;;
   0.630000;0.630000;0.630000;;
   TextureFilename {
    "uv®.png";
   }
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   5.000000;
   0.070000;0.070000;0.070000;;
   0.630000;0.630000;0.630000;;
   TextureFilename {
    "uv®.png";
   }
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   5.000000;
   0.070000;0.070000;0.070000;;
   0.630000;0.630000;0.630000;;
   TextureFilename {
    "uv®.png";
   }
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   5.000000;
   0.070000;0.070000;0.070000;;
   0.630000;0.630000;0.630000;;
   TextureFilename {
    "uv®.png";
   }
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   5.000000;
   0.070000;0.070000;0.070000;;
   0.630000;0.630000;0.630000;;
   TextureFilename {
    "uv®.png";
   }
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   5.000000;
   0.070000;0.070000;0.070000;;
   0.630000;0.630000;0.630000;;
   TextureFilename {
    "uv®.png";
   }
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   5.000000;
   0.070000;0.070000;0.070000;;
   0.630000;0.630000;0.630000;;
   TextureFilename {
    "uv®¬¨.png";
   }
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   5.000000;
   0.070000;0.070000;0.070000;;
   0.630000;0.630000;0.630000;;
   TextureFilename {
    "uv®¬¨.png";
   }
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   5.000000;
   0.070000;0.070000;0.070000;;
   0.630000;0.630000;0.630000;;
   TextureFilename {
    "uv®¬¨.png";
   }
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   5.000000;
   0.070000;0.070000;0.070000;;
   0.630000;0.630000;0.630000;;
   TextureFilename {
    "uv®¬¨.png";
   }
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   5.000000;
   0.070000;0.070000;0.070000;;
   0.630000;0.630000;0.630000;;
   TextureFilename {
    "uv®¬¨.png";
   }
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   5.000000;
   0.070000;0.070000;0.070000;;
   0.630000;0.630000;0.630000;;
   TextureFilename {
    "uv®¬¨.png";
   }
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   5.000000;
   0.060000;0.060000;0.060000;;
   0.610000;0.610000;0.610000;;
   TextureFilename {
    "uvì_P.png";
   }
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   5.000000;
   0.060000;0.060000;0.060000;;
   0.610000;0.610000;0.610000;;
   TextureFilename {
    "uvì_P.png";
   }
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   5.000000;
   0.060000;0.060000;0.060000;;
   0.610000;0.610000;0.610000;;
   TextureFilename {
    "uvä.png";
   }
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   5.000000;
   0.060000;0.060000;0.060000;;
   0.610000;0.610000;0.610000;;
   TextureFilename {
    "uvä.png";
   }
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   5.000000;
   0.060000;0.060000;0.060000;;
   0.610000;0.610000;0.610000;;
   TextureFilename {
    "uvø.png";
   }
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   5.000000;
   0.060000;0.060000;0.060000;;
   0.610000;0.610000;0.610000;;
   TextureFilename {
    "uvø.png";
   }
  }
 }
 MeshNormals {
  11;
  0.000000;-0.018011;-0.999838;,
  0.000000;-0.000000;1.000000;,
  0.000000;-1.000000;-0.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  -0.000011;0.000000;1.000000;,
  -0.000013;0.000000;-1.000000;,
  -0.000011;0.000000;1.000000;,
  0.000000;1.000000;0.000000;,
  -1.000000;-0.000000;-0.000001;;
  26;
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;1,1,1,1;,
  4;5,5,5,5;,
  4;2,2,2,2;,
  4;5,5,5,5;,
  4;4,4,4,4;,
  4;1,1,1,1;,
  4;3,3,3,3;,
  4;9,9,9,9;,
  4;10,10,10,10;,
  4;5,5,5,5;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;6,6,6,6;,
  4;5,5,5,5;,
  4;2,2,2,2;,
  4;5,5,5,5;,
  4;7,7,7,7;,
  4;8,8,8,8;,
  4;3,3,3,3;;
 }
 MeshTextureCoords {
  72;
  0.987970;0.359290;,
  0.988610;0.369800;,
  0.864960;0.370810;,
  0.861780;0.360310;,
  0.988610;0.112930;,
  0.988610;0.120230;,
  0.858850;0.120230;,
  0.858850;0.112930;,
  0.974240;0.593400;,
  0.974240;0.630850;,
  0.940950;0.630850;,
  0.940950;0.593400;,
  0.974240;0.380030;,
  0.940950;0.380030;,
  0.997220;0.380030;,
  0.990090;0.593400;,
  0.917970;0.593400;,
  0.917970;0.380030;,
  0.975460;0.379880;,
  0.942160;0.379880;,
  0.942160;0.593200;,
  0.975460;0.593200;,
  0.974240;0.593400;,
  0.940950;0.593400;,
  0.940950;0.630850;,
  0.974240;0.630850;,
  0.974240;0.380030;,
  0.940950;0.380030;,
  0.990090;0.593400;,
  0.997220;0.380030;,
  0.917970;0.380030;,
  0.917970;0.593400;,
  0.975460;0.379880;,
  0.975460;0.593200;,
  0.942160;0.593200;,
  0.942160;0.379880;,
  0.995930;0.120230;,
  0.995930;0.362470;,
  0.851550;0.120230;,
  0.854480;0.360310;,
  0.988610;0.120230;,
  0.858850;0.120230;,
  0.861780;0.360250;,
  0.987970;0.359230;,
  0.974240;0.593400;,
  0.974240;0.630850;,
  0.940950;0.630850;,
  0.940950;0.593400;,
  0.974240;0.380030;,
  0.940950;0.380030;,
  0.997220;0.380030;,
  0.990090;0.593400;,
  0.917970;0.593400;,
  0.917970;0.380030;,
  0.975460;0.379880;,
  0.942160;0.379880;,
  0.942160;0.593200;,
  0.975460;0.593200;,
  0.974240;0.593400;,
  0.940950;0.593400;,
  0.940950;0.630850;,
  0.974240;0.630850;,
  0.974240;0.380030;,
  0.940950;0.380030;,
  0.990090;0.593400;,
  0.997220;0.380030;,
  0.917970;0.380030;,
  0.917970;0.593400;,
  0.975460;0.379880;,
  0.975460;0.593200;,
  0.942160;0.593200;,
  0.942160;0.379880;;
 }
}
