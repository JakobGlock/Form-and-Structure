// fragment shader

#version 330
precision highp float;

#define TWO_PI 6.283185307179586476925286766559f

out vec4 outputColor;
uniform sampler2DRect tex0;
uniform float blurAmnt;

void main(){

    /* Im not using this but you can get the pixel coords with this */
    vec2 uv = vec2(gl_FragCoord.x, gl_FragCoord.y); // Generally divide by height and width

    vec4 color = vec4(0., 0., 0. , 0.);

    color += 1.0 * texture(tex0, uv + vec2(0.0, blurAmnt * -4.0));
    color += 2.0 * texture(tex0, uv + vec2(0.0, blurAmnt * -3.0));
    color += 3.0 * texture(tex0, uv + vec2(0.0, blurAmnt * -2.0));
    color += 4.0 * texture(tex0, uv + vec2(0.0, blurAmnt * -1.0));

    color += 5.0 * texture(tex0, uv + vec2(0.0, blurAmnt));

    color += 4.0 * texture(tex0, uv + vec2(0.0, blurAmnt * 1.0));
    color += 3.0 * texture(tex0, uv + vec2(0.0, blurAmnt * 2.0));
    color += 2.0 * texture(tex0, uv + vec2(0.0, blurAmnt * 3.0));
    color += 1.0 * texture(tex0, uv + vec2(0.0, blurAmnt * 4.0));

    color /= 25.0;

    outputColor = color;
}
