#include "include_cheat.h"

bool g_started = false;

uintptr_t __stdcall init_main( const HMODULE h_module )
{
	g_started = true;
	g_module = h_module;

	init::on_startup();

	return 0;
}

BOOL APIENTRY DllMain( HMODULE h_module, uintptr_t  dw_reason_for_call, LPVOID lp_reserved )
{
	switch ( dw_reason_for_call )
	{
		case DLL_PROCESS_ATTACH:
		{
			CreateThread( NULL, NULL, reinterpret_cast< LPTHREAD_START_ROUTINE >( init_main ), h_module, NULL, NULL );
#ifndef _DEBUG
			/*while ( !g_started )
				Sleep( 1 );*/
			//SuspendThread( NULL );
#endif
			return true;
		}
		default:
			return true;
	}
}

