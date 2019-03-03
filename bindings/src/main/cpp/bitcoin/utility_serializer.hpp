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
#ifndef LIBBITCOIN_UTILITY_SERIALIZER_HPP
#define LIBBITCOIN_UTILITY_SERIALIZER_HPP

#include <cstddef>
#include <cstdint>
#include <functional>
#include <string>
#include <bitcoin/bitcoin/error.hpp>
#include <bitcoin/bitcoin/math/hash.hpp>
#include <bitcoin/bitcoin/utility/data.hpp>
////#include <bitcoin/bitcoin/utility/noncopyable.hpp>
//#include <bitcoin/bitcoin/utility/writer.hpp>
#include <bitcoin/bitcoin/utility/serializer.hpp>
#include <math_hash_digest.hpp>
#include <math_short_hash.hpp>
#include <math_mini_hash.hpp>
#include <utility_data_slice.hpp>
#include <utility_serializer_functor.hpp>

namespace libbitcoin {
namespace api {

/// Writer to wrap arbitrary iterator.
template <typename Iterator>
class utility_serializer
//  : public writer/*, noncopyable*/
{
public:
//    typedef std::function<void(serializer<Iterator>&)> functor;

    utility_serializer(const Iterator begin);

    template <typename Tuple>
    void write_forward(const Tuple& data);

    template <typename Tuple>
    void write_reverse(const Tuple& data);

    template <typename Integer>
    void write_big_endian(Integer value);

    template <typename Integer>
    void write_little_endian(Integer value);

    /// Context.
    operator bool() const;
    bool operator!() const;

    /// Write hashes.
    void write_hash(const math_hash_digest& hash);
    void write_short_hash(const math_short_hash& hash);
    void write_mini_hash(const math_mini_hash& hash);

    /// Write big endian integers.
    void write_2_bytes_big_endian(uint16_t value);
    void write_4_bytes_big_endian(uint32_t value);
    void write_8_bytes_big_endian(uint64_t value);
    void write_variable_big_endian(uint64_t value);
    void write_size_big_endian(size_t value);

    /// Write little endian integers.
    void write_error_code(const code& ec);
    void write_2_bytes_little_endian(uint16_t value);
    void write_4_bytes_little_endian(uint32_t value);
    void write_8_bytes_little_endian(uint64_t value);
    void write_variable_little_endian(uint64_t value);
    void write_size_little_endian(size_t value);

    /// Write one byte.
    void write_byte(uint8_t value);

    /// Write all bytes.
    void write_bytes(const utility_data_slice data);

    /// Write required size buffer.
    void write_bytes(const uint8_t* data, size_t size);

    /// Write variable length string.
    void write_string(const std::string& value);

    /// Write required length string, padded with nulls.
    void write_string(const std::string& value, size_t size);

    /// Advance iterator without writing.
    void skip(size_t size);

    // non-interface
    //-------------------------------------------------------------------------

    /// Delegate write to a write function.
    void write_delegated(utility_serializer_functor<Iterator> write);

    /// Utility for variable skipping of writer.
    size_t read_size_big_endian();

    /// Utility for variable skipping of writer.
    size_t read_size_little_endian();

	serializer<Iterator> getValue() {
		return value;
	}

	void setValue(serializer<Iterator> value) {
		this->value = value;
	}
private:
	serializer<Iterator> value;
//    bool valid_;
//    Iterator iterator_;
};

// Factories.
//-----------------------------------------------------------------------------

template <typename Iterator>
utility_serializer<Iterator> make_unsafe_serializer(Iterator begin);
} // namespace api
} // namespace libbitcoin

#include <bitcoin/bitcoin/impl/utility/serializer.ipp>

#endif
