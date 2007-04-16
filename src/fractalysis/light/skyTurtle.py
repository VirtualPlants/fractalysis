import openalea.plantgl.all as pgl
import math

elevations = [9.23, 9.23, 9.23, 9.23, 9.23, 9.23, 9.23, 9.23, 9.23, 9.23, 10.81, 10.81, 10.81, 10.81, 10.81, 26.57, 26.57, 26.57, 26.57, 26.57, 31.08, 31.08, 31.08,31.08, 31.08, 31.08, 31.08, 31.08, 31.08, 31.08, 47.41, 47.41, 47.41, 47.41, 47.41, 52.62, 52.62, 52.62, 52.62, 52.62, 69.16, 69.16, 69.16, 69.16,69.16, 90]

azimuths = [12.23, 59.77, 84.23, 131.77, 156.23, 203.77, 228.23, 275.77, 300.23, 347.77, 36, 108, 180, 252, 324, 0, 72, 144, 216, 288, 23.27, 48.73, 95.27, 120.73,167.27, 192.73, 239.27, 264.73, 311.27, 336.73, 0, 72, 144, 216, 288, 36, 108, 180, 252, 324, 0, 72, 144, 216, 288, 180]

weights = [0.026808309,0.026808309,0.026808309,0.026808309,0.026808309,0.026808309,0.026808309,0.026808309,0.026808309,0.026808309,0.029325083,0.029325083,0.029325083,0.029325083,0.029325083,0.031299545,0.031299545,0.031299545,0.031299545,0.031299545,0.038160959,0.038160959,0.038160959,0.038160959,0.038160959,0.038160959,0.038160959,0.038160959,0.038160959,0.038160959,0.045638829,0.045638829,0.045638829,0.045638829,0.045638829,0.050212264,0.050212264,0.050212264,0.050212264,0.050212264,0.052965108,0.052965108,0.052965108,0.052965108,0.052965108,0.0481]


def plotSkyTurtle():
  pgl.Viewer.start()
  sc = pgl.Scene()
  for i in range(len(elevations)):
    pos = pgl.Vector3(pgl.Vector3.Spherical(30,math.radians(azimuths[i]),math.radians(90-elevations[i])))
    sc += pgl.Shape(pgl.Translated(pos,pgl.Sphere(0.5)),pgl.Material(),i+1)
  pgl.Viewer.display(sc)

def getSkyTurtleAt(i):
  return (azimuths[i-1],elevations[i-1],weights[i-1])

def getSkyTurtleDir(i):
  return -pgl.Vector3(pgl.Vector3.Spherical(1,math.radians(azimuths[i-1]),math.radians(90-elevations[i-1])))

def getSkyTurtleRotationAngles(i):
  return (- math.radians(azimuths[i-1]), math.radians(elevations[i-1]))

def skyTurtleDir():
  return [ getSkyTurtleDir(i) for i in range(getSkyTurtleSize()) ]

def skyTurtleWDir():
  return [ (getSkyTurtleDir(i),weights[i]) for i in range(getSkyTurtleSize()) ]

def skyTurtle():
  return [ getSkyTurtleAt(i) for i in range(getSkyTurtleSize()) ]

def getSkyTurtleSize():
  return len(azimuths)

