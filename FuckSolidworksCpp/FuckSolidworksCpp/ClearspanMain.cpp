#include <atlbase.h>

#import "sldworks.tlb" raw_interfaces_only, raw_native_types, no_namespace, named_guids 
#import "swconst.tlb" raw_interfaces_only, raw_native_types, no_namespace, named_guids   


int main()
{
	
	CoInitialize(NULL);

	{
		CComPtr<ISldWorks> swApp;

		CComPtr<IModelDoc2> swDoc;

		HRESULT hres; 
		
		swApp.CoCreateInstance(__uuidof(SldWorks), NULL, CLSCTX_LOCAL_SERVER);

		if (!swApp)
			return 0;

		swApp->put_Visible(VARIANT_TRUE);

		CComBSTR DefaultPartTemplate;

		swApp->GetUserPreferenceStringValue(swUserPreferenceStringValue_e::swDefaultTemplatePart, &DefaultPartTemplate);

		swApp->INewDocument2(DefaultPartTemplate, 0, 0, 0, &swDoc);

		if (!swDoc)
			return 0;

	}

	CoUninitialize();
	
}