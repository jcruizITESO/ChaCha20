#include <iostream>
#include "sodium.h"
#include <cstring>
#include <fstream>
#include <iomanip>

using namespace std;

int main()
{
    if (sodium_init() < 0) {
        /* panic! the library couldn't be initialized; it is not safe to use */
        return -1;
    }

    string fileText;
    string letter;
    
    ifstream m("C:/Users/jcro_/Desktop/ING DE SOFTWARE/Cifrado.txt");

    while (!m.eof()) {
        m >> letter;
        fileText += letter +" ";
    }
    m.close();

    unsigned char text[128];
    strcpy((char*)(text), fileText.c_str());
    int text_len = strlen((char*)text);
    unsigned char* cifrado = new unsigned char[text_len];
    unsigned char* descifrado = new unsigned char[text_len];
    unsigned char k[crypto_stream_chacha20_KEYBYTES];
    unsigned char n[crypto_stream_chacha20_NONCEBYTES];

    crypto_secretbox_keygen(k);
    randombytes_buf(n, sizeof n);
    int errorCode = crypto_stream_chacha20_xor(cifrado, text, text_len, n, k);
    

    for (int i = 0; i < text_len; i++) 
        std::cout << std::setfill('0') << std::setw(2) << std::hex << int(cifrado[i]);
    
    std::cout << std::endl;

    errorCode = crypto_stream_chacha20_xor(descifrado, cifrado, text_len, n, k);

    for (int i = 0; i < text_len; i++) 
        std::cout << std::setfill('0') << std::setw(2) << std::hex << int(descifrado[i]);
    
    std::cout << std::endl;
    std::cout << descifrado;


    return 0;
}

