all_lib_headers += files(
    'Nest/Foo.hxx',

    # Nest.Core.Utility
    'Nest/Core/Utility/Atomic.hxx',
    'Nest/Core/Utility/CommonTypes.hxx',
    'Nest/Core/Utility/Optional.hxx',
    'Nest/Core/Utility/Traits/NonCopyable.hxx',
    'Nest/Core/Utility/Traits/NonMovable.hxx',

    # Nest.Core.Containers
    'Nest/Core/Containers/ConcurrentQueue.hxx',

    # Nest.Core.Communication
    'Nest/Core/Communication/Channel.hxx',
    'Nest/Core/Communication/Oneshot.hxx',
    'Nest/Core/Communication/OneshotChannel.hxx',
    'Nest/Core/Communication/Receiver.hxx',
    'Nest/Core/Communication/Transmitter.hxx',
    'Nest/Core/Communication/Tunnel.hxx',
    'Nest/Core/Communication/Concepts/Channel.hxx',
    'Nest/Core/Communication/Concepts/Receiver.hxx',
    'Nest/Core/Communication/Concepts/Transmitter.hxx',
)


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