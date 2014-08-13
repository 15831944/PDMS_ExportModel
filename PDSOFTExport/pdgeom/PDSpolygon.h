// PDSpolygon.h: interface for the PDSpolygon class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(PDSPOLYGON_H)
#define PDSPOLYGON_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PDPrimary3D.h"


class PDSpolygon : public PDPrimary3D
{
public:
	ACRX_DECLARE_MEMBERS(PDSpolygon); 

  PDSpolygon();

  // Vh��OutPtArr��InPtArrArrΪ�ֲ�����ϵ������
	PDSpolygon(const AcGePoint3d& oriPt, const AcGeVector3d& V1, const AcGeVector3d& V2, 
             const AcGeVector3d& Vh, double H, const AcGePoint3dArray& OutPtArr, 
             const std::vector<AcGePoint3dArray>& InPtArrArr, bool HasSnap = false, int CorrType = 1/* 0: ����ϵ��1: ����ϵ*/);

  // Vh��PtArrΪ�ֲ�����ϵ������
	PDSpolygon(int OutPtNum, const std::vector<int>& InPtNumArr, const AcGePoint3d& oriPt, 
             const AcGeVector3d& V1, const AcGeVector3d& V2, const AcGeVector3d& Vh, 
             double H, const AcGePoint3dArray& PtArr, bool HasSnap = false, int CorrType = 1/* 0: ����ϵ��1: ����ϵ*/);

	// Vh��OutPtArr��InPtArrArrΪ�ֲ�����ϵ������
	PDSpolygon(const AcGePoint3d& oriPt, const AcGeVector3d& V1, const AcGeVector3d& V2, 
			   const AcGeVector3d& Vh, double H, 
			   const std::vector<t_PolylineVertex> &OutPtArr,
			   const std::vector< std::vector<t_PolylineVertex> > &InPtArrArr, 
			   int Precision = PRIMARY3D_DEFAULT_PRECISION, bool HasSnap = false, int CorrType = 1/* 0: ����ϵ��1: ����ϵ*/);

	virtual ~PDSpolygon();
public:
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
#else
	virtual Adesk::Boolean worldDraw(AcGiWorldDraw* mode);
	virtual Acad::ErrorStatus transformBy(const AcGeMatrix3d &xform);
	virtual void list() const;
	virtual Acad::ErrorStatus   getGeomExtents(AcDbExtents& extents) const;
	virtual Acad::ErrorStatus explode(AcDbVoidPtrArray& entitySet) const;
	virtual Acad::ErrorStatus getOsnapPoints(AcDb::OsnapMode osnapMode,
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


  // �ռ�����ƽ������ϵԭ��
	const AcGePoint3d &getOri() const;
  // X�᷽��
  const AcGeVector3d &getV1() const;
  // Y�᷽��
  const AcGeVector3d &getV2() const;
  // ���췽��(��������ϵ����)
  const AcGeVector3d &getVh() const;
  // ����߶�
  double                    getH() const;
  Acad::ErrorStatus         setH(double val);
  // �⻷�Ķ��㣨��������ϵ�����꣩
  const std::vector<t_PolylineVertex> &getOut() const;
  // �ڻ��Ķ��㣨��������ϵ�����꣩
	const std::vector< std::vector<t_PolylineVertex> > &getIn() const;

  // Vh��OutPtArr��InPtArrArrΪ�ֲ�����ϵ������
  Acad::ErrorStatus         setVal(const AcGePoint3d& oriPt, const AcGeVector3d& V1, const AcGeVector3d& V2, 
                                   const AcGeVector3d& Vh, double H, const AcGePoint3dArray& OutPtArr, 
                                   const std::vector<AcGePoint3dArray>& InPtArrArr, int CorrType = 1/* 0: ������ϵ��1: ����ϵ*/);
  // Vh��OutPtArr��InPtArrArrΪ�ֲ�����ϵ������
  Acad::ErrorStatus         setVal(const AcGePoint3d& oriPt, const AcGeVector3d& V1, const AcGeVector3d& V2, 
	  const AcGeVector3d& Vh, double H, const std::vector<t_PolylineVertex>& OutPtArr,
	  const std::vector< std::vector<t_PolylineVertex> >& InPtArrArr, int CorrType = 1/* 0: ������ϵ��1: ����ϵ*/);

    virtual void createBody();

	//  [9/5/2007 suzhiyong]
	virtual Acad::ErrorStatus explodeTo3DSolid(AcDb3dSolid* &p3dSolid) const;

protected:
    Adesk::Boolean drawPolylineVertex(AcGiWorldDraw* mode, 
                                     const std::vector<t_PolylineVertex> &vertexArr, 
                                     int &gsIndex, 
                                     int Precision) const;

private:	// �洢������
  // ���е�ͷ����Ϊ��������ϵ������
	AcGePoint3d               m_ptOri;      // �ռ�����ƽ������ϵԭ��
    AcGeVector3d              m_vecV1;      // X�᷽��
    AcGeVector3d              m_vecV2;      // Y�᷽��
    AcGeVector3d              m_vecVh;      // ���췽��
    double                    m_dH;         // ����߶�
    AcGePoint3dArray          m_ptarrOut;   // �⻷�Ķ���	//�����ݲ�ʹ���ˣ���m_vertexArrOut���
	std::vector<AcGePoint3dArray>  m_ptarrarrIn; // �ڻ��Ķ���	//�����ݲ�ʹ���ˣ���m_vertexArrArrIn���

	// version 2
	std::vector<t_PolylineVertex>  m_vertexArrOut; // �⻷�Ķ��㣨��������ϵ�����꣩
	std::vector< std::vector<t_PolylineVertex> >  m_vertexArrArrIn; // �ڻ��Ķ��㣨��������ϵ�����꣩
	
private:	// ���洢������
	double GetMaxLen();
	double m_dMaxLength;

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
MAKE_ACDBOPENOBJECT_FUNCTION(PDSpolygon);

#endif // !defined(PDSPOLYGON_H)
