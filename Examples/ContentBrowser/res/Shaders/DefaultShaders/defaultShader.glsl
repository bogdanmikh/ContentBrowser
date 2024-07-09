void mainImage( out vec4 fragColor, in vec2 fragCoord ) {
    vec2 uv = v_TexCoordOut;
    float intensity = sin(iTime) * 0.3;

    float localIntensity = abs(sin(iTime));
    float amount = localIntensity * intensity * 0.1;
    vec3 col;
    col.r = texture( iChannel0, vec2(uv.x + amount, uv.y) ).r;
    col.g = texture( iChannel0, uv ).g;
    col.b = texture( iChannel0, vec2(uv.x - amount, uv.y) ).b;
    fragColor = vec4(col, 1.0);
}
