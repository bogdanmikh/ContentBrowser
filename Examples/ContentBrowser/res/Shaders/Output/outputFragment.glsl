void mainImage( out vec4 fragColor, in vec2 fragCoord ) {
    vec2 uv = v_TexCoordOut;
    uv.x = -uv.x;
    fragColor = texture( iChannel0, uv );
}
