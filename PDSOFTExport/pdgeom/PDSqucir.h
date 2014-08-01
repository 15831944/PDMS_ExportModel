// PDSqucir.h: interface for the PDSqucir class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PDSQUCIR_H__1AA9CC4F_A723_41EC_8795_4E8983C2CA60__INCLUDED_)
#define AFX_PDSQUCIR_H__1AA9CC4F_A723_41EC_8795_4E8983C2CA60__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PDPrimary3D.h"


class PDSqucir : public PDPrimary3D  
{
public:
	struct SquCirInfo
	{
		AcGePoint3d cirCen;			//!< ��ԲԲ��
		AcGePoint3d squCen;			//!< �췽����
		AcGePoint3d midCen;			//!< ��ԲԲ�ĺ��췽���������е�
		AcGePoint3d orhtpt;			//!< ��ԲԲ�����췽�ϵ�ͶӰ

		AcGeVector3d normal;		//!< �췽�͵�Բ�ķ���
		AcGeVector3d vLength;		//!< �췽���ȷ���

		double length;				//!< �췽����,��vLength��Ӧ
		double width;				//!< �췽���

		double radius;				//!< ��Բ�뾶
	};
public:
	ACRX_DECLARE_MEMBERS(PDSqucir);

	PDSqucir(bool HasSnap = false);
	PDSqucir(AcGePoint3d p1,AcGeVector3d v1,double l,double w,
				AcGePoint3d p2,AcGeVector3d v2,double r,int precision = 12,
				bool HasSnap = false,int CorrType = 1/* 0: ������ϵ��1: ����ϵ*/);
	virtual ~PDSqucir();

private:
	AcGePoint3d m_ptP1,m_ptP2;
	AcGeVector3d m_VectSqu,m_VectCir;
	double m_dLength,m_dWidth,m_dRadius;
	Adesk::UInt32 m_nPrecision;


	//version 2
	AcGeVector3d  m_VectW;
	double m_dMaxLength;
public:
	virtual void createBody();
	Acad::ErrorStatus getVertices(int Precision, AcGePoint3dArray& vertexArray, 
                                          AcGeIntArray &stdIdx, int &actPrecision) const;
	Acad::ErrorStatus getVertices(int Precision, AcGePoint3dArray& vertexArray) const;
#ifdef _OBJECTARX2010_
	virtual Adesk::Boolean subWorldDraw(AcGiWorldDraw* mode);
	virtual Acad::ErrorStatus subTransformBy(const AcGeMatrix3d &xform);
	virtual void subList() const;
	virtual Acad::ErrorStatus subGetGeomExtents(AcDbExtents& extents) const;
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
	virtual Acad::ErrorStatus getGeomExtents(AcDbExtents& extents) const;
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
	void getActDivid(int Precision, AcGeDoubleArray &dividDbl, AcGeIntArray &stdIdx) const;//added by linlin 20050818


    //////////// adding function
	Acad::ErrorStatus getgrippoints(AcGePoint3dArray& gripArray) const;

	const AcGePoint3d &getRectOrg() const;
	const AcGePoint3d &getCircCenter() const;
	double getLength() const;
	double getWidth() const;
	double getRadius() const;
	Acad::ErrorStatus getprecision(Adesk::UInt32& precision);
	const AcGeVector3d &getVectCir() const;
	const AcGeVector3d &getVectSqu() const;
	const AcGeVector3d &getVectWidth() const;

	/*!
	 * ��ȡSquCirInfo��Ϣ
	 * \return SquCirInfo
	 */
	SquCirInfo getSquCirInfo() const;

	Acad::ErrorStatus setParameters(AcGePoint3d ptP1,AcGePoint3d ptP2,
		                            double length,double width,double radius,
                                    Adesk::UInt32 precision,AcGeVector3d vectCir,
                                    AcGeVector3d vectSqu,
									 int CorrType = 1/* 0: ������ϵ��1: ����ϵ*/);
	Acad::ErrorStatus getRightHandCoord(AcGePoint3d &p1, 
                                        AcGeVector3d &vlength, 
                                        AcGeVector3d &vcir, 
                                        AcGeVector3d &vwidth, 
                                        double &length, 
                                        double &width) const;
	double GetMaxLength();

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
MAKE_ACDBOPENOBJECT_FUNCTION(PDSqucir);

#endif // !defined(AFX_PDSQUCIR_H__1AA9CC4F_A723_41EC_8795_4E8983C2CA60__INCLUDED_)
