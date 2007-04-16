# -*- coding: iso-8859-15 -*-

# Header

#Check dependencies

#####################
# Import dependencies

import os, sys
pj= os.path.join

try:
    from openalea import config
except ImportError:
    print """
ImportError : openalea.config not found. 
Please install the openalea package before.	
See http://openalea.gforge.inria.fr
"""
    sys.exit()

try:
    from openalea.distx import setup
except ImportError:
    print """
ImportError : openalea.distx package not found.
Please, first install the openalea.distx package.
See http://openalea.gforge.inria.fr
"""
    sys.exit()


##############
# Setup script

# Package name
name= 'fractalysis'

#openalea namespace
namespace=config.namespace 

pkg_name= namespace + '.' + name

# Package version policy
# major.minor.patch
# alpha: patch + 'a'+ 'number'
# beta: patch= patch + 'b' + 'number'
major= '0'
minor= '0'
patch= '2'
version= '%s.%s.%s' % (major, minor, patch)

# Description of the package

# Short description
description= '3D Fractal analysis package.' 

long_description= '''
It contains code in C++, Python, as well as Boost.Python wrappers.
The package can be installed on various platform.
'''

# Author
author= 'Da SILVA David'
author_email= 'david.da_silva@cirad.fr'

# URL
url= 'http://openalea.gforge.inria.fr'

# License: License for the starter package.
# Please, choose an OpenSource license for distribution of your package.

# LGPL compatible INRIA license
license= 'Cecill-C' 

# Scons build directory
build_prefix= "build_scons"

# For other meta-information, please read the Python distutils documentation.

# Main setup
setup(
    # Meta data
    name=name,
    version=version,
    description=description,
    long_description=long_description,
    author=author,
    author_email=author_email,
    url=url,
    license=license,
    
    # Define what to execute with scons
    # scons is responsible to put compiled library in the write place
    # ( lib/, package/, etc...)
    scons_scripts = ['SConstruct'],

    # scons parameters  
    scons_parameters = ["build","build_prefix="+build_prefix],
    
    namespace=[namespace],

    # pure python  packages
    packages= [ pkg_name, pkg_name+'.light', pkg_name+'.engine', pkg_name+'.fractutils' ],
    # python packages directory
    package_dir= {  pkg_name : pj('src',name)
                    pkg_name+'.light' :pj('src', name, 'light'),
                    pkg_name+'.engine' :pj('src', name, 'engine'),
                    pkg_name+'.fractutils' :pj('src', name, 'fractutils'),
                  },

    # add package platform libraries if any
    package_data= { pkg_name : ['*.so', '*.dll', '*.pyd']},
                     

    # copy shared data in default OpenAlea directory
    # map of 'destination subdirectory' : 'source subdirectory'
    external_data={pj('doc', name) : 'doc',
                   pj('test', name) : 'test',
                   pj('include', name) : pj(build_prefix, 'include', name),
                   pj('lib'):  pj(build_prefix,'lib'),
                   },

    

    #Add to PATH environment variable for openalea lib on Windows platform
    set_env_var=['PATH='+os.path.normpath(pj(config.prefix_dir,'lib'))]

    )


