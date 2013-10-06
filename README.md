# snake

This program is a game named snake, it is still under development, there are some functions waiting to be added.

## Environment
You should download the ncurses first, if you do not have it. Do this:

    $ curl -O ftp://ftp.gnu.org/gnu/ncurses/ncurses-5.9.tar.gz
    $ tar -xzvf ncurses-5.9.tar.gz
    $ cd ./ncurses-5.9
    $ ./configure --prefix=/usr/local \
    --without-cxx --without-cxx-binding --without-ada --without-progs --without-curses-h \
    --with-shared --without-debug \
    --enable-widec --enable-const --enable-ext-colors --enable-sigwinch --enable-wgetch-events \
    && make
    $ sudo make install

The system can be OS X, and other linux versions.

## Installation & Running

    git clone https://github.com/Liuyu314/snake.git
    cd snake
    make

## Usage

    UP - w
    DOWN - s
    LEFT - a
    RIGHT - d
    QUIT - q

## License

MIT License