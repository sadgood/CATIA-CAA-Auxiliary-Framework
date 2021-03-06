//===================================================================
// COPYRIGHT Tony 2016/11/18
//===================================================================
// PartEnhancement.cpp
// Header definition of class DownReference
//===================================================================
//
// Usage notes:
//
//===================================================================
//  2016/11/18 Creation: Code generated by the 3DS wizard
//===================================================================

#include "PartEnhancement.h"
// C++
#include <iostream>
using std::cout;
using std::endl;

// System
#include "CATLISTV_CATBaseUnknown.h"

// CATPLMComponentInterfaces
#include "CATIPLMNavEntity.h"
#include "CATIPLMNavReference.h"
#include "CATIPLMNavRepReference.h"
#include "CATIPLMNavRepInstance.h"
#include "CATListPtrCATIPLMNavEntity.h"
#include "CATIPLMNavOccurrence.h"

// CATPLMIdentificationAccess
#include "CATPLMCoreType.h"

// ObjectModelerNavigator
#include "CATINavigateObject.h"
#include "CATIGraphNode.h"
#include "CATNavigController.h"
#include "CATINavigElement.h"
#include "CATNavigInstance.h"
#include "CATIGraphLink.h"
#include "CATIRedrawEvent.h"
#include "CATINavigNodeCtrl.h"

// AfrNavigator 
#include "CATFrmNavigGraphicWindow.h"
#include "CATNavigBox.h"

// ObjectModelerSystem 
#include "CATIAlias.h"

// CATMecModUseItf 
#include "CATIMmiPrtContainer.h"
#include "CATIMmiUseGeometricalElement.h"
#include "CATIMmiUseCreateImport.h"
#include "CATMmiUseServicesFactory.h"

// CATMecModLiveUseItf
#include "CATIPartRequest.h"
#include "CATIMmiMechanicalFeature.h"

// KnowledgeInterfaces
#include "CATICkeParm.h"
#include "CATICkeObject.h"
#include "CATCkeObjectAttrReadServices.h"
#include "CATIParmPublisher.h"
#include "CATCkeGlobalFunctions.h"
#include "CATIKweModelServices.h"
#include "CATICkeParameterSet.h"
#include "CATICkeRelationForwards.h"

// CAT3DPhysicalRepInterfaces
#include "CATIPsiRepresentationLoadMode.h"

// Mathematics
#include "CATMathPoint.h"
#include "CATMathPlane.h"
#include "CATMathLine.h"

// GMModelInterfaces
#include "CATBody.h"
#include "CATCell.h"
#include "CATVertex.h"
#include "CATEdge.h"
#include "CATFace.h"

// GeometricObjects
#include "CATPoint.h"
#include "CATSurface.h"
#include "CATPlane.h"
#include "CATCurve.h"
#include "CATLine.h"
#include "CATEdgeCurve.h"
#include "CATSurParam.h"

// MeasureGeometryInterfaces
#include "CATIMeasurableInContext.h"

// VisualizationInterfaces 
#include "CATIBuildPath.h"
#include "CATPathElement.h"


namespace JNCTonySpace{

HRESULT DownwardRef(CATIPLMNavReference *iPLMRef, DownwardDegree iDegree, void** oppv, int iPos)
{
	HRESULT rc = S_OK;
	if (NULL == iPLMRef || NULL == oppv)
	{
		rc = E_FAIL;
		return rc ;
	}

	//step 1:get the list of the children
	CATListPtrCATIPLMNavEntity  lstRepInst;
	if (SUCCEEDED(rc))
	{
		CATPLMCoreType repinstype = PLMCoreRepInstance;
		rc = iPLMRef->ListChildren(lstRepInst, 1, &repinstype);
	}
	if (iPos > lstRepInst.Size())
	{
		rc = E_NOINTERFACE;
		return rc ;
	}

	//step 2:get the direct child of the 3D part
	CATIPLMNavEntity *_piPLMNavEntity = NULL;
	if (SUCCEEDED(rc)) 
		_piPLMNavEntity = lstRepInst.operator[](iPos);
	if (NULL == _piPLMNavEntity)
		rc = E_NOINTERFACE;

	if (0 == iDegree)
	{
		rc = _piPLMNavEntity->QueryInterface(IID_CATIPLMNavRepInstance, oppv);
		lstRepInst.RemoveAll();
		return rc;
	}

	//step 3:get the repref of the 3dpart
	CATIPLMNavRepInstance * _piPLMNavRepInst = NULL;
	CATIPLMNavRepReference * _piPLMNavRepRef = NULL;
	if (SUCCEEDED(rc)) 
		rc = _piPLMNavEntity->QueryInterface(IID_CATIPLMNavRepInstance,(void**)&_piPLMNavRepInst);

	if (SUCCEEDED(rc)) 
		rc = _piPLMNavRepInst->GetRepReferenceInstanceOf(_piPLMNavRepRef);

	rc = _piPLMNavRepRef->QueryInterface(IID_CATIPLMNavRepReference, oppv);
	if (1 == iDegree)
	{
		lstRepInst.RemoveAll();
		if (NULL!=_piPLMNavRepInst)  {_piPLMNavRepInst->Release(); _piPLMNavRepInst=NULL;}
		if (NULL!=_piPLMNavRepRef)  {_piPLMNavRepRef->Release(); _piPLMNavRepRef = NULL;}
		return rc ;
	}

	if (NULL!=_piPLMNavRepInst)  {_piPLMNavRepInst->Release(); _piPLMNavRepInst=NULL;}
	lstRepInst.RemoveAll();

	//step 4:load the rep in edit mode
	CATIPsiRepresentationLoadMode *_piPsiRepLoadMode = NULL;
	if (2 == iDegree)
	{
		if (SUCCEEDED(rc)) 
			rc=_piPLMNavRepRef->QueryInterface(IID_CATIPsiRepresentationLoadMode,(void**)&_piPsiRepLoadMode);
		if (SUCCEEDED(rc)) 
			rc=_piPsiRepLoadMode->ChangeLoadingMode(CATIPsiRepresentationLoadMode::EditMode);
	}
	
	if (NULL != _piPLMNavRepRef)  {_piPLMNavRepRef->Release(); _piPLMNavRepRef = NULL;}
	if (NULL != _piPsiRepLoadMode){_piPsiRepLoadMode->Release(); _piPsiRepLoadMode=NULL;}

	return rc;
}


HRESULT DownwardRef(CATIPLMNavReference_var& spPLMRef, DownwardDegree iDegree, void** oppv, int iPos)
{
	HRESULT rc = S_OK;
	if (NULL_var == spPLMRef || NULL == oppv)
	{
		rc = E_FAIL;
		return rc ;
	}

	//step 1:get the list of the children
	CATListPtrCATIPLMNavEntity  lstRepInst;
	CATPLMCoreType repinstype = PLMCoreRepInstance;
	if (SUCCEEDED(rc))
		rc =spPLMRef->ListChildren(lstRepInst, 1, &repinstype);
	if (iPos > lstRepInst.Size())
	{
		rc = E_NOINTERFACE;
		return rc ;
	}

	//step 2:get the direct child of the 3D part
	CATIPLMNavEntity *_piPLMNavEntity = NULL;
	if (SUCCEEDED(rc)) 
		_piPLMNavEntity = lstRepInst.operator[](iPos);
	if (NULL == _piPLMNavEntity)
		rc = E_NOINTERFACE;

	if (0 == iDegree)
	{
		rc = _piPLMNavEntity->QueryInterface(IID_CATIPLMNavRepInstance, oppv);
		lstRepInst.RemoveAll();
		return rc;
	}

	//step 3:get the repref of the 3dpart
	CATIPLMNavRepInstance * _piPLMNavRepInst = NULL;
	CATIPLMNavRepReference * _piPLMNavRepRef = NULL;
	if (SUCCEEDED(rc)) 
		rc = _piPLMNavEntity->QueryInterface(IID_CATIPLMNavRepInstance,(void**)&_piPLMNavRepInst);

	if (SUCCEEDED(rc)) 
		rc = _piPLMNavRepInst->GetRepReferenceInstanceOf(_piPLMNavRepRef);

	rc = _piPLMNavRepRef->QueryInterface(IID_CATIPLMNavRepReference, oppv);
	if (1 == iDegree)
	{
		lstRepInst.RemoveAll();
		if (NULL!=_piPLMNavRepInst)  {_piPLMNavRepInst->Release(); _piPLMNavRepInst=NULL;}
		if (NULL!=_piPLMNavRepRef)  {_piPLMNavRepRef->Release(); _piPLMNavRepRef = NULL;}
		return rc ;
	}

	if (NULL!=_piPLMNavRepInst)  {_piPLMNavRepInst->Release(); _piPLMNavRepInst=NULL;}
	lstRepInst.RemoveAll();

	//step 4:load the rep in edit mode
	CATIPsiRepresentationLoadMode *_piPsiRepLoadMode = NULL;
	if (2 == iDegree)
	{
		if (SUCCEEDED(rc)) 
			rc=_piPLMNavRepRef->QueryInterface(IID_CATIPsiRepresentationLoadMode,(void**)&_piPsiRepLoadMode);
		if (SUCCEEDED(rc)) 
			rc=_piPsiRepLoadMode->ChangeLoadingMode(CATIPsiRepresentationLoadMode::EditMode);
	}
	
	if (NULL != _piPLMNavRepRef)  {_piPLMNavRepRef->Release(); _piPLMNavRepRef = NULL;}
	if (NULL != _piPsiRepLoadMode){_piPsiRepLoadMode->Release(); _piPsiRepLoadMode=NULL;}

	return rc;
}


void DownwardRef(CATIPLMNavReference *iPLMRef, DownwardDegree iDegree, CATBaseUnknown_var& ospOutput, int iPos)
{
	HRESULT rc = S_OK;
	if (NULL == iPLMRef)
		return ;

	//step 1:get the list of the children
	CATListPtrCATIPLMNavEntity  ListOfRepIns;
	if (SUCCEEDED(rc))
	{
		CATPLMCoreType repinstype = PLMCoreRepInstance;
		rc = iPLMRef->ListChildren(ListOfRepIns, 1, &repinstype);
	}

	if (iPos > ListOfRepIns.Size())
	{
		rc = E_NOINTERFACE;
		return ;
	}

	//step 2:get the direct child of the 3D part
	CATIPLMNavEntity *_piPLMNavEntity = NULL;
	if (SUCCEEDED(rc)) 
		_piPLMNavEntity = ListOfRepIns.operator[](iPos);
	if (NULL == _piPLMNavEntity)
		rc = E_NOINTERFACE;
	if (0 == iDegree)
	{
		/*cout<<"DownwardDegree is converted to 0"<<endl;*/
		ospOutput = _piPLMNavEntity;
		ListOfRepIns.RemoveAll();
		return ;
	}
	else
		cout<<"DownwardDegree compare with int failed"<<endl;

	//step 3:get the repref of the 3dpart
	CATIPLMNavRepInstance * _piPLMNavRepInst = NULL;
	CATIPLMNavRepReference * _piPLMNavRepRef = NULL;
	if (SUCCEEDED(rc)) 
		rc = _piPLMNavEntity->QueryInterface(IID_CATIPLMNavRepInstance,(void**)&_piPLMNavRepInst);

	if (SUCCEEDED(rc)) 
		rc = _piPLMNavRepInst->GetRepReferenceInstanceOf(_piPLMNavRepRef);

	ospOutput = _piPLMNavRepRef;
	if (1 == iDegree)
	{
		ListOfRepIns.RemoveAll();
		if (NULL!=_piPLMNavRepInst)  {_piPLMNavRepInst->Release(); _piPLMNavRepInst=NULL;}
		if (NULL!=_piPLMNavRepRef)  {_piPLMNavRepRef->Release(); _piPLMNavRepRef = NULL;}
		return ;
	}

	if (NULL!=_piPLMNavRepInst)  {_piPLMNavRepInst->Release(); _piPLMNavRepInst=NULL;}
	ListOfRepIns.RemoveAll();

	//step 4:load the rep in edit mode
	CATIPsiRepresentationLoadMode *_piPsiRepLoadMode = NULL;
	if (2 == iDegree)
	{
		if (SUCCEEDED(rc)) 
			rc=_piPLMNavRepRef->QueryInterface(IID_CATIPsiRepresentationLoadMode,(void**)&_piPsiRepLoadMode);
		if (SUCCEEDED(rc)) 
			rc=_piPsiRepLoadMode->ChangeLoadingMode(CATIPsiRepresentationLoadMode::EditMode);
	}
	
	if (NULL != _piPLMNavRepRef)  {_piPLMNavRepRef->Release(); _piPLMNavRepRef = NULL;}
	if (NULL != _piPsiRepLoadMode){_piPsiRepLoadMode->Release(); _piPsiRepLoadMode=NULL;}

	return ;
}


void DownwardRef(CATIPLMNavReference_var& spPLMRef, DownwardDegree iDegree, CATBaseUnknown_var& ospOutput, int iPos)
{
	HRESULT rc = S_OK;
	if (NULL_var == spPLMRef)
		return ;

	//step 1:get the list of the children
	CATListPtrCATIPLMNavEntity  lstRepInst;
	CATPLMCoreType repinstype = PLMCoreRepInstance;
	if (SUCCEEDED(rc))
		rc =spPLMRef->ListChildren(lstRepInst, 1, &repinstype);
	if (iPos > lstRepInst.Size())
	{
		rc = E_NOINTERFACE;
		return ;
	}

	//step 2:get the direct child of the 3D part
	CATIPLMNavEntity *_piPLMNavEntity = NULL;
	if (SUCCEEDED(rc)) 
		_piPLMNavEntity = lstRepInst.operator[](iPos);
	if (NULL == _piPLMNavEntity)
		rc = E_NOINTERFACE;

	if (0 == iDegree)
	{
		ospOutput = _piPLMNavEntity;
		lstRepInst.RemoveAll();
		return ;
	}

	//step 3:get the repref of the 3dpart
	CATIPLMNavRepInstance * _piPLMNavRepInst = NULL;
	CATIPLMNavRepReference * _piPLMNavRepRef = NULL;
	if (SUCCEEDED(rc)) 
		rc = _piPLMNavEntity->QueryInterface(IID_CATIPLMNavRepInstance,(void**)&_piPLMNavRepInst);

	if (SUCCEEDED(rc)) 
		rc = _piPLMNavRepInst->GetRepReferenceInstanceOf(_piPLMNavRepRef);

	ospOutput = _piPLMNavRepRef;
	if (1 == iDegree)
	{
		lstRepInst.RemoveAll();
		if (NULL!=_piPLMNavRepInst)  {_piPLMNavRepInst->Release(); _piPLMNavRepInst=NULL;}
		if (NULL!=_piPLMNavRepRef)  {_piPLMNavRepRef->Release(); _piPLMNavRepRef = NULL;}
		return ;
	}

	if (NULL!=_piPLMNavRepInst)  {_piPLMNavRepInst->Release(); _piPLMNavRepInst=NULL;}
	lstRepInst.RemoveAll();

	//step 4:load the rep in edit mode
	CATIPsiRepresentationLoadMode *_piPsiRepLoadMode = NULL;
	if (2 == iDegree)
	{
		if (SUCCEEDED(rc)) 
			rc=_piPLMNavRepRef->QueryInterface(IID_CATIPsiRepresentationLoadMode,(void**)&_piPsiRepLoadMode);
		if (SUCCEEDED(rc)) 
			rc=_piPsiRepLoadMode->ChangeLoadingMode(CATIPsiRepresentationLoadMode::EditMode);
	}
	
	if (NULL != _piPLMNavRepRef)  {_piPLMNavRepRef->Release(); _piPLMNavRepRef = NULL;}
	if (NULL != _piPsiRepLoadMode){_piPsiRepLoadMode->Release(); _piPsiRepLoadMode=NULL;}

	return ;
}

void GetMechPartFromRef( CATIPLMNavReference_var spPLMRef, CATIMmiMechanicalFeature_var& spOutPart, int iPos /*= 1*/ )
{
	HRESULT rc = S_OK;
	spOutPart = NULL_var;
	if (NULL_var == spPLMRef)
		return ;

	//step 1:get the list of the children
	CATListPtrCATIPLMNavEntity  lstRepInst;
	CATPLMCoreType repinstype = PLMCoreRepInstance;
	if (SUCCEEDED(rc))
		rc =spPLMRef->ListChildren(lstRepInst, 1, &repinstype);
	if (iPos > lstRepInst.Size())
	{
		rc = E_NOINTERFACE;
		return ;
	}

	//step 2:get the direct child of the 3D part
	CATIPLMNavEntity *_piPLMNavEntity = NULL;
	if (SUCCEEDED(rc) && lstRepInst.Size() >= iPos) 
		_piPLMNavEntity = lstRepInst.operator[](iPos);
	if (NULL == _piPLMNavEntity)
	{
		rc = E_NOINTERFACE;
		return;
	}

	//step 3:get the repref of the 3dpart
	CATIPLMNavRepInstance * _piPLMNavRepInst = NULL;
	CATIPLMNavRepReference * _piPLMNavRepRef = NULL;
	if (SUCCEEDED(rc)) 
		rc = _piPLMNavEntity->QueryInterface(IID_CATIPLMNavRepInstance,(void**)&_piPLMNavRepInst);

	if (SUCCEEDED(rc)) 
		rc = _piPLMNavRepInst->GetRepReferenceInstanceOf(_piPLMNavRepRef);

	if (NULL!=_piPLMNavRepInst)  {_piPLMNavRepInst->Release(); _piPLMNavRepInst=NULL;}
	lstRepInst.RemoveAll();

	//step 4:load the rep in edit mode
	CATIPsiRepresentationLoadMode *_piPsiRepLoadMode = NULL;

	if (SUCCEEDED(rc)) 
		rc=_piPLMNavRepRef->QueryInterface(IID_CATIPsiRepresentationLoadMode,(void**)&_piPsiRepLoadMode);
	if (SUCCEEDED(rc)) 
		rc=_piPsiRepLoadMode->ChangeLoadingMode(CATIPsiRepresentationLoadMode::EditMode);
	
	//step 5:get the mechanical part
	CATIMmiPrtContainer * piPrtContainer = NULL;
	_piPLMNavRepRef->RetrieveApplicativeContainer("CATPrtCont", IID_CATIMmiPrtContainer, (void**)&piPrtContainer);
	if (NULL != piPrtContainer)
	{
		piPrtContainer->GetMechanicalPart(spOutPart);
		piPrtContainer -> Release(); piPrtContainer = NULL;
	}

	if (NULL != _piPLMNavRepRef)  {_piPLMNavRepRef->Release(); _piPLMNavRepRef = NULL;}
	if (NULL != _piPsiRepLoadMode){_piPsiRepLoadMode->Release(); _piPsiRepLoadMode=NULL;}

	return ;
}

HRESULT GetTargetParameter(CATIPLMNavRepReference_var& ispPLMRepRef, CATUnicodeString iParaName, CATICkeParm_var& ospCkeParm)
{
	HRESULT rc = E_FAIL;

	if (NULL_var != ispPLMRepRef)
		rc = S_OK;
	else
		return rc;

	// Set EditMode
	CATIPsiRepresentationLoadMode *_piPsiRepLoadMode = NULL;
	rc = ispPLMRepRef->QueryInterface(IID_CATIPsiRepresentationLoadMode,(void**)&_piPsiRepLoadMode);
	if (SUCCEEDED(rc)) 
		rc=_piPsiRepLoadMode->ChangeLoadingMode(CATIPsiRepresentationLoadMode::EditMode);
	if (NULL != _piPsiRepLoadMode){_piPsiRepLoadMode->Release(); _piPsiRepLoadMode = NULL;}

	// Get Mechanical Part
	CATIMmiPrtContainer * piPrtContainer = NULL;
	CATIMmiMechanicalFeature_var spPart;
	ispPLMRepRef->RetrieveApplicativeContainer("CATPrtCont", IID_CATIMmiPrtContainer, (void**)&piPrtContainer);
	if (NULL != piPrtContainer)
	{
		rc = piPrtContainer->GetMechanicalPart(spPart);
		piPrtContainer -> Release(); piPrtContainer = NULL;
	}
	else
	{
		rc = E_FAIL;
		piPrtContainer = NULL;
		cout<<"ERROR get part"<<endl;
		return rc;
	}

	// Get Parameters
	CATIParmPublisher_var spPartPublisher = NULL_var;
	spPartPublisher = spPart;
	if (NULL_var == spPartPublisher)
	{
		rc = E_FAIL;
		cout<<"No Publisher"<<endl;
		return rc;
	}

	CATICkeParameterSet_var spParmSet = NULL_var;
	if (SUCCEEDED(rc))
	{
		CATIKweModelServices_var spKweModelServices=NULL_var;
		spKweModelServices = CATCkeGlobalFunctions::GetModelServices();

		if (NULL_var!=spKweModelServices)	
			spParmSet = spKweModelServices->GetCurrentSet(CATIKweModelServices::Parameter,spPartPublisher);		
	}
	if (NULL_var == spParmSet)
	{
		rc = E_FAIL;
		cout<<"ERROR get paraset"<<endl;
		return rc;
	}

	CATCkeListOfParm ParamList;
	if (SUCCEEDED(rc))
		ParamList = spParmSet->Parameters();

	// Get Target Parameter
	rc = E_INVALIDARG;
	CATUnicodeString strTemp="";
	for(int i = 1; i <= ParamList->Size(); i++)
	{
		CATICkeParm_var spTempPara = ParamList->operator[](i);
		if (NULL_var == spTempPara)
			continue;
		strTemp = spTempPara->RelativeName(spPartPublisher);
		int cSplashIndex = -1;
		cSplashIndex = strTemp.SearchSubString("\\",0,CATUnicodeString::CATSearchModeBackward);
		if (-1 != cSplashIndex)
			strTemp = strTemp.SubString(cSplashIndex + 1,strTemp.GetLengthInChar() - cSplashIndex-1);

		if (iParaName == strTemp)
		{
			ospCkeParm = spTempPara;
			rc = S_OK;
			break;
		}
		strTemp = "";
	}

	delete ParamList;

	return rc;
}

HRESULT GetTargetParameter( CATIParmPublisher_var& ispPublisher, CATUnicodeString iParaName, CATICkeParm_var& ospCkeParm )
{
	HRESULT rc = E_FAIL;

	if (NULL_var != ispPublisher)
		rc = S_OK;
	else
		return rc;

	CATICkeParameterSet_var spParmSet = NULL_var;
	if (SUCCEEDED(rc))
	{
		CATIKweModelServices_var spKweModelServices=NULL_var;
		spKweModelServices = CATCkeGlobalFunctions::GetModelServices();

		if (NULL_var!=spKweModelServices)	
			spParmSet = spKweModelServices->GetCurrentSet(CATIKweModelServices::Parameter,ispPublisher);		
	}
	if (NULL_var == spParmSet)
	{
		rc = E_FAIL;
		cout<<"ERROR get paraset"<<endl;
		return rc;
	}

	CATCkeListOfParm ParamList;
	if (SUCCEEDED(rc))
		ParamList = spParmSet->Parameters();

	// Get Target Parameter
	rc = E_INVALIDARG;
	CATUnicodeString strTemp="";
	for(int i = 1; i <= ParamList->Size(); i++)
	{
		CATICkeParm_var spTempPara = ParamList->operator[](i);
		if (NULL_var == spTempPara)
			continue;
		strTemp = spTempPara->RelativeName(ispPublisher);
		int cSplashIndex = -1;
		cSplashIndex = strTemp.SearchSubString("\\",0,CATUnicodeString::CATSearchModeBackward);
		if (-1 != cSplashIndex)
			strTemp = strTemp.SubString(cSplashIndex + 1,strTemp.GetLengthInChar() - cSplashIndex-1);

		if (iParaName == strTemp)
		{
			ospCkeParm = spTempPara;
			rc = S_OK;
			break;
		}
		strTemp = "";
	}

	delete ParamList;

	return rc;
}

HRESULT GetTargetParameter(CATIMmiMechanicalFeature_var& ispMechFea, CATUnicodeString iParaName, CATICkeParm_var& ospCkeParm)
{
	HRESULT rc = E_FAIL;

	if (NULL_var != ispMechFea)
		rc = S_OK;
	else
		return rc;

	CATIParmPublisher_var spPublisher = ispMechFea;
	if (NULL_var == spPublisher)
	{
		rc = E_FAIL;
		return rc;
	}
	CATIKweModelServices_var spKweModelServices = NULL_var;
	spKweModelServices = CATCkeGlobalFunctions::GetModelServices();
	if (NULL_var!=spKweModelServices)
	{
		CATListValCATBaseUnknown_var splist;
		spKweModelServices->VisibleParms(spPublisher,splist);

		rc = E_INVALIDARG;
		for(int i = 1; i <= splist.Size(); i++)
		{
			CATICkeParm_var spTempPara = splist.operator[](i);
			if (NULL_var == spTempPara)
				continue;
			
			if (iParaName == spTempPara->RelativeName(spPublisher) || iParaName == spTempPara->InternalRole())
			{
				ospCkeParm = spTempPara;
				rc = S_OK;
				break;
			}
		}
	}

	return rc;
}

HRESULT GetMathPoint( CATBaseUnknown_var ispObject,CATMathPoint& oMathPoint )
{
	// CATPoint
	CATPoint_var spPoint = ispObject;
	if (!!spPoint)
	{
		spPoint->GetMathPoint(oMathPoint);
		return S_OK;
	}

	// CATVertex
	CATVertex_var spVertex = ispObject;
	if (!!spVertex)
	{
		CATPoint *pPoint = spVertex->GetPoint();
		if (NULL != pPoint)
		{
			pPoint->GetMathPoint(oMathPoint);
			return S_OK;
		}
	}

	// Feature(the first CATVertex)
	CATBody_var spiBody = NULL_var;
	CATIMmiUseGeometricalElement_var spGeoSurf= NULL_var;
	spGeoSurf = ispObject; 
	if (NULL_var !=spGeoSurf) spGeoSurf ->GetBodyResult(spiBody) ; 
	if(spiBody != NULL_var) 
	{
		CATLISTP(CATCell) LISTCell; 
		spiBody->GetAllCells( LISTCell, 0 ); 
		for( int index = 1; index <= LISTCell.Size(); index++ )
		{ 
			CATCell * pCell = LISTCell[index]; 
			if(pCell == NULL) 
			{
				cout<<"CATCell is NULL."<<endl;
				continue;
			}

			CATCell_var spCell = pCell;

			CATVertex_var spVertex = spCell;
			if(spVertex == NULL_var) 
			{
				cout<<"CATVertex is NULL_var."<<endl;
				continue;
			}

			CATPoint *pPoint = spVertex->GetPoint();
			if(pPoint == NULL) 
			{
				cout<<"GetPoint failed."<<endl;
				continue;
			}

			pPoint->GetMathPoint(oMathPoint);
			return S_OK;
		}
	}

	return E_FAIL;
}

HRESULT GetMathLine( CATBaseUnknown_var ispObject,CATMathLine& oMathLine )
{
	HRESULT rc = E_FAIL;
	CATMathPoint originPoint;
	CATMathDirection mathDir;

	// CATLine
	CATLine_var spLine ;
	spLine = ispObject;
	if(!!spLine) 
	{
		originPoint = spLine->GetOrigin();
		mathDir = spLine->GetDirection();
		rc = S_OK;
	}

	// CATEdge
	CATEdge_var spEdge = ispObject;
	if(!!spEdge) 
	{
		CATEdgeCurve_var spCurve = spEdge->GetCurve();
		if(!!spCurve) 
		{
			CATLine_var spLine ;
			spLine = spCurve;
			if(!!spLine) 
			{
				originPoint = spLine->GetOrigin();
				mathDir = spLine->GetDirection();
				rc = S_OK;
			}
		}
	}

	// Feature(the first line CATEdge)
	CATBody_var spBody = NULL_var;
	CATIMmiUseGeometricalElement_var spGeoSurf= NULL_var;
	spGeoSurf = ispObject; 
	if (NULL_var !=spGeoSurf) spGeoSurf ->GetBodyResult(spBody) ; 
	if(spBody != NULL ) 
	{
		CATLISTP(CATCell) LISTCell; 
		spBody->GetAllCells( LISTCell, 1 ); 
		for( int index = 1; index <= LISTCell.Size(); index++ )
		{ 
			CATCell * pCell = LISTCell[index]; 
			if(pCell == NULL) 
			{
				cout<<"CATCell is NULL."<<endl;
				continue;
			}

			CATCell_var spCell = pCell;

			CATEdge_var spEdge = spCell;
			if(spEdge == NULL_var) 
			{
				cout<<"CATEdge_var is NULL_var."<<endl;
				continue;
			}

			CATEdgeCurve_var spCurve = spEdge->GetCurve();
			if(spCurve == NULL_var) 
			{
				cout<<"CATEdgeCurve_var is NULL_var."<<endl;
				continue;
			}

			CATLine_var spLine ;
			spLine = spCurve;
			if(!!spLine) 
			{
				cout<<"CATLine_var is NULL_var"<<endl;
				continue;
			}

			originPoint = spLine->GetOrigin();
			mathDir = spLine->GetDirection();
			rc = S_OK;
			break;
		}
	}

	if (SUCCEEDED(rc))
		oMathLine = CATMathLine(originPoint,mathDir);

	return rc;
}

HRESULT GetMathPlane( CATBaseUnknown_var ispObject,CATMathPlane& oMathPlane )
{
	CATBoolean isMathPlane = FALSE;
	CATBody_var spBody = NULL_var;
	CATIMmiUseGeometricalElement_var spGeoSurf= NULL_var;
	spGeoSurf = ispObject; 
	if (NULL_var !=spGeoSurf) spGeoSurf ->GetBodyResult(spBody) ; 

	double maxAreaValue=0.0;
	if(spBody != NULL ) 
	{
		CATLISTP(CATCell) LISTCell; 
		spBody->GetAllCells(LISTCell, 2 ); 
		for( int index = 1; index <= LISTCell.Size(); index++ )
		{ 
			CATCell * pCell = LISTCell[index]; 
			if(pCell == NULL) 
			{
				cout<<"CATCell is NULL."<<endl;
				continue;
			}

			CATCell_var spCell = pCell;
			CATFace_var spFace = spCell;
			if(spFace == NULL_var) 
			{
				cout<<"CATFace_var is NULL_var."<<endl;
				continue;
			}

			CATSurParam oCenterParam;
			spFace->EstimateCenterParam(oCenterParam);

			CATSurface_var spSurface = spFace->GetSurface();
			if(spSurface == NULL_var) 
			{
				cout<<"CATSurface_var is NULL_var."<<endl;
				continue;
			}
			CATMathPoint mathPlaneOriginalPoint = spSurface->EvalPoint(oCenterParam);
			//spFace->EstimateCenter(mathPlaneOriginalPoint);

			double areaValue;
			areaValue = spFace->CalcArea();
			if (areaValue>maxAreaValue)
			{
				maxAreaValue = areaValue;
				CATIMeasurableInContext_var spiMeasurableInContext = NULL_var;
				spiMeasurableInContext = spFace;
				if (spiMeasurableInContext == NULL_var)
				{
					cout<<"Get CATIMeasurableInContext failed."<<endl;
					continue;
				}

				CATMeasurableName shapeName;
				spiMeasurableInContext->GetShapeName(shapeName);
				if (shapeName == CATMeasurablePlane)
				{
					spiMeasurableInContext->GetPlane(oMathPlane);
					oMathPlane.SetOrigin(mathPlaneOriginalPoint);
					isMathPlane = TRUE;
				}
			}
		}
	}
	else  
		cout<<"Get Body From Feature is failed."<<endl;

	if (isMathPlane)
	{
		return S_OK;
	}
	return E_FAIL;
}

HRESULT GetTreeFather( CATBaseUnknown_var ispObject,CATBaseUnknown_var& iospFather )
{
	HRESULT rc = S_OK;
	iospFather = NULL_var;

	CATNavigController* _pNavigController = NULL;
	CATFrmLayout * pLayout = CATFrmLayout::GetCurrentLayout();
	if ( NULL != pLayout )
	{
		CATFrmWindow * pCurrentWindow = pLayout->GetCurrentWindow();
		if ( NULL != pCurrentWindow )
		{
			if ( 1 == pCurrentWindow->IsAKindOf("CATFrmNavigGraphicWindow") )
			{
				CATFrmNavigGraphicWindow * pFrmNavigGraphicWindow = (CATFrmNavigGraphicWindow*) pCurrentWindow ;
				CATNavigBox * pNavigBox = NULL ;
				pNavigBox = pFrmNavigGraphicWindow->GetNavigBox();
				if ( NULL != pNavigBox )
					_pNavigController = pNavigBox->GetController();			
			}
		}
	}

	if (NULL != _pNavigController)
	{
		CATListValCATBaseUnknown_var* lst_Node = NULL;
		lst_Node = _pNavigController->GetAssociatedElements(ispObject);
		if (NULL != lst_Node && lst_Node->Size() > 0)
		{
			CATIGraphNode_var spNode = (*lst_Node)[1];
			if (!!spNode)
			{
				int linknum = spNode->GetNbFatherLinks();
				if (0 != linknum)
				{
					CATIGraphLink* piLink = spNode->GetIndexedFatherLink(1);
					if (NULL != piLink)
					{
						CATINavigElement_var spFaterEle = piLink->GetFatherNode();
						piLink->Release();piLink = NULL;
						if (!!spFaterEle)
						{
							CATNavigInstance* piFatherIns = spFaterEle->GetAssociatedInstance();
							if (NULL != piFatherIns)
								iospFather = piFatherIns->GetReference();
						}
					}
					else
						rc = E_UNEXPECTED;
				}
				else
					rc = E_FAIL;
			}
			else
				rc = E_INVALIDARG;
		}
		else
			rc = E_INVALIDARG;

		if(NULL != lst_Node)
		{
			delete lst_Node;
			lst_Node = NULL;
		}
	}
	else
		rc = E_UNEXPECTED;
	
	
	return rc;
}

HRESULT GetTreeChildren( CATBaseUnknown_var ispObject,CATListValCATBaseUnknown_var& ioChildrenList )
{
	HRESULT rc = S_OK;
	ioChildrenList.RemoveAll();

	CATNavigController* _pNavigController = NULL;
	CATFrmLayout * pLayout = CATFrmLayout::GetCurrentLayout();
	if ( NULL != pLayout )
	{
		CATFrmWindow * pCurrentWindow = pLayout->GetCurrentWindow();
		if ( NULL != pCurrentWindow )
		{
			if ( 1 == pCurrentWindow->IsAKindOf("CATFrmNavigGraphicWindow") )
			{
				CATFrmNavigGraphicWindow * pFrmNavigGraphicWindow = (CATFrmNavigGraphicWindow*) pCurrentWindow ;
				CATNavigBox * pNavigBox = NULL ;
				pNavigBox = pFrmNavigGraphicWindow->GetNavigBox();
				if ( NULL != pNavigBox )
					_pNavigController = pNavigBox->GetController();			
			}
		}
	}

	if (NULL != _pNavigController)
	{
		CATListValCATBaseUnknown_var* lst_Node = NULL;
		lst_Node = _pNavigController->GetAssociatedElements(ispObject);
		if (NULL != lst_Node && lst_Node->Size() > 0)
		{
			CATIGraphNode_var spNode = (*lst_Node)[1];
			if (!!spNode)
			{
				int ExpMode = spNode->IsExpanded();
				CATINavigNodeCtrl_var spControl = spNode;
				if (0 == ExpMode && NULL_var != spControl)
					spControl->Dereference(1);

				int linknum = spNode->GetNbChildLinks();
				for (int i = 1; i <= linknum; i++)
				{
					CATBaseUnknown_var spEach = NULL_var;
					CATIGraphLink* piLink = spNode->GetIndexedChildLink(i);
					if (NULL != piLink)
					{
						CATINavigElement_var spChildEle = piLink->GetChildNode();
						piLink->Release();piLink = NULL;
						if (!!spChildEle)
						{
							CATNavigInstance* piChildIns = spChildEle->GetAssociatedInstance();
							if (NULL != piChildIns)
								spEach = piChildIns->GetReference();
						}
					}
					if (NULL_var != spEach)
						ioChildrenList.Append(spEach);
				}
				if (0 == ExpMode && NULL_var != spControl)
					spControl->Undereference();

				if (ioChildrenList.Size() == 0)
					rc = S_FALSE;
			}
			else
				rc = E_INVALIDARG;
		}
		else
			rc = E_INVALIDARG;

		if(NULL != lst_Node)
		{
			delete lst_Node;
			lst_Node = NULL;
		}
	}
	else
		rc = E_UNEXPECTED;


	return rc;
}

HRESULT GetPathFather( CATBaseUnknown_var ispObject,CATBaseUnknown_var& iospFather )
{
	iospFather = NULL_var;

	CATIBuildPath_var spBuildPath = ispObject;
	if (NULL_var == spBuildPath)
		return E_NOINTERFACE;

	CATPathElement * pPath = NULL;
	HRESULT rc = spBuildPath->ExtractPathElement(NULL, &pPath);
	if (FAILED(rc))
		return rc;

	int PathSize = pPath->GetSize();
	if (PathSize < 2)
		return E_FAIL;

	iospFather = pPath->operator[](PathSize-2); 
	if (NULL_var == iospFather)
		return E_UNEXPECTED;

	return S_OK;
}

void CopyFeature( CATIMmiMechanicalFeature_var ispSourceObject, 
				 CATIMmiMechanicalFeature_var ispTargetObject, 
				 CATIPLMNavOccurrence_var iSourceOcc, 
				 CATIPLMNavOccurrence_var iTargetOcc, 
				 CATIMmiMechanicalFeature_var &ioSpiCopyResult, 
				 CATBoolean WithLink /*= FALSE*/ )
{
	if (ispSourceObject == NULL_var)
		return;

	CATIMmiUseCreateImport* pCreateImport = NULL;
	CATMmiUseServicesFactory::CreateMmiUseCreateImport(pCreateImport);
	if (pCreateImport == NULL) 
		return;

	if (FAILED(pCreateImport->SetObject(ispSourceObject)))
		return;

	if (FAILED(pCreateImport->SetTarget(ispTargetObject)))
		return;

	if (FAILED(pCreateImport->SetPLMOccurrences(iSourceOcc,iTargetOcc))) 
		return;

	if (FAILED(pCreateImport->SetLinkMode(WithLink))) 
		return;

	if (FAILED(pCreateImport->Run(ioSpiCopyResult))) 
		return;

	pCreateImport->Reset();
}

}




