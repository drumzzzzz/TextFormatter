// Adapter design pattern project for UWGB Computer Science Fall semester, 2020.
// Reads a list of text strings from an input file, performs the selected formatting operations
// and saves the results to an output file.
#include <iostream>
#include <string>
#include <vector>
#include <ctype.h>
#include "FileIO.h"

using namespace std;

// Abstarct standard formatter operation types
// lc: lower case, uc: upper case, rp: remove punctuation
class Converter
{
public:
	virtual void format(string process_type, vector<string>* file_text) = 0;
	virtual ~Converter() {}
};

// Abstract advanced formatter operation types
// cw: capitalize word, cs: capitalize sentence, al: alternate letters, 
class AdvancedConverter
{
public:
	AdvancedConverter() {}
	virtual void capitalizeWord(vector<string>* file_text) = 0;
	virtual void decapitalizeWord(vector<string>* file_text) = 0;
	virtual void alternateLetters(vector<string>* file_text) = 0;

	virtual ~AdvancedConverter() {}
};

// Capitalize per word converter
class CapitalConverter: public AdvancedConverter
{
public:
	void capitalizeWord(vector<string>* file_text) override
	{
		char c;
		bool isLetter;

		cout << "[Formatting to capital letters per word]" << endl;

		for (string& s : *file_text)
		{
			if (!s.empty())
			{
				for (unsigned int i = 0; i < s.size(); i++)
				{
					if (isalpha(s[i]))
					{
						if (i == 0 || !isalpha(s[i - 1]))
						{
							s[i] = std::toupper(s[i]);
						}
					}
				}
			}
		}
	}

	void decapitalizeWord(vector<string>* file_text) override
	{}

	void alternateLetters(vector<string>* file_text) override
	{}

	~CapitalConverter() {}
};

// Decapitalize per word converter
class DeCapitalConverter : public AdvancedConverter
{
public:
	void decapitalizeWord(vector<string>* file_text) override
	{
		char c;
		bool isLetter;

		cout << "[Formatting to decapitalized letters per word]" << endl;

		for (string& s : *file_text)
		{
			if (!s.empty())
			{
				for (unsigned int i = 0; i < s.size(); i++)
				{
					isLetter = isalpha(s[i]);

					if ((i == 0 && isLetter) || (i > 0 && !isalpha(s[i - 1]) && isLetter))
					{
						s[i] = std::tolower(s[i]);
					}
					else if (isLetter)
					{
						s[i] = std::toupper(s[i]);
					}
				}
			}
		}
	}

	void capitalizeWord(vector<string>* file_text) override
	{}

	void alternateLetters(vector<string>* file_text) override
	{}

	~DeCapitalConverter() {}
};

// Alternate per letter converter
class AlternateConverter : public AdvancedConverter
{
public:
	void alternateLetters(vector<string>* file_text) override
	{
		bool isUpper = false;

		cout << "[Alternating letters per word]" << endl;

		for (string& s : *file_text)
		{
			if (!s.empty())
			{
				for (unsigned int i = 0; i < s.size(); i++)
				{
					if (isalpha(s[i]))
					{
						s[i] = (isUpper) ? toupper(s[i]) : tolower(s[i]);
						isUpper = !isUpper;
					}
				}
			}
		}
	}

	void capitalizeWord(vector<string>* file_text) override
	{}

	void decapitalizeWord(vector<string>* file_text) override
	{}

	~AlternateConverter() {}
};

// Advanced text formatting adapter
class TextAdapter : public Converter
{
	AdvancedConverter* advancedConverter;

public:
	TextAdapter(string file_type)
	{
		if (file_type.compare("cw") == 0) 
		{
			advancedConverter = new CapitalConverter();
		}
		else if (file_type.compare("dw") == 0)
		{
			advancedConverter = new DeCapitalConverter();
		}
		else if (file_type.compare("al") == 0)
		{
			advancedConverter = new AlternateConverter();
		}
	}

	void format(string file_type, vector<string>* file_text) override
	{
		if (file_type.compare("cw") == 0) 
		{
			advancedConverter->capitalizeWord(file_text);
		}
		else if (file_type.compare("dw") == 0)
		{
			advancedConverter->decapitalizeWord(file_text);
		}
		else if (file_type.compare("al") == 0) 
		{
			advancedConverter->alternateLetters(file_text);
		}
	}

	~TextAdapter()
	{
		delete advancedConverter;
	}
};

// TextFormatter class: performs formatting per operation type and displays results
class TextFormatter : public Converter , public FileIO
{
	TextAdapter* textAdapter = nullptr;

private:
	static void DisplayResults(vector<string>* file_text)
	{
		cout << endl;
		for (string s : *file_text)
		{
			cout << s << endl;
		}
		cout << endl;
	}

public:
	void format(string format_type, vector<string>* file_text) override
	{		
		// Standard converter: upper/lower case
		if (format_type.compare("uc") == 0 || format_type.compare("lc") == 0)
		{
			bool isUpper = format_type.compare("uc") == 0;

			cout << "[Formatting to " << ((isUpper) ? "Upper" : "Lower") << " Case]";
			
			for (string &s : *file_text)
			{
				if (!s.empty())
				{
					for (unsigned int i = 0; i < s.size(); i++)
					{
						if (!ispunct(s[i]) && isalpha(s[i]))
							s[i] = (isUpper) ? toupper(s[i]) : tolower(s[i]);
					}
				}
			}
		}
		// Standard converter: remove puncuation
		else if (format_type.compare("rp") == 0)
		{
			cout << "[Formatting to no punctuation]";

			for (string& s : *file_text)
			{
				if (!s.empty())
				{
					for (unsigned int i = 0; i < s.size(); i++)
					{
						if (ispunct(s[i]))
						{
							s[i] = '\0';
						}
					}
				}
			}
		}
		// Advanced converter: captitalize words, decapitalize words or alternate letters 
		else if (format_type.compare("cw") == 0 || format_type.compare("dw") == 0 || format_type.compare("al") == 0)
		{
			textAdapter = new TextAdapter(format_type);
			textAdapter->format(format_type, file_text);
			delete textAdapter;
		}
		else // Invalid or non-implemented operation
		{
			cout << "\nSkipping Unknown Command Operation: " << format_type << endl;
			return;
		}

		DisplayResults(file_text);
	}

	// File operations
	
	static vector<string>* ReadFile(string filename)
	{
		cout << "Reading file: '" << filename << "'" << endl;
		return fileRead(filename);
	}

	static bool WriteFile(string filename, vector<string>* data)
	{
		cout << "Writing file: '" << filename << "'" << endl;
		return fileWrite(filename, data, false);
	}
};

// Argument extents
const int ARGUMENT_MAX = 11;
const int ARGUMENT_SIZE = 2;

int main(int argc, char* argv[])
{
	// Validate arguments
	if (argc <= 3 || argc > ARGUMENT_MAX)
	{
		cerr << "Usage: " << endl <<
			argv[0] << "'text file in' 'text file out <operation> <operation> ...'" << endl
			<< "Example: inputfile.txt outputfile.txt lc cw" << endl;
		return -1;
	}

	// Iterate, validate and format arguments - add to array
	vector<string> format_types;
	for (int idx = 3; idx < argc; idx++)
	{
		if (strlen(argv[idx]) != ARGUMENT_SIZE)
		{
			cout << "Invalid Command Argument: " << argv[idx] << endl;
			return -1;
		}

		string arg = argv[idx];
		
		for (unsigned int i = 0; i < arg.size(); i++)
		{
			arg[i] = tolower(arg[i]);
		}

		format_types.push_back(arg);
	};

	// Create formatter, read text and perform the operations 
	TextFormatter textFormatter;
	vector<string>* file_text_in = TextFormatter::ReadFile(argv[1]);

	for(string format_type : format_types)
	{
		textFormatter.format(format_type, file_text_in);
	}

	// Save results
	TextFormatter::WriteFile(argv[2], file_text_in);

	return 0;
}