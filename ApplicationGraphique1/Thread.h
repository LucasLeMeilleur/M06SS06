//---------------------------------------------------------------------------

#ifndef ThreadH
#define ThreadH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
class ThRecherche : public TThread
{
private:
protected:
	void __fastcall Execute();
public:
	__fastcall ThRecherche(bool CreateSuspended);
};
//---------------------------------------------------------------------------
#endif
