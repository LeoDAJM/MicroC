// MicroC.cpp: define el punto de entrada de la aplicación.
//

#include "MicroC.h"

using namespace std;

int main()
{
	cout << "Hello CMake." << endl;
	ModUSCS USCSimple;
	string s;
	int tmp;
	while (true) {
		cout << "Señal[S] : ";
		cin >> s; // Suppose s = "100100101"
		cout << "|" << s << "|" << endl;
		USCSimple.cw = (uint32_t)bitset<32>(s).to_ulong();
		if (USCSimple.cw == 0) break; // Exit condition
		cout << endl;
		cout << "Valor B : ";
		cin >> tmp; // Suppose s = "100100101"
		USCSimple.B = static_cast<uint8_t>(tmp);
		cout << endl << "----------------------------------" << endl;
		cout << hex << "B IN: " << static_cast<int>(USCSimple.B) << "		Flags: " << static_cast<int>(USCSimple.F) << "R: " << static_cast<int>(USCSimple.R) << endl;
		cout << "----------------------------------" << endl;
	}
	return 0;
}
