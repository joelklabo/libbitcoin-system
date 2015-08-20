/**
 * Copyright (c) 2011-2015 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin.
 *
 * libbitcoin is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License with
 * additional permissions to the one published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version. For more information see LICENSE.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include <bitcoin/bitcoin/utility/deadline.hpp>

#include <functional>
#include <system_error>
#include <boost/asio.hpp>
#include <boost/date_time.hpp>
#include <boost/system/error_code.hpp>
#include <bitcoin/bitcoin/error.hpp>
#include <bitcoin/bitcoin/utility/assert.hpp>
#include <bitcoin/bitcoin/utility/threadpool.hpp>

namespace libbitcoin {

using std::placeholders::_1;

static const auto std_timeout = error::channel_timeout;
static const auto std_cancel = error::operation_failed;
static const auto boost_cancel = boost::asio::error::operation_aborted;

// This can be used safely in a heap allocated class.
// This is guaranteed to call handler exactly once (unless prepetually reset).
deadline::deadline(threadpool& pool, boost::posix_time::time_duration duration,
    handler handle_expiration)
  : duration_(duration), timer_(pool.service()), handler_(handle_expiration)
{
    DEBUG_ONLY(const auto cancel = error::boost_to_error_code(boost_cancel));
    BITCOIN_ASSERT_MSG(cancel == std_cancel, "Unexpected error code mapping.");
}

// static, allows caller to test for timer cancellation in handler.
bool deadline::canceled(const std::error_code& ec)
{
    return ec == std_cancel;
}

// Start can be used to reset the timer as well.
void deadline::start()
{
    stop();
    timer_.expires_from_now(duration_);
    timer_.async_wait(
        std::bind(&deadline::handle_timer,
            shared_from_this(), _1));
}

// Cancellation calls handle_timer with boost::asio::error::operation_aborted.
void deadline::stop()
{
    boost::system::error_code code;
    timer_.cancel(code);

    // If cancellation fails the call to handle_timer would be delayed until
    // the timer actually fires. So there is no need to handle this error, it
    // just results in a slower completion (and is very unlikely to occur).
    BITCOIN_ASSERT(code);
}

void deadline::handle_timer(const boost::system::error_code& ec)
{
    // A boost success code implies that the timer fired.
    if (!ec)
        handler_(std_timeout);
    else
        handler_(error::boost_to_error_code(ec));
}

} // namespace libbitcoin
