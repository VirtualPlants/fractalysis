#include <iostream>
#include <assert.h>

#define LGT_MAKEDLL

#include <plantgl/tool/timer.h>
#include <plantgl/scenegraph/container/pointarray.h>
#include <plantgl/algo/base/discretizer.h>
#include <plantgl/algo/base/surfcomputer.h>
#include <plantgl/algo/base/volcomputer.h>

#include <plantgl/algo/fitting/fit.h>
#include <plantgl/scenegraph/transformation/translated.h>



using namespace std;

#include "fractalysis/light/msStruct.h"

msNode::msNode( int s ):
 scale( s ),
 id( 0 ),
 cplx( 0 ),
 surface( 0 ),
 volume( 0 ),
 globalOpacity(-1)
{/*
  scale = s;
  id = 0;
  cplx = 0;
  components = vector<int>();
  surface = 0;
  volume = 0;
  interceptedBeams = DirectionalHitBeamsMap();
  projSurface =  DirectionalFloatMap();
  pOmega =  DirectionalFloatMap();*/
}

msNode::~msNode() {}

void msNode::setId( int i) {id = i;}
void msNode::setCplx( int c ) {cplx = c; }
void msNode::addComponent( int c )
{ 
  components.push_back( c ); 
  //cout<<"compo size is : "<<components.size()<<endl;
}
void msNode::setComponents( const vector<int>& v ) { components = v; }
void msNode::setSurface( float s ) { surface = s;}
void msNode::setVolume( float v ) { volume = v;}
void msNode::setShape( ShapePtr sh ) 
{
  shape = sh; 
  setSurface( computeSurface() );
  setVolume(  computeVolume() );
}

void msNode::setGlobalOpacity(float p) { globalOpacity = p;}

void msNode::addInterBeam( Vector3 v, iBeam ib )
{
  v.normalize();
  if( interceptedBeams.find( v ) == interceptedBeams.end() )
    {
      vector<iBeam> vect;
      vect.insert( vect.begin(), ib );
      //assert( vect.size() == 1 && vect.capacity() >= 1 && vect[0] == ib);
      interceptedBeams[ v ] = vect;
    }
  else
    {
       interceptedBeams[ v ].push_back( ib );
    }
}
void msNode::setProjSurface( Vector3 v, float s ) 
{
  v.normalize();
  projSurface[ v ] = s;
  //cout<<"projSurface of node "<<getId()<<" : "<<s<<endl;
}
void msNode::setPOmega( Vector3 v, DistribVect d, float po )
{
  v.normalize();
  map<Vector3, map< DistribVect, float> >::iterator pom_it= pOmega.find( v );
  if( pom_it != pOmega.end() ) //v already has pomega calculated
  {
    ( pom_it->second )[ d ] = po;
  }
  else
  {
    map<DistribVect, float> distribMap;
    distribMap[ d ] = po;
    pOmega[ v ] = distribMap;
  }
  //cout<<"POmega for node "<<getId()<<" is "<<po<<endl;
}

int msNode::getId() { return id;}
int msNode::getScale() {return scale;}
int msNode::getCplx() {return cplx;}
vector<int> msNode::getComponents() { return components; }
float msNode::getSurface() {return surface;}
float msNode::getVolume() {return volume;}
ShapePtr msNode::getShape() {return shape;}
float msNode::getGlobalOpacity() {return globalOpacity;}

vector<iBeam> * msNode::getIBeams(Vector3 v)
{
  DirectionalHitBeamsMap::iterator ibeams_it = interceptedBeams.find(v);
  if( ibeams_it != interceptedBeams.end())
    return &ibeams_it->second;
  else
  {
    vector<iBeam> * v = new vector<iBeam>();
    return  v;
  }
}

float msNode::getBeamLength( Vector3 v, int x, int y )
{
  v.normalize();
  if( interceptedBeams.find( v ) == interceptedBeams.end() )
  {
    //cout<<"getBeamLength : Direction was not computed or an error has occured, please report, nodeId : "<<getId()<<endl;
  }
  else
  {
    vector<iBeam> vect = interceptedBeams[ v ];
    for( vector<iBeam>::iterator iBeam_iter = vect.begin(); iBeam_iter != vect.end(); ++iBeam_iter )
    {
      if( iBeam_iter->id_x == x && iBeam_iter->id_y == y )
        { return iBeam_iter->length;}
    }
    return -1; //this beam does not intercept this node
  }
}

float msNode::getProjSurface( Vector3 v ) //return 0 if problem
{
  v.normalize();
  if( projSurface.find( v ) == projSurface.end() )
  {
    cout<<"getProjSurface : Direction was not computed or an error has occured, please report, nodeId : "<<getId()<<" direction : "<<v<<endl;
    return 0;
  }
  else
    { return projSurface[ v ]; }
}

float msNode::getPOmega( Vector3 v, DistribVect d ) //return -1 if problem
{
  v.normalize();
  DirectionalDistribPMap::const_iterator pom_it= pOmega.find( v );
  if( pom_it == pOmega.end() ) //Direction does not exist
  {
    //cout<<"getPOmega : Direction was not computed or an error has occured, please report, nodeId : "<<getId()<<endl;
    return -1;
  }
  else
  {
    map<DistribVect, float>::const_iterator distri_it= ( pom_it->second ).find( d );
    if( distri_it == ( pom_it->second ).end() ) //Distribution does not exist for that direction
      {
        //cout<<"Distribution for this direction was not computed"<<endl;
        return -1;
      }
    else
    {
      //cout<<"Returning computed pomega"<<endl;
      return distri_it->second;
    }
  }
}

float msNode::computeSurface()
{
  Discretizer d;
  SurfComputer surfc( d );
  if( shape->apply( surfc ) )
    return surfc.getSurface();
}

float msNode::computeVolume()
{
  Discretizer d;
  VolComputer volc( d );
  if( shape->apply( volc ) )
    return volc.getVolume();
}

void msNode::afficheInfo()
{
  cout<<"Id : "<<getId()<<endl;
  cout<<"Scale : "<<getScale()<<endl;
  cout<<"Complex : "<<getCplx()<<endl;
  cout<<"Components by idx : ";
  for( int i = 0; i<getComponents().size(); ++i )
  {
    cout<<getComponents()[ i ]<<" ";
  }
  cout<<endl<<"Components by iterator : ";
  vector<int> v = getComponents();
  for( vector<int>::const_iterator vit = v.begin(); vit != v.end(); ++vit )
  {
    cout<< *vit<<" ";
  }
  cout<<endl;
  cout<<"Surface : "<<getSurface()<<endl;
  cout<<"Volume : "<<getVolume()<<endl;
  cout<<"#####################################################"<<endl;
}

void msNode::cleanMaps()
{
  interceptedBeams.clear();
  projSurface.clear();
  pOmega.clear();
}

/******************* scaledStruct *********************************/

scaledStruct::scaledStruct( string plname )
{
  plantName = plname;
  nodeList = vector<msNode *>() ;
}

scaledStruct::~scaledStruct()
{
  for( int i = 0; i<nodeList.size(); i++ )
    delete nodeList[ i ];
}

string scaledStruct::getName() {return plantName;}
void scaledStruct::setName(string pln) {plantName = pln;}
int scaledStruct::depth() {return scales.size();}

void scaledStruct::addNode( msNode * n ) { nodeList.push_back( n ); }
void scaledStruct::setNodeList(const vector<msNode *>& v ) { nodeList = v; }

msNode * scaledStruct::getNode( int id )
{
  id--;
  if( id >=0 && id< nodeList.size() )
    return nodeList[ id ];
}

vector<int> scaledStruct::getAtoms(int id )
{
  msNode * n = getNode( id );
  vector<int> atoms;
  vector<int> compo = n->getComponents();
  if( compo.size() == 0 )
  {
    atoms.push_back( n->getId() );
  }
  else
  {
    for( int i=0; i<compo.size(); i++ )
    {
      vector<int> v = getAtoms( compo[ i ] );
      for( int j = 0; j < v.size(); j++ )
        atoms.push_back( v[ j ] );
    }
  }
  //delete n;  fait une erreur de seg, pkoi ?
  return atoms;
}

vector<int> scaledStruct::get1Scale( int sc )
{
  vector<int> v;
  msNode * n;
  for( int i=0; i < nodeList.size(); i++ )
  {
    n = nodeList[ i ];
    if( n->getScale() == sc )
      v.push_back( n->getId() );
    
  }
  return v;
}

int scaledStruct::countScale()
{
  int nbSc = 0;
  scales.clear();
  if( nodeList.size() > 0 )
  {
    for( int i=0; i<nodeList.size(); i++ )
    {
      msNode * n = nodeList[ i ];
      if( scales.find( n->getScale() ) == scales.end() )
        scales[ n->getScale() ] = 1;
      else
        scales[ n->getScale() ] += 1;
    }

  hash_map<int, int>::iterator mit;
  for( mit = scales.begin(); mit != scales.end(); mit++ )
    {
      cout<<"Scale "<<mit->first<<" : "<<mit->second<<endl;
      nbSc++;
    }
  }
  else
  {
    cout<<"Node must be defined first"<<endl;
  }
  return nbSc;
}

void scaledStruct::sonOf( int comp, int cplx )
{
  getNode( comp )->setCplx( cplx );
  getNode( cplx )->addComponent( comp );
} 

void scaledStruct::cleanNodes()
{
  for(int i=0; i<nodeList.size(); ++i)
  {
    nodeList[i]->cleanMaps();
  }
}

ScenePtr scaledStruct::genNodeScene( int id )
{
  ScenePtr scene = new Scene();
  vector<int> list = getAtoms( id );
  msNode * n;
  for( int i=0; i<list.size(); ++i )
  {
    n = getNode( list[ i ] );
    scene->add( n->getShape() );
  }
  n = getNode( id );
  if( n->getComponents().size() != 0 )
    scene->add( n->getShape() );
  return scene; 
}

ScenePtr scaledStruct::genSelectScene()
{
  vector<uint32_t> sel = PGLViewerApplication3::getSelection();
  ScenePtr scene = new Scene();
  for ( int i=0; i<sel.size(); ++i )
  {
    ScenePtr sc = genNodeScene( sel[ i ] );
    for( Scene::const_iterator sc_it = sc->getBegin(); sc_it != sc->getEnd(); ++sc_it )
    {
      scene->add( * sc_it );
    }
  }
  return scene;
}

ScenePtr scaledStruct::genScaleScene( int sc)
{
  ScenePtr scene = new Scene();
  vector<int> vect = get1Scale( sc );
  msNode * node;
  for( int i=0; i<vect.size(); ++i )
  {
    node = getNode( vect[ i ] );
    scene->add( node->getShape() );
  }
  node = NULL;
  delete node;
  return scene;
}

float scaledStruct::totalLA( int id )
{
  vector<int> leaves = getAtoms( id );
  float leafArea = 0;
  for( int i=0 ; i<leaves.size(); ++i )
    leafArea += getNode( leaves[ i ] )->getSurface();

  return leafArea;
}

vector< pair<uint32_t,double> >  scaledStruct::computeProjections( Vector3 v )
{
  Timer t;
  t.start();
  //setting the camera according to scene size
  v.normalize();
  
  PGLViewerApplication3::animation( true );
  PGLViewerApplication3::glFrameSize( 600,600 ); //size can be changed...
  PGLViewerApplication3::setOrthographicCamera ();
  PGLViewerApplication3::setGrid (false, false, false, false);
  PGLViewerApplication3::display( genScaleScene( 1 ) );
  //camera is set, doing the projections
  vector< pair<uint32_t,double> > proj, total;
  vector< pair<uint32_t,double> >::const_iterator it_proj;
  ScenePtr sc ;
  BoundingBoxPtr bbox;
  Vector3 bb_center, cam_pos;
  hash_map<int, int>::iterator mit;
  msNode * node;
  for( mit = scales.begin(); mit != scales.end(); mit++ )
  {
    sc = centerShapes( genScaleScene( mit->first ) );
    cout<<"Projecting scale "<<mit->first<<endl;
    bbox = getBBox(  sc );
    if( bbox == NULL )
      {
      cout<<"Bbox problem"<<endl;
      bbox = new BoundingBox( Vector3( -500,-500,-500 ), Vector3( 500,500,500 ) ); //default bbox
      }
    bb_center = bbox->getCenter();
    float d_factor = ( bbox->getXRange()+bbox->getYRange()+bbox->getZRange() );
    cam_pos = bb_center + v*-3*d_factor;
    //cout<<"Camera pos : "<<cam_pos<<"  looking at : "<<bb_center<<endl;
    PGLViewerApplication3::lookAt(cam_pos, bb_center );
    PGLViewerApplication3::display( sc );
    proj = PGLViewerApplication3::getProjectionSizes( sc );
    
    for( it_proj = proj.begin(); it_proj != proj.end(); ++it_proj )
    {
      total.push_back( *it_proj);
      node = getNode( it_proj->first );
      node->setProjSurface( v, it_proj->second );
    }
  }
  t.stop();
  cout<<"Projections computed in "<<t.elapsedTime()<<"s"<<endl;
  node = NULL;
  delete node;
  return total;
}

void scaledStruct::sprojToNodes(Vector3 v, vector< pair<uint32_t,double> > sproj)
{
  msNode * node;
  v.normalize();
  for( vector< pair<uint32_t,double> >::const_iterator it_sproj = sproj.begin(); it_sproj != sproj.end(); ++it_sproj )
  {
    node = getNode( it_sproj->first );
    node->setProjSurface( v, it_sproj->second );
  }
  node = NULL;
  delete node;
}

void scaledStruct::beamsToNodes( Vector3 direction, ViewRayPointHitBuffer3 * beams )
{
  direction.normalize();
  int nbLign = beams->getColsSize();
  int nbCol = beams->getRowsSize();
  RayPointHitList3::iterator raypointhit_it;
  msNode * node;
  iBeam ib ;
  for( int lgn=0; lgn< nbLign; ++lgn )
  {
    for( int col=0; col<nbCol; ++col )
    {
      RayPointHitList3 oneBeam = beams->getAt( lgn, col );
      for( raypointhit_it=oneBeam.begin(); raypointhit_it!=oneBeam.end(); ++raypointhit_it )
      {
        node = getNode( raypointhit_it->id );
        ib.id_x = lgn; 
        ib.id_y = col;
        ib.length = norm(raypointhit_it->zmax - raypointhit_it->zmin);
        node->addInterBeam( direction, ib );
      }
    }
  }
  node = NULL;
  delete node;
}

float scaledStruct::probaClassic(int node_id, Vector3 direction)
{
  
  msNode * node = getNode(node_id);
  float vol = node->getVolume();
  direction.normalize();
  vector<iBeam> * interBeams = node->getIBeams(direction);
  int beta = interBeams->size();
  assert(beta>0 && "intercepted beam list must not be empty");
  float som=0;
  vector<int> leaves_id = getAtoms(node_id);
  vector<float> leaves_sproj;
  for(int i=0; i<leaves_id.size(); ++i)
  {
    leaves_sproj.push_back(getNode(leaves_id[i]) -> getProjSurface(direction));
  }
  /*
  Recuperer le vecteur de toutes les feuilles : getAtoms
  faire pour chq rayon une boucle sur ces feuilles en faisant le produit des
  1-sproj(feuille) x (*ibeams_it).length/node->getVolume
  sommer tous les 1-produit
  renvoyer le tout pour le calcul du starClassic
  faire la fonction starClassic
  */
  float l, prod;
  vector<iBeam>::const_iterator ibeams_it ;
  for(ibeams_it = interBeams->begin(); ibeams_it != interBeams->end(); ++ibeams_it)
  {
    l = (*ibeams_it).length;
    prod=1;
    for(int s=0; s<leaves_sproj.size(); ++s)
    { 
      prod*=(1-l*leaves_sproj[s]/vol); //assuming that leaves are opaque thus pOmega=1
    }
    som += (1-prod);
  }
  node = NULL;
  delete node;
  return som/beta;
}

Array2<float> scaledStruct::probaImage( int node_id, Vector3 direction, vector<distrib> distribution, uint32_t width, uint32_t height )
{
  Array2<float> picture(width, height, 0);
  msNode * node = getNode(node_id);
  direction.normalize();
  assert(scales.size() - node->getScale() == distribution.size() && 
          "Distribution size must be scales size - 1");
  assert(node->getComponents().size() > 0);
  
  vector<iBeam> * interBeams = node->getIBeams(direction);
  int beta = interBeams->size();
  assert(beta>0 && "intercepted beam list must not be empty");
  float som=0;
  float pixOmega;
  vector<iBeam>::const_iterator ibeams_it ;
  for(ibeams_it = interBeams->begin(); ibeams_it != interBeams->end(); ++ibeams_it)
  {
    pixOmega= probaBeamIntercept( node_id, direction, distribution, (*ibeams_it).id_x, (*ibeams_it).id_y);
    som += pixOmega;
    picture.setAt((*ibeams_it).id_x, (*ibeams_it).id_y, pixOmega);
  }
  //cout<<node_id<<"  som : "<<som<<endl;
  node->setPOmega(direction, distribution, som/beta);
  node = NULL;
  delete node;
  return picture;
}


float scaledStruct::probaIntercept( int node_id, Vector3 direction, vector<distrib> distribution )
{
  msNode * node = getNode(node_id);
  direction.normalize();
  assert(scales.size() - node->getScale() == distribution.size() && 
          "Distribution size must be scales size - 1");
  if(node->getComponents().size() == 0)
    { 
      if(node->getGlobalOpacity() != -1)
        return node->getGlobalOpacity();
      else
        return 1; //leaves are condidered opaque for now
    }
  else
  {
    float proba = node->getPOmega(direction, distribution);
    if( proba >= 0)
      return proba;
    else //distribution not computed
    {
      vector<iBeam> * interBeams = node->getIBeams(direction);
      int beta = interBeams->size();
      //assert(beta>0 && "intercepted beam list must not be empty");
      if(beta > 0)
      {
        float som=0;
        vector<iBeam>::const_iterator ibeams_it ;
        for(ibeams_it = interBeams->begin(); ibeams_it != interBeams->end(); ++ibeams_it)
        {
          som += probaBeamIntercept( node_id, direction, distribution, (*ibeams_it).id_x, (*ibeams_it).id_y);
        }
        cout<<node_id<<"  som : "<<som<<"   beta : "<<beta<<endl;
        node->setPOmega(direction, distribution, som/beta);
        return som/beta;
      }
      else
      {
        cout<<"node "<<node_id<<" not intercepted by any beam -_-"<<endl;
        node->setPOmega(direction, distribution, 0);
        return 0;
      }
    }
  }
  node = NULL;
  delete node;
}


float scaledStruct::probaBeamIntercept( int node_id , Vector3 direction, vector<distrib> distribution, int x_beamId, int y_beamId)
{
  msNode * node = getNode(node_id);
  direction.normalize();
  //cout<<"Beamintercep :node id/scale/distrib"<<node_id<<" / "<<node->getScale()<<" / "<<distribution.size()<<endl;  
  assert(scales.size() - node->getScale() == distribution.size() && 
          "Distribution size must be scales size - 1");
  distrib local_distrib;
  if(distribution.size() == 0 )
    {
      assert(node->getComponents().size() == 0 && "leaf don't have components or distrib too short"); //leaf case
      if(node->getGlobalOpacity() != -1)
        return node->getGlobalOpacity();
      else
        return 1;
    }
  else
  {
    local_distrib = distribution.front(); //contain the local distribution
    distribution.erase(distribution.begin()); //shorter by one to send to finer scale
  } 

  /*************************  Real distribution  *****************************************/
  if(local_distrib == Real)
  {
    bool intercept = false;
    float prod =1;
    vector<int> compo =node->getComponents(); 
    for(int c=0; c<compo.size(); ++c)
    {
      msNode * x = getNode(compo[c]);
      float beam_length =x->getBeamLength(direction, x_beamId, y_beamId);
      if( beam_length >= 0)
      {
        intercept = true;
        prod *= (1 - probaBeamIntercept(x->getId(), direction, distribution, x_beamId, y_beamId));
      }
    }
    if(intercept)
      {
        assert(1-prod >= 0);
        return 1-prod;
      }
    else
      return 0;
  }

  /************************* Turbid distribution  ****************************************/
  else if(local_distrib == Turbid)
  {
    float length = node->getBeamLength(direction, x_beamId, y_beamId);
    float prod=1;
    float px, sproj ;
    vector<int> compo =node->getComponents(); 
    for(int c=0; c<compo.size(); ++c)
    {
      msNode * x = getNode(compo[c]);
      sproj = x->getProjSurface(direction);
      if(sproj == 0)
      {
        computeProjections(direction);
        sproj = x->getProjSurface(direction);
      }
      px = probaIntercept(x->getId(), direction, distribution);
      prod *= (1 - ( ( sproj * length * px) / node->getVolume()));
    }
    assert(1-prod >= 0);
    return 1-prod;
  }
  node = NULL;
  delete node;
}

float scaledStruct::starClassic(int node_id, Vector3 direction)
{
  Timer t;
  t.start();
  msNode * node = getNode(node_id);
  direction.normalize();
  float pomega, somega, surfaceFoliaire;
  somega = node->getProjSurface(direction);
  if(somega == 0)
  { 
    computeProjections(direction);
    somega = node->getProjSurface(direction);
  }
  surfaceFoliaire = totalLA(node_id);
  pomega = probaClassic(node_id, direction);

  t.stop();
  cout<<"Classic star computed in "<<t.elapsedTime()<<"s"<<endl;
  node = NULL;
  delete node;
  return somega * pomega / surfaceFoliaire;

}

float scaledStruct::star(int node_id, Vector3 direction, vector<distrib> distribution)
{
  Timer t;
  t.start();
  msNode * node = getNode(node_id);
  direction.normalize();
  float pomega, somega, surfaceFoliaire;
  somega = node->getProjSurface(direction);
  if(somega == 0)
  { 
    computeProjections(direction);
    somega = node->getProjSurface(direction);
  }
  surfaceFoliaire = totalLA(node_id);
  //should try to get it from node, if not compute it
  pomega = node->getPOmega(direction, distribution);

  if(pomega < 0)
    pomega = probaIntercept(node_id, direction, distribution);

  t.stop();
  cout<<"star computed in "<<t.elapsedTime()<<"s"<<endl;
  node = NULL;
  delete node;
  return somega * pomega / surfaceFoliaire;
}


/***************************************************************************************/
/*                          End of classes definition                                  */
/***************************************************************************************/
ScenePtr centerShapes( const ScenePtr& scene )
{
  ScenePtr ctrd_sc = new Scene();
  ShapePtr old_sh, new_sh;
  TranslatedPtr tr;
  BoundingBoxPtr bbox;
  for( Scene::iterator sc_it = scene->getBegin(); sc_it != scene->getEnd(); ++sc_it )
  {
    old_sh = ShapePtr::Cast( * sc_it );
    bbox = getBBox( old_sh );
    tr = new Translated( bbox->getCenter()*-1, old_sh->getGeometry() );
    new_sh = new Shape( GeometryPtr::Cast( tr ), old_sh->getAppearance(), old_sh->getId() );
    ctrd_sc->add( new_sh );
  }
  return ctrd_sc;
}

BoundingBoxPtr getBBox( const ShapePtr& shape )
{
  Discretizer d;
  BBoxComputer bbc( d );

  if( shape->apply( bbc ) )//true means bboxcomputer went ok
    return bbc.getBoundingBox ( );
  else
    return NULL;
}

BoundingBoxPtr getBBox( const ScenePtr& scene )
{
  Discretizer d;
  BBoxComputer bbc( d );

  if( scene->apply( bbc ) )//true means bboxcomputer went ok
    return bbc.getBoundingBox ( );
  else
    return NULL;
}


scaledStruct * ssFromDict( string sceneName, ScenePtr& scene, const dicoTable& dt )
{
  Timer t;
  t.start();
  hash_map<int, int> idList; // id shape are uint32, does it matter ?
  int pos =0; //position de la shape dans la scene
  for( Scene::iterator sc_it = scene->getBegin(); sc_it != scene->getEnd(); ++sc_it )
  {
    idList[ ( *sc_it )->getId() ]= pos++ ;
  }
  hash_map<int, int> old2new;
  vector<msNode *> nodeList;
  int nodeListCount =0;
  msNode * node;
  for( int i=0; i<dt.size(); i++ ) //for each scale
  {
    int s = dt.size() - i; //scale from smallest (dt.size()) to largest (1)
    decompoMap scaleMap = dt[ s-1 ];
    for( decompoMap::iterator dcm_it = scaleMap.begin(); dcm_it!=scaleMap.end(); dcm_it++ ) // for each component
    {
      node = new msNode( s );
      node->setId( ++nodeListCount );
      nodeList.push_back( node );

      if( s == 1 ) //the root, should be unique
        node->setCplx( -1 ); //-1 mean no Cplx

      vector<int> subelmt = dcm_it -> second;
      for( int sb=0; sb<subelmt.size(); ++sb ) //for each sub element
      {
        bool leaf = false;
        int idx; //idList index of target id in case of leaf = shape index in scene
        int idl =0;
        hash_map<int,int>::const_iterator idl_it=idList.find( subelmt[ sb ] ) ;
        if( idl_it != idList.end() )
          {
            leaf =true;
            idx =idl_it->second;
          }
        if( leaf )
        {
          msNode * leaf = new msNode( s+1 );
          leaf->setId( ++nodeListCount );
          nodeList.push_back( leaf );
          ShapePtr scShape = ShapePtr::Cast ( scene->getAt( idx ) );
          ShapePtr leafShape = new Shape( scShape->getGeometry(), scShape->getAppearance(), leaf->getId() );
          leaf->setShape( leafShape );
          leaf->setCplx( node->getId() ); //embeded in python addComponent method
          node->addComponent( leaf->getId() );
        }
        else  //it is not a leaf
        {
          hash_map<int,int>::const_iterator o2n_it = old2new.find( subelmt[ sb ] );
          if( o2n_it != old2new.end() )
          {
            node->addComponent( o2n_it->second );
            nodeList[ o2n_it->second - 1 ]->setCplx( node->getId() );
          }
        }
      }
      if( dcm_it->first != node->getId() )
        old2new[ dcm_it->first ] = node->getId();
      ShapePtr cvxhull = new Shape();
      
      /*
      cvxhull must be the convex hull of all node's component shape
      */
      Point3ArrayPtr pointList = new Point3Array();
      Discretizer d;
      vector<int> compo = node->getComponents();
      for( int i=0; i<compo.size(); ++i )
        {
          if( nodeList[ compo[ i ] - 1 ]->getShape()->apply( d ) ) //true if discretization is ok
            {
              Point3ArrayPtr shapePoints = d.getDiscretization()->getPointList();
              ( * pointList )+=( * shapePoints );
            }
        }
      Fit f;
      f.setPoints( pointList );
      GeometryPtr hull = f.convexHull();
      if( hull.isNull() )
        cout<<"Convex hull not computed"<<endl;
      cvxhull->getGeometry() = hull; 
      AppearancePtr ap = nodeList[ compo[ 0 ] -1 ]->getShape()->getAppearance();
      cvxhull->getAppearance() = ap;
      node->setShape( cvxhull );
    }
  }
  for( int i=0; i<nodeList.size(); ++i )
  {
    msNode * n = nodeList[ i ];
    n->getShape()->id = n ->getId();
  }
  scaledStruct * ss = new scaledStruct( sceneName );
  ss->setNodeList( nodeList );
  ss->countScale();
  t.stop();
  cout<<"scaledStructure generated in : "<<t.elapsedTime()<<"s"<<endl;
  node = NULL;
  delete node;
  return ss;
}