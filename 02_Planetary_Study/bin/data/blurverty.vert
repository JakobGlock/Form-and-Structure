// vertex shader

#version 330

// these are for the programmable pipeline system
uniform mat4 modelViewProjectionMatrix;
in vec4 position;

void main()
{
    /* Store position */
    vec4 pos = position;

    /* Output the new position */
    gl_Position = modelViewProjectionMatrix * pos;

}
