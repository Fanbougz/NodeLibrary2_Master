//
// Created by Dorian on 6/5/2022.
//

#ifndef LIBRARY_STRINGLIBRARY_H
#define LIBRARY_STRINGLIBRARY_H

#endif //LIBRARY_STRINGLIBRARY_H


#include "Context.h"
#include "Node.h"
#include "Attribute.h"
#include "NodeEvaluationContext.h"
#include "NodeFactory.h"


#include <string>

namespace StringNodes
{

    class ConstantString : public NodeLibrary::Node
    {
    public:
        std::string Type() const override
        {
            return "ConstantString";
        }

//        [[nodiscard]]
//        std::string Description() const override
//        {
//            return "Constant string value.";
//        }

        explicit ConstantString(std::string id): NodeLibrary::Node(id)
        {

        }

        void InitAttributes() override
        {
            CreateAttribute<std::string>("String", NodeLibrary::Attribute::ValueType::Single,
                                         NodeLibrary::Attribute::Type::Static);
        }
    };


    class ConstantStringBuilder: public NodeLibrary::DefaultNodeBuilder
    {
    public:
        NodeLibrary::Node* CreateNode() override
        {
            return new ConstantString("");
        }
    };

    class StringJoin: public NodeLibrary::Node
    {
    public:
        std::string Type() const override
        {
            return "StringJoin";
        }

//        [[nodiscard]]
        std::string Description() const override
        {
            return std::string("Joins string from \"Strings\" attribute using") +
                   "delimiter specified in \"Delimiter\" and stores" +
                   "it in \"Output\"";
        }

        bool IsDynamic() const override
        {
            return true;
        }

        bool AutoComputes() const override
        {
            return true;
        }

        StringJoin(std::string id): NodeLibrary::Node(id)
        {

        }

        void InitAttributes() override
        {
            CreateAttribute<std::string>("Strings", NodeLibrary::Attribute::ValueType::Multi,
                                         NodeLibrary::Attribute::Type::Input);
            CreateAttribute<std::string>("delimiter", NodeLibrary::Attribute::ValueType::Single,
                                         NodeLibrary::Attribute::Type::Input);
            CreateAttribute<std::string>("ResultString", NodeLibrary::Attribute::ValueType::Single,
                                         NodeLibrary::Attribute::Type::Output);
        }

        bool Evaluate(NodeLibrary::NodeEvaluationContext& ctx) override
        {
            std::string delimiter = ctx.GetAttributeValue<std::string>("delimiter");
            std::vector<std::string> strings = ctx.GetAttributeArrayValue<std::string>("Strings");

            std::string result;

            if (strings.empty())
            {
                return ctx.SetAttributeValue<std::string>("ResultString", "");
            }

            unsigned int lastIndex = strings.size() - 1;
            for (unsigned int i = 0; i < strings.size(); i++)
            {
                result += strings.at(i);
                if (i != lastIndex)
                    result += delimiter;
            }

            return ctx.SetAttributeValue<std::string>("ResultString", result);
        }
    };

    class StringsJoinBuilder: public NodeLibrary::DefaultNodeBuilder
    {
        NodeLibrary::Node* CreateNode() override
        {
            return new StringJoin("");
        }
    };


    class StringSplit: public NodeLibrary::Node
    {
    public:
        std::string Type() const override
        {
            return "StringSplit";
        }

        bool IsDynamic() const override
        {
            return true;
        }

        bool AutoComputes() const override
        {
            return true;
        }

        StringSplit(std::string id): NodeLibrary::Node(id)
        {

        }

        void InitAttributes() override
        {
            CreateAttribute<std::string>("String", NodeLibrary::Attribute::ValueType::Single,
                                         NodeLibrary::Attribute::Type::Input);
            CreateAttribute<std::string>("Delimiter", NodeLibrary::Attribute::ValueType::Single,
                                         NodeLibrary::Attribute::Type::Input);
            CreateAttribute<std::string>("ResultStrings", NodeLibrary::Attribute::ValueType::Multi,
                                         NodeLibrary::Attribute::Type::Output);
        }

        bool Evaluate(NodeLibrary::NodeEvaluationContext& ctx) override
        {
            std::string str = ctx.GetAttributeValue<std::string>("String");
            std::string delimiter = ctx.GetAttributeValue<std::string>("Delimiter");

            int index = 0;
            std::vector<std::string> substrings;

            std::string substring;
            unsigned int loop = 0;
            for (char c : str)
            {
                if (c == delimiter.at(index))
                {
                    index += 1;
                }
                else
                {
                    index = 0;
                }

                if (index >= delimiter.size())
                {
                    if (!substring.empty())
                    {
                        substrings.push_back(substring);
                    }
                    substring.clear();
                    index = 0;
                }
                else if (loop == (str.size() - 1))
                {
                    substring += c;
                    if (!substring.empty())
                    {
                        substrings.push_back(substring);
                    }
                }
                else
                {
                    substring += c;
                }

                loop += 1;
            }

            unsigned int multiIndex = 0;
            for (const std::string& substr : substrings)
            {
                ctx.SetAttributeIndexValue("ResultStrings", multiIndex, substr);
                multiIndex += 1;
            }

            return true;
        }
    };


    class StringSplitBuilder: public NodeLibrary::DefaultNodeBuilder
    {
        NodeLibrary::Node* CreateNode()
        {
            return new StringSplit("");
        }
    };
}