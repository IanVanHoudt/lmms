/*
 * ProjectVersion.cpp - compare versions in import upgrades
 *
 * Copyright (c) 2007 Javier Serrano Polo <jasp00/at/users.sourceforge.net>
 * Copyright (c) 2008 Tobias Doerffel <tobydox/at/users.sourceforge.net>
 * Copyright (c) 2015 Tres Finocchiaro <tres.finocchiaro/at/gmail.com>
 *
 * This file is part of LMMS - http://lmms.io
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program (see COPYING); if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 *
 */


#include "ProjectVersion.h"

int parseMajor(QString & version) {
	return version.section( '.', 0, 0 ).toInt();
}




int parseMinor(QString & version) {
	return version.section( '.', 1, 1 ).toInt();
}




int parseRelease(QString & version) {
	return version.section( '.', 2 ).section( '-', 0, 0 ).toInt();
}




QString parseBuild(QString & version) {
	return version.section( '.', 2 ).section( '-', 1 );
}




ProjectVersion::ProjectVersion(QString version, CompareType c) :
	m_version(version),
	m_major(parseMajor(m_version)),
	m_minor(parseMinor(m_version)),
	m_release(parseRelease(m_version)) ,
	m_build(parseBuild(m_version)),
	m_compareType(c)
{
}




ProjectVersion::ProjectVersion(const char* version, CompareType c) :
	m_version(QString(version)),
	m_major(parseMajor(m_version)),
	m_minor(parseMinor(m_version)),
	m_release(parseRelease(m_version)),
	m_build(parseBuild(m_version)),
	m_compareType(c)
{
}




int ProjectVersion::compare(const ProjectVersion & a, const ProjectVersion & b, CompareType c)
{
	if(a.getMajor() != b.getMajor())
	{
		return a.getMajor() - b.getMajor();
	}

	else if(c == CompareType::Major)
	{
		return 0;
	}

	if(a.getMinor() != b.getMinor())
	{
		return a.getMinor() - b.getMinor();
	}
	else if(c == CompareType::Minor)
	{
		return 0;
	}

	if(a.getRelease() != b.getRelease())
	{
		return a.getRelease() - b.getRelease();
	}
	else if(c == CompareType::Release)
	{
		return 0;
	}

	// make sure 0.x.y > 0.x.y-patch
	if(a.getBuild().isEmpty())
	{
		return 1;
	}
	if(b.getBuild().isEmpty())
	{
		return -1;
	}

	return QString::compare(a.getBuild(), b.getBuild());
}




int ProjectVersion::compare(ProjectVersion v1, ProjectVersion v2)
{
	return compare(v1, v2, std::min(v1.getCompareType(), v2.getCompareType()));
}



