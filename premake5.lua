output_dir				= '%{cfg.buildcfg}_%{cfg.architecture}_%{cfg.system}'

workspace 'Roman'
	architecture		'x64'
	configurations		{ 'Debug', 'Release' }
	flags				{ 'MultiProcessorCompile' }
	startproject		'Roman'
	language			'C++'
	cppdialect			'C++latest'
	conformancemode		'On'
	staticruntime		'On'
	floatingpoint		'Fast'
	rtti				'Off'
	exceptionhandling	'Off'
	buildoptions		{ '/Zc:rvalueCast' }
	files				{ '**.cc', '**.hh' }
	objdir				( '.bin_int/' .. output_dir .. '/%{prj.name}' )
	targetdir			( '.bin/'	  .. output_dir .. '/%{prj.name}' )
	debugdir			( '.bin/'	  .. output_dir .. '/%{prj.name}' )

	filter 'files:**.cc'
		compileas		'C++ModuleInterface'

	filter 'files:**.hh'
		compileas		'C++HeaderUnit'

	filter 'configurations:Debug'
		runtime			'Debug'
		symbols			'On'
		defines			'DEBUG'

	filter 'configurations:Release'
		runtime			'Release'
		optimize		'Speed'
		buildoptions	'/Ob3'
		flags			{ 'LinkTimeOptimization' }

project 'Roman'
	location			'Roman'
	entrypoint			'mainCRTStartup'
	kind				'ConsoleApp'