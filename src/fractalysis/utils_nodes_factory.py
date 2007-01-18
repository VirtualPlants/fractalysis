#       File author(s): Christophe Pradal <christophe.prada@cirad.fr>
#                       Samuel Dufour-Kowalski <samuel.dufour@sophia.inria.fr>
#
#       Distributed under the Cecill-C License.
#       See accompanying file LICENSE.txt or copy at
#           http://www.cecill.info/licences/Licence_CeCILL-C_V1-en.html
# 
#       OpenAlea WebSite : http://openalea.gforge.inria.fr
#


__doc__="""
Factory for utils_nodes simplify the wralea file 
"""

__license__= "Cecill-C"
__revision__=" $Id: $ "



from openalea.core.core import Factory


def define_factory(package):
    """ Define factories for arithmetics nodes """

    nf = Factory( name= "regLin", 
                      description= "linear regression", 
                      category = "Tools", 
                      nodemodule = "utils_nodes",
                      nodeclass = "linearRegression",
                      widgetmodule = None,
                      widgetclass = None, 
                      parameters = [ 'alpha', 'origin' ]
                      )

    package.add_factory( nf )

    nf = Factory( name= "regLin2Plot", 
                      description= "Transform a linear regression into plotable object", 
                      category = "Tools", 
                      nodemodule = "utils_nodes",
                      nodeclass = "regLin2Plot",
                      widgetmodule = None,
                      widgetclass = None, 
                      parameters = [ 'pointLegend', 'pointMarker', 'pointColor', 'regLineStyle' ]
                      )

    package.add_factory( nf )

    nf = Factory( name= "plot2D", 
                      description= "Plot a list of 2D plotable objects", 
                      category = "Tools", 
                      nodemodule = "utils_nodes",
                      nodeclass = "plot2D",
                      widgetmodule = None,
                      widgetclass = None, 
                      parameters = [ 'title', 'xlabel', 'ylabel' ]
                      )

    package.add_factory( nf )

