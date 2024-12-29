#ifndef STRING_CRYPTO_H
#define STRING_CRYPTO_H



#include <string>
#include <vector>
#include <random>
#include <ctime>
#include <sstream>
#include <iomanip>

class SecureStringCrypto {
private:
    static const std::string DEFAULT_KEY;

    static std::string base64_encode(const std::vector<unsigned char>& data) {
        const std::string base64_chars =
            "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
        std::string encoded;
        int i = 0;
        int j = 0;
        unsigned char array3[3];
        unsigned char array4[4];

        for (unsigned char c : data) {
            array3[i++] = c;
            if (i == 3) {
                array4[0] = (array3[0] & 0xfc) >> 2;
                array4[1] = ((array3[0] & 0x03) << 4) + ((array3[1] & 0xf0) >> 4);
                array4[2] = ((array3[1] & 0x0f) << 2) + ((array3[2] & 0xc0) >> 6);
                array4[3] = array3[2] & 0x3f;

                for (i = 0; i < 4; i++)
                    encoded += base64_chars[array4[i]];
                i = 0;
            }
        }

        if (i) {
            for (j = i; j < 3; j++)
                array3[j] = '\0';

            array4[0] = (array3[0] & 0xfc) >> 2;
            array4[1] = ((array3[0] & 0x03) << 4) + ((array3[1] & 0xf0) >> 4);
            array4[2] = ((array3[1] & 0x0f) << 2) + ((array3[2] & 0xc0) >> 6);

            for (j = 0; j < i + 1; j++)
                encoded += base64_chars[array4[j]];

            while (i++ < 3)
                encoded += '=';
        }

        return encoded;
    }

    static std::vector<unsigned char> base64_decode(const std::string& encoded) {
        const std::string base64_chars =
            "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
        std::vector<unsigned char> decoded;
        int i = 0;
        int j = 0;
        int in_ = 0;
        unsigned char array4[4], array3[3];

        for (char c : encoded) {
            if (c == '=') break;
            if (c == ' ' || c == '\n') continue;

            array4[i++] = base64_chars.find(c);

            if (i == 4) {
                array3[0] = (array4[0] << 2) + ((array4[1] & 0x30) >> 4);
                array3[1] = ((array4[1] & 0xf) << 4) + ((array4[2] & 0x3c) >> 2);
                array3[2] = ((array4[2] & 0x3) << 6) + array4[3]; 

                for (i = 0; i < 3; i++)
                    decoded.push_back(array3[i]);
                i = 0;
            }
        }

        if (i) {
            array3[0] = (array4[0] << 2) + ((array4[1] & 0x30) >> 4);
            array3[1] = ((array4[1] & 0xf) << 4) + ((array4[2] & 0x3c) >> 2);

            for (j = 0; j < i - 1; j++)
                decoded.push_back(array3[j]);
        }

        return decoded;
    }

    static std::vector<unsigned char> xor_with_key(const std::vector<unsigned char>& data,
        const std::string& key) {
        std::vector<unsigned char> result;
        for (size_t i = 0; i < data.size(); ++i) {
            result.push_back(data[i] ^ key[i % key.length()]);
        }
        return result;
    }

public:
    static std::string encrypt(const std::string& input, const std::string& key = DEFAULT_KEY) {
        std::vector<unsigned char> data(input.begin(), input.end());

        auto encrypted = xor_with_key(data, key);

        return base64_encode(encrypted);
    }

    static std::string decrypt(const std::string& input, const std::string& key = DEFAULT_KEY) {
        auto decoded = base64_decode(input);

        auto decrypted = xor_with_key(decoded, key);

        return std::string(decrypted.begin(), decrypted.end());
    }
};

const std::string SecureStringCrypto::DEFAULT_KEY = "X9f#k2P$mL7@vN3q";

#endif