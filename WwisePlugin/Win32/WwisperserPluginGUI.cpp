// [wp-enhanced template] **Do not delete this line**

#include "WwisperserPluginGUI.h"

AK_WWISE_PLUGIN_GUI_WINDOWS_BEGIN_POPULATE_TABLE(PropTable)
// [PropertyTable]
// [/PropertyTable]
AK_WWISE_PLUGIN_GUI_WINDOWS_END_POPULATE_TABLE()

WwisperserPluginGUI::WwisperserPluginGUI()
{
}

ADD_AUDIOPLUGIN_CLASS_TO_CONTAINER(
    Wwisperser,            // Name of the plug-in container for this shared library
    WwisperserPluginGUI,   // Authoring plug-in class to add to the plug-in container
    Wwisperser           // Corresponding Sound Engine plug-in class
);

// [wp-enhanced] Uncomment the following lines if you want to use a custom GUI
// HINSTANCE WwisperserPluginGUI::GetResourceHandle() const
// {
//     AFX_MANAGE_STATE( AfxGetStaticModuleState() );
//     return AfxGetStaticModuleState()->m_hCurrentResourceHandle;
// }
//  
// bool WwisperserPluginGUI::GetDialog( AK::Wwise::Plugin::eDialog in_eDialog, UINT & out_uiDialogID, AK::Wwise::Plugin::PopulateTableItem *& out_pTable ) const
// {
//     AKASSERT( in_eDialog == AK::Wwise::Plugin::SettingsDialog );
//  
//     out_uiDialogID = IDD_DIALOG1;
//     out_pTable = PropTable;
//  
//     return true;
// }
//  
// bool WwisperserPluginGUI::WindowProc( AK::Wwise::Plugin::eDialog in_eDialog, HWND in_hWnd, uint32_t in_message, WPARAM in_wParam, LPARAM in_lParam, LRESULT & out_lResult )
// {
//     switch ( in_message )
//     {
//     case WM_INITDIALOG:
//         m_hwndPropView = in_hWnd;
//         break;
//     case WM_DESTROY:
//         m_hwndPropView = NULL;
//         break;
//     }
//     out_lResult = 0;
//     return false;
// }