// MFC_OSG.cpp : implementation of the cOSG class
//
#include "stdafx.h"
#include "MFC_OSG.h"
#include <osgGA/StateSetManipulator>
#include <osg/MatrixTransform>
#include <osgDB/WriteFile>
#include <osg/Multisample>

#include <Standard_ErrorHandler.hxx>
#include <Standard_Failure.hxx>
#include <Standard_ConstructionError.hxx>

#include "GeometryUtility.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace NHibernate;
using namespace DbModel;

#define MULTI_SAMPLES 0

class AxesCallback : public osg::NodeCallback
{
public:
	AxesCallback(cOSG* mOsg) :_mOsg(mOsg){}
	virtual void operator()(osg::Node* node, osg::NodeVisitor* nv)
	{
		if (nv->getVisitorType() == osg::NodeVisitor::UPDATE_VISITOR)
		{
			osg::Camera* camera = dynamic_cast<osg::Camera*>(node);
			if (camera)
			{
				osg::Vec3 eye, center, up;
				//_mOsg->getManipulator()->getMatrix().getLookAt(eye,center,up,30);
				_mOsg->getViewer()->getCamera()->getViewMatrixAsLookAt(eye, center, up, 30);
				osg::Matrixd matrix;
				matrix.makeLookAt(eye - center, osg::Vec3(0, 0, 0), up); // always look at (0, 0, 0)
				camera->setViewMatrix(matrix);
				//camera->setProjectionMatrixAsOrtho(-1.5, _mOsg/50, -1.5, _height/50)
			}
		}
		traverse(node, nv);
	}
private:
	cOSG* _mOsg;
};

cOSG::cOSG(HWND hWnd) :
   m_hWnd(hWnd)
   , mHints(new osg::TessellationHints)
{
	mHints->setDetailRatio(0.5f);
}

cOSG::~cOSG()
{
    mViewer->setDone(true);
    Sleep(1000);
    mViewer->stopThreading();

    delete mViewer;
}

void cOSG::InitOSG(std::string modelname)
{
    // Store the name of the model to load
    m_ModelName = modelname;

    // Init different parts of OSG
    InitManipulators();
    InitSceneGraph();
    InitCameraConfig();
}

void cOSG::InitManipulators(void)
{
    // Create a trackball manipulator
    trackball = new osgGA::TrackballManipulator();

    // Create a Manipulator Switcher
    keyswitchManipulator = new osgGA::KeySwitchMatrixManipulator;

    // Add our trackball manipulator to the switcher
    keyswitchManipulator->addMatrixManipulator( '1', "Trackball", trackball.get());

    // Init the switcher to the first manipulator (in this case the only manipulator)
    keyswitchManipulator->selectMatrixManipulator(0);  // Zero based index Value
}


void cOSG::InitSceneGraph(void)
{
    // Init the main Root Node/Group
    mRoot  = new osg::Group;

#if MULTI_SAMPLES > 0
	osg::Multisample *ms = new osg::Multisample;
	ms->setHint(osg::Multisample::NICEST);
	mRoot->getOrCreateStateSet()->setAttributeAndModes(ms, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
#endif

	path modelFile(m_ModelName);
	if (modelFile.extension() == ".db") {
		mModel = InitOSGFromDb();
		if (mModel == NULL)
			return;
		//osg::ref_ptr<osg::StateSet> stateSet = mModel->getOrCreateStateSet();
		//stateSet->setMode(GL_BLEND, osg::StateAttribute::ON);
		//stateSet->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF);
		//stateSet->setMode(GL_LIGHTING, )
	}
	else {
		// Load the Model from the model name
		mModel = osgDB::readNodeFile(m_ModelName);
	}

	if (!mModel) return;

	// Optimize the model
	osgUtil::Optimizer optimizer;
	optimizer.optimize(mModel.get());
	if (mPoints != NULL)
		optimizer.optimize(mPoints);
	optimizer.reset();

	// Add the model to the scene
	mRoot->addChild(mModel.get());
	if (mPoints != NULL)
		mRoot->addChild(mPoints);
}

void cOSG::InitCameraConfig(void)
{
    // Local Variable to hold window size data
    RECT rect;

    // Create the viewer for this window
    mViewer = new osgViewer::Viewer();

    // Add a Stats Handler to the viewer
    mViewer->addEventHandler(new osgViewer::StatsHandler);
	mViewer->addEventHandler(new osgGA::StateSetManipulator(mViewer->getCamera()->getOrCreateStateSet()));

    // Get the current window size
    ::GetWindowRect(m_hWnd, &rect);

    // Init the GraphicsContext Traits
    osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;

    // Init the Windata Variable that holds the handle for the Window to display OSG in.
    osg::ref_ptr<osg::Referenced> windata = new osgViewer::GraphicsWindowWin32::WindowData(m_hWnd);

    // Setup the traits parameters
    traits->x = 0;
    traits->y = 0;
    traits->width = rect.right - rect.left;
    traits->height = rect.bottom - rect.top;
    traits->windowDecoration = false;
    traits->doubleBuffer = true;
    traits->sharedContext = 0;
    traits->setInheritedWindowPixelFormat = true;
    traits->inheritedWindowData = windata;

#if MULTI_SAMPLES > 0
	osg::ref_ptr<osg::DisplaySettings> &ds = osg::DisplaySettings::instance();
	traits->sampleBuffers = ds->getMultiSamples();
	traits->samples = 4;
#endif

    // Create the Graphics Context
    osg::GraphicsContext* gc = osg::GraphicsContext::createGraphicsContext(traits.get());

    // Init Master Camera for this View
    osg::ref_ptr<osg::Camera> camera = mViewer->getCamera();

    // Assign Graphics Context to the Camera
    camera->setGraphicsContext(gc);

    // Set the viewport for the Camera
    camera->setViewport(new osg::Viewport(traits->x, traits->y, traits->width, traits->height));

    // Set projection matrix and camera attribtues
    camera->setClearMask(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    camera->setClearColor(osg::Vec4f(0.2f, 0.2f, 0.4f, 1.0f));
    camera->setProjectionMatrixAsPerspective(
        30.0f, static_cast<double>(traits->width)/static_cast<double>(traits->height), 1.0, 1000.0);

    // Add the Camera to the Viewer
    //mViewer->addSlave(camera.get());
    mViewer->setCamera(camera.get());

    // Add the Camera Manipulator to the Viewer
    mViewer->setCameraManipulator(keyswitchManipulator.get());

    // Set the Scene Data
    mViewer->setSceneData(mRoot.get());

	InitAxis(traits->width, traits->height);

    // Realize the Viewer
    mViewer->realize();

    // Correct aspect ratio
    /*double fovy,aspectRatio,z1,z2;
    mViewer->getCamera()->getProjectionMatrixAsPerspective(fovy,aspectRatio,z1,z2);
    aspectRatio=double(traits->width)/double(traits->height);
    mViewer->getCamera()->setProjectionMatrixAsPerspective(fovy,aspectRatio,z1,z2);*/
}

void cOSG::PreFrameUpdate()
{
    // Due any preframe updates in this routine
}

void cOSG::PostFrameUpdate()
{
    // Due any postframe updates in this routine
}

osg::Group *cOSG::InitOSGFromDb()
{
	DbModel::Util^ util = gcnew DbModel::Util();
	try {
		util->init(gcnew String(m_ModelName.c_str()), false);
		NHibernate::ISession^ session = util->SessionFactory->OpenSession();
		try {
			NHibernate::ITransaction^ tx = session->BeginTransaction();
			try {
				osg::Group* group = new osg::Group;
				group->addChild(CreateCylinders(session));
				group->addChild(CreateCone(session));
				group->addChild(CreateBoxs(session));
				group->addChild(CreateCircularTorus(session));
				group->addChild(CreateSnout(session));
				group->addChild(CreateDish(session));
				tx->Commit();
				return group;
			}
			catch (Exception ^e) {
				tx->Rollback();
				throw;
			}
		}
		finally {
			session->Close();
		}
	}
	finally {
		util->~Util();
	}

	return NULL;
}

inline void Point2Vec3(Point^ pnt, osg::Vec3 &vec)
{
	vec[0] = pnt->X;
	vec[1] = pnt->Y;
	vec[2] = pnt->Z;
}

osg::Node* cOSG::CreateCylinders(NHibernate::ISession^ session)
{
	osg::Geode *pCylinders = new osg::Geode();
	//osg::Group *pCylinders = new osg::Group();
	IList<Cylinder^>^ cylList = session->CreateQuery("from Cylinder")->List<Cylinder^>();
	osg::Vec3 center, dir;
	//for each (Cylinder^ cyl in cylList) {
	for (int i = 0; i < cylList->Count; ++i) {
		Cylinder^ cyl = cylList->default[i];
		Point2Vec3(cyl->Org, center);
		Point2Vec3(cyl->Height, dir);
		float height = dir.length();

		osg::Matrixf matrix = osg::Matrixf::rotate(osg::Z_AXIS, dir);
		osg::Quat quat;
		quat.set(matrix);

		osg::Cylinder *pOsgCyl = new osg::Cylinder(center + dir / 2.0, safe_cast<float>(cyl->Radius), height);
		pOsgCyl->setRotation(quat);

		osg::ShapeDrawable *pShape = new osg::ShapeDrawable(pOsgCyl, mHints);
		pCylinders->addDrawable(pShape);

		//pCylinders->addChild(BuildCylinder(cyl));

		//CreatePoint(center, 0);
		//CreatePoint(center + osg::Z_AXIS * height, 1);
		//CreatePoint(center + dir, 2);
	}

	return pCylinders;
}

osg::Node* cOSG::CreateCone(NHibernate::ISession^ session)
{
	osg::Geode *pCones = new osg::Geode();
	IList<Cone^>^ coneList = session->CreateQuery("from Cone")->List<Cone^>();
	osg::Vec3 center, dir;
	for (int i = 0; i < coneList->Count; ++i)
	{
		Cone^ cone = coneList->default[i];
		Point2Vec3(cone->Org, center);
		Point2Vec3(cone->Height, dir);
		float height = dir.length();

		osg::Matrixf matrix = osg::Matrixf::rotate(osg::Z_AXIS, dir);
		osg::Quat quat;
		quat.set(matrix);

		osg::Cone *pOsgCyl = new osg::Cone(center + dir / 2.0, safe_cast<float>(cone->Radius), height);
		pOsgCyl->setRotation(quat);

		osg::ShapeDrawable *pShape = new osg::ShapeDrawable(pOsgCyl, mHints);
		pCones->addDrawable(pShape);
	}
	return pCones;
}

osg::Geode * cOSG::CreateBoxs(NHibernate::ISession^ session)
{
	osg::Geode *pBoxs = new osg::Geode();
	IList<Box^>^ boxList = session->CreateQuery("from Box")->List<Box^>();
	osg::Vec3 org, xlen, ylen, zlen;
	for (int i = 0; i < boxList->Count; ++i) {
		Box^ box = boxList->default[i];
		Point2Vec3(box->Org, org);
		Point2Vec3(box->XLen, xlen);
		Point2Vec3(box->YLen, ylen);
		Point2Vec3(box->ZLen, zlen);

		osg::Vec3 center = org + xlen / 2.0 + ylen / 2.0 + zlen / 2.0;
		osg::Box *pOsgBox = new osg::Box(center, xlen.length(), ylen.length(), zlen.length());

		osg::Matrixf matrix = osg::Matrixf::rotate(osg::Z_AXIS, zlen);
		osg::Vec3 y = matrix.preMult(osg::Y_AXIS);
		matrix *= osg::Matrixf::rotate(y, ylen);
		osg::Quat quat;
		quat.set(matrix);
		pOsgBox->setRotation(quat);

		osg::ShapeDrawable *pShape = new osg::ShapeDrawable(pOsgBox, mHints);
		pBoxs->addDrawable(pShape);
	}
	
	return pBoxs;
}

osg::Node* cOSG::CreateCircularTorus(NHibernate::ISession^ session)
{
	osg::Group *pCts = new osg::Group();
	IList<CircularTorus^>^ ctList = session->CreateQuery("from CircularTorus")->List<CircularTorus^>();
	for (int i = 0; i < ctList->Count; ++i) {
		CircularTorus^ ct = ctList->default[i];
		pCts->addChild(BuildCircularTorus(ct));
		try
		{
			pCts->addChild(BuildCircularTorus(ct));
		}
		catch (Standard_ConstructionError &e)
		{
			AfxMessageBox(e.GetMessageString(), MB_OK | MB_ICONERROR);
		}
	}
	return pCts;
}

osg::Node* cOSG::CreateSnout(NHibernate::ISession^ session)
{
	osg::Group *pSnouts = new osg::Group();
	IList<Snout^>^ snoutList = session->CreateQuery("from Snout")->List<Snout^>();
	for (int i = 0; i < snoutList->Count; ++i) {
		Snout^ snout = snoutList->default[i];
		pSnouts->addChild(BuildSnout(snout));
	}
	return pSnouts;
}

osg::Node* cOSG::CreateDish(NHibernate::ISession^ session)
{
	osg::Group *pDish = new osg::Group();
	IList<Dish^>^ dishList = session->CreateQuery("from Dish")->List<Dish^>();
	for (int i = 0; i < dishList->Count; ++i) {
		Dish^ dish = dishList->default[i];
		try
		{
			pDish->addChild(BuildDish(dish));
		}
		catch (Standard_ConstructionError &e)
		{
			AfxMessageBox(e.GetMessageString(), MB_OK | MB_ICONERROR);
		}
	}
	return pDish;
}

void cOSG::CreatePoint(const osg::Vec3 &pos, int idx)
{
	if (mPoints == NULL)
		mPoints = new osg::Geode();
	osg::Sphere *pSphere = new osg::Sphere(pos, 5.0f);
	osg::ShapeDrawable *pShape = new osg::ShapeDrawable(pSphere, mHints);
	osg::Vec4 col(1, 0, 0, 0);
	switch (idx)
	{
	case 0:
		col = osg::Vec4(1, 0, 0, 0);
		break;
	case 1:
		col = osg::Vec4(0, 1, 0, 0);
		break;
	case 2:
		col = osg::Vec4(0, 0, 1, 0);
		break;
	default:
		break;
	}
	pShape->setColor(col);
	mPoints->addDrawable(pShape);
}

void cOSG::InitAxis(double width, double height)
{
	//����������
	Axescamera = new osg::Camera;
	Axescamera->setProjectionMatrix(osg::Matrix::ortho2D(-1.5, width / 50, -1.5, height / 50));
	Axescamera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
	Axescamera->setClearMask(GL_DEPTH_BUFFER_BIT);
	Axescamera->setRenderOrder(osg::Camera::POST_RENDER);
	Axescamera->setUpdateCallback(new AxesCallback(this));
	std::string path = "axes.ive";
	osg::ref_ptr<osg::Node> axes = osgDB::readNodeFile(path);
	Axescamera->addChild(axes);
	mRoot->addChild(Axescamera);
}

void cOSG::SaveAs(const TCHAR *filename)
{
	osgDB::writeNodeFile(*mRoot, filename);
}



/*void cOSG::Render(void* ptr)
{
    cOSG* osg = (cOSG*)ptr;

    osgViewer::Viewer* viewer = osg->getViewer();

    // You have two options for the main viewer loop
    //      viewer->run()   or
    //      while(!viewer->done()) { viewer->frame(); }

    //viewer->run();
    while(!viewer->done())
    {
        osg->PreFrameUpdate();
        viewer->frame();
        osg->PostFrameUpdate();
        //Sleep(10);         // Use this command if you need to allow other processes to have cpu time
    }

    // For some reason this has to be here to avoid issue: 
    // if you have multiple OSG windows up 
    // and you exit one then all stop rendering
    AfxMessageBox("Exit Rendering Thread");

    _endthread();
}*/

CRenderingThread::CRenderingThread( cOSG* ptr )
:   OpenThreads::Thread(), _ptr(ptr), _done(false)
{
}

CRenderingThread::~CRenderingThread()
{
    _done = true;
    while( isRunning() )
        OpenThreads::Thread::YieldCurrentThread();
}

void CRenderingThread::run()
{
    if ( !_ptr )
    {
        _done = true;
        return;
    }

    osgViewer::Viewer* viewer = _ptr->getViewer();
    do
    {
        _ptr->PreFrameUpdate();
        viewer->frame();
        _ptr->PostFrameUpdate();
    } while ( !testCancel() && !viewer->done() && !_done );
}