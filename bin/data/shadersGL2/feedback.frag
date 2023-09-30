#version 120

uniform sampler2D tex0;
uniform sampler2D tex1;
uniform vec2 u_resolution;

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
  float fbAmount = 4 * (0.5 + 0.5 * sin(u_time * 0.1));

  vec4 texFb = texture2D(tex0, uv);
  vec4 texView = texture2D(tex1, vec2(uv.x, 1. - uv.y));
  vec4 texFbDisplace = texture2D(
    tex0,
    (
      uv
      + 0.01 * vec2(sin(u_time * 0.1), sin(u_time * 0.02))
    ) * (1.0001 + 0.0001 * sin(u_time * 0.1))
  );

  float mixVal = 4.;

  color = mix(
    mix(texFb, texFbDisplace, fbAmount),
    texView,
    texView.a
  );

  // color = quantColor(color, 2);
  // gl_FragColor = vec4(color.rgb - floor((100. * color.rgb)) / 100., 1.);
  gl_FragColor = color;
}

