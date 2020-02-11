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
#ifndef LIBBITCOIN__MESSAGE_HEADING_HPP
#define LIBBITCOIN__MESSAGE_HEADING_HPP

//#include <cstdint>
#include <cstddef>
//#include <istream>
//#include <string>
//#include <boost/array.hpp>
//#include <bitcoin/bitcoin/constants.hpp>
#include <bitcoin/bitcoin/define.hpp>
#include <bitcoin/bitcoin/message/heading.hpp>
//#include <bitcoin/bitcoin/math/checksum.hpp>
#include <bitcoin/p_std_string.hpp>
#include <bitcoin/utility_data_chunk.hpp>
//#include <bitcoin/bitcoin/utility/reader.hpp>
//#include <bitcoin/bitcoin/utility/writer.hpp>

namespace libbitcoin {
//namespace message {
namespace api {

//enum class message_type
//{
//    unknown,
//    address,
//    alert,
//    block,
//    block_transactions,
//    compact_block,
//    fee_filter,
//    filter_add,
//    filter_clear,
//    filter_load,
//    get_address,
//    get_block_transactions,
//    get_blocks,
//    get_data,
//    get_headers,
//    headers,
//    inventory,
//    memory_pool,
//    merkle_block,
//    not_found,
//    ping,
//    pong,
//    reject,
//    send_compact,
//    send_headers,
//    transaction,
//    verack,
//    version
//};

class BC_API message_heading
{
public:
    static size_t maximum_size();
    static size_t maximum_payload_size(uint32_t version, bool witness);
    static size_t satoshi_fixed_size();
    static message_heading factory(const utility_data_chunk& data);
//    static message_heading factory(std::istream& stream);
//    static message_heading factory(reader& source);

    message_heading();
//    message_heading(uint32_t magic, const std::string& command, uint32_t payload_size,
//        uint32_t checksum);
    message_heading(uint32_t magic, p_std_string& command, uint32_t payload_size,
        uint32_t checksum);
    message_heading(const message_heading& other);
//    message_heading(message_heading&& other);

    uint32_t magic() const;
    void set_magic(uint32_t value);

    p_std_string command();
//    const std::string& command() const;
//    void set_command(const std::string& value);
    void set_command(p_std_string& value);

    uint32_t payload_size() const;
    void set_payload_size(uint32_t value);

    uint32_t checksum() const;
    void set_checksum(uint32_t value);

    message::message_type type() const;

    bool from_data(const utility_data_chunk& data);
//    bool from_data(std::istream& stream);
//    bool from_data(reader& source);
    utility_data_chunk to_data() const;
//    void to_data(std::ostream& stream) const;
//    void to_data(writer& sink) const;
    bool is_valid() const;
    void reset();

    // This class is move assignable but not copy assignable.
//    message_heading& operator=(message_heading&& other);
    message_heading& assign(message_heading&& other);
//    void operator=(const message_heading&) = delete;

//    bool operator==(const message_heading& other) const;
    bool eq(const message_heading& other) const;
//    bool operator!=(const message_heading& other) const;

public:
    message::heading* getValue() {
        return value_;
    }

    void setValue(message::heading* value) {
        value_ = value;
    }
private:
    message::heading* value_;
//    uint32_t magic_;
//    std::string command_;
//    uint32_t payload_size_;
//    uint32_t checksum_;
};

} // namespace api
//} // namespace message
} // namespace libbitcoin

#endif
