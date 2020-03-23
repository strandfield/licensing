// Copyright (C) 2020 Vincent Chambrin
// This file is part of the 'licensing' project
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef LIBLICENSING_VENDOR_H
#define LIBLICENSING_VENDOR_H

#include "licensing/licensing.h"

#include <utility>

namespace licensing
{

/*!
 * \fn std::pair<std::string, std::string> gen_key_pair()
 * \brief generates a public/private key pair
 */
LIBLICENSING_API std::pair<std::string, std::string> gen_key_pair();

/*!
 * \fn std::string sign(const std::string& license, const std::string& privkey)
 * \brief signs a license
 */
LIBLICENSING_API std::string sign(const std::string& license, const std::string& privkey);

} // namespace licensing

#endif // LIBLICENSING_VENDOR_H
