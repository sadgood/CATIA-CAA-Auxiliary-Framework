
//===================================================================
// COPYRIGHT Tony 2017/03/28
//===================================================================
// JNCTempTextRepComp.cpp
// Header definition of class JNCTempTextRepComp
//===================================================================
//
// Usage notes:
//
//===================================================================
//  2017/03/28 Creation: Code generated by the 3DS wizard
//===================================================================

#ifndef JNCTempTextRepComp_H
#define JNCTempTextRepComp_H

#include "CATModelForRep3D.h"

//Mathematics 
#include "CATMathPoint.h"
#include "CATMathPlane.h"

//VisualizationFoundation 
#include "CATRep.h"
#include "CAT3DAnnotationTextGP.h"
#include "CAT3DCustomRep.h"

//-----------------------------------------------------------------------

class JNCTempTextRepComp: public CATModelForRep3D

{
CATDeclareClass;

public:

	// Standard constructors and destructors
	// -------------------------------------
	JNCTempTextRepComp ();
	virtual ~JNCTempTextRepComp ();


	virtual HRESULT CreateDefaultTypeText(CATMathPoint iOrigin,CATUnicodeString  strText) ;

	virtual HRESULT SetGraphicRepresentation (CATRep *  iRep ) ;

	virtual HRESULT GetGraphicRepresentation (CATRep **  oRep) ;

	virtual HRESULT GetInformation(CATMathPoint& oOrigin,CATUnicodeString& strText ) ;


private:
	// Copy constructor and equal operator
	// -----------------------------------
	JNCTempTextRepComp (JNCTempTextRepComp &);
	JNCTempTextRepComp& operator=(JNCTempTextRepComp&);

	CATMathPoint _mathPt;
	CATUnicodeString _strText;

};

//-----------------------------------------------------------------------

#endif
