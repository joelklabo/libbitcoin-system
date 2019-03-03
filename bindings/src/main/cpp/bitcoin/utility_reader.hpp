/**
 * Copyright (c) 2011-2017 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef LIBBITCOIN__UTILITY_READER_HPP
#define LIBBITCOIN__UTILITY_READER_HPP

#include <cstddef>
#include <cstdint>
#include <string>
#include <bitcoin/bitcoin/error.hpp>
#include <utility_data_chunk.hpp>
#include <math_hash_digest.hpp>
#include <math_short_hash.hpp>
#include <math_mini_hash.hpp>

namespace libbitcoin {
namespace api {

/// Reader interface.
class BC_API utility_reader
{
public:
	virtual ~utility_reader();

    /// Context.
    virtual operator bool() const = 0;
    virtual bool operator!() const = 0;
    virtual bool is_exhausted() const = 0;
    virtual void invalidate() = 0;

    /// Read hashes.
    virtual math_hash_digest read_hash() = 0;
    virtual math_short_hash read_short_hash() = 0;
    virtual math_mini_hash read_mini_hash() = 0;

    /// Read big endian integers.
    virtual uint16_t read_2_bytes_big_endian() = 0;
    virtual uint32_t read_4_bytes_big_endian() = 0;
    virtual uint64_t read_8_bytes_big_endian() = 0;
    virtual uint64_t read_variable_big_endian() = 0;
    virtual size_t read_size_big_endian() = 0;

    /// Read little endian integers.
    virtual code read_error_code() = 0;
    virtual uint16_t read_2_bytes_little_endian() = 0;
    virtual uint32_t read_4_bytes_little_endian() = 0;
    virtual uint64_t read_8_bytes_little_endian() = 0;
    virtual uint64_t read_variable_little_endian() = 0;
    virtual size_t read_size_little_endian() = 0;

    /// Read/peek one byte.
    virtual uint8_t peek_byte() = 0;
    virtual uint8_t read_byte() = 0;

    /// Read all remaining bytes.
    virtual utility_data_chunk read_bytes() = 0;

    /// Read required size buffer.
    virtual utility_data_chunk read_bytes(size_t size) = 0;

    /// Read variable length string.
    virtual std::string read_string() = 0;

    /// Read required length string and trim nulls.
    virtual std::string read_string(size_t size) = 0;

    /// Advance iterator without reading.
    virtual void skip(size_t size) = 0;
};

} // namespace api
} // namespace libbitcoin

#endif
