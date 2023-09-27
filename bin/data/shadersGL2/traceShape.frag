#version 120

uniform sampler2D u_tex0;
uniform vec2 u_tex0Resolution;
uniform vec2 u_resolution;
uniform vec2 u_offset;
uniform float u_scale;
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
    (vec2(uv.x, uv.y) + u_offset) / (proportions * u_scale)
  );

  float shape = quant((tex.r + tex.g + tex.b) / 3., 4);
  vec3 mix = shape * vec3(
    u_color.r,
    u_color.g,
    u_color.b
  );

  color = vec4(
    mix,
    tex.a
  );

  gl_FragColor = color;
}
