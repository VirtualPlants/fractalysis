
# This file has been generated at Thu Sep  4 16:25:51 2008

from openalea.core import *


__name__ = 'Demo.Fractal'

__editable__ = True
__description__ = 'fractal analysis tools demo'
__license__ = 'Cecill-C'
__url__ = ''
__alias__ = []
__version__ = '0.1'
__authors__ = 'DDS'
__institutes__ = 'INRIA - CIRAD - UM2'
__icon__ = 'boxcounting_icon.png'
 

__all__ = ['BoxCountingMethod', '_147493996', '_147493964']



BoxCountingMethod = CompositeNodeFactory(name='BoxCountingMethod', 
                             description='Assessing fractal dimension using BCM', 
                             category='compute engine',
                             doc='',
                             inputs=[],
                             outputs=[],
                             elt_factory={  2: ('vplants.fractalysis.engine', 'BCM'),
   3: ('openalea.plottools', 'PointLine Style'),
   4: ('Geometric Operator', 'import scene'),
   5: ('openalea.plottools', 'Iterables to Sequence'),
   6: ('openalea.plottools', 'VS Plot'),
   7: ('PlantGL.Objects', 'Scene'),
   8: ('openalea.data', 'int'),
   9: ('vplants.fractalysis.engine', 'Voxelize'),
   10: ('PlantGL.Visualization', 'plot3D'),
   11: ('openalea.stat.regression', 'linear regression to plot (plotools)'),
   12: ('openalea.stat.regression', 'linear regression (scipy)'),
   14: ('system', 'annotation'),
   15: ('system', 'annotation'),
   16: ('system', 'annotation'),
   17: ('system', 'annotation'),
   18: ('Demo.Fractal', 'AC2-4.geom'),
   19: ('openalea.stat.descriptive', 'log'),
   20: ('openalea.plottools', 'VS Plot'),
   22: ('openalea.stat.descriptive', 'log'),
   23: ('system', 'annotation'),
   24: ('system', 'annotation'),
   25: ('system', 'annotation'),
   26: ('system', 'annotation'),
   27: ('system', 'annotation'),
   28: ('system', 'annotation'),
   29: ('system', 'annotation')},
                             elt_connections={  135712464: (7, 0, 9, 0),
   135712476: (3, 0, 6, 0),
   135712488: (11, 0, 20, 0),
   135712500: (2, 1, 5, 1),
   135712512: (18, 0, 4, 0),
   135712524: (5, 0, 3, 0),
   135712536: (2, 1, 19, 0),
   135712548: (2, 0, 22, 0),
   135712560: (7, 0, 2, 0),
   135712572: (19, 0, 12, 1),
   135712584: (12, 0, 11, 0),
   135712596: (22, 0, 12, 0),
   135712608: (2, 0, 5, 0),
   135712620: (4, 0, 7, 0),
   135712632: (9, 3, 10, 0),
   135712644: (8, 0, 2, 1),
   135712656: (11, 1, 20, 0),
   135712668: (8, 0, 9, 1)},
                             elt_data={  2: {  'block': False,
         'caption': 'BCM',
         'hide': True,
         'lazy': True,
         'minimal': False,
         'port_hide_changed': set([]),
         'posx': 227.5,
         'posy': 257.5,
         'priority': 0,
         'user_application': None},
   3: {  'block': False,
         'caption': 'PointLine Style',
         'hide': True,
         'lazy': True,
         'minimal': False,
         'port_hide_changed': set([]),
         'posx': 46.658134928814718,
         'posy': 481.5429564678135,
         'priority': 0,
         'user_application': None},
   4: {  'block': False,
         'caption': 'import scene',
         'hide': True,
         'lazy': True,
         'minimal': False,
         'port_hide_changed': set([]),
         'posx': 155.22957614096273,
         'posy': 76.785677662246371,
         'priority': 0,
         'user_application': None},
   5: {  'block': False,
         'caption': 'Iterables to Sequence',
         'hide': True,
         'lazy': True,
         'minimal': False,
         'port_hide_changed': set([]),
         'posx': 19.381398803388947,
         'posy': 380.17207344746254,
         'priority': 0,
         'user_application': None},
   6: {  'block': False,
         'caption': 'VS Plot',
         'hide': True,
         'lazy': True,
         'minimal': False,
         'port_hide_changed': set([]),
         'posx': 48.316269857629436,
         'posy': 601.7022323084982,
         'priority': 0,
         'user_application': False},
   7: {  'block': False,
         'caption': 'Scene',
         'hide': True,
         'lazy': False,
         'minimal': False,
         'port_hide_changed': set([]),
         'posx': 203.75,
         'posy': 138.75,
         'priority': 0,
         'user_application': None},
   8: {  'block': False,
         'caption': '25',
         'hide': True,
         'lazy': True,
         'minimal': False,
         'port_hide_changed': set([]),
         'posx': 388.85808541357301,
         'posy': 139.43258923050058,
         'priority': 0,
         'user_application': None},
   9: {  'block': False,
         'caption': 'Voxelize',
         'hide': True,
         'lazy': True,
         'minimal': False,
         'port_hide_changed': set([]),
         'posx': 502.5,
         'posy': 260.0,
         'priority': 0,
         'user_application': None},
   10: {  'block': False,
          'caption': 'plot3D',
          'hide': True,
          'lazy': False,
          'minimal': False,
          'port_hide_changed': set([]),
          'posx': 637.43837760713973,
          'posy': 337.7773007678714,
          'priority': 0,
          'user_application': False},
   11: {  'block': False,
          'caption': 'linear regression to plot (plotools)',
          'hide': True,
          'lazy': True,
          'port_hide_changed': set([]),
          'posx': 296.90628739182443,
          'posy': 568.14173646473898,
          'priority': 0,
          'user_application': None},
   12: {  'block': False,
          'caption': 'linear regression (scipy)',
          'hide': True,
          'lazy': True,
          'port_hide_changed': set([]),
          'posx': 327.5,
          'posy': 503.75,
          'priority': 0,
          'user_application': None},
   14: {  'posx': 828.84613432754031,
          'posy': -186.06474123604232,
          'txt': 'Packages : Fractalysis, plantGL, plotools'},
   15: {  'posx': 827.86782506410691,
          'posy': -97.822342501219325,
          'txt': 'Credits : \n    BOUDON Frederic\n'},
   16: {  'posx': 825.54895222181813,
          'posy': -128.27516039549721,
          'txt': 'Team : Virtual Plants'},
   17: {  'posx': 826.70838864296263,
          'posy': -156.49966902634202,
          'txt': 'Authors : Da SILVA D.'},
   18: {  'block': False,
          'caption': 'AC2-4.geom',
          'hide': True,
          'lazy': True,
          'port_hide_changed': set([2]),
          'posx': 158.75,
          'posy': -25.0,
          'priority': 0,
          'user_application': None},
   19: {  'block': False,
          'caption': 'log',
          'hide': True,
          'lazy': True,
          'port_hide_changed': set([]),
          'posx': 433.75,
          'posy': 440.0,
          'priority': 0,
          'user_application': None},
   20: {  'block': False,
          'caption': 'VS Plot',
          'hide': True,
          'lazy': True,
          'minimal': False,
          'port_hide_changed': set([]),
          'posx': 381.72184004441021,
          'posy': 708.3226616029616,
          'priority': 0,
          'user_application': False},
   22: {  'block': False,
          'caption': 'log',
          'hide': True,
          'lazy': True,
          'port_hide_changed': set([]),
          'posx': 342.5,
          'posy': 436.25,
          'priority': 0,
          'user_application': None},
   23: {  'posx': -122.49163933336786,
          'posy': 112.13116536048625,
          'txt': 'Opening plant Scene'},
   24: {  'posx': 742.95639777273368,
          'posy': 319.03864039654229,
          'txt': 'Visualization of smaller\nvoxelized scene'},
   25: {  'posx': -24.294511043078387,
          'posy': -163.44587820637565,
          'txt': 'Box Counting Method'},
   26: {  'posx': 470.21894780330308,
          'posy': 139.99429544065032,
          'txt': 'greatest grid subdivision factor'},
   27: {  'posx': -255.54890860337179,
          'posy': 248.08159686435584,
          'txt': 'Applaying the BCM procedure to\na range of grid subdivision factor'},
   28: {  'posx': -431.37227150842944,
          'posy': 467.21552506769319,
          'txt': 'Visualization of relation between\nthe number of intercepted voxels\nand their size'},
   29: {  'posx': 717.25391788802699,
          'posy': 606.58412626430436,
          'txt': 'Assessing the fractal dimension as the\nslope of the linear regression line between\nthe log of number of intercepted voxels\nand the log of their size'},
   '__in__': {  'caption': 'In',
                'hide': True,
                'lazy': True,
                'minimal': False,
                'port_hide_changed': set([]),
                'posx': 20.0,
                'posy': 5.0,
                'priority': 0},
   '__out__': {  'caption': 'Out',
                 'hide': True,
                 'lazy': True,
                 'minimal': False,
                 'port_hide_changed': set([]),
                 'posx': 20.0,
                 'posy': 250.0,
                 'priority': 0}},
                             elt_value={  2: [],
   3: [(1, "'Mango a19'"), (2, "'-'"), (3, "'4'"), (4, "'Default'")],
   4: [],
   5: [],
   6: [  (1, "'PointLine'"),
         (2, "'Box Couting Method'"),
         (3, "'$\\\\delta$'"),
         (4, "'$N_{\\\\delta}$'"),
         (5, '0'),
         (6, '0')],
   7: [],
   8: [(0, '25')],
   9: [(2, 'True')],
   10: [],
   11: [],
   12: [],
   14: [],
   15: [],
   16: [],
   17: [],
   18: [  (0, 'PackageData(Demo.Fractal, AC2-4.geom)'),
          (1, 'None'),
          (2, 'None')],
   19: [],
   20: [  (1, "'PointLine'"),
          (2, "'Box Counting Method'"),
          (3, "'$\\\\log(\\\\delta)$'"),
          (4, "'$log(N_{\\\\delta})$'"),
          (5, 'True'),
          (6, '0')],
   22: [],
   23: [],
   24: [],
   25: [],
   26: [],
   27: [],
   28: [],
   29: [],
   '__in__': [],
   '__out__': []},
                             lazy=True,
                             )



_147493996 = DataFactory(name='AC2-4.geom', 
                    description='', 
                    editors=None,
                    includes=None,
                    )


_147493964 = DataFactory(name='AC3-4.geom', 
                    description='', 
                    editors=None,
                    includes=None,
                    )



