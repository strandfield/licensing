// Copyright (C) 2020 Vincent Chambrin
// This file is part of the 'licensing' project
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef LIBLICENSING_H
#define LIBLICENSING_H

#if (defined(WIN32) || defined(_WIN32)) && !defined(LIBLICENSING_STATIC_LINKING)

#if defined(LIBLICENSING_BUILD_LIB)
#  define LIBLICENSING_API __declspec(dllexport)
#else
#  define LIBLICENSING_API __declspec(dllimport)
#endif

#else

#  define LIBLICENSING_API

#endif

#include <string>

namespace licensing
{

/*!
 * \fn bool verify(const std::string& license, const std::string& signature, const std::string& pubkey)
 * \brief verifies that a license's signature is valid
 */
LIBLICENSING_API bool verify(const std::string& license, const std::string& signature, const std::string& pubkey);

} // namespace licensing

#endif // LIBLICENSING_H
