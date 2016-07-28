/** @file
    @brief Implementation

    @date 2016

    @author
    Sensics, Inc.
    <http://sensics.com>

*/

// Copyright 2016 Sensics, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// 	http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// Internal Includes
#include <osvr/Util/LineLogger.h>

// Library/third-party includes
#include <spdlog/spdlog.h>

// Standard includes
#include <algorithm> // for std::move
#include <string>    // for std::string
#include <utility>   // for std::forward

namespace osvr {
namespace util {
    namespace log {
        namespace detail {

            LineLogger::LineLogger(spdlog::details::line_logger &&line_logger)
                : lineLogger_(new ::spdlog::details::line_logger(
                      std::move(line_logger))) {
                // do nothing
            }

            LineLogger::LineLogger(LineLogger &&other)
                : lineLogger_(std::move(other.lineLogger_)) {}

            LineLogger::~LineLogger() {}

            void LineLogger::write(const char *what) {
                lineLogger_->write(what);
            }

            LineLogger &LineLogger::append(const std::string &what) {
                lineLogger_->operator<<(what);
                return *this;
            }

            void LineLogger::disable() { lineLogger_->disable(); }

            bool LineLogger::is_enabled() const {
                return lineLogger_->is_enabled();
            }

        } // end namespace detail
    }     // end namespace log
} // end namespace util
} // end namespace osvr
