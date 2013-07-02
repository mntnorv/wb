/*
 * wb - A wallbase.cc image downloader
 *
 * Copyright (C) 2013 Mantas Norvaiša
 *
 * This file is part of wb.
 * 
 * wb is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * wb is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with wb.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>

#include "filesys.h"

/**
 * Checks if a directory exists
 *
 * @param path - the path of the directory to check
 * @return 1 if the dir exists, 0 otherwise
 */
int
dir_exists(const char *path) {
	int exists = 0;
	DIR *dir;
	dir = opendir(path);

	if (dir != NULL) {
		exists = 1;
		closedir(dir);
	}

	return exists;
}
