/*
 * Copyright (C) 2008-2011 Geometer Plus <contact@geometerplus.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */

#ifndef __MERGEDSTREAM_H__
#define __MERGEDSTREAM_H__

#include <shared_ptr.h>
#include <ZLInputStream.h>

class MergedStream : public ZLInputStream {

protected:
	virtual shared_ptr<ZLInputStream> nextStream() = 0;
	virtual void resetToStart() = 0;

private:
	bool open();
	size_t read(char *buffer, size_t maxSize);
	void close();
	void seek(int offset, bool absoluteOffset);
	size_t offset() const;
	size_t sizeOfOpened();

private:
	shared_ptr<ZLInputStream> myCurrentStream;
	size_t myOffset;
};

#endif /* __MERGEDSTREAM_H__ */
