/*
    This file is part of cpp-ethereum.

    cpp-ethereum is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    cpp-ethereum is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with cpp-ethereum.  If not, see <http://www.gnu.org/licenses/>.
*/
/** @file Exceptions.h
* @author Gav Wood <i@gavwood.com>
* @date 2014
*/

// Modified by Evgeniy Sukhomlinov 2018

#pragma once

#include <exception>
#include <string>
#include <boost/exception/all.hpp>
#include <boost/throw_exception.hpp>
#include "CommonData.h"

namespace XDag
{
    /// Base class for all exceptions.
    struct Exception : virtual std::exception, virtual boost::exception
    {
        Exception(std::string _message = std::string()) : m_message(std::move(_message)) {}
        const char* what() const noexcept override { return m_message.empty() ? std::exception::what() : m_message.c_str(); }

    private:
        std::string m_message;
    };

#define DEV_SIMPLE_EXCEPTION(X) struct X: virtual Exception { const char* what() const noexcept override { return #X; } }

    /// Base class for all RLP exceptions.
    struct RLPException : virtual Exception { RLPException(std::string _message = std::string()) : Exception(_message) {} };
#define DEV_SIMPLE_EXCEPTION_RLP(X) struct X: virtual RLPException { const char* what() const noexcept override { return #X; } }

    DEV_SIMPLE_EXCEPTION_RLP(BadCast);
    DEV_SIMPLE_EXCEPTION_RLP(BadRLP);
    DEV_SIMPLE_EXCEPTION_RLP(OversizeRLP);
    DEV_SIMPLE_EXCEPTION_RLP(UndersizeRLP);

    DEV_SIMPLE_EXCEPTION(BadHexCharacter);

    struct ExternalFunctionFailure : virtual Exception { public: ExternalFunctionFailure(std::string _f) : Exception("Function " + _f + "() failed.") {} };

    // error information to be added to exceptions
    using errinfo_invalidSymbol = boost::error_info<struct tag_invalidSymbol, char>;
    using errinfo_comment = boost::error_info<struct tag_comment, std::string>;
}
