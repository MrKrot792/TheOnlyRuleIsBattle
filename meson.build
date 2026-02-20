project('TheOnlyRuleIsBattle', 'c', version: '0.0.1',
        meson_version: '>= 0.39.1')

cc = meson.get_compiler('c')

ncurses_dep = dependency('ncurses')

source_c = [
  'src/character.c',
  'src/main.c',
  'src/render.c',
  'src/world.c',
  'src/app.c',
  'src/fps.c',
  'src/log.c',
  'src/camera.c',
  'src/texture.c',
  'src/blocks.c',
  'src/layer.c',
  'src/aabb.c',
  'src/moves.c',
  'src/physics.c',

  'src/layers/exit_button.c',
  'src/layers/ui.c',

  'src/layers/game.c',
  'src/layers/game/attack.c',
  'src/layers/game/play.c',
  'src/layers/game/preview.c',
]

inc = include_directories('include')

TheOnlyRuleIsBattle = executable('torib',
  source_c,
  dependencies : [ ncurses_dep ],
  install : true,
  include_directories: inc,
  link_args: [ '-ggdb', '-lm' ],
)
