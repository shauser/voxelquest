#version 120
#extension GL_EXT_frag_depth : enable

uniform float cellsPerHolder;
uniform float heightOfNearPlane;
uniform float clipDist;
uniform vec2 bufferDim;
uniform vec3 lookAtVec;
uniform vec3 cameraPos;

varying vec4 TexCoord0;
varying vec4 TexCoord1;



$


void main() {

    vec4 screenPos = gl_ModelViewProjectionMatrix * gl_Vertex;
    
    float camDis = distance(cameraPos.xyz,gl_Vertex.xyz);
    float zbVal = 1.0-camDis/clipDist;
    //float zbVal = 1.0-screenPos.z/clipDist;
    
    TexCoord0 = vec4(gl_Vertex.xyz,zbVal);
    TexCoord1 = gl_MultiTexCoord0;
    
    gl_Position = screenPos;
}

$


void main() {
    
    gl_FragData[0] = TexCoord0;
    gl_FragData[1] = TexCoord1;
}









// #extension GL_EXT_frag_depth : enable
// varying vec3 vColor;

// void main() {
//     float a = pow(2.0*(gl_PointCoord.x - 0.5), 2.0);
//     float b = pow(2.0*(gl_PointCoord.y - 0.5), 2.0);
//     float c = 1.0 - (a + b);
//     if(c < 0.0) {
//         discard;
//     }
//     gl_FragColor = vec4(vColor, 1.0);
//     gl_FragDepthEXT = gl_FragCoord.z + blendDepth*(1.0-pow(c, 1.0)) * gl_FragCoord.w;
// }





// //via http://prideout.net/blog/?p=64

// out vec4 FragColor;

// uniform mat4 Modelview;
// uniform float FocalLength;
// uniform vec2 WindowSize;
// uniform vec3 RayOrigin;

// struct Ray {
//     vec3 Origin;
//     vec3 Dir;
// };

// struct AABB {
//     vec3 Min;
//     vec3 Max;
// };

// bool IntersectBox(Ray r, AABB aabb, out float t0, out float t1)
// {
//     vec3 invR = 1.0 / r.Dir;
//     vec3 tbot = invR * (aabb.Min-r.Origin);
//     vec3 ttop = invR * (aabb.Max-r.Origin);
//     vec3 tmin = min(ttop, tbot);
//     vec3 tmax = max(ttop, tbot);
//     vec2 t = max(tmin.xx, tmin.yz);
//     t0 = max(t.x, t.y);
//     t = min(tmax.xx, tmax.yz);
//     t1 = min(t.x, t.y);
//     return t0 <= t1;
// }

// void main()
// {
//     vec3 rayDirection;
//     rayDirection.xy = 2.0 * gl_FragCoord.xy / WindowSize - 1.0;
//     rayDirection.z = -FocalLength;
//     rayDirection = (vec4(rayDirection, 0) * Modelview).xyz;

//     Ray eye = Ray( RayOrigin, normalize(rayDirection) );
//     AABB aabb = AABB(vec3(-1.0), vec3(+1.0));

//     float tnear, tfar;
//     IntersectBox(eye, aabb, tnear, tfar);
//     if (tnear < 0.0) tnear = 0.0;

//     vec3 rayStart = eye.Origin + eye.Dir * tnear;
//     vec3 rayStop = eye.Origin + eye.Dir * tfar;
    
//     // Transform from object space to texture coordinate space:
//     rayStart = 0.5 * (rayStart + 1.0);
//     rayStop = 0.5 * (rayStop + 1.0);

//     // Perform the ray marching:
//     vec3 pos = rayStart;
//     vec3 step = normalize(rayStop-rayStart) * stepSize;
//     float travel = distance(rayStop, rayStart);
//     for (int i=0; i < MaxSamples && travel > 0.0; ++i, pos += step, travel -= stepSize) {
    
//         // ...lighting and absorption stuff here...

//     }
