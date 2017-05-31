// fragment shader

#version 330
precision highp float;

#define TWO_PI 6.283185307179586476925286766559f

out vec4 outputColor;
uniform float time;
in vec4 verts;

/* Light positions */
const vec3 spotLight1 = normalize(vec3(.5, .5, 1.0));

void main(){

    /* Im not using this but you can get the pixel coords with this */
    vec2 pos = vec2(gl_FragCoord.x, gl_FragCoord.y) / 600.; // Generally divide by height and width
    pos = pos * 2.0 - 1.0; // then scale if you want

    /* Normalize verts from the vertex shader */
    vec3 normal = normalize(verts.xyz);

    /* Basic diffuse lighting */
    float diffuse1 = pow(max(0., dot(normal, spotLight1)), 2.);

    /* Output the color */
    outputColor = vec4(vec3(diffuse1 + 0.0625), 1.0);

}

