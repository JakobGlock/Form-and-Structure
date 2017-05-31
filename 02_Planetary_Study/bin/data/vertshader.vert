// vertex shader

#version 330

// these are for the programmable pipeline system
uniform mat4 modelViewProjectionMatrix;
in vec4 position;

/* Send a vec to the fragment shader */
out vec4 verts;

/* Some values from outside the shader */
uniform float time;
uniform vec3 freq;
uniform vec3 depth;

void main()
{
    /* Store position */
    vec4 pos = position;

    /* Mess with the vertices */
    pos.x += (cos(pos.y * freq.x + time) * depth.x);
    pos.y += (sin(pos.z * freq.y + time) * depth.y);
    pos.z += (sin(pos.x * freq.z + time) * depth.z);

    /* Output the new position */
    gl_Position = modelViewProjectionMatrix * pos;

    /* Send some values to the fragment shader */
    verts = pos;
}
