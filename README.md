wb
==

[![Build Status](https://travis-ci.org/mntnorv/wb.png)](https://travis-ci.org/mntnorv/wb)

A wallbase.cc image search tool, written in C

Features
--------

`wb` can get images from:
 - The main search page
 - Toplist
 - Random images

All wallbase.cc image filters are supported:
 - Query string
 - Color
 - Boards (Manga / Anime, Wallpapers / General, High Resolution)
 - Purity (SFW, Sketchy, NSFW)
 - Aspect ratio
 - Resolution

Images can be sorted by relevance, views, date and favorites.

`wb` also supports logging in to wallbase.cc for getting **NSFW** images.

Dependencies
------------

wb depends on:
 - `libcurl` for networking functionality
 - `libtidy` for HTML cleanup, HTML to XML conversion
 - `libxml2` for XPath functionality

Installation
------------

To install run `make` and `make install`.

Bugs
----

If you find a bug create an issue in this Github page.

License
-------

```
Copyright 2013 Mantas Norvaiša.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>.
This is free software: you are free to change and redistribute it. There is NO
WARRANTY, to the extent permitted by law.
```
