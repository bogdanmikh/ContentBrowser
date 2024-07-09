#version 330

in vec2 v_TexCoordOut;

uniform int iFrame;
uniform float iTime;
uniform float iTimeDelta;
uniform vec2 iResolution;
uniform vec2 iMouse;
uniform sampler2D iChannel0;
uniform sampler2D iChannel1;
uniform sampler2D iChannel2;
uniform sampler2D iChannel3;
uniform sampler2D iChannel4;
uniform sampler2D iChannel5;
uniform sampler2D iChannel6;
uniform sampler2D iChannel7;
uniform sampler2D iChannel8;
uniform sampler2D iChannel9;
uniform sampler2D iChannel10;
uniform sampler2D iChannel11;
uniform sampler2D iChannel12;
uniform sampler2D iChannel13;
uniform sampler2D iChannel14;
uniform sampler2D iChannel15;
uniform sampler2D iSegmentationMask;
uniform sampler2D iOriginalTexture;

out vec4 f_ColorOut;

void mainImage( out vec4 fragColor, in vec2 fragCoord );

void main() {
    mainImage( f_ColorOut, gl_FragCoord.xy );
}