#include <iostream> 
#include <cstdint>
#include <string>
#include <sstream>
#include <iomanip>
#include <openssl/sha.h>  // tu dois avoir OpenSSL installé

// Fonction SHA256 simple pour mining (exemple rapide)
std::string sha256(const std::string &str) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((const unsigned char*)str.c_str(), str.size(), hash);
    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i)
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    return ss.str();
}

int main() {
    std::cout << "Genesis Miner started" << std::endl;

    std::string prefix = "0000"; // difficulté : nombre de zéros au début
    uint64_t nonce = 0;
    std::string genesis_data = "Mon coinwow genesis block";

    while (true) {
        std::string to_hash = genesis_data + std::to_string(nonce);
        std::string hash = sha256(to_hash);

        if (hash.substr(0, prefix.size()) == prefix) {
            std::cout << "Found nonce: " << nonce << std::endl;
            std::cout << "Hash: " << hash << std::endl;
            break;
        }
        ++nonce;
        if (nonce % 1000000 == 0) 
            std::cout << "Still mining... nonce=" << nonce << std::endl;
    }

    return 0;
}

