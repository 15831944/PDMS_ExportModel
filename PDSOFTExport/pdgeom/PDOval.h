// PDOval.h: interface for the PDOval class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PDOVAL_H__2A74E268_7791_41B8_83C0_1E5E27B3555D__INCLUDED_)
#define AFX_PDOVAL_H__2A74E268_7791_41B8_83C0_1E5E27B3555D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PDPrimary3D.h"


class PDOval : public PDPrimary3D  
{
public:
	ACRX_DECLARE_MEMBERS(PDOval);

	PDOval(bool HasSnap = false);
	PDOval(double lengthA, double lengthB, double lengthR, 
           const AcGePoint3d pt, const AcGeVector3d vect, 
           Adesk::UInt32 precisionA = PRIMARY3D_DEFAULT_PRECISION, 
           Adesk::UInt32 precisionB = PRIMARY3D_DEFAULT_PRECISION, 
           bool HasSnap = false);
	virtual ~PDOval();

private:
	double m_dlengthA, m_dlengthB, m_dlengthR;
	AcGePoint3d m_ptCenter;
	AcGeVector3d m_vect;
	Adesk::UInt32 m_nprecisionA;  //�����ʷ־���
    Adesk::UInt32 m_nprecisionB;  //γ���ʷ־���

public:
	/*---------------------------------------------------------------------------
     * ����: _make_eqovalpt
     * ����: ��� "���豸�����ͷ�ϻ�����" �Ĺ���
     * ע��: ��
    */
    int   _make_eqovalpt(double lengthR,AcGeVector3d vec,ads_point pt,ads_point normal) ;
    Acad::ErrorStatus getVertices(int precisionA, int precisionB, 
                                  AcGePoint3dArray &vertexArray, 
                                  AcGeIntArray &stdBIdx, 
                                  int &actPrecisionA, int &actPrecisionB) const;
	Acad::ErrorStatus getVertices(int precisionA, int precisionB, 
		AcGePoint3dArray &vertexArray) const;

	/*!
	 * ��ȡm_vect��Ax��Χ�ɵ��ķ�֮һ��Բ�ϵĵ�
	 * \param [in] precisionA 
	 * \param [in] xAxis 
	 * \param [in/out] vertexArray 
	 * \precondition xAxis �� m_vect ����
	 * \return
	 */
	Acad::ErrorStatus getVertices(const int& precisionA, const AcGeVector3d& xAxis, 
								  AcGePoint3dArray & vertexArray) const;
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
	virtual Acad::ErrorStatus subMoveGripPointsAt(const AcDbIntArray& indices,
		const AcGeVector3d& offset);
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
	virtual Acad::ErrorStatus moveGripPointsAt(const AcDbIntArray& indices,
		const AcGeVector3d& offset);
#endif

	virtual Acad::ErrorStatus	dwgInFields(AcDbDwgFiler* filer);
	virtual Acad::ErrorStatus	dwgOutFields(AcDbDwgFiler* filer) const;
	virtual Acad::ErrorStatus	dxfInFields(AcDbDxfFiler* filer);
	virtual Acad::ErrorStatus	dxfOutFields(AcDbDxfFiler* filer) const;

	////// adding function///
	Acad::ErrorStatus getgrippoints(AcGePoint3dArray& gripArray) const;

    Acad::ErrorStatus setParameters(double lengthA, double lengthB, 
        double lengthR, const AcGePoint3d pt, const AcGeVector3d vect, 
        Adesk::UInt32 precisionA = PRIMARY3D_DEFAULT_PRECISION, 
        Adesk::UInt32 precisionB = PRIMARY3D_DEFAULT_PRECISION);

	AcGePoint3d getpointCenter() const;
	double getlengthA() const;
	double getlengthB() const;
	double getlengthR() const;
	Adesk::UInt32 getprecisionA() const;
	Adesk::UInt32 getprecisionB() const;
	AcGeVector3d getVect() const;
    // ȡ�������ͷ�ĸ߶�
    double getOvalHeight() const;
    // ȡ����Բ��Բ��
    AcGePoint3d getEllipseCen() const;

    // ȡ�ú��ʵ��ʷ־��ȣ����ʵ���С�����ʷ־��Ⱦͻ�ͣ����ʵ��ϴ����ʷ�
    // ���Ȳ�����ʵ���޶����ʷ־���m_dDividPrecision��
    virtual int getMaxPrecision(AcGiWorldDraw *mode) const;

    // ȡ�ú��ʵ��ʷ־��ȣ����ʵ���С�����ʷ־��Ⱦͻ�ͣ����ʵ��ϴ����ʷ�
    // ���Ȳ�����ʵ���޶����ʷ־���m_nprecisionA��m_nprecisionB��
    int getMaxPrecisionA(AcGiWorldDraw *mode) const;
    int getMaxPrecisionB(AcGiWorldDraw *mode) const;

    virtual void createBody();

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
  virtual bool isValidData(double &f); //����Ƿ��Ա���ݾ��ǺϷ�����, �����س�����

};
MAKE_ACDBOPENOBJECT_FUNCTION(PDOval);

#endif // !defined(AFX_PDOVAL_H__2A74E268_7791_41B8_83C0_1E5E27B3555D__INCLUDED_)
