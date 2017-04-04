#ifndef _XML_H_
#define _XML_H_

#include <string>
#include <vector>
#include <fstream>

using namespace std;

#define XML_OK			0
#define XML_OPEN_FAILED	1

class XmlException {
public:
	XmlException(const char *msg, int lineno)
	{
		m_msg = msg;
		m_lineno = lineno;
	}
	string m_msg;
	int m_lineno;
};

class Xml {
public:
	Xml();
	enum element_t {
		begin,
		end
	};
	int open(istream&);
	int open(ostream&);
	bool isRead();
	// Advance until a start element
	element_t GetStartElement();
	// Get the next element
	element_t GetNextElement();
	element_t GetCurrentElement();
	const char *GetElementName();
	bool IsStartElement(const char *name);
	bool IsEndElement(const char *name);
	const char *GetValue(const char *name);
	int GetIntValue(const char *name);
	long GetLongValue(const char *name);

	void write(const char *name, const string&);
	void write(const char *name, int);
	void write(const char *name, long);
	void starttag(const char *);
	void endtag(const char *);
	int getFileVersion() const {return m_fileVersion;}
	void setFileVersion(int v) {m_fileVersion = v;}
private:
	void indent();
	char GetChar();
private:
	int m_indent;
	bool m_bRead;
	int m_fileVersion;
	ostream *m_ostr;
	istream *m_istr;
	element_t m_currElement;
	string m_elementName;
	string m_curvalue;
	int m_lineno;
};

#endif //_XML_H_
