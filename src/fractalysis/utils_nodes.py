# -*- python -*-
#
#       OpenAlea.Core.Library: OpenAlea Core Library module
#
#       Copyright or (C) or Copr. 2006 INRIA - CIRAD - INRA  
#
#       File author(s): David Da SILVA <david.da_silva@cirad.fr>
#
#       Distributed under the Cecill-C License.
#       See accompanying file LICENSE.txt or copy at
#           http://www.cecill.info/licences/Licence_CeCILL-C_V1-en.html
# 
#       OpenAlea WebSite : http://openalea.gforge.inria.fr
#


__doc__="""
utils nodes
"""

__license__= "Cecill-C"
__revision__=" $Id: utils_nodes.py $ "



#from core.core import Node
#from openalea.core.interface import IFloat
#from openalea.core.interface import IStr
from openalea.core import *
import utils

class linearRegression( Node ):
    """Linear regression 
    Input 0 : X values
    Input 1 : Y values
    Input 2 : alpha
    Output 0 : linear regression output"""

    def __init__( self ):

        Node.__init__( self )

        #defines I/O
        self.add_input( name = "X", interface=None, value=[ 0.69314718,  1.79175949,  2.48490667,  3.17805386,  3.87120104] )
        self.add_input( name = "Y", interface=None, value=[ 2.07944154,  2.7080502,   4.41884061,  5.58724866,  6.92264389] )
        self.add_input( name = "alpha", interface=IFloat, value=5. )
        self.add_input( name = "origin", interface=IBool, value=False )
        self.add_output( name = "reg", interface=None )

    def __call__( self, inputs= () ):
        """ inputs is the list of input values """
        if self.get_input_by_key( "origin" ):
            print "Origin will not work if x values are < 0"
            reg = utils.regLinOri(self.get_input_by_key( "X" ),self.get_input_by_key( "Y" ),self.get_input_by_key( "alpha" ) )
        else:
            reg = utils.regLin(self.get_input_by_key( "X" ),self.get_input_by_key( "Y" ),self.get_input_by_key( "alpha" ) )
        
        #print reg
        return ( reg, )

class regLin2Plot( Node ):
    """Generate a plotable object from a linear regression
    Input 0 : linear regression object
    Output 0 : plotable object"""

    def __init__( self ):

        Node.__init__( self )

        #defines I/O
        self.add_input( name='reg', interface=None )
        self.add_input( name='pointLegend', interface=IStr, value='Data' )
        self.add_input( name='pointMarker', interface=IStr, value='^' )
        self.add_input( name='pointColor', interface=IStr, value='dodgerblue' )
        self.add_input( name='regLineStyle', interface=IStr, value='-' )
        self.add_output( name='plotObj', interface=None )

    def __call__( self, inputs=() ):
        return ( utils.regLin2Plot( self.get_input_by_key( 'reg' ), self.get_input_by_key( 'pointLegend' ), self.get_input_by_key( 'regLineStyle' ), self.get_input_by_key( 'pointMarker' ), self.get_input_by_key( 'pointColor' ) ), )


class plot2D( Node ):
    """Generate a plot from 2D plotable object
    Input 0 : 2D plotable object list"""

    def __init__(self ):
        Node.__init__( self )

        #defines I/O
        self.add_input( name='plotObjList', interface=Node )
        self.add_input( name='title', interface=IStr, value='MyPlot' )
        self.add_input( name='xlabel', interface=IStr, value='x-axis' )
        self.add_input( name='ylabel', interface=IStr, value='y-axis' )

    def __call__( self, inputs=() ):
        utils.plot2D( self.get_input_by_key( 'plotObjList' ), self.get_input_by_key( 'title' ), self.get_input_by_key( 'xlabel' ), self.get_input_by_key( 'ylabel' ) )
