/** @file
    @brief Implementation

    @date 2014

    @author
    Ryan Pavlik
    <ryan@sensics.com>
    <http://sensics.com>
*/

// Copyright 2014 Sensics, Inc.
//
// All rights reserved.
//
// (Final version intended to be licensed under
// the Apache License, Version 2.0)

// Internal Includes
#include "PathParseAndRetrieve.h"
#include <osvr/Routing/Constants.h>
#include <osvr/Routing/PathNode.h>
#include <osvr/Util/Verbosity.h>

// Library/third-party includes
#include <boost/assert.hpp>
#include <boost/algorithm/string/find_iterator.hpp>
#include <boost/algorithm/string/finder.hpp>
#include <boost/range/adaptor/sliced.hpp>

// Standard includes
// - none

namespace osvr {
namespace routing {
    PathNode &pathParseAndRetrieve(std::string const &path, PathNode &root) {

        using std::string;
        using boost::split_iterator;
        using boost::algorithm::make_split_iterator;
        using boost::adaptors::sliced;
        using boost::first_finder;
        using boost::is_equal;
        BOOST_ASSERT_MSG(root.isRoot(), "Must pass the root node!");
        if (path.empty() || path == getPathSeparator()) {
            /// @todo is an empty path valid input?
            return root;
        }
        if (path.at(0) != getPathSeparatorCharacter()) {
            throw std::runtime_error(
                "Path must be absolute (begin with a forward slash)!");
        }
        PathNode *ret = &root;

        // Get the boost range that excludes the leading slash
        auto range_excluding_leading_slash = path | sliced(1, path.size() - 1);

        // Iterate through the chunks of the path, split by a slash.
        typedef split_iterator<string::const_iterator> string_split_iterator;
        for (string_split_iterator It = make_split_iterator(
                 range_excluding_leading_slash,
                 first_finder(getPathSeparator(), is_equal()));
             It != string_split_iterator(); ++It) {
            OSVR_DEV_VERBOSE(boost::copy_range<std::string>(*It));
            ret = &(ret->getOrCreateChildByName(
                boost::copy_range<std::string>(*It)));
        }
        return *ret;
    }
} // namespace routing
} // namespace osvr