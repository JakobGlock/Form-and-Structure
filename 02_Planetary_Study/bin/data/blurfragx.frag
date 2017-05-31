// fragment shader

#version 330
precision highp float;

#define TWO_PI 6.283185307179586476925286766559f

// Gussian blur - https://github.com/openframeworks/openFrameworks/blob/master/examples/shader/09_gaussianBlurFilter/bin/data/shadersGL3/shaderBlurX.frag

out vec4 outputColor;
uniform sampler2DRect tex0; // Get texture
uniform float blurAmnt; // Blur amount

void main(){

    /* Get pixel cords */
    vec2 uv = vec2(gl_FragCoord.x, gl_FragCoord.y);

    /* Variable to save color */
    vec4 color = vec4(0.);

    /* Accumulate pixel color values from the texture and scale them with differnet weights */
    color += 1.0 * texture(tex0, uv + vec2(blurAmnt * -4.0, 0.0));
    color += 2.0 * texture(tex0, uv + vec2(blurAmnt * -3.0, 0.0));
    color += 3.0 * texture(tex0, uv + vec2(blurAmnt * -2.0, 0.0));
    color += 4.0 * texture(tex0, uv + vec2(blurAmnt * -1.0, 0.0));

    color += 5.0 * texture(tex0, uv + vec2(blurAmnt, 0));

    color += 4.0 * texture(tex0, uv + vec2(blurAmnt * 1.0, 0.0));
    color += 3.0 * texture(tex0, uv + vec2(blurAmnt * 2.0, 0.0));
    color += 2.0 * texture(tex0, uv + vec2(blurAmnt * 3.0, 0.0));
    color += 1.0 * texture(tex0, uv + vec2(blurAmnt * 4.0, 0.0));

    /* Scale the final color */
    color /= 25.0;

    /* Output color */
    outputColor = color;
}
