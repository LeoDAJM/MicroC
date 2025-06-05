// MicroC.cpp: define el punto de entrada de la aplicación.
//

#include "MicroC.h"

using namespace std;

int main()
{
	cout << "Hello CMake." << endl;
	ModUSCS USCSimple;
	string s;
	while (true) {
		cout << "Señal[S] : ";
		cin >> s; // Suppose s = "100100101"
		USCSimple.cw = (uint32_t)bitset<32>(s).to_ulong();
		if (USCSimple.cw == 0) break; // Exit condition
		cout << endl;
		cout << "Valor B : ";
		cin >> USCSimple.B; // Suppose s = "100100101"
		cout << endl << "----------------------------------" << endl;
		cout << hex << "B IN: " << USCSimple.B << "Flags: " << USCSimple.F << "R: " << USCSimple.R << endl;
		cout << "----------------------------------" << endl;
	}
	return 0;
}
