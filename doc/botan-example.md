
```cpp
#include <botan/auto_rng.h>
#include <botan/ecdsa.h>
#include <botan/ec_group.h>
#include <botan/pubkey.h>
#include <botan/hex.h>
#include <botan/base32.h>
#include <botan/base64.h>

#include <botan/data_src.h>
#include <botan/pkcs8.h>
#include <botan/x509_key.h>
```

```cpp
Botan::AutoSeeded_RNG rng;
// Generate ECDSA keypair
Botan::ECDSA_PrivateKey key_pair(rng, Botan::EC_Group("secp521r1"));

std::string private_key_str = Botan::PKCS8::PEM_encode(key_pair);
std::string public_key_str = Botan::X509::PEM_encode(key_pair);

std::cout << private_key_str << std::endl;
std::cout << public_key_str << std::endl;

Botan::DataSource_Memory private_key_data_source{ private_key_str };
auto private_key = Botan::PKCS8::load_key(private_key_data_source);

Botan::DataSource_Memory public_key_data_source{ public_key_str };
auto public_key = Botan::X509::load_key(public_key_data_source);

std::string text("This is a tasty burger!");
std::vector<uint8_t> data(text.data(), text.data() + text.length());
// sign data
 Botan::PK_Signer signer(*private_key, rng, "EMSA1(SHA-256)");
//Botan::PK_Signer signer(*private_key, rng, "EMSA1(SHA-1)");
signer.update(data);
std::vector<uint8_t> signature = signer.signature(rng);
std::cout << "Signature:" << std::endl << Botan::base64_encode(signature) << std::endl;
std::cout << "Signature:" << std::endl << Botan::base32_encode(signature) << std::endl;
std::cout << "Signature:" << std::endl << Botan::hex_encode(signature) << std::endl;
// verify signature
Botan::PK_Verifier verifier(*public_key, "EMSA1(SHA-256)");
verifier.update(data);
std::cout << std::endl << "is " << (verifier.check_signature(signature) ? "valid" : "invalid") << std::endl;
```