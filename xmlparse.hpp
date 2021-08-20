#pragma once

#include <map>
#include <string>
#include <vector>

class XMLNode
{
  public:
    std::string tag;
    std::map<std::string, std::string> fields;
    std::vector<XMLNode*> children;
    std::vector<XMLNode*> interfaces;
    XMLNode(const std::string& t) : tag(t)
    {}
    void AddChild(XMLNode* x)
    {
        children.push_back(x);
    }
    void do_Print(int indent)
    {
        for (int i = 0; i < indent; i++)
            printf("  ");
        printf("%s", tag.c_str());
        if (fields["name"] != "")
        {
            printf(" name=[%s]", fields["name"].c_str());
        }
        printf("\n");
        for (XMLNode* ch : children)
        {
            ch->do_Print(indent + 1);
        }
    }
    void Print()
    {
        do_Print(0);
    }
    void SetName(const std::string& n)
    {
        fields["name"] = n;
    }
    std::vector<std::string> GetChildNodeNames();
    std::vector<std::string> GetInterfaceNames();
};

XMLNode* ParseXML(const std::string& sv);
void DeleteTree(XMLNode* x);