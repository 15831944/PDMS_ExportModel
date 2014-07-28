// PDConcone.h: interface for the PDConcone class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PDCONCONE_H__97C51767_32AD_4C04_8F89_2B0616EEAEE7__INCLUDED_)
#define AFX_PDCONCONE_H__97C51767_32AD_4C04_8F89_2B0616EEAEE7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PDPrimary3D.h"


class PDConcone : public PDPrimary3D  
{
public:
	ACRX_DECLARE_MEMBERS(PDConcone);
	PDConcone(bool HasSnap = false);
	PDConcone(const AcGePoint3d &ptStart, const AcGePoint3d &ptEnd, 
              double Diameter1, double Diameter2, 
              int Precision = PRIMARY3D_DEFAULT_PRECISION, 
              bool HasSnap = false);
	virtual ~PDConcone();

public:
	
/*---------------------------------------------------------------------------
* ����: _make_eqovalpt
* ����: ��� "���豸�����ͷ�ϻ�����" �Ĺ���
* ע��: ��
*/
	int  _make_eqovalpt(double lengthR,AcGeVector3d vec,ads_point pt,ads_point normal) ;
    Acad::ErrorStatus getVertices(int Precision, AcGePoint3dArray& vertexArray, 
                                  AcGeIntArray &stdIdx, int &actPrecision) const;
	///////////////////////////////////////////////////////////////////////////////
	///  public overloaded constant  getVertices
	///  <TODO: insert function description here>
	///
	///  @param  Precision int     
	///  @param  vertexArray AcGePoint3dArray &    
	///
	///  @return Acad::ErrorStatus 
	///
	///  @remarks ���øú�����Ҫ��֤�Ѿ��ǵȷ�
	///
	///  @see 
	///
	///  @author BeJing ZhongKe Fulong, shinf @date 2007-1-5
	/// �����пƸ���������������޹�˾��PDSOFT��Ʒ��ҵ��--�з�
	///////////////////////////////////////////////////////////////////////////////
	Acad::ErrorStatus getVertices(int Precision, AcGePoint3dArray& vertexArray/*, AcGeVector3d & faceVects*/) const;
#ifdef _OBJECTARX2010_
	virtual Adesk::Boolean subWorldDraw(AcGiWorldDraw* mode);
	virtual Acad::ErrorStatus subTransformBy(const AcGeMatrix3d &xform);
	virtual void  subList() const;
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
	virtual void  list() const;
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


	Acad::ErrorStatus getgrippoints(AcGePoint3dArray& gripArray) const;

	Acad::ErrorStatus setParameters(const AcGePoint3d &ptStart, 
                                    const AcGePoint3d &ptEnd, 
                                    double Diameter1, double Diameter2, 
                                    int Precision = PRIMARY3D_DEFAULT_PRECISION);

	AcGePoint3d getpointStart() const;
	AcGePoint3d getpointEnd() const;
	double getDiameter1() const;
	double getDiameter2() const;

    // ȡ�ú��ʵ��ʷ־��ȣ����ʵ���С�����ʷ־��Ⱦͻ�ͣ����ʵ��ϴ����ʷ�
    // ���Ȳ�����ʵ���޶����ʷ־���m_dDividPrecision��
    virtual int getMaxPrecision(AcGiWorldDraw *mode) const;

    virtual void createBody();

	//  [9/5/2007 suzhiyong]
	virtual Acad::ErrorStatus explodeTo3DSolid(AcDb3dSolid* &p3dSolid) const;

private:
	AcGePoint3d m_ptEnd;
	AcGePoint3d m_ptStart;
	double m_dDiameter1;
	double m_dDiameter2;

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
MAKE_ACDBOPENOBJECT_FUNCTION(PDConcone);

#endif // !defined(AFX_PDCONCONE_H__97C51767_32AD_4C04_8F89_2B0616EEAEE7__INCLUDED_)
