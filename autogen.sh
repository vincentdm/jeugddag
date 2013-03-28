#!/bin/bash

autoreconf -v -Im4 && ./configure $*

exit $?
