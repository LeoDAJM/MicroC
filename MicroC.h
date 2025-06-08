// MicroC.h: archivo de inclusión para archivos de inclusión estándar del sistema,
// o archivos de inclusión específicos de un proyecto.

#pragma once

#include <bit>
#include <bitset>
#include <cstdint>
#include <iostream>
#include <unordered_map>

#ifndef RAM64K_HPP
#define RAM64K_HPP

#include <cstring> // Para std::memset
/*
const std::unordered_map<std::string, uint16_t> UBCS_parser = {
	{"CLR" ,0x0}, {"IN A" ,0x1} , {"IN B" ,0x2},
	{"NEG" ,0x3}, {"NOT" ,0x4} , {"AND" ,0x5},
	{"OR" ,0x6}, {"XOR" ,0x7} , {"ADD" ,0x8},
	{"SUB" ,0x9}, {"INC" ,0xA} , {"DEC" ,0xB},
};*/

const std::unordered_map<std::string, uint16_t> MUXALU = {
	{"AND", 0x0 << 6}, {"OR", 0x1 << 6}, {"XOR", 0x2 << 6}, {"UBC", 0x3 << 6}, {"TD", 0x4 << 6},
};

const std::unordered_map<std::string, uint16_t> ALUS_parser = {
	{"CLR" ,0x0}, {"IN A" ,0x1} , {"IN B" ,0x2},
	{"NEG" ,0x3}, {"NOT" ,0x4} , {"AND" ,0x5},
	{"OR" ,0x6}, {"XOR" ,0x7} , {"ADD" ,0x8},
	{"SUB" ,0x9}, {"INC" ,0xA} , {"DEC" ,0xB},
};
const std::unordered_map<std::string, uint16_t> ExALU_parser = {
	{"CLR" ,0x0}, {"IN A" ,0x1} , {"IN B" ,0x2},
	{"NEG" ,0x3}, {"NOT" ,0x4} , {"AND" ,0x5},
	{"OR" ,0x6}, {"XOR" ,0x7} , {"ADD" ,0x8},
	{"SUB" ,0x9}, {"INC" ,0xA} , {"DEC" ,0xB},

};
/*
const std::unordered_map<uint8_t, uint16_t> ALUS_decoder = {
	{0x0 ,0b0110 00000}, {0x1 ,0b0110 10000} , {0x2 ,0b0110 01000},
	{0x3 ,0b0110}, {0x4 ,0b0110} , {0x5 ,0b0000},
	{0x6 ,0b0010}, {0x7 ,0b0100} , {0x8 ,0b0110},
	{0x9 ,0b0110}, {0xA ,0b0110} , {0xB ,0b0110},
};
const std::unordered_map<uint8_t, uint16_t> ALUS_decoder = {
	{0x0 ,MUXALU.at("UBC") + 0x0}, {0x1 ,MUXALU.at("UBC") + 0x10} , {0x2 ,MUXALU.at("UBC") + 0x8},
	{0x3 ,MUXALU.at("UBC") + 0x15}, {0x4 ,MUXALU.at("UBC") + 0x14} , {0x5 ,MUXALU.at("AND") + 0x0},
	{0x6 ,MUXALU.at("OR") + 0x0}, {0x7 ,MUXALU.at("XOR") + 0x0} , {0x8 ,MUXALU.at("UBC") + 0x18},
	{0x9 ,MUXALU.at("UBC") + 0x1B}, {0xA ,MUXALU.at("UBC") + 0x11} , {0xB ,MUXALU.at("UBC") + 0x12},
};} */

const std::unordered_map<uint8_t, uint16_t> ALUS_decoder = {
	{ALUS_parser.at("CLR") ,MUXALU.at("UBC") + 0x0},		{ALUS_parser.at("IN A") ,MUXALU.at("UBC") + 0x10} ,	{ALUS_parser.at("IN B") ,MUXALU.at("UBC") + 0x8},
	{ALUS_parser.at("NEG") ,MUXALU.at("UBC") + 0x15},		{ALUS_parser.at("NOT") ,MUXALU.at("UBC") + 0x14} ,	{ALUS_parser.at("AND") ,MUXALU.at("AND") + 0x0},
	{ALUS_parser.at("OR") ,MUXALU.at("OR") + 0x0},		{ALUS_parser.at("XOR") ,MUXALU.at("XOR") + 0x0} ,		{ALUS_parser.at("ADD") ,MUXALU.at("UBC") + 0x18},
	{ALUS_parser.at("SUB") ,MUXALU.at("UBC") + 0x1B},		{ALUS_parser.at("INC") ,MUXALU.at("UBC") + 0x11} ,	{ALUS_parser.at("DEC") ,MUXALU.at("UBC") + 0x12},
};

/* OK
0 <=> 011000000
1 <=> 011010000
2 <=> 011001000
3 <=> 011010101
4 <=> 011010100
5 <=> 000000000
6 <=> 001000000
7 <=> 010000000
8 <=> 011011000
9 <=> 011011011
A <=> 011010001
B <=> 011010010
*/


std::unordered_map<uint8_t, uint16_t> ExALU_decoder = ALUS_decoder;
//ExALU_decoder.insert({})
const uint32_t USCS_decoder[0xB] = {
	0b1100000, 0b1110000
};

class RAM64K {
private:
	static constexpr size_t SIZE = 65536;
	uint8_t data[SIZE];  // RAM fija de 64 KiB

public:
	// Constructor: inicializa RAM a cero
	RAM64K() {
		clear();
	}

	// Escribe un byte en una dirección (no se valida rango)
	// Rápido, sin protección: el programador debe usarlo correctamente
	void write(uint16_t address, uint8_t value) {
		data[address] = value;
	}

	// Lee un byte de una dirección (sin verificación de rango)
	uint8_t read(uint16_t address) const {
		return data[address];
	}

	// Limpia toda la RAM con ceros (rápido)
	void clear() {
		std::memset(data, 0, SIZE);
	}

	// Acceso directo con operador [] (sin verificación)
	// Se marca inline porque es una función muy pequeña y
	// se define dentro del encabezado (.hpp), así evitamos errores de linking
	inline uint8_t& operator[](uint16_t address) {
		return data[address];
	}

	inline const uint8_t& operator[](uint16_t address) const {
		return data[address];
	}
};


#endif // RAM64K_HPP

inline void adder8(uint8_t& A, uint8_t& B, uint8_t& result, uint8_t& control, uint8_t& batch) {
	// Control Word (Co, CW[6], Cin)
	// x x MuxCin AND(2) XOR(2) Cin
	// batch1
	// x x x x x x Co Cin2
	//uint8_t G = {0}; // Generate
	//uint8_t P = {0}; // Propagate
	// Si S5 == 1 C0 = CF, else C0 = S0
	uint8_t C = (control & ~(control >> 5)) | (batch & (control >> 5)) & 1; // Carries
	uint8_t P = A ^ B;
	uint8_t G = A & B;
	// Calculamos acarreos usando carry lookahead
	for (int i = 1; i <= 7; ++i) {
		// C[i] = G[i-1] | (P[i-1] & C[i-1])
		C |= ((G | (P & C)) & (1 << (i - 1))) << 1;
	}
	batch |= ((G | (P & C)) & 0x80) >> 6;   // CF
	batch |= (C << 1) & 0x40;;   // HF
	result = P ^ C;
}

inline void UBC(uint8_t& X, uint8_t& Y, uint8_t& cw, uint8_t& batch, uint8_t& S) {
	uint8_t A = (X & -((cw >> 4) & 1)) ^ -((cw >> 2) & 1);
	uint8_t B = (Y & -((cw >> 3) & 1)) ^ -((cw >> 1) & 1);
	adder8(A, B, S, cw, batch);
}

// Barrel Shifter
inline void BS(uint8_t& A, uint16_t& cw, uint8_t& batch, uint8_t& result) {
	/* 
	0 0 0 -> Rot. Der. woC
	0 0 1 -> Rot. Der. wC
	0 1 0 -> Rot. Izq. woC
	0 1 1 -> Rot. Izq. wC
	1 0 0 -> Des. Der. Arith.
	1 0 1 -> Des. Der. Log.
	1 1 0 -> Des. Izq. Arith.
	1 1 1 -> Des. Izq. Log.
	batch1
	x x x x x VF CF Cin2
	*/
	switch (cw & 0x7)
	{
	case 0:
		result = std::rotr(A, 1);
		break;
	case 1:
		result = A >> 1;        //ResW
		result |= (batch << 6) & 0x80;  //MSBRes
		batch &= 0xFD;
		batch |= (A & 1) << 1;  //CF
		break;
	case 2:
		result = std::rotl(A, 1);
		break;
	case 3:
		result = A << 1;        //ResW
		result |= (batch >> 1) & 0x1;  //LSBRes
		batch &= 0xFD;
		batch |= (A & 0x80) >> 6;  //CF
		break;
	case 4:
		result = (A >> 1) | (A & 0x80);
		break;
	case 5:
		result = A >> 1;
		break;
	case 6:
		result = (A << 1) | (A & 0x80);
		break;
	case 7:
		result = A << 1;
		break;
	default:
		std::cout << "Error S[MUX TD]" << std::endl;
		break;
	}
	batch &= 0xFB;
	batch |= (((result >> 6) ^ batch) << 1) & 0x04;
}

inline void ALU (uint8_t& A, uint8_t& B, uint16_t& cw, uint8_t& batch, uint8_t& R) {
	uint8_t tmp;
	batch &= 0x01;
	switch ((cw >> 6) & 0x7) {
		case 0:
			R = A & B;
			break;
		case 1:
			R = A | B;
			break;
		case 2:
			R = A ^ B;
			break;
		case 3:
			// uint8_t y = static_cast<uint8_t>(x);
			tmp = cw;
			UBC(A, B, tmp, batch, R);
			break;
		case 4:
			if ((cw >> 3) & 1) tmp = B;
			else tmp = A;
			
			BS(tmp, cw, batch, R);
			break;
		default:
			std::cout << "Error S[MUX ALU]" << std::endl;
			break;
	}
	//    batch1
	//      x HF PF ZF NF VF CF Cin2
	for (uint_fast8_t i = 0; i < 8; i++)
	{
		batch |= ((R >> i) & 0x1) << 4; //ZF
		batch ^= ((R >> i) & 0x1) << 5; //PF
	}
	batch |= (R >> 4) & 0x08; //NF Signo
	batch |= ((((cw >> 4) & (cw >> 3) & cw) & ((R  & (A ^ B)) >> 7)) | (((cw >> 4) & (cw >> 3) & cw) & ((~A & ~B & R) | (A & B & ~R))) << 2) & 0x02; // VF

}


inline void USCS(uint8_t& B, uint8_t& R, uint32_t& cw, uint8_t& F) {
	uint8_t Rtmp = { 0 };		// Revisar, maybe inutil con ALU(A, R, cw2, Ftmp, R);
	uint8_t Ftmp = { 0 };
	uint16_t cw2 = cw;
	ALU(R, B, cw2, Ftmp, Rtmp);
	R = Rtmp;
	//      x HF PF ZF NF VF CF Cin2
	if ((cw >> 11) & 0x1) {
		F &= 0xFD;
		F |= ((Ftmp & (cw >> 8)) | (cw >> 9)) & 0x02;	//CF 9-11
	}
	if ((cw >> 14) & 0x1) {
		F &= 0xFB;
		F |= ((Ftmp & (cw >> 10)) | (cw >> 11)) & 0x04;	//VF 12-14
	}
	if ((cw >> 16) & 0x1) {								//CLK HPNZ
		F &= 0x87;
		//(cw >> 9) ? clrb(F, 3) : F |= 0x08;	//HF 3
		F |= (cw >> 9) & Ftmp & 0x40;	// HF
		F |= Ftmp & 0x38;				// PF ZF NF
	}
}

class ModUSCS
{
public:
	uint8_t B = { 0 };
	uint8_t R = { 0 };
	uint32_t COp = { 0 };
	uint32_t cw = { 0 };
	uint8_t F = { 0 };
	inline void run () {
		USCS(R, B, cw, F);
	}
};

inline void decoUSCS() {
}

inline void clrb(uint8_t& byte, int_fast8_t i) {
	// Establecer un bit de un byte en 0 o 1 (borra el anterior valor)
	byte &= ~(1 << i);
	//byte |= 
}


/*
class ModUSCS
{
private:
	uint8_t Rtmp = { 0 };
	uint8_t Ftmp = { 0 };
public:
	uint8_t A = { 0 };
	uint8_t R = { 0 };
	uint32_t &cw;
	uint8_t F = { 0 };
	ModUSCS(uint32_t &cwref) : cw(cwref) {}
	inline void run () {
		uint16_t cw2 = cw;
		ALU(A, R, cw2, Ftmp, Rtmp);
		R = Rtmp;
		//      x HF PF ZF NF VF CF Cin2
		if ((cw >> 11) & 0x1) {
			F &= 0xFD;
			F |= ((Ftmp & (cw >> 8)) | (cw >> 9)) & 0x02;	//CF 9-11
		}
		if ((cw >> 14) & 0x1) {
			F &= 0xFB;
			F |= ((Ftmp & (cw >> 10)) | (cw >> 11)) & 0x04;	//VF 12-14
		}
		if ((cw >> 17) & 0x1) {								//CLK HPNZ
			F &= 0x87;
			//(cw >> 9) ? clrb(F, 3) : F |= 0x08;	//HF 3
			F |= (cw >> 9) & Ftmp & 0x40;	// HF
			F |= Ftmp & 0x38;				// PF ZF NF
		}
	}
};
*/