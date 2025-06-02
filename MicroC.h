// MicroC.h: archivo de inclusión para archivos de inclusión estándar del sistema,
// o archivos de inclusión específicos de un proyecto.

#pragma once

#include <iostream>

#ifndef RAM64K_HPP
#define RAM64K_HPP

#include <cstdint>
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

class UBC {
private:
    static void execute(uint8_t& X, uint8_t& Y, uint8_t& cw, uint8_t& S, uint8_t& A, uint8_t& B) {
        A = (X & -((cw >> 4) & 1)) ^ -((cw >> 2) & 1);
        B = (Y & -((cw >> 3) & 1)) ^ -((cw >> 1) & 1);
		adder8(A, B, S, cw);
    }
public:
    static void adder8(uint8_t& A, uint8_t& B, uint8_t& result, uint8_t& control) {
        // Control Word (Co, CW[6], Cin)
        uint8_t G = {0}; // Generate
        uint8_t P = {0}; // Propagate
        uint8_t C = control; // Carries

        P = A ^ B;
        G = A & B;
        C &= 1;
        // Calculamos acarreos usando carry lookahead
        for (int i = 1; i <= 7; ++i) {
            // C[i] = G[i-1] | (P[i-1] & C[i-1])
            C |= ((G | (P & C)) & (1 << (i - 1))) << 1;
        }
        control |= ((G | (P & C)) & 0x80);
        result = P ^ C;
    }
};

class UBC {
private:
    uint8_t X = { 0 };  // Entrada A
    uint8_t Y = { 0 };  // Entrada B
    uint8_t cw = { 0 };  // Control Word (Co, MUX (S6-5), CW[4] (S4-1), Cin (S0) )
    uint8_t S = { 0 };  // Suma S
	ubc = UBC();
public:

    void mux(uint8_t A, uint8_t B, uint8_t* result, uint8_t* control) {
        // Control Word (Co, CW[6], Cin)
        uint8_t R = { 0 }; // Generate

		uint8_t muxS = (*control >> 5) & 0x03; // MUX selector bits

        switch (muxS) {
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
            
        }

        P = A ^ B;
        G = A & B;
        C &= 1;
        // Calculamos acarreos usando carry lookahead
        for (int i = 1; i <= 7; ++i) {
            // C[i] = G[i-1] | (P[i-1] & C[i-1])
            C |= ((G | (P & C)) & (1 << (i - 1))) << 1;
        }
        *control |= ((G | (P & C)) & 0x80);
        *result = P ^ C;
    }
};
