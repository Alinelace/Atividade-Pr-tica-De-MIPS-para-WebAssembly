#include <stdint.h>
#include <stdbool.h>
#include <limits.h>

// Macro para exportar as funções para o WebAssembly
#define WASM_EXPORT __attribute__((visibility("default")))

// Soma básica (vulnerável a overflow)
WASM_EXPORT int32_t soma(int32_t a, int32_t b) {
    return a + b;
}


// Soma segura com detecção lógica de overflow via MSB/Sinais
WASM_EXPORT int32_t soma_segura(int32_t a, int32_t b, bool* teve_overflow) {
    int32_t resultado = a + b;
    
    // Overflow ocorre se:
    // 1. Positivo + Positivo = Negativo
    // 2. Negativo + Negativo = Positivo
    if ((a > 0 && b > 0 && resultado < 0) || (a < 0 && b < 0 && resultado >= 0)) {
        *teve_overflow = true;
    } else {
        *teve_overflow = false;
    }
    
    return resultado;
}


// Subtração básica
WASM_EXPORT int32_t sub(int32_t a, int32_t b) {
    return a - b;
}

// Subtração segura
WASM_EXPORT int32_t sub_segura(int32_t a, int32_t b, bool* teve_overflow) {
    int32_t resultado = a - b;
    
    // Overflow ocorre se:
    // 1. Positivo - Negativo = Negativo
    // 2. Negativo - Positivo = Positivo
    if ((a >= 0 && b < 0 && resultado < 0) || (a < 0 && b > 0 && resultado >= 0)) {
        *teve_overflow = true;
    } else {
        *teve_overflow = false;
    }
    
    return resultado;
}


// Multiplicação básica
WASM_EXPORT int32_t mul(int32_t a, int32_t b) {
    return a * b;
}

// Multiplicação segura
WASM_EXPORT int32_t mul_segura(int32_t a, int32_t b, bool* teve_overflow) {
    // Promove os operandos para 64 bits para calcular o produto exato
    int64_t produto_64 = (int64_t)a * (int64_t)b;
    
    // Verifica se o resultado extrapola o intervalo de 32 bits assinados
    if (produto_64 > INT32_MAX || produto_64 < INT32_MIN) {
        *teve_overflow = true;
    } else {
        *teve_overflow = false;
    }
    
    return (int32_t)produto_64;
}

