/*
 * Copyright (C) 2004-2011 Geometer Plus <contact@geometerplus.com>
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

#ifndef __FORMATPLUGIN_H__
#define __FORMATPLUGIN_H__

#include <jni.h>

#include <string>
#include <vector>

#include <shared_ptr.h>

class Book;
class BookModel;
//class ZLOptionsDialog;
//class ZLOptionsDialogTab;
class ZLFile;
class ZLInputStream;
class ZLImage;

/*class FormatInfoPage {

protected:
	FormatInfoPage();

public:
	virtual ~FormatInfoPage();
};*/

class FormatPlugin {

protected:
	FormatPlugin();

public:
	virtual ~FormatPlugin();

	virtual bool providesMetaInfo() const = 0;
	virtual bool acceptsFile(const ZLFile &file) const = 0;
	//virtual FormatInfoPage *createInfoPage(ZLOptionsDialog &dialog, const ZLFile &file);

	virtual const std::string &tryOpen(const ZLFile &file) const;
	virtual bool readMetaInfo(Book &book) const = 0;
	virtual bool readModel(BookModel &model) const = 0;
	virtual shared_ptr<ZLImage> coverImage(const ZLFile &file) const;

protected:
	static void detectEncodingAndLanguage(Book &book, ZLInputStream &stream);
	static void detectLanguage(Book &book, ZLInputStream &stream);
};

class PluginCollection {

public:
	static PluginCollection &Instance();
	static void deleteInstance();

private:
	PluginCollection();

public:
	~PluginCollection();

public:
	shared_ptr<FormatPlugin> plugin(const ZLFile &file, bool strong);
	shared_ptr<FormatPlugin> plugin(const Book &book);

	bool isLanguageAutoDetectEnabled();
	std::string defaultLanguage();
	std::string defaultEncoding();

private:
	static PluginCollection *ourInstance;

	jobject myJavaInstance;

	std::vector<shared_ptr<FormatPlugin> > myPlugins;
};

//inline FormatInfoPage::FormatInfoPage() {}
//inline FormatInfoPage::~FormatInfoPage() {}
inline FormatPlugin::FormatPlugin() {}
inline FormatPlugin::~FormatPlugin() {}
//inline FormatInfoPage *FormatPlugin::createInfoPage(ZLOptionsDialog&, const ZLFile&) { return 0; }

#endif /* __FORMATPLUGIN_H__ */
