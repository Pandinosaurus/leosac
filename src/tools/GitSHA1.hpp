/*
    Copyright (C) 2014-2017 Leosac

    This file is part of Leosac.

    Leosac is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Leosac is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <string>

/**
 * This is the header file for a generated source file,
 * GitSHA1.cpp. CMake generates that file from
 * the GitSHA1.cpp.in file.
 */

namespace Leosac
{
namespace Tools
{
/**
 * Retrieve the SHA1 of the HEAD commit when
 * Leosac was built.
 */
const std::string &get_git_sha1();
}
}