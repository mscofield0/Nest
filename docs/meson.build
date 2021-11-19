cdata = configuration_data()
cdata.set('TOP_SRCDIR', meson.source_root())
cdata.set('TOP_BUILDDIR', meson.build_root())
cdata.set('OUTPUT_DIR', join_paths(meson.build_root(), 'docs'))
cdata.set('README_PATH', join_paths(meson.source_root(), 'README.md'))
cdata.set('VERSION', meson.version())
cdata.set('PROJECT_NAME', meson.project_name())

doxyfile = configure_file(
  input: 'Doxyfile.in',
  output: 'Doxyfile',
  configuration: cdata,
  install: false
)

doxygen = find_program('doxygen')

docs_target = run_target('docs', command: [doxygen, doxyfile])