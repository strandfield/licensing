// Copyright (C) 2020 Vincent Chambrin
// This file is part of the 'licensing' project
// For conditions of distribution and use, see copyright notice in LICENSE

#include "licensing/licensing.h"

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

namespace licensing
{

bool verify(const std::string& license, const std::string& signature, const std::string& pubkey)
{
  Botan::DataSource_Memory public_key_data_source{ pubkey };
  auto public_key = Botan::X509::load_key(public_key_data_source);
  std::vector<uint8_t> data(license.data(), license.data() + license.length());
  auto decoded_signature = Botan::base32_decode(signature);
  Botan::PK_Verifier verifier(*public_key, "EMSA1(SHA-256)");
  verifier.update(data);
  return verifier.check_signature(decoded_signature);
}

} // namespace licensing