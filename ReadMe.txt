=================  Template file (*.tmpl) ===================================
A template (.tmpl) file takes the following form...

<root>
	<file>
		<input>stdafx.h</input>
		<output>ProjDir/stdafx.h</output>
		<desc>Precompiled header</desc>
	</file>
	<file>
		<input>stdafx.cpp</input>
		<output>$(ProjDir)/stdafx.cpp</output>
		<desc>Precompiled source</desc>
	</file>
	<variable>
		<name>ProjDir</name>
		<prompt>Enter the directory of the project</prompt>
	</variable>
</root>

===== tag definition ========

<file>  Describes the input and output files
    <input> This is the filename of the input template
    <output> This is the output file name. You may use variable substitution here. Directories will be created
             as necessary
</file>

<variable>  Create a variable to substitute
     <name> This is the name of the variable. Any occurance of $(name) will cause the sequence to be
            replaced with the value of the variable
     <prompt> This will cause a dialog box to prompt for the value of the variable
     <value>  This will define the variable. Variable substitution can be used here as well
     <file>  This will define the variable from the contents of the specified file
             (this is not yet implemented)
     
     <prompt>, <value> and <file> are mutually exclusive
</variable>

==============  Input files ========================

Input files are copied to the output until a $(xxx) variable is found. This is then substituted with the
variable defined in the template file.

There are a number of predefined variables:
$(DATE) will cause the date to be output in the form of "Wed Jan 02 02:03:55 2005"
$(TIMESTAMP) will cause the current date to be output as the number of seconds since 1970
$(RANDOM) will cause a random number to be generated
$(GUID) will generate a GUID

Variable substitutuion taks the form of:
%(var) - Subsitution will be converted to lower case
@(var) - substitution will be converted to uppercase
$(var) - No case conversion will take place