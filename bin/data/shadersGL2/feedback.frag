#version 120

uniform sampler2D u_tex0;
uniform vec2 u_tex0Resolution;

uniform sampler2D u_tex1;
uniform vec2 u_tex1Resolution;

uniform vec2 u_resolution;
uniform vec2 u_displace;

uniform float u_time;

void main() {
  vec4 color = vec4(0,0,0,0);
  vec2 uv = gl_FragCoord.xy / u_resolution;
  vec4 tex0 = texture2D(u_tex1, uv);
  vec4 tex1 = texture2D(
    u_tex0,
    uv + vec2(0.01 * sin(u_time * 0.01))
  );

  float mixVal = 4.;

  color = mix(tex0, tex1, 3 + 2 * sin(u_time * 0.1));
  gl_FragColor = color;
}

