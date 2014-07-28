// PDEcone.h: interface for the PDEcone class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PDECONE_H__3E5242A3_B1C0_4F47_A689_286BE75A2B1C__INCLUDED_)
#define AFX_PDECONE_H__3E5242A3_B1C0_4F47_A689_286BE75A2B1C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PDPrimary3D.h"


class PDEcone : public PDPrimary3D  
{
public:
	ACRX_DECLARE_MEMBERS(PDEcone);
	PDEcone(bool HasSnap = false);
	PDEcone(const AcGePoint3d &ptStart, const AcGePoint3d &ptEnd, 
            double Diameter1, double Diameter2, const AcGeVector3d &vect, 
            int Precision = PRIMARY3D_DEFAULT_PRECISION, 
            bool HasSnap = false);
	virtual ~PDEcone();

public:
	/*---------------------------------------------------------------------------
* ����: _make_eqovalpt
* ����: ��� "���豸�����ͷ�ϻ�����" �Ĺ���
* ע��: ��
*/
    int   _make_eqovalpt(double lengthR,AcGeVector3d vec,ads_point pt,ads_point normal) ;
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

	Acad::ErrorStatus setParameters(const AcGePoint3d &ptStart, 
                                    const AcGePoint3d &ptEnd, 
                                    double d1, 
                                    double d2, 
                                    const AcGeVector3d &vect, 
                                    int Precision = PRIMARY3D_DEFAULT_PRECISION);

	AcGePoint3d getpointStart() const;
	AcGePoint3d getpointEnd() const;
	double getDiameter1() const;
	double getDiameter2() const;
	AcGeVector3d getVect() const;

    /*!
     * ȡ�õ���ķ�ʸ
     *
     * @param none
     *
     * @return AcGeVector3d  : ����ķ�ʸ
     */
    AcGeVector3d getFaceVect() const;

	/*!
	 * ��ȡm_ptStart��m_ptEnd���ڵ����ϵ�ͶӰ
	 * \return AcGePoint3d
	 */
	AcGePoint3d getStartPtOrthoInEntPtPlane()const;
	/*!
	 * ��ȡm_ptEnd��m_ptStart���ڵ����ϵ�ͶӰ
	 * \return AcGePoint3d
	 */
	AcGePoint3d getEndPtOrthoInStartPtPlane()const;

	/*!
	 * ��ȡԲ̨��
	 * \return double
	 */
	double getHeight()const;


    // ȡ�ú��ʵ��ʷ־��ȣ����ʵ���С�����ʷ־��Ⱦͻ�ͣ����ʵ��ϴ����ʷ�
    // ���Ȳ�����ʵ���޶����ʷ־���m_dDividPrecision��
    virtual int getMaxPrecision(AcGiWorldDraw *mode) const;

    virtual void createBody();

    Acad::ErrorStatus explodeToSurface(AcDbVoidPtrArray& entitySet) const;

	//  [9/5/2007 suzhiyong]
	virtual Acad::ErrorStatus explodeTo3DSolid(AcDb3dSolid* &p3dSolid) const;

private:
    /*!
    * �����Ѿ����뵽���еĲ����������յ��ƫ�ķ���ʹ��ֵ��ȷ��
    *
    * @param none
    *
    * @return Acad::ErrorStatus  : ��ԶΪAcad::eOk
    */
    Acad::ErrorStatus CalActParameter();

	AcGePoint3d m_ptEnd;
	AcGePoint3d m_ptStart;
	double m_dDiameter1;
	double m_dDiameter2;
	AcGeVector3d m_vect;

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
MAKE_ACDBOPENOBJECT_FUNCTION(PDEcone);

#endif // !defined(AFX_PDECONE_H__3E5242A3_B1C0_4F47_A689_286BE75A2B1C__INCLUDED_)
