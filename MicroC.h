// MicroC.h: archivo de inclusión para archivos de inclusión estándar del sistema,
// o archivos de inclusión específicos de un proyecto.

#pragma once

#include <bit>
#include <bitset>
#include <cstdint>
#include <iostream>

#ifndef RAM64K_HPP
#define RAM64K_HPP

#include <cstring> // Para std::memset

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
    uint8_t G = {0}; // Generate
    uint8_t P = {0}; // Propagate
    uint8_t C = (control & ~(control >> 5)) | (batch & (control >> 5)) & 1; // Carries
    P = A ^ B;
    G = A & B;
    // Calculamos acarreos usando carry lookahead
    for (int i = 1; i <= 7; ++i) {
        // C[i] = G[i-1] | (P[i-1] & C[i-1])
        C |= ((G | (P & C)) & (1 << (i - 1))) << 1;
    }
    batch |= ((G | (P & C)) & 0x80) >> 6;
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
    x x x x x x CF Cin2
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

}

inline void ALU (uint8_t& A, uint8_t& B, uint16_t& cw, uint8_t& batch, uint8_t& R) {
    uint8_t tmp;
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
    }
    batch |= (R >> 4) & 0x08; //NF Signo

    
    Z = 
    batch |= ((cw >> 3) & (cw >> 3) & cw)
}

class USCS
{
private:
    uint8_t A = { 0 };
    uint8_t B = { 0 };
    uint32_t cw = { 0 };
    uint8_t R = { 0 };
    uint8_t F = { 0 };
public:
    inline void run () {
        ALU(A, B, cw, F, R);
        R = B;
    }
};


inline void USCS (uint8_t& A, uint8_t& cw, uint8_t& F, uint8_t& R) {

}