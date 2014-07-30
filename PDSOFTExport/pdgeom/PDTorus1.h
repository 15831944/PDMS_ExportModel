// PDTorus1.h: interface for the PDTorus1 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PDTORUS1_H__56A7EFCD_B268_46A1_8CF7_500463001708__INCLUDED_)
#define AFX_PDTORUS1_H__56A7EFCD_B268_46A1_8CF7_500463001708__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PDPrimary3D.h"


class PDTorus1 : public PDPrimary3D  
{
public:
	ACRX_DECLARE_MEMBERS(PDTorus1);

	PDTorus1(bool HasSnap = false);
  // angleΪ�Ƕȣ�[0,360]��
	PDTorus1( AcGePoint3d center, AcGePoint3d p1, AcGePoint3d p2,double dia1,double dia2,double angle,
				int prearc = 20, int precir = 20, bool HasSnap = false,int CorrType = 1 /*0-����ϵ��1-����ϵ*/);
	
	virtual ~PDTorus1();

private:
	double m_dDiameter1,m_dDiameter2;
	double m_dAngle;
	AcGePoint3d m_ptCenter,m_ptP1,m_ptP2;
	Adesk::UInt32 m_nprecisionArc,m_nprecisionCir;
  AcGeVector3d m_v3; //��һ���������ж�������ϵ

public:
	virtual void createBody();
    // ȡ�ú��ʵ��ʷ־��ȣ����ʵ���С�����ʷ־��Ⱦͻ�ͣ����ʵ��ϴ����ʷ�
    // ���Ȳ�����ʵ���޶����ʷ־���m_dDividPrecision��
    virtual int getMaxPrecision(AcGiWorldDraw *mode) const;
    // ȡ�ú��ʵ��ʷ־��ȣ����ʵ���С�����ʷ־��Ⱦͻ�ͣ����ʵ��ϴ����ʷ�
    // ���Ȳ�����ʵ���޶����ʷ־���m_nprecisionArc��m_nprecisionCir��
    int getMaxPrecisionArc(AcGiWorldDraw *mode) const;
    int getMaxPrecisionCir(AcGiWorldDraw *mode) const;  
	double PDTorus1::getStartCenDist() const;	   
    AcGeVector3d getStartCenVect() const;// ȡ��Բ�����ĵ�Բ������ʸ��
	AcGeVector3d getEndCenVect() const;// ȡ��Բ�����ĵ�Բ���յ��ʸ��

// added by linlin 20080812

	  Acad::ErrorStatus getVertices(int precisionArc, int precisionCir, 
                                  AcGePoint3dArray& vertexArray, 
                                  AcGeIntArray &stdArcIdx, AcGeIntArray &stdCirIdx, 
                                  int &actPrecisionArc, int &actPrecisionCir) const;// added by linlin 20080812
	  Acad::ErrorStatus getVertices(int precisionArc, int precisionCir, 
                                  AcGePoint3dArray& vertexArray) const;// added by linlin 20080812

#ifdef _OBJECTARX2010_
	virtual Adesk::Boolean subWorldDraw(AcGiWorldDraw* mode);
	virtual Acad::ErrorStatus subTransformBy(const AcGeMatrix3d &xform);
	virtual void subList() const;
	virtual Acad::ErrorStatus   subGetGeomExtents(AcDbExtents& extents) const;
	virtual Acad::ErrorStatus subExplode(AcDbVoidPtrArray& entitySet) const;
	virtual Acad::ErrorStatus   subGetOsnapPoints(
		AcDb::OsnapMode     osnapMode,
		Adesk::GsMarker     gsSelectionMark,
		const AcGePoint3d&  pickPoint,
		const AcGePoint3d&  lastPoint,
		const AcGeMatrix3d& viewXform,
		AcGePoint3dArray&   snapPoints,
		AcDbIntArray &   geomIds) const;
	virtual Acad::ErrorStatus subGetGripPoints(
		AcGePoint3dArray& gripPoints,
		AcDbIntArray& osnapModes,
		AcDbIntArray& geomIds) const;
#else
	virtual Adesk::Boolean worldDraw(AcGiWorldDraw* mode);
	virtual Acad::ErrorStatus transformBy(const AcGeMatrix3d &xform);
	virtual void list() const;
	virtual Acad::ErrorStatus   getGeomExtents(AcDbExtents& extents) const;
	virtual Acad::ErrorStatus explode(AcDbVoidPtrArray& entitySet) const;
	virtual Acad::ErrorStatus getOsnapPoints(  AcDb::OsnapMode osnapMode,
		int gsSelectionMark,
		const AcGePoint3d&    pickPoint,
		const AcGePoint3d&    lastPoint,
		const AcGeMatrix3d&   viewXform,
		AcGePoint3dArray&     snapPoints,
		AcDbIntArray&         geomIds) const;
	virtual Acad::ErrorStatus getGripPoints(
		AcGePoint3dArray& gripPoints,
		AcDbIntArray& osnapModes,
		AcDbIntArray& geomIds) const;
#endif

	virtual Acad::ErrorStatus	dwgInFields(AcDbDwgFiler* filer);
	virtual Acad::ErrorStatus	dwgOutFields(AcDbDwgFiler* filer) const;
	virtual Acad::ErrorStatus	dxfInFields(AcDbDxfFiler* filer);
	virtual Acad::ErrorStatus	dxfOutFields(AcDbDxfFiler* filer) const;


	const AcGePoint3d &getCenter() const;
	const AcGePoint3d &getP1() const;
	const AcGePoint3d &getP2() const;
	double getDiameter1() const;
	double getDiameter2() const;
	double getAngle() const;  // ����ֵΪ�Ƕȣ�[0,360]��
	Adesk::UInt32 getprecisionArc();
	Adesk::UInt32 getprecisionCir();

	/*!
	 * ��ȡ�յ����� 
	 * \return AcGePoint3d
	 */
	AcGePoint3d getEndPoint() const;

	/*!
	* ��ȡ���ƽ�淨��
	* \return  AcGeVector3d
	*/
	AcGeVector3d getStartPlaneNormal() const;

	/*!
	* ��ȡ�յ�ƽ�淨��
	* \return  AcGeVector3d
	*/
	AcGeVector3d getEndPlaneNormal() const;


	//  [9/5/2007 suzhiyong]
	virtual Acad::ErrorStatus explodeTo3DSolid(AcDb3dSolid* &p3dSolid) const;

	 Acad::ErrorStatus explodeToSurface(AcDbVoidPtrArray& entitySet) const;
	Acad::ErrorStatus setParameters(AcGePoint3d ptCenter,AcGePoint3d ptP1,
		                            AcGePoint3d ptP2, double diameter1, double diameter2,
									double Angle, Adesk::UInt32 precisionArc,
									Adesk ::UInt32 precisionCir,int CorrType = 1 /*0-����ϵ��1-����ϵ*/);

#ifndef _OBJECTARX2010_
private:
	void *operator new[](unsigned nSize) { return 0; }
	void operator delete[](void *p) {};
	void *operator new[](unsigned nSize, const char *file, int line) { return 0; }
#endif

public:
  //zxb,20090113,����audit����ʱֻcheck�����Ա����
  virtual Acad::ErrorStatus audit(AcDbAuditInfo* pAuditInfo);
  virtual void setDefault(); //����ȱʡ�Ķ�������
  virtual bool isValidData(double &f); //����Ƿ��Ա���ݾ��ǺϷ�����,�����س��������
};
MAKE_ACDBOPENOBJECT_FUNCTION(PDTorus1);

#endif // !defined(AFX_PDTORUS1_H__56A7EFCD_B268_46A1_8CF7_500463001708__INCLUDED_)
