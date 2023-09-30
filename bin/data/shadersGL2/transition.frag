#version 120

uniform sampler2D tex0;
uniform sampler2D tex1;
uniform vec2 u_resolution;

uniform float u_transition;
uniform int u_flip;

void main() {
  vec4 color = vec4(0,0,0,0);
  vec2 uv = gl_FragCoord.xy / u_resolution;

  vec4 tex0Color = texture2D(tex0, vec2(uv.x, uv.y));
  vec4 tex1Color = texture2D(tex1, vec2(uv.x, uv.y));

  gl_FragColor = mix(
    tex0Color,
    tex1Color,
    u_flip * (1 - u_transition) +
    (1 - u_flip) * u_transition
  );
  // gl_FragColor = vec4(1., 0., 0., 1.);
}

