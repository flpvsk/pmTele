#version 120

uniform sampler2D u_tex0;
uniform vec2 u_tex0Resolution;
uniform vec2 u_resolution;
uniform vec3 u_color;
varying vec2 v_texcoord;

float quant(float v, float steps) {
  return v - mod(v, 1 / (steps + 1));
}

void main() {
  vec4 color = vec4(0,0,0,0);
  vec2 uv = gl_FragCoord.xy / u_resolution;
  vec2 proportions = u_tex0Resolution / u_resolution;
  vec4 tex = texture2D(
    u_tex0,
    vec2(uv.x, 1. - uv.y) / proportions
  );

  float shape = quant((tex.r + tex.g + tex.b) / 3., 4);
  vec3 mix = shape * vec3(
    quant(u_color.r, 4),
    quant(u_color.g, 4),
    quant(u_color.b, 4)
  );
  color = vec4(
    mix,
    quant(tex.a, 4)
  );

  gl_FragColor = color;
}
