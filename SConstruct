# -*-python-*-

from openalea.sconsx import config, environ
import os, fnmatch

Config= config.Config
ALEAConfig= config.ALEAConfig
ALEAEnvironment= config.ALEAEnvironment

pj= os.path.join

name='fractalysis'

SConsignFile()

options = Options(['../options.py', 'options.py'], ARGUMENTS )

wrapper_conf= ALEAConfig(name,['boost_python', 'alea', 'plantgl'])
cpp_conf= ALEAConfig(name, ['alea', 'plantgl'])
opt_conf= ALEAConfig(name, ['boost_python', 'alea'])

# Set all the common options for the package
opt_conf.UpdateOptions( options )

opt_env= Environment( options= options )
opt_conf.Update( opt_env )

# Generate Help available with the cmd scons -h
Help(options.GenerateHelpText(opt_env))

# Set build directory
prefix= opt_env['build_prefix']
BuildDir( prefix, '.' )

cpp_env= ALEAEnvironment( cpp_conf, 'options.py', ARGUMENTS )
cpp_env.Append( CPPPATH = pj( '$build_includedir','fractalysis' ) )
#cpp_env.Append( EXTRA_CPPPATH = pj( '$build_includedir','plantgl' ) )
wrapper_env= ALEAEnvironment( wrapper_conf, 'options.py', ARGUMENTS )
wrapper_env.Append( CPPPATH = pj( '$build_includedir','fractalysis' ) )
#wrapper_env.Append( EXTRA_CPPPATH = pj( '$build_includedir','plantgl' ) )

# Build stage
SConscript( pj(prefix,"src/cpp/SConscript"),
            exports={"env":cpp_env} )

SConscript( pj(prefix,"src/wrapper/SConscript"),
            exports={"env":wrapper_env} )


Default("build")
