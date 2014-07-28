/////////////////////////////////////////////
// PDPrimary3D custom object.

#if !defined(ARX__PDPRIMARY3D_H__20010918_151458)
#define ARX__PDPRIMARY3D_H__20010918_151458

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <dbents.h>
#include <dbcurve.h>
#include <dbsol3d.h>

#ifdef _OBJECTARX14_
#define   bool   int
#define   true   1
#define   false   0
#endif
#include <amodeler.h>
using namespace AModeler;


#pragma warning(disable: 4275 4251)

/**
  PDPrimary3D���������ϵ��
  PDPrimary3D
      PDBox
          PdsDbPrecomp
          PdsDbSupVirBox
      PDBox1
      PDConcone
      PdsDbConnect
          PdsDbBoltConnect
              PdsDbBolt
              PdsDbNut
              PdsDbWasher
      PDCylinder
          PDScylinder
      PDEcone
      PDOval
      PDPrism
      PDPrism1
      PDRevolve
      PDSaddle
      PDSphere
      PDSpolygon
      PDSqucir
      PDSqucone
      PDSqutorus
      PDSqutorus1
      PDTorus
      PDTorus1
      PDWedge
 */

extern Acad::ErrorStatus addToDb(AcDbEntity *pEnt);
//int getOrbitFlag();

#ifndef PI
#define PI 3.1415926535897932384626433832795L
#endif

#define PRIMARY3D_DEFAULT_PRECISION 32
#define PRIMARY3D_WIREFRAME_LINENUM  8
#define PRIMARY3D_WIREFRAME_LINENUM4  4
#define PRIMARY3D_SIMPLIZE_SCALE 3
#define PRIMARY3D_SIMPLIZE_SCALE4 5
//////////////////////////////////////////////////////////////////////////
//�򻯵ĵȼ�
#ifndef PRIMARY3D_SIMPLIZE_RATE0
#define  PRIMARY3D_SIMPLIZE_RATE0 0 // ����
#define  PRIMARY3D_SIMPLIZE_RATE1 1 // 1����
#define  PRIMARY3D_SIMPLIZE_RATE2 2 // 2 ����
#endif

#define POLYLINEVERTE_FLAG_L   1
#define POLYLINEVERTE_FLAG_A   2
#define POLYLINEVERTE_FLAG_AM   3
#define POLYLINEVERTE_FLAG_LC   4
#define POLYLINEVERTE_FLAG_AC   5
#define POLYLINEVERTE_FLAG_C   6

//�������������GS��� 
//begin::added by szw 2009.11.18
enum BOX_SelectionMarker{
	BOTTOM_PLANE = 1,
	TOP_PLANE,
	FRONT_PLANE,
	LEFT_PLANE,
	RIGHT_PLANE,
	BACK_PLANE
};
//end::added by szw 2009.11.18

struct t_PolylineVertex
{
   // 1��ֱ�ߵ���㣻2��Բ������㣻3��Բ�����м�һ�㣻4�������ߵ����һ�㣬
   // �ö����߷���ҷ��ʹ��ֱ�ߣ�5�������ߵ����һ�㣬�ö����߷���ҷ��ʹ
   // ��Բ������������Բ���ϵ��м�һ�㣻6��Բ�ϵĵ㣨�����������е�����һ��
   Adesk::Int16 m_vertexFlag;
   AcGePoint3d m_vertex;
};

//struct shellData
//{
//	Adesk::UInt32 nbVertex;
//	AcGePoint3dArray pVertexList;
//	Adesk::UInt32 faceListSize;
//	std::vector<Adesk::Int32> pFaceList;
//	AcGiEdgeData *pEdgeData;
//	AcGiFaceData *pFaceData;
//	AcGiVertexData *pVertexData;
//	bool bAutoGenerateNormals;
//
//	shellData() : pEdgeData(NULL), pFaceData(NULL), pVertexData(NULL)
//	{
//	}
//
//	shellData(const shellData &op)
//	{
//		if(this == &op)
//			return ;
//		operator=(op);
//	}
//
//	shellData &operator=(const shellData &op)
//	{
//		if(this == &op)
//			return *this;
//		nbVertex = op.nbVertex;
//		pVertexList = op.pVertexList;
//		faceListSize = op.faceListSize;
//		pFaceList.clear();
//		pFaceList.insert(pFaceList.begin(), op.pFaceList.begin(), op.pFaceList.end());
//		//if(pEdgeData != NULL)
//		//	delete pEdgeData;
//		pEdgeData = op.pEdgeData;
//		//if(pFaceData != NULL)
//		//	delete pFaceData;
//		pFaceData = op.pFaceData;
//		//if(pVertexData != NULL)
//		//	delete pVertexData;
//		pVertexData = op.pVertexData;
//		bAutoGenerateNormals = op.bAutoGenerateNormals;
//		return *this;
//	}
//};

class PDPrimary3D : public AcDbCurve
{
public:

   ACRX_DECLARE_MEMBERS(PDPrimary3D);

   // Constructor / Destructor
   PDPrimary3D(bool HasSnap = false);
   virtual ~PDPrimary3D();

   //{{AFX_ARX_METHODS(PDPrimary3D)
#ifdef _OBJECTARX2010_
   virtual Adesk::Boolean subWorldDraw(AcGiWorldDraw* mode);
   virtual Acad::ErrorStatus subTransformBy(const AcGeMatrix3d& xform);
   virtual void              subList() const;
   virtual Acad::ErrorStatus subGetGeomExtents(AcDbExtents& extents) const;
#else
   virtual Adesk::Boolean worldDraw(AcGiWorldDraw* mode);
   virtual Acad::ErrorStatus transformBy(const AcGeMatrix3d& xform);
   virtual void              list() const;
   virtual Acad::ErrorStatus getGeomExtents(AcDbExtents& extents) const;
#endif
   virtual Acad::ErrorStatus dxfOutFields(AcDbDxfFiler* pFiler) const;
   virtual Acad::ErrorStatus dxfInFields(AcDbDxfFiler* pFiler);
   virtual Acad::ErrorStatus dwgOutFields(AcDbDwgFiler* pFiler) const;
   virtual Acad::ErrorStatus dwgInFields(AcDbDwgFiler* pFiler);
   //}}AFX_ARX_METHODS

   //{{AFX_ARX_DATA_ACCESS(PDPrimary3D)
   Acad::ErrorStatus setDividPrecision(const Adesk::Int32 dDividPrecision);
   Adesk::Int32 dividPrecision() const;
   //}}AFX_ARX_DATA_ACCESS

    ////�����������������Ƿ������׽��////
    bool hasSnap() const;
    void setHasSnap(bool val);

    /** ȡ���Ƿ��������ʷ־���
     * @return bool
     *
     * �����������ʷ־��ȣ�����������Ԫ����ʾ�ٶȣ�����render������
     * ���ɵ�ͼƬ����Ч�������룬�������������ʷ־��ȣ���render��������
     * ��ͼƬЧ���ã�����Ԫ����ʾ�ٶ��п����½���
     */ 
    Adesk::Int16 getCalMaxPrecision() const;
    /** �����Ƿ��������ʷ־���
     * @param val - ���룺�Ƿ��������ʷ־���
     * @return void
     *
     * �����������ʷ־��ȣ�����������Ԫ����ʾ�ٶȣ�����render������
     * ���ɵ�ͼƬ����Ч�������룬�������������ʷ־��ȣ���render��������
     * ��ͼƬЧ���ã�����Ԫ����ʾ�ٶ��п����½���
     */ 
    void setCalMaxPrecision(Adesk::Int16 val);

    // ȡ�ú��ʵ��ʷ־��ȣ����ʵ���С�����ʷ־��Ⱦͻ�ͣ����ʵ��ϴ����ʷ�
    // ���Ȳ�����ʵ���޶����ʷ־���m_dDividPrecision��
    virtual int getMaxPrecision(AcGiWorldDraw *mode) const;
    void getActDivid(int Precision, AcGeDoubleArray &dividDbl, AcGeIntArray &stdIdx) const;

    virtual void createBody();

	virtual Acad::ErrorStatus explodeTo3DSolid(AcDb3dSolid* &p3dSolid) const;

   // ȡ��Amodeler ģ�͵�ʵ��
   const Body* getBody() const;
   // ���Amodelerģ�͵�ʵ��
   Acad::ErrorStatus clearBody();

   Acad::ErrorStatus convertPolyVertexToSegments(const std::vector<t_PolylineVertex> &vertexArr, const AcGeVector3d &norm, AcDbVoidPtrArray &curveSegments) const;
   Acad::ErrorStatus convertPolyVertexToAmodelerData(const std::vector<t_PolylineVertex> &vertexArr, AcGePoint3d* &vertices, PolygonVertexData** &vertexData, 
      int &iVertices, AcGeVector3d &normal) const;
   void getPolylineVertices(AcGePoint3d* vertices, const AcGeDoubleArray &bulge, const AcGeVector3d normal, int isClosed, PolygonVertexData** &vertexData) const;
   double circleRadiusFromBulge(const AcGePoint3d& p1, const AcGePoint3d& p2, double bulge) const;

   static bool isLeftCoord(AcGeVector3d x,AcGeVector3d y, AcGeVector3d z);

   void getSolidInfo(const AcDbObjectId &solidId);
   //void getSolidWorldDrawInfo(const AcDbObjectId &solidId);

protected:
   //{{AFX_ARX_DATA(PDPrimary3D)
   Adesk::Int32 m_dDividPrecision;
   ////����ͳһ���������������ʾ����////
   //}}AFX_ARX_DATA

    ////�����������������Ƿ������׽��////
    Adesk::Int16 m_bHasSnap;

    ////////
   
    //! �Ƿ��������ʷ־���
    /*! �����������ʷ־��ȣ�����������Ԫ����ʾ�ٶȣ�����render������
     *  ���ɵ�ͼƬ����Ч�������룬�������������ʷ־��ȣ���render��������
     *  ��ͼƬЧ���ã�����Ԫ����ʾ�ٶ��п����½���
     */ 
    Adesk::Int16 m_bCalMaxPrecision;

    // version 2
    // version 3 ����m_3dGeom���д洢
    Body m_3dGeom;  // Amodeler ģ�͵�ʵ��
	AcDb3dSolid m_3dSolid;	// AcDb3dSolidʵ��
	// version 4
	std::vector<AcGePoint3dArray> m_ptsArr;	//Brep�����ĵ�

public:
   bool m_no8;      //������8�ȷ�
   int m_drawType;	//��ʾ��ʽ��0��������Body��3dSolid��brep��ʾ��1��Body��ʾ��2��3dSolid��ʾ��3��brep��ʾ

   //std::vector<shellData> m_shelldata;

#ifndef _OBJECTARX2010_
private:
   void *operator new[](unsigned nSize) { return 0; }
   void operator delete[](void *p) {};
   void *operator new[](unsigned nSize, const char *file, int line) { return 0; }
#endif

public:
  virtual void setDefault(); //����ȱʡ�Ķ�������
  virtual bool isValidData(double &f); //����Ƿ��Ա���ݾ��ǺϷ�����,�����س���ĸ�����
};
MAKE_ACDBOPENOBJECT_FUNCTION(PDPrimary3D);

#include <float.h>
inline bool isValidFloat(double f)
{
  int flt = _fpclass(f);
  return ((flt)&_FPCLASS_NN||(flt)&_FPCLASS_NZ||(flt)&_FPCLASS_PZ||(flt)&_FPCLASS_PN)?true:false;
}

Acad::ErrorStatus auditPDPrimary3D(PDPrimary3D *pent, AcDbAuditInfo* pAuditInfo,const TCHAR *prompt);

#endif // !defined(ARX__PDPRIMARY3D_H__20010918_151458)
