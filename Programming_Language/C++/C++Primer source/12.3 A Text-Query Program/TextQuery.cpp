#include "TextQuery.h"
#include <sstream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

TextQuery::TextQuery(ifstream& ifs) : file(new vector<string>)
{
	string text;
	while (getline(ifs, text)) //对文件中每一行，保存到text中
	{
		file->push_back(text);  //保存文本
		int n = file->size() - 1;  //当前行号
		istringstream line(text); //将行文本分解为单词
		string word;
		while (line >> word) //对行中的每个单词
		{
			auto &lines = wm[word]; //如果单词不在wm中，以之为下标在wm中添加一项，lines是一个share_ptr
			if (!lines) 
				lines.reset(new set<line_no>);  // 如果第一次遇到这个单词，此指针为空，则新建一个set
			lines->insert(n); //将此行号插入set中
		}
	}
}

QueryResult TextQuery::query(const string& s) const
{
	static shared_ptr<set<line_no> > nodata(new set<line_no>);
    // 使用find而不是下标运算符来查找单词，避免将单词添加到wm中
	auto loc = wm.find(s);
	if (loc == wm.end())
		return QueryResult(s, nodata, file);  // 未找到
	else
		return QueryResult(s, loc->second, file);
}

std::ostream& print(std::ostream& os, const QueryResult& qr)
{
	// 如果找到了单词，打印出现次数和所有出现的位置
    os << qr.sought << " occurs " << qr.lines->size() << " "
		<< "time" << (qr.lines->size() > 1 ? "s" : "") << endl;
	// 打印单词出现的每一行
    for (auto num : *qr.lines)
		os << "\t(line " << num + 1 << ") " << *(qr.file->begin() + num) << endl;
	return os;
}

