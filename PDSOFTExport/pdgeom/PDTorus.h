// PDTorus.h: interface for the PDTorus class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PDTORUS_H__3434182C_8E65_4EC1_8708_4FB90733A9B0__INCLUDED_)
#define AFX_PDTORUS_H__3434182C_8E65_4EC1_8708_4FB90733A9B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PDPrimary3D.h"


class PDTorus : public PDPrimary3D  
{
public:
	ACRX_DECLARE_MEMBERS(PDTorus);

	PDTorus(bool HasSnap = false);
	PDTorus(const AcGePoint3d &center, const AcGePoint3d &p1, 
            const AcGePoint3d &p2, double dia1, double dia2, int d,
			int prearc = PRIMARY3D_DEFAULT_PRECISION, 
            int precir = PRIMARY3D_DEFAULT_PRECISION, 
            bool HasSnap = false,int CorrType = 1 /*0-����ϵ��1-����ϵ*/);
	virtual ~PDTorus();

private:
	virtual void createBody();
	double m_dDiameter1,m_dDiameter2;
	Adesk::UInt32 m_nDirection;
	AcGePoint3d m_ptCenter,m_ptP1,m_ptP2;
	Adesk::UInt32 m_nprecisionArc,m_nprecisionCir;
  AcGeVector3d m_v3; //��һ���������ж�������ϵ

public:
    Acad::ErrorStatus getVertices(int precisionArc, int precisionCir, 
                                  AcGePoint3dArray& vertexArray, 
                                  AcGeIntArray &stdArcIdx, AcGeIntArray &stdCirIdx, 
                                  int &actPrecisionArc, int &actPrecisionCir) const;
	Acad::ErrorStatus getVertices(int precisionArc, int precisionCir, AcGePoint3dArray& vertexArray) const;

#ifdef _OBJECTARX2010_
	virtual Adesk::Boolean subWorldDraw(AcGiWorldDraw* mode);
	virtual Acad::ErrorStatus subTransformBy(const AcGeMatrix3d &xform);
	virtual void subList() const;// added by linlin 20080812
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
	virtual void list() const;// added by linlin 20080812
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


    // ȡ�ú��ʵ��ʷ־��ȣ����ʵ���С�����ʷ־��Ⱦͻ�ͣ����ʵ��ϴ����ʷ�
    // ���Ȳ�����ʵ���޶����ʷ־���m_dDividPrecision��
    virtual int getMaxPrecision(AcGiWorldDraw *mode) const;

    // ȡ�ú��ʵ��ʷ־��ȣ����ʵ���С�����ʷ־��Ⱦͻ�ͣ����ʵ��ϴ����ʷ�
    // ���Ȳ�����ʵ���޶����ʷ־���m_nprecisionArc��m_nprecisionCir��
    int getMaxPrecisionArc(AcGiWorldDraw *mode) const;
    int getMaxPrecisionCir(AcGiWorldDraw *mode) const;
	AcGePoint3dArray getPtOnCentAix(int Precision);
	const AcGePoint3d &getCenter() const;
	const AcGePoint3d &getP1() const;
	const AcGePoint3d &getP2() const;
	double getDiameter1() const;
	double getDiameter2() const;
	Adesk::UInt32 getDirection() const;
	Adesk::UInt32 getprecisionArc() const;
	Adesk::UInt32 getprecisionCir() const;

	Acad::ErrorStatus setParameters(const AcGePoint3d &center, 
                                    const AcGePoint3d &p1, 
                                    const AcGePoint3d &p2, 
                                    double dia1, double dia2, int d,
                                    int prearc = PRIMARY3D_DEFAULT_PRECISION, 
                                    int precir = PRIMARY3D_DEFAULT_PRECISION,
                                    int CorrType = 1 /*0-����ϵ��1-����ϵ*/);

    // ȡ��Բ����㵽Բ�����ĵľ���
    double getStartCenDist() const;
    // ȡ��Բ���յ㵽Բ�����ĵľ���
    double getEndCenDist() const;
    // ȡ��Բ�����ĵ�Բ������ʸ��
    AcGeVector3d getStartCenVect() const;
    // ȡ��Բ�����ĵ�Բ���յ��ʸ��
    AcGeVector3d getEndCenVect() const;
    // ȡ��Բ���ķ�ʸ
    AcGeVector3d getNormal() const;
    // ȡ��Բ����ɨ���ĽǶ�
    double getAngle() const;

	/*!
	 * ȡ���յ�����
	 * \return AcGePoint3d
	 */
	AcGePoint3d getEndPoint() const;

	/*!
	 * ��ȡ��㼴m_ptP1���淨��
	 * \return  AcGeVector3d
	 */
	AcGeVector3d getStartPlaneNormal() const;

	/*!
	 * ��ȡ�յ㼴m_ptP2���淨��
	 * \return  AcGeVector3d
	 */
	AcGeVector3d getEndPlaneNormal() const;

    Acad::ErrorStatus explodeToSurface(AcDbVoidPtrArray& entitySet) const;

	//  [9/5/2007 suzhiyong]
	virtual Acad::ErrorStatus explodeTo3DSolid(AcDb3dSolid* &p3dSolid) const;

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
MAKE_ACDBOPENOBJECT_FUNCTION(PDTorus);

#endif // !defined(AFX_PDTORUS_H__3434182C_8E65_4EC1_8708_4FB90733A9B0__INCLUDED_)
