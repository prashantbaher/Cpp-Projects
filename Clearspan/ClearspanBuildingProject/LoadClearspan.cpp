// Including ATL Base Library
#include <atlbase.h>

// Importing Libraries
#import "sldworks.tlb" raw_interfaces_only, raw_native_types, no_namespace, named_guids 
#import "swconst.tlb" raw_interfaces_only, raw_native_types, no_namespace, named_guids 

// Running Solidworks from our Application
int RunSolidworks()
{
	// Initializing the COM object with NULL Value
	CoInitialize(NULL);

	// Brackets to destroy the objects after use
	{
		// Defining Solidworks Application COM Pointer
		CComPtr<ISldWorks> swApp;

		// Defining Solidworks Model Document COM Pointer
		CComPtr<IModelDoc2> swDoc;

		// Defining HRESULT type variable for true or false
		HRESULT hres;

		// Creating Co-Instances of Solidworks
		hres = swApp.CoCreateInstance(__uuidof(SldWorks), NULL, CLSCTX_LOCAL_SERVER);

		// If Solidworks app is not created then return 0
		if (FAILED(hres))
			return 0;

		// Making Solidworks Visible
		swApp->put_Visible(VARIANT_TRUE);

		// Creating COM Style String for storing Default Part Template location
		CComBSTR DefaultPartTemplate;

		// Setting Default Part Template location in DefaultPartTemplate variable
		swApp->GetUserPreferenceStringValue(swUserPreferenceStringValue_e::swDefaultTemplatePart, &DefaultPartTemplate);

		// Creating New Part Document
		hres = swApp->INewDocument2(DefaultPartTemplate, 0, 0, 0, &swDoc);

		// If new document is not created then return 0
		if (FAILED(hres))
			return 0;
	}

	// Un-initialize COM Instance
	CoUninitialize();
}