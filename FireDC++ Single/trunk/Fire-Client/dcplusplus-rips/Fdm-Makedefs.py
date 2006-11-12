#!/usr/bin/python
import re
import codecs
import xml.sax.saxutils

def makename(oldname):
	name = "";
	nextBig = True;
	for x in oldname:
		if x == '_':
			nextBig = True;
		else:
			if nextBig:
				name += x.upper();
				nextBig = False;
			else:
				name += x.lower();
				
	return name;

	
version = re.search("VERSIONSTRING (\S+)", file("../client/version.h").read()).group(1)

varstr = "";
strings = "";
varname = "";
names = "";
varstrTwo = "";
stringsTwo = "";
varnameTwo = "";
namesTwo = "";
boolTwoVar = "F";
boolTwoDef = "F";

prolog = "";

example = '<?xml version="1.0" encoding="utf-8" standalone="yes"?>\n';
example += '<Language Name="Example Language" Author="Pothead" Version=' + version + ' Revision="1" RightToLeft="0">\n'
example += '\t<Strings>\n';

lre = re.compile('\s*(\w+),\s*//\s*\"(.+)\"\s*')

decoder = codecs.getdecoder('cp1252')
encoder = codecs.getencoder('utf8')
recodeattr = lambda s: encoder(decoder(xml.sax.saxutils.quoteattr(s))[0])[0]
recodeval = lambda s: encoder(decoder(xml.sax.saxutils.escape(s, {"\\t" : "\t"}))[0])[0]

for x in file("dcplusplus-rips/Fire-StringDefs.h", "r"):
    if x.startswith("// @StringsTwo: "):
        varstrTwo = x[15:].strip()
        boolTwoDef = "V";
    elif x.startswith("// @NamesTwo: "):
        varnameTwo = x[13:].strip()
        boolTwoDef = "V";
    elif x.startswith("// @Strings: "):
        varstr = x[13:].strip();
    elif x.startswith("// @Names: "):
        varname = x[11:].strip();
    elif x.startswith("// @Prolog: "):
        prolog += x[12:];
    elif len(x) >= 5:
        match = lre.match(x);
        if match is not None:
            name , value = match.groups();
            if boolTwoDef == "V":
                boolTwoDef = "VV"
                stringsTwo += '"' + value + '", \n'
                newname = makename(name)
                namesTwo += '"' + newname + '", \n'
                example += '\t</Strings>\n'
                example += '\t<StringsTwo>\n'
                example += '\t\t<StringTwo Name=%s>%s</StringTwo>\n' % (recodeattr(newname),  recodeval(value));
            elif boolTwoDef == "F":
                strings += '"' + value + '", \n'
                newname = makename(name)
                names += '"' + newname + '", \n'
                example += '\t\t<String Name=%s>%s</String>\n' % (recodeattr(newname),  recodeval(value));
            elif boolTwoDef == "VV":
                stringsTwo += '"' + value + '", \n'
                newname = makename(name)
                namesTwo += '"' + newname + '", \n'
                example += '\t\t<StringTwo Name=%s>%s</StringTwo>\n' % (recodeattr(newname),  recodeval(value))
		
example += '\t</StringsTwo>\n';
example += '</Language>\n';

file('dcplusplus-rips/Fire-StringDefs.cpp', 'w').write(prolog + varstr + " = {\n" + strings + "};\n" + varname + " = {\n" + names + "};\n" + varstrTwo + " = {\n" + stringsTwo + "};\n" + varnameTwo + " = {\n" + namesTwo + "};\n");
file('../Fire-Example.xml', 'w').write(example);
