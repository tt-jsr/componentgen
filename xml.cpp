#include "stdafx.h"
#include "direct.h"
#include <vector>
#include <string>
#include <fstream>
#include <set>
#include <strstream>

using namespace std;

#include "xml.h"



Xml::Xml()
{
	m_bRead = true;
	m_indent = 0;
	m_lineno = 0;
}

int Xml::open(ostream& strm)
{
	m_ostr = &strm;

	m_bRead = false;

	return XML_OK;
}

int Xml::open(istream& strm)
{
	m_bRead = true;
	m_istr = &strm;

	m_istr->setf(ios_base:: skipws);

	return XML_OK;
}

bool Xml::isRead()
{
	return m_bRead;
}

Xml::element_t Xml::GetStartElement()
{
	element_t et = GetNextElement();
	while (et != begin)
		et = GetNextElement();
	return et;
}

Xml::element_t Xml::GetNextElement()
{
	char c = 0;
	
	m_elementName = "";

	while (c != '<')
		c = GetChar();
	c = GetChar();
	if (c == '!') {
		// We have a comment
		char lastchar = 0;
		while (true) {
			c = GetChar();
			if (lastchar == '!' && c == '>')
				return GetNextElement();
			lastchar = c;
		}		
	}
	if (c == '/') {
		// we have an end element
		m_currElement = end;
	} else {
		m_currElement = begin;
		m_elementName += c;
	}
	// now collect chars
	while (true) {	
		c = GetChar();
		if (c == '>')
			return m_currElement;
		m_elementName += c;		
	}
	return m_currElement;
}

Xml::element_t Xml::GetCurrentElement()
{
	return m_currElement;
}

const char *Xml::GetElementName()
{
	return m_elementName.c_str();
}

bool Xml::IsStartElement(const char *name)
{
	if (stricmp(m_elementName.c_str(), name) == 0 && m_currElement == begin)
		return true;
	return false;
}

bool Xml::IsEndElement(const char *name)
{
	if (stricmp(m_elementName.c_str(), name) == 0 && m_currElement == end)
		return true;
	return false;
}

const char *Xml::GetValue(const char *name)
{
	m_curvalue = "";
	char c;

	if (stricmp(name, m_elementName.c_str()) != 0) {
		strstream s;
		s << "Expected element " << name << ", found " << m_elementName;
		throw XmlException(s.str(), m_lineno);
	}
	while (true) {
		c = GetChar();
		switch (c) {
		case '&':
			{
				string s;
				s = "&";
				while (c != ';') {
					c = GetChar();
					s += c;
				};
				if (stricmp(s.c_str(), "&amp;") == 0)
					m_curvalue += '&';
				if (stricmp(s.c_str(), "&lt;") == 0)
					m_curvalue += '<';
				if (stricmp(s.c_str(), "&lt;") == 0)
					m_curvalue += '>';
				if (stricmp(s.c_str(), "&quot;") == 0)
					m_curvalue += '"';
				if (stricmp(s.c_str(), "&nbsp;") == 0)
					m_curvalue += ' ';
			}
			break;
		case '<':
			m_istr->putback('<');
			return m_curvalue.c_str();
		default:
			m_curvalue += c;
			break;
		}
	}	
}

int Xml::GetIntValue(const char *name)
{
	return atoi(GetValue(name));
}

long Xml::GetLongValue(const char *name)
{
	return atol(GetValue(name));
}


void Xml::starttag(const char *p)
{
	if (m_bRead) {
		
	} else {
		indent();
		*m_ostr << "<" << p << ">" << endl;
		m_indent += 4;
	}
}

void Xml::endtag(const char *p)
{	
	if (m_bRead) {
		
	} else {
		m_indent -= 4;
		indent();
		*m_ostr << "</" << p << ">" << endl;
	}
}


void Xml::write(const char *name, const string& s)
{
	indent();
	*m_ostr << "<" << name << ">";
	const char *p = s.c_str();
	while (*p) {
		switch (*p) {
		case '<':
			*m_ostr << "&lt;";
			break;
		case '>':
			*m_ostr << "&gt;";
			break;
		case '"':
			*m_ostr << "&quot;";
			break;
		case '&':
			*m_ostr << "&amp;";
			break;
		default:
			*m_ostr << *p;
			break;
		}
		++p;
	}

	*m_ostr << "</" << name << ">" << endl;
}

void Xml::write(const char *name, int n)
{
	indent();
	*m_ostr << "<" << name << ">" << n << "</" << name << ">" << endl;
}

void Xml::write(const char *name, long l)
{
	indent();
	*m_ostr << "<" << name << ">" << l << "</" << name << ">" << endl;
}

void Xml::indent()
{
	for (int i = 0; i < m_indent; i++)
		*m_ostr << ' ';
}

char Xml::GetChar()
{
	char c = m_istr->get();
	if (c == '\n')
		++m_lineno;
	return c;
}
