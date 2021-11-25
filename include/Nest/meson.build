# =========== Generated headers
cdata = configuration_data()
cdata.set('PROJECT_NAME', meson.project_name())
cdata.set('UPPERCASE_PROJECT_NAME', meson.project_name().to_upper())
cdata.set('VERSION', meson.project_version())
version_parts = meson.project_version().split('.')
cdata.set('VERSION_MAJOR', version_parts.get(0))
cdata.set('VERSION_MINOR', version_parts.get(1))
cdata.set('VERSION_PATCH', version_parts.get(2))
cdata.set('VERSION_TWEAK', version_parts.get(3))

configure_file(
  input: 'Version.hxx.in',
  output: 'Version.hxx',
  install_dir: meson.project_name(),
  configuration: cdata,
)

configure_file(
  input: 'Export.hxx.in',
  output: 'Export.hxx',
  install_dir: meson.project_name(),
  configuration: cdata,
)