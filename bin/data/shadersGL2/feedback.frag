#version 120

uniform sampler2D tex0;
uniform vec2 u_resolution;
uniform vec2 u_displace;

uniform float u_time;

varying vec2 v_texcoord;

vec4 quantColor(vec4 v, float steps) {
  return vec4(
    v.r - mod(v.r, 1 / (steps + 1)),
    v.g - mod(v.g, 1 / (steps + 1)),
    v.b - mod(v.b, 1 / (steps + 1)),
    v.a
  );
}

void main() {
  vec4 color = vec4(0,0,0,0);
  vec2 uv = gl_FragCoord.xy / u_resolution;
  float fbAmount = (0.5 + 0.5 * sin(u_time * 0.1));

  vec4 texFb = texture2D(tex0, uv);
  vec4 texFbDisplace = texture2D(
    tex0,
    (
      uv
      // + 0.01 * vec2(sin(u_time * 0.1), sin(u_time * 0.02))
    ) * (1.00 + 0.01 * sin(u_time * 0.1))
  );

  float mixVal = 4.;

  color = fbAmount * mix(
    texFb,
    texFbDisplace, 2 + 4 * sin(u_time * 0.001)
  );
  // color = quantColor(color, 2);
  // gl_FragColor = vec4(color.rgb - floor((100. * color.rgb)) / 100., 1.);
  gl_FragColor = color;
}

