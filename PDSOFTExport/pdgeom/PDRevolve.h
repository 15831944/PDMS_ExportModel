// PDRevolve.h: interface for the PDRevolve class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(PDREVOLVE_H)
#define PDREVOLVE_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PDPrimary3D.h"

struct _t_Arc_params
{
public:
	double m_dRadius;
	AcGeVector3d m_vectStart;
	AcGePoint3d m_cenPt;
	AcGeVector3d m_normal;
};
class PDRevolve : public PDPrimary3D
{
public:
	ACRX_DECLARE_MEMBERS(PDRevolve); 

	PDRevolve();
	PDRevolve(const AcGePoint3d& AxisPt, const AcGeVector3d& AxisVec, 
              const std::vector<t_PolylineVertex>& PtArrint, int Precision = PRIMARY3D_DEFAULT_PRECISION, bool HasSnap = false);

	virtual ~PDRevolve();
public:
#ifdef _OBJECTARX2010_
	virtual Adesk::Boolean subWorldDraw(AcGiWorldDraw* mode);
	virtual Acad::ErrorStatus	subTransformBy(const AcGeMatrix3d &xform);
	virtual void				subList() const;
	virtual Acad::ErrorStatus   subGetGeomExtents(AcDbExtents& extents) const;
	virtual Acad::ErrorStatus	subExplode(AcDbVoidPtrArray& entitySet) const;
	virtual Acad::ErrorStatus   subGetOsnapPoints(
		AcDb::OsnapMode     osnapMode,
		Adesk::GsMarker     gsSelectionMark,
		const AcGePoint3d&  pickPoint,
		const AcGePoint3d&  lastPoint,
		const AcGeMatrix3d& viewXform,
		AcGePoint3dArray&   snapPoints,
		AcDbIntArray &   geomIds) const;
#else
	virtual Adesk::Boolean worldDraw(AcGiWorldDraw* mode);
	virtual Acad::ErrorStatus	transformBy(const AcGeMatrix3d &xform);
	virtual void				list() const;
	virtual Acad::ErrorStatus   getGeomExtents(AcDbExtents& extents) const;
	virtual Acad::ErrorStatus	explode(AcDbVoidPtrArray& entitySet) const;
	virtual Acad::ErrorStatus	getOsnapPoints(AcDb::OsnapMode osnapMode,
		int gsSelectionMark,
		const AcGePoint3d&    pickPoint,
		const AcGePoint3d&    lastPoint,
		const AcGeMatrix3d&   viewXform,
		AcGePoint3dArray&     snapPoints,
		AcDbIntArray&         geomIds) const;
#endif

	virtual Acad::ErrorStatus	dwgInFields(AcDbDwgFiler* filer);
	virtual Acad::ErrorStatus	dwgOutFields(AcDbDwgFiler* filer) const;
	virtual Acad::ErrorStatus	dxfInFields(AcDbDxfFiler* filer);
	virtual Acad::ErrorStatus	dxfOutFields(AcDbDxfFiler* filer) const;

	// ȡ�ú��ʵ��ʷ־��ȣ����ʵ���С�����ʷ־��Ⱦͻ�ͣ����ʵ��ϴ����ʷ�
	// ���Ȳ�����ʵ���޶����ʷ־���m_dDividPrecision��
	virtual int getMaxPrecision(AcGiWorldDraw *mode) const;

	// ��ת����һ��
	AcGePoint3d               getPtAxis() const;	
	// ��ת�᷽��
	AcGeVector3d              getVecAxis() const;		
	// ��ת����Ķ���
	std::vector<t_PolylineVertex>  getPolylineVertex() const;
	// ��ת�Ƕ�, ���ȱ�ʾ
	double					  getAngle() const;

	Acad::ErrorStatus		  setVal(const AcGePoint3d &ptAxis, const AcGeVector3d &vecAxis, const std::vector<t_PolylineVertex>& val);

	Acad::ErrorStatus getVertices(int Precision, std::vector<AcGePoint3dArray>& vertexArray, 
								  AcGeIntArray &stdIdx, int &actPrecision) const;
	Acad::ErrorStatus getVertices(int Precision, std::vector<AcGePoint3dArray>& vertexArray) const;

    virtual void createBody();

	virtual Acad::ErrorStatus explodeTo3DSolid(AcDb3dSolid* &p3dSolid) const;

private:
	// ���е�ͷ����Ϊ��������ϵ������
	AcGePoint3d               m_ptAxis;			// ��ת����һ��
    AcGeVector3d              m_vecAxis;		// ��ת�᷽��
	double					  m_angle;			// ��ת�Ƕ�
	std::vector<t_PolylineVertex>  m_polylineVertex; // ��ת����Ķ���
	std::vector<_t_Arc_params> m_CirclePts;//һ��Բ����������
	double m_dMaxRadius;
private:

#ifndef _OBJECTARX2010_
	void *operator new[](unsigned nSize) { return 0; }
	void operator delete[](void *p) {};
	void *operator new[](unsigned nSize, const char *file, int line) { return 0; }
#endif

	void  GetCirclePtsAndMaxRadius();

public:
  //zxb,20090113,����audit����ʱֻcheck�����Ա����
  virtual Acad::ErrorStatus audit(AcDbAuditInfo* pAuditInfo);
  virtual void setDefault(); //����ȱʡ�Ķ�������
  virtual bool isValidData(double &f); //����Ƿ��Ա���ݾ��ǺϷ�����, �����س�����

};
MAKE_ACDBOPENOBJECT_FUNCTION(PDRevolve);

#endif // !defined(PDREVOLVE_H)
