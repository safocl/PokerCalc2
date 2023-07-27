#\file CmakeLists.txt
#\copyright GPL-3.0-or-later
#\author safocl (megaSafocl)
#\date 2023
#
#\detail \"Copyright safocl (megaSafocl) 2023\"
#This file is part of PokerCalc2.
#
#PokerCalc2 is free software: you can redistribute it and/or modify it under
#the terms of the GNU General Public License as published by the Free Software
#Foundation, either version 3 of the License, or any later version.
#
#PokerCalc2 is distributed in the hope that it will be useful, but
#WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
#or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
#more details.
#
#You should have received a copy of the GNU General Public License along with
#PokerCalc2. If not, see <https://www.gnu.org/licenses/>.

cmake_minimum_required( VERSION 3.12 )
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# add_compile_options(-std=gnu++2b)
add_compile_options(-Wall -Wextra -Wformat -Wformat-security -pedantic -pedantic-errors -Werror -g)
add_compile_options(-fPIC -pie -fstack-protector)
project( PokerCalc2 LANGUAGES CXX )

add_subdirectory( src )
