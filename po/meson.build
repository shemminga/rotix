i18n = import('i18n')

add_project_arguments(
  [
    '-DI18N=1',
    '-DPACKAGE="rotix"',
    '-DLOCALEDIR="@0@"'.format( get_option('prefix') / get_option('localedir'))
  ], language:'c')
i18n.gettext(meson.project_name())

