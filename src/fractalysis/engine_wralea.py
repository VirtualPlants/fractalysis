# -*- python -*-
#
#       OpenAlea.Core.Library: OpenAlea Core Library module
#
#       Copyright or (C) or Copr. 2006 INRIA - CIRAD - INRA  
#
#       File author(s): Da SILVA David <david.da_silva@cirad.fr>
#
#       Distributed under the Cecill-C License.
#       See accompanying file LICENSE.txt or copy at
#           http://www.cecill.info/licences/Licence_CeCILL-C_V1-en.html
# 
#       OpenAlea WebSite : http://openalea.gforge.inria.fr
#


__doc__="""
Wralea for Fractalysis.Library 
"""

__license__= "Cecill-C"
__revision__=" $Id$ "



from openalea.core import *

def register_packages(pkgmanager):
    """ Initialisation function
    Return a list of package to include in the package manager.
    This function is called by the package manager when it is updated
    """


    metainfo={ 'version' : '0.0.1',
               'license' : 'CECILL-C',
               'authors' : 'SDK, CP',
               'institutes' : 'INRIA/CIRAD',
               'description' : 'utils nodes.',
               }


    package = Package("fractalysis.engine", metainfo)

###### begin nodes definitions #############

    nf = Factory( name="BCM",
                  description="Apply box counting method on scene",
                  category="Data Types",
                  nodemodule="engine_nodes",
                  nodeclass="BCM",
                  inputs=(dict(name="scene", interface=IFileStr,),
                          dict(name="stopFactor", interface=IInt, value=3),),
                  outputs=(dict(name="scales", interface = ISequence),
                           dict(name="interceptedVoxels", interface = ISequence),),
                  )

    package.add_factory( nf )

###### end nodes definitions ###############

    pkgmanager.add_package(package)


