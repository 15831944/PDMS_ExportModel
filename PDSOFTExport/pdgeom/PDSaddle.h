// PDSaddle.h: interface for the PDSaddle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PDSADDLE_H__D9D7F3E9_BD26_4AFD_AA65_82A5590954E3__INCLUDED_)
#define AFX_PDSADDLE_H__D9D7F3E9_BD26_4AFD_AA65_82A5590954E3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PDPrimary3D.h"


class PDSaddle : public PDPrimary3D  
{
public:
	struct SideFace //!< ��¼����m_ptP���ڲ����ϵ��ĸ������Լ�Բ�����˵���е�
	{
		AcGePoint3d originPt;  //!< ��m_ptP;
		AcGePoint3d vertexHeight;   //!< m_ptP�ظ߶ȣ���Z�򣩵�����Ǹ�����
		AcGePoint3d vertexWidth;	//!< m_ptP�ؿ�ȷ��򵽴�Ķ���
		AcGePoint3d vertexRemain;   //!< ��ȥoriginPt, vertexHeight,  vertexWidth ��ʣ�µ����һ������

		AcGePoint3d nearArcPt; //!< ����vertexHeight�����Բ���˵㣬������vertexHeight��ͬһ����
		AcGePoint3d farArcPt;  //!< ����vertexRemain�����Բ���˵㣬������vertexRemain��ͬһ����
		AcGePoint3d midArcPt;  //!< Բ���е�

		bool flag;  //!< �� flag == true���� nearArcPt == vertexHeight �� farArcPt == vertexRemain��
					//!< ��֮����flag == false, �� nearArcPt != vertexHeight �� farArcPt != vertexRemain
	};

public:
	ACRX_DECLARE_MEMBERS(PDSaddle);

	PDSaddle(bool HasSnap = false);
  // angleΪ�Ƕ�
	PDSaddle( double l,double w,double h,AcGePoint3d p,double angle,double radius,int precision, 
            const AcGeVector3d &insX = AcGeVector3d(1, 0, 0), const AcGeVector3d &insY = AcGeVector3d(0, 1, 0),
			bool HasSnap = false,int CorrType = 1/* 0: ����ϵ��1: ����ϵ*/);

	virtual ~PDSaddle();


private:
	double m_dLength,m_dWidth,m_dHeight,m_dRadius;
	AcGePoint3d m_ptP;
	double m_dAngle;
	Adesk::UInt32 m_nPrecision;

  //version 2
  AcGeVector3d m_insX;  //������X����
  AcGeVector3d m_insY;  //������Y����
  AcGeVector3d m_insZ;  //������Z����
  	

public:
	Acad::ErrorStatus getVertices(int Precision, AcGePoint3dArray& vertexArray, 
                                          AcGeIntArray &stdIdx, int &actPrecision) const;
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

	Acad::ErrorStatus getpointP(AcGePoint3d& ptP);
	Acad::ErrorStatus getangle(double& angle);  // angleΪ�Ƕ�
	Acad::ErrorStatus getlength(double& length);
	Acad::ErrorStatus getheight(double& height);
	Acad::ErrorStatus getwidth(double& width);
	Acad::ErrorStatus getradius(double& radius);
	Acad::ErrorStatus getlengthVwidthV(AcGeVector3d &lengthvect,AcGeVector3d &widthvect) const;
	Acad::ErrorStatus getprecision(Adesk::UInt32& precision);
	Acad::ErrorStatus getInsDir(AcGeVector3d& insX, AcGeVector3d& insY, AcGeVector3d& insZ);

	/*!
	 * ��ȡ���εĶ�λ�㣨��m_ptP�����ڲ�����ĸ����㼰Բ���е�
	 * \return  SideFace
	 */
	SideFace getSideFaceInfo() const;



  Acad::ErrorStatus getRightHandCoord(AcGePoint3d &ori, 
                                        AcGeVector3d &vecx, 
                                        AcGeVector3d &vecy, 
                                        AcGeVector3d &vecz, 
										AcGeVector3d &vlength,
                                        AcGeVector3d &vwidth,
                                        double &length, 
                                        double &width, 
                                        double &height) const;

  	Acad::ErrorStatus setParameters(AcGePoint3d ptP,double angle,double length,
		                            double height,double width,double radius,
									const AcGeVector3d& insX, const AcGeVector3d& insY,	
									Adesk::UInt32 precision,
                                    int CorrType = 1/* 0: ������ϵ��1: ����ϵ*/);

  Acad::ErrorStatus getExtrudePolygonPts(AcGePoint3dArray& vertexArray) const;
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
MAKE_ACDBOPENOBJECT_FUNCTION(PDSaddle);

#endif // !defined(AFX_PDSADDLE_H__D9D7F3E9_BD26_4AFD_AA65_82A5590954E3__INCLUDED_)
