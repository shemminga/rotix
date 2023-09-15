project('rotix', 'c', version: '0.83', license: 'GPL-2.0-or-later')
cc = meson.get_compiler('c')

if get_option('i18n')
  subdir('po')
endif

if not cc.check_header('getopt.h')
  add_project_arguments('-DNO_GETOPT_LONG=1', language:'c')
endif


src = ['help.c', 'rot.c', 'rotix.c']

executable('rotix', sources: src, install: true)
install_man('rotix.1')

