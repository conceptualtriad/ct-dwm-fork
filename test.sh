#!/bin/bash

< file.txt PERLIO=:utf8 perl -Mlocale -MUnicode::Normalize -lne '
  $_=NFKD($_); $n{$&}++ if /^[[:alpha:]]/u && /^\X/u;
    END{for $i (sort keys %n) {print "$n{$i} $i"}}'
