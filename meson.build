project('main', 'c',
	version: '0.1',
	default_options: [
		'buildtype=debug',
		'c_std=c11',
		'warning_level=3',
		'b_vscrt=md',
		'backend=ninja'])

add_project_arguments([
	'/wd4996',
	'/wd5050',
	'/wd4838',
	'/wd4100' ], language: 'c')

win_includes = [
	'C:\\Program Files (x86)\\Microsoft Visual Studio\\2022\\BuildTools\\VC\\Tools\\MSVC\\14.44.35207\\include',
	'C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.26100.0\\um',
	'C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.26100.0\\ucrt' ]

executable('main',
	'main.c',
	include_directories: win_includes,
	dependencies: [
		meson.get_compiler('c').find_library('kernel32'),
		meson.get_compiler('c').find_library('user32'),
		meson.get_compiler('c').find_library('shlwapi') ],
	c_args: [
		'/Zi',
		'/Od',
		'/Ob0',
		'/EHsc',
		'/nologo' ],
	link_args: [
		'/DEBUG', '/MACHINE:X64', ],
	override_options: {
		'b_pch': false } )
