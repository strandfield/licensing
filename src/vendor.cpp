// Copyright (C) 2020 Vincent Chambrin
// This file is part of the 'licensing' project
// For conditions of distribution and use, see copyright notice in LICENSE

#include "licensing/vendor.h"

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

#include <iostream>

namespace licensing
{

std::pair<std::string, std::string> gen_key_pair()
{
  Botan::AutoSeeded_RNG rng;

  // Generate ECDSA keypair
  Botan::ECDSA_PrivateKey key_pair(rng, Botan::EC_Group("secp521r1"));

  std::string private_key_str = Botan::PKCS8::PEM_encode(key_pair);
  std::string public_key_str = Botan::X509::PEM_encode(key_pair);

  return std::pair<std::string, std::string>(std::move(public_key_str), std::move(private_key_str));
}

std::string sign(const std::string& license, const std::string& privkey)
{
  Botan::AutoSeeded_RNG rng;

  Botan::DataSource_Memory private_key_data_source{ privkey };
  auto private_key = Botan::PKCS8::load_key(private_key_data_source);

  std::vector<uint8_t> data(license.data(), license.data() + license.length());

  Botan::PK_Signer signer(*private_key, rng, "EMSA1(SHA-256)");
  signer.update(data);
  std::vector<uint8_t> signature = signer.signature(rng);

  return Botan::base32_encode(signature);
}

} // namespace licensing