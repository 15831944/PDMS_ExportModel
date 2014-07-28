// PDSqutorus1.h: interface for the PDSqutorus1 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PDSQUTORUS1_H__1CCAF625_0496_4E57_BE19_497B4B45E7F3__INCLUDED_)
#define AFX_PDSQUTORUS1_H__1CCAF625_0496_4E57_BE19_497B4B45E7F3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PDPrimary3D.h"


class PDSqutorus1 : public PDPrimary3D  
{
public:
	ACRX_DECLARE_MEMBERS(PDSqutorus1);

	PDSqutorus1(bool HasSnap = false);
  // angleΪ�Ƕȣ�[0,360]��
	PDSqutorus1( AcGePoint3d p, AcGePoint3d p1, AcGeVector3d normalP2,
		double l1,double w1,double l2,double w2,
		double angle, int n = 20, bool HasSnap = false,int CorrType = 1 /*0-����ϵ��1-����ϵ*/);
	virtual ~PDSqutorus1();

private:
	double m_dLength1,m_dWidth1,m_dLength2,m_dWidth2,m_dDiameter;
	double m_dAngle;
	AcGePoint3d m_ptP,m_ptP1;
  AcGeVector3d m_normalP2;
  	Adesk::UInt32 m_nN;
    AcGeVector3d m_v3; //��һ���������ж�������ϵ

public:
	virtual void createBody();
	Acad::ErrorStatus getVertices(int Precision, AcGePoint3dArray& vertexArray, AcGeIntArray &stdIdx, int &actPrecision) const; 
	Acad::ErrorStatus getVertices(int Precision, AcGePoint3dArray& vertexArray) const; 
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
	virtual Acad::ErrorStatus  explodeToSurface(AcDbVoidPtrArray& entitySet) const;


	Acad::ErrorStatus getpointP(AcGePoint3d& ptP);
	Acad::ErrorStatus getpointP1(AcGePoint3d& ptP1);
	AcGeVector3d getNormalP2() const;
	Acad::ErrorStatus getLength1(double& length1);
	Acad::ErrorStatus getLength2(double& length2);
	Acad::ErrorStatus getWidth1(double& width1);
	Acad::ErrorStatus getWidth2(double& width2);
	Acad::ErrorStatus getAngle(double& Angle);  // angleΪ�Ƕȣ�[0,360]��
	Acad::ErrorStatus getDiameter(double& diameter);
	Acad::ErrorStatus getN(Adesk::UInt32& n);

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

	/*!
	 * ��ȡ�յ�����
	 * \return AcGePoint3d
	 */
	AcGePoint3d getEndPoint() const;


	//  [9/5/2007 suzhiyong]
	virtual Acad::ErrorStatus explodeTo3DSolid(AcDb3dSolid* &p3dSolid) const;
	AcGeVector3d getEndCenVect() const;

	Acad::ErrorStatus setParameters(AcGePoint3d ptP,AcGePoint3d ptP1,AcGeVector3d normalP2,
		                            double length1, double length2, double width1,
									double width2, double Angle, double diameter,
									Adesk::UInt32 n,int CorrType = 1 /*0-����ϵ��1-����ϵ*/);// angleΪ�Ƕȣ�[0,360]��

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
MAKE_ACDBOPENOBJECT_FUNCTION(PDSqutorus1);

#endif // !defined(AFX_PDSQUTORUS1_H__1CCAF625_0496_4E57_BE19_497B4B45E7F3__INCLUDED_)
