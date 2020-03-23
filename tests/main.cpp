// Copyright (C) 2018 Vincent Chambrin
// This file is part of the 'licensing' project
// For conditions of distribution and use, see copyright notice in LICENSE

#include "licensing/licensing.h"
#include "licensing/vendor.h"

#include <iostream>

int main(int argc, char *argv[])
{
  std::pair<std::string, std::string> keys = licensing::gen_key_pair();

  std::string license = "john.doe@example.com/super-user/2020-12-25";

  std::string sig = licensing::sign(license, keys.second);

  std::cout << "Signing: " << license << std::endl;
  std::cout << "Signature:" << std::endl << sig << std::endl;

  bool result = licensing::verify(license, sig, keys.first);

  if (!result)
    return 1;

  license = "john.doe@example.com/super-user/2021-12-25";

  result = licensing::verify(license, sig, keys.first);

  if (result)
    return 2;

  return 0;
}
