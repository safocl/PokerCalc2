#*@file meson.build
#*@copyright GPL-3.0-or-later
#*@author safocl (megaSafocl)
#*@date 2023
#
#*@detail \"Copyright safocl (megaSafocl) 2023\"
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

src = files('main.cpp', 'card.cpp', 'hand.cpp', 'deck.cpp', 'board.cpp',
      'equity.cpp', 'strength.cpp', 'combo.cpp', 'range.cpp')

dep_thread = dependency('threads')

executable('PokerCalc2', src,

          cpp_args: ['-Wformat', '-Wformat-security', '-fPIC',
                    # '-pedantic', '-pedantic-errors',
                    '-fstack-protector'],

          dependencies: dep_thread,
  )
